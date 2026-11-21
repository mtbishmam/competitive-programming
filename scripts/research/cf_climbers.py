#!/usr/bin/env python3
"""Collect reproducible first-time Codeforces rank-promotion cohorts.

Usage: python3 scripts/research/cf_climbers.py OUT_DIR [--months 18] [--limit 50]
Only the public official Codeforces API is used. Responses are cached as gzip JSON.
"""
import argparse
import concurrent.futures
import datetime as dt
import gzip
import json
import pathlib
import random
import threading
import time
import urllib.error
import urllib.parse
import urllib.request

API = "https://codeforces.com/api/"
THRESHOLDS = (1900, 2100, 2400)
# These 14 contests returned no rating-change result during the 2026-10-11 scan.
UNRATED_IDS = {2251, 2215, 2216, 2214, 2206, 2199, 2198, 2177, 2181,
               2172, 2168, 2141, 2142, 2105}
lock = threading.Lock()
next_request = 0.0


def api(cache, method, **params):
    global next_request
    key = method + "__" + "__".join(f"{k}={v}" for k, v in sorted(params.items()))
    path = cache / (urllib.parse.quote(key, safe="=__-") + ".json.gz")
    if path.exists():
        with gzip.open(path, "rt") as f:
            return json.load(f)
    url = API + method + "?" + urllib.parse.urlencode(params)
    for attempt in range(7):
        with lock:
            delay = max(0, next_request - time.monotonic())
            next_request = max(next_request, time.monotonic()) + 0.34
        if delay:
            time.sleep(delay)
        try:
            req = urllib.request.Request(url, headers={"User-Agent": "cf-cohort-study/1.0"})
            with urllib.request.urlopen(req, timeout=45) as response:
                payload = json.load(response)
            if payload.get("status") != "OK":
                raise RuntimeError(payload.get("comment", "API failed"))
            result = payload["result"]
            with gzip.open(path, "wt") as f:
                json.dump(result, f, separators=(",", ":"))
            return result
        except (urllib.error.URLError, TimeoutError, json.JSONDecodeError, RuntimeError) as exc:
            if attempt == 6:
                raise RuntimeError(f"{method} {params}: {exc}") from exc
            time.sleep(min(30, 2 ** attempt + random.random()))


def date(s):
    return dt.datetime.fromtimestamp(s, dt.timezone.utc).strftime("%Y-%m-%d")


def fetch_status(cache, handle, cutoff):
    found = []
    offset = 1
    while True:
        page = api(cache, "user.status", handle=handle, **{"from": offset, "count": 1000})
        found.extend(x for x in page if x["creationTimeSeconds"] >= cutoff)
        if len(page) < 1000 or page[-1]["creationTimeSeconds"] < cutoff:
            break
        offset += 1000
    return found


def main():
    p = argparse.ArgumentParser()
    p.add_argument("out", type=pathlib.Path)
    p.add_argument("--months", type=int, default=18)
    p.add_argument("--limit", type=int, default=50)
    p.add_argument("--through", default=dt.datetime.now(dt.timezone.utc).date().isoformat())
    p.add_argument("--min-prior-contests", type=int, default=30)
    p.add_argument("--min-history-days", type=int, default=365)
    a = p.parse_args()
    out = a.out
    cache = out / "api-cache"
    cache.mkdir(parents=True, exist_ok=True)
    through = dt.date.fromisoformat(a.through)
    start = through - dt.timedelta(days=round(a.months * 365.25 / 12))
    start_ts = int(dt.datetime.combine(start, dt.time(), dt.timezone.utc).timestamp())
    end_ts = int(dt.datetime.combine(through + dt.timedelta(days=1), dt.time(), dt.timezone.utc).timestamp())
    contests = [c for c in api(cache, "contest.list", gym="false")
                if c.get("phase") == "FINISHED" and start_ts <= c.get("startTimeSeconds", 0) < end_ts]
    contests.sort(key=lambda c: c["startTimeSeconds"], reverse=True)
    print(f"Finished contests in window: {len(contests)}", flush=True)
    changes = {}
    def get_changes(c):
        if c["id"] in UNRATED_IDS:
            return c["id"], None, "no rating changes in initial scan"
        try:
            return c["id"], api(cache, "contest.ratingChanges", contestId=c["id"]), None
        except Exception as e:
            return c["id"], None, str(e)
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        for i, (cid, result, error) in enumerate(pool.map(get_changes, contests), 1):
            changes[cid] = result
            if i % 20 == 0:
                print(f"Rating-change contests: {i}/{len(contests)}", flush=True)
    events = {t: [] for t in THRESHOLDS}
    for c in contests:
        for row in changes[c["id"]] or []:
            for t in THRESHOLDS:
                if row["oldRating"] < t <= row["newRating"]:
                    events[t].append(row)
    for t in THRESHOLDS:
        events[t].sort(key=lambda r: r["ratingUpdateTimeSeconds"], reverse=True)
        print(f"Candidate crossings {t}: {len(events[t])}", flush=True)
    histories = {}
    selected = {t: [] for t in THRESHOLDS}
    exclusions = {t: {"prior_crossing": 0, "low_activity": 0, "short_history": 0, "api_error": 0} for t in THRESHOLDS}
    # Shared histories make selection inexpensive when the same user crosses multiple ranks.
    for t in THRESHOLDS:
        for e in events[t]:
            if len(selected[t]) >= a.limit:
                break
            h = e["handle"]
            if h not in histories:
                try:
                    histories[h] = api(cache, "user.rating", handle=h)
                except Exception:
                    exclusions[t]["api_error"] += 1
                    continue
            hist = sorted(histories[h], key=lambda x: x["ratingUpdateTimeSeconds"])
            crossing = next((r for r in hist if r["oldRating"] < t <= r["newRating"]), None)
            if not crossing or crossing["contestId"] != e["contestId"]:
                exclusions[t]["prior_crossing"] += 1
                continue
            earlier = [r for r in hist if r["ratingUpdateTimeSeconds"] < e["ratingUpdateTimeSeconds"]]
            if len(earlier) < a.min_prior_contests or earlier[0]["ratingUpdateTimeSeconds"] > e["ratingUpdateTimeSeconds"] - a.min_history_days*86400:
                exclusions[t]["short_history"] += 1
                continue
            before = [r for r in hist if e["ratingUpdateTimeSeconds"] - 90*86400 <= r["ratingUpdateTimeSeconds"] < e["ratingUpdateTimeSeconds"]]
            if len(before) < 2:
                exclusions[t]["low_activity"] += 1
                continue
            selected[t].append({"handle": h, "crossing": crossing, "history": hist})
        print(f"Verified first-time {t}: {len(selected[t])}; exclusions {exclusions[t]}", flush=True)
    unique = {u["handle"]: u for rows in selected.values() for u in rows}
    # Pull only six months preceding each selected crossing, plus one day after for boundary safety.
    cutoffs = {h: min(u["crossing"]["ratingUpdateTimeSeconds"] for rows in selected.values()
                       for u in rows if u["handle"] == h) - 184*86400 for h in unique}
    submissions = {}
    def get_user(item):
        h, cutoff = item
        try:
            return h, fetch_status(cache, h, cutoff), None
        except Exception as e:
            return h, None, str(e)
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        for i, (h, rows, error) in enumerate(pool.map(get_user, cutoffs.items()), 1):
            submissions[h] = rows
            if error:
                print(f"Submission error {h}: {error}", flush=True)
            if i % 20 == 0:
                print(f"Submission histories: {i}/{len(unique)}", flush=True)
    own = api(cache, "user.rating", handle="mtbishmam")
    own_subs = fetch_status(cache, "mtbishmam", end_ts - 184*86400)
    output = {
        "source": API, "through": str(through), "start": str(start), "thresholds": THRESHOLDS,
        "min_prior_contests": a.min_prior_contests, "min_history_days": a.min_history_days,
        "contests": contests, "rating_changes": changes, "events": events,
        "selected": selected, "exclusions": exclusions, "submissions": submissions,
        "own": {"handle": "mtbishmam", "history": own, "submissions": own_subs},
    }
    path = out / "cohorts.json.gz"
    with gzip.open(path, "wt") as f:
        json.dump(output, f, separators=(",", ":"))
    print(f"Saved {path}", flush=True)


if __name__ == "__main__":
    main()
