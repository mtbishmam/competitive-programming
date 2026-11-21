#!/usr/bin/env python3
"""Summarize cf_climbers.py output; writes inspectable CSV and JSON tables."""
import bisect
import collections
import csv
import datetime as dt
import gzip
import json
import math
import pathlib
import statistics as st
import sys


def percentile(xs, q):
    xs = sorted(x for x in xs if x is not None)
    if not xs:
        return None
    pos = (len(xs)-1)*q
    lo = math.floor(pos)
    hi = math.ceil(pos)
    return xs[lo]*(hi-pos)+xs[hi]*(pos-lo) if lo != hi else xs[lo]


def desc(xs):
    xs = [x for x in xs if x is not None]
    return {"n": len(xs), "mean": round(st.mean(xs), 2) if xs else None,
            "min": min(xs) if xs else None, "p25": percentile(xs, .25),
            "median": percentile(xs, .5), "p75": percentile(xs, .75),
            "max": max(xs) if xs else None}


def spearman(xs, ys):
    pairs = [(x,y) for x,y in zip(xs,ys) if x is not None and y is not None]
    if len(pairs)<8:
        return None
    def ranks(values):
        order = sorted(range(len(values)), key=lambda i: values[i])
        result = [0.]*len(values)
        for i,j in enumerate(order):
            result[j] = i+1
        groups = collections.defaultdict(list)
        for i,v in enumerate(values): groups[v].append(i)
        for ids in groups.values():
            for i in ids: result[i] = st.mean(result[j] for j in ids)
        return result
    a,b = ranks([p[0] for p in pairs]), ranks([p[1] for p in pairs])
    ma,mb=st.mean(a),st.mean(b)
    den=math.sqrt(sum((x-ma)**2 for x in a)*sum((y-mb)**2 for y in b))
    return round(sum((x-ma)*(y-mb) for x,y in zip(a,b))/den,3) if den else None


def band(n):
    if n is None: return "unknown"
    if n < 1200: return "<1200"
    if n >= 2400: return "2400+"
    return f"{(n//100)*100}-{(n//100)*100+99}" if n >= 1800 else f"{(n//200)*200}-{(n//200)*200+199}"


def offset_band(x):
    if x is None: return "unrated"
    if x < -300: return "<-300"
    if x < -100: return "-300..-101"
    if x <= 100: return "-100..+100"
    if x <= 200: return "+101..+200"
    if x <= 300: return "+201..+300"
    if x <= 400: return "+301..+400"
    return ">+400"


def rating_at(history, t):
    times = [r["ratingUpdateTimeSeconds"] for r in history]
    i = bisect.bisect_right(times, t)-1
    return history[i]["newRating"] if i>=0 else (history[0]["oldRating"] if history else None)


def get_days_gap(times, start, end):
    days = sorted(set(dt.datetime.fromtimestamp(t,dt.timezone.utc).date() for t in times))
    boundaries = [start] + days + [end]
    return max((boundaries[i+1]-boundaries[i]).days-1 for i in range(len(boundaries)-1))


def main():
    out = pathlib.Path(sys.argv[1])
    with gzip.open(out / "cohorts.json.gz", "rt") as f: data=json.load(f)
    contests = {str(c["id"]): c for c in data["contests"]}
    changes = {str(k):v for k,v in data["rating_changes"].items()}
    calendar = [c for c in data["contests"] if changes.get(str(c["id"]))]
    rated_ranges = {}
    for c in calendar:
        old = [r["oldRating"] for r in changes[str(c["id"])] if r["oldRating"] > 0]
        if old: rated_ranges[c["id"]] = (min(old), max(old))
    summaries=[]; month_rows=[]; solve_rows=[]; contest_rows=[]; progression=[]
    for threshold, users in data["selected"].items():
        for user in users:
            h=user["handle"]; hist=user["history"]
            crossing=user["crossing"]
            end=contests[str(crossing["contestId"])]["startTimeSeconds"]
            start=end-180*86400
            raw=data["submissions"].get(h)
            if raw is None: continue
            # One first accepted submission per problem during the window.
            accepted={}; attempts_by_problem=collections.defaultdict(list)
            for s in raw:
                t=s["creationTimeSeconds"]
                if not start<=t<end: continue
                p=s["problem"]; pid=(p.get("contestId"),p.get("index"),p.get("problemsetName"))
                attempts_by_problem[pid].append(s)
                if s.get("verdict") == "OK":
                    if pid not in accepted or t<accepted[pid]["creationTimeSeconds"]:
                        accepted[pid]=s
            rated=[r for r in hist if str(r["contestId"]) in contests
                   and start<=contests[str(r["contestId"])]["startTimeSeconds"]<end
                   and r["ratingUpdateTimeSeconds"]<crossing["ratingUpdateTimeSeconds"]]
            rated.sort(key=lambda r:r["ratingUpdateTimeSeconds"])
            participated={r["contestId"] for r in rated}
            live_by_contest=collections.defaultdict(set)
            for pid,s in accepted.items():
                c=contests.get(str(s.get("contestId")))
                if c and s.get("author",{}).get("participantType")=="CONTESTANT" and s["contestId"] in participated and c["startTimeSeconds"]<=s["creationTimeSeconds"]<c["startTimeSeconds"]+c["durationSeconds"]:
                    live_by_contest[s["contestId"]].add(pid)
            upsolves=collections.defaultdict(list)
            upsolve_meta={}
            for pid,s in accepted.items():
                cid=s.get("contestId"); c=contests.get(str(cid))
                if cid not in participated or not c or pid in live_by_contest[cid] or s.get("author",{}).get("participantType")=="VIRTUAL": continue
                delay=s["creationTimeSeconds"]-(c["startTimeSeconds"]+c["durationSeconds"])
                if 0<=delay<=14*86400:
                    upsolves[cid].append((pid,delay,s))
                    upsolve_meta[pid]=(delay/3600,any(c["startTimeSeconds"]<=a["creationTimeSeconds"]<c["startTimeSeconds"]+c["durationSeconds"] for a in attempts_by_problem[pid]))
            evaluable=[r for r in rated if contests[str(r["contestId"])]["startTimeSeconds"]+contests[str(r["contestId"])]["durationSeconds"]+14*86400<=end]
            evaluable_ids={r["contestId"] for r in evaluable}
            opportunities=set()
            for c in calendar:
                ct=c["startTimeSeconds"]
                if start<=ct<end and c["id"] in rated_ranges:
                    low,high=rated_ranges[c["id"]]
                    current=rating_at(hist,ct)
                    if current is not None and low<=current<=high:
                        opportunities.add(ct)
            if rated:
                changes_list=[r["newRating"]-r["oldRating"] for r in rated]
                contest_times=[contests[str(r["contestId"])]["startTimeSeconds"] for r in rated if str(r["contestId"]) in contests]
                drawdown=0; peak=hist[0]["oldRating"] if hist else 0
                for r in hist:
                    if r["ratingUpdateTimeSeconds"] > crossing["ratingUpdateTimeSeconds"]: break
                    peak=max(peak,r["newRating"]); drawdown=max(drawdown,peak-r["newRating"])
                gaps=[(b-a)/86400 for a,b in zip(contest_times,contest_times[1:])]
                losses=[i for i,x in enumerate(changes_list) if x<0]
                continued=sum(i+1<len(rated) and rated[i+1]["ratingUpdateTimeSeconds"]-rated[i]["ratingUpdateTimeSeconds"]<=30*86400 for i in losses)
                recovery_days=[]
                for i in losses:
                    loss=rated[i]
                    regained=next((r for r in hist if loss["ratingUpdateTimeSeconds"]<r["ratingUpdateTimeSeconds"]<=crossing["ratingUpdateTimeSeconds"] and r["newRating"]>=loss["oldRating"]),None)
                    if regained:
                        recovery_days.append((regained["ratingUpdateTimeSeconds"]-loss["ratingUpdateTimeSeconds"])/86400)
            else:
                changes_list=[]; drawdown=0; gaps=[]; losses=[]; continued=0; recovery_days=[]
            start_rating=rating_at(hist,start)
            window_peak=start_rating or 0
            window_drawdown=0
            for r in rated:
                window_peak=max(window_peak,r["newRating"])
                window_drawdown=max(window_drawdown,window_peak-r["newRating"])
            unique=list(accepted.values())
            virtual_rounds={(s.get("author",{}).get("contestId"),s.get("author",{}).get("startTimeSeconds")) for s in raw if start<=s["creationTimeSeconds"]<end and s.get("author",{}).get("participantType")=="VIRTUAL"}
            practice=[]; live=[]
            for s in unique:
                pid=(s["problem"].get("contestId"),s["problem"].get("index"),s["problem"].get("problemsetName"))
                typ="live" if pid in live_by_contest.get(s.get("contestId"),set()) else "upsolve" if any(pid==p for p,_,_ in upsolves.get(s.get("contestId"),[])) else "other"
                rating=s["problem"].get("rating")
                current=rating_at(hist,s["creationTimeSeconds"])
                offset=rating-current if rating is not None and current is not None else None
                solve_rows.append({"threshold":threshold,"handle":h,"time":s["creationTimeSeconds"],"contest_id":s.get("contestId"),"index":s["problem"].get("index"),"problem_rating":rating,"user_rating":current,"offset":offset,"offset_band":offset_band(offset),"type":typ,"upsolve_evaluable":typ=="upsolve" and s.get("contestId") in evaluable_ids,"upsolve_delay_hours":upsolve_meta.get(pid,(None,None))[0],"attempted_during_live_contest":upsolve_meta.get(pid,(None,None))[1],"tags":";".join(s["problem"].get("tags",[]))})
                (live if typ=="live" else practice).append(s)
            window_start=dt.datetime.fromtimestamp(start,dt.timezone.utc).date()
            window_end=dt.datetime.fromtimestamp(end,dt.timezone.utc).date()
            activity_times=[s["creationTimeSeconds"] for s in raw if start<=s["creationTimeSeconds"]<end]
            active_days=len({dt.datetime.fromtimestamp(t,dt.timezone.utc).date() for t in activity_times})
            solve_days=len({dt.datetime.fromtimestamp(s["creationTimeSeconds"],dt.timezone.utc).date() for s in unique})
            last3=[s for s in unique if s["creationTimeSeconds"]>=end-90*86400]
            def month_index(t): return min(5,max(0,int((end-1-t)//(30*86400))))
            for m in range(6):
                ss=[s for s in unique if month_index(s["creationTimeSeconds"])==m]
                rr=[r for r in rated if month_index(contests[str(r["contestId"])]["startTimeSeconds"])==m]
                raw_ok=[s for s in raw if s.get("verdict")=="OK" and start<=s["creationTimeSeconds"]<end and month_index(s["creationTimeSeconds"])==m]
                times={s["creationTimeSeconds"] for s in ss}
                month_solves=[x for x in solve_rows if x["handle"]==h and x["threshold"]==threshold and x["time"] in times]
                ratings=[x["problem_rating"] for x in month_solves if x["problem_rating"] is not None]
                offsets=[x["offset"] for x in month_solves if x["offset"] is not None]
                rating_bands=collections.Counter("unrated" if x["problem_rating"] is None else f"{(x['problem_rating']//200)*200}-{(x['problem_rating']//200)*200+199}" for x in month_solves)
                offset_bands=collections.Counter(x["offset_band"] for x in month_solves)
                tags=collections.Counter(tag for x in month_solves for tag in x["tags"].split(";") if tag)
                month_activity=[s["creationTimeSeconds"] for s in raw if start<=s["creationTimeSeconds"]<end and month_index(s["creationTimeSeconds"])==m]
                month_start_date=dt.datetime.fromtimestamp(end-(m+1)*30*86400,dt.timezone.utc).date()
                month_end_date=dt.datetime.fromtimestamp(end-m*30*86400,dt.timezone.utc).date()
                month_rows.append({"threshold":threshold,"handle":h,"month_before":m+1,"rated_contests":len(rr),"accepted_submissions":len(raw_ok),"unique_solves":len(ss),"problems_per_day":len(ss)/30,"problems_per_week":len(ss)*7/30,"live_solves":sum(x["type"]=="live" for x in month_solves),"upsolves":sum(x["type"]=="upsolve" for x in month_solves),"other_solves":sum(x["type"]=="other" for x in month_solves),"virtual_first_solves":sum(s.get("author",{}).get("participantType")=="VIRTUAL" for s in ss),"virtual_rounds":len({(s.get("author",{}).get("contestId"),s.get("author",{}).get("startTimeSeconds")) for s in raw if start<=s["creationTimeSeconds"]<end and month_index(s["creationTimeSeconds"])==m and s.get("author",{}).get("participantType")=="VIRTUAL"}),"active_days":len({dt.datetime.fromtimestamp(t,dt.timezone.utc).date() for t in month_activity}),"solve_days":len({dt.datetime.fromtimestamp(s["creationTimeSeconds"],dt.timezone.utc).date() for s in ss}),"longest_inactive_gap_days":get_days_gap(month_activity,month_start_date,month_end_date),"avg_problem_rating":st.mean(ratings) if ratings else None,"median_problem_rating":percentile(ratings,.5),"max_problem_rating":max(ratings) if ratings else None,"p75_problem_rating":percentile(ratings,.75),"p90_problem_rating":percentile(ratings,.9),"mean_offset":st.mean(offsets) if offsets else None,"median_offset":percentile(offsets,.5),"p75_offset":percentile(offsets,.75),"p90_offset":percentile(offsets,.9),"rating_band_counts_json":dict(rating_bands),"rating_band_shares_json":{k:v/len(ss) for k,v in rating_bands.items()} if ss else {},"offset_band_counts_json":dict(offset_bands),"offset_band_shares_json":{k:v/len(ss) for k,v in offset_bands.items()} if ss else {},"topic_counts_json":dict(tags)})
            monthly=[x for x in month_rows if x["handle"]==h and x["threshold"]==threshold]
            for r in rated:
                n=len(changes.get(str(r["contestId"])) or [])
                c=contests.get(str(r["contestId"]),{})
                contest_rows.append({"threshold":threshold,"handle":h,"contest_id":r["contestId"],"date":dt.datetime.fromtimestamp(c.get("startTimeSeconds",r["ratingUpdateTimeSeconds"]),dt.timezone.utc).date().isoformat(),"name":r["contestName"],"old_rating":r["oldRating"],"new_rating":r["newRating"],"change":r["newRating"]-r["oldRating"],"rank":r["rank"],"rated_participants":n,"rank_percentile":round(100*(1-r["rank"]/n),2) if n else None,"upsolves_14d":len(upsolves[r["contestId"]])})
            def first_reach(level):
                return next((r["ratingUpdateTimeSeconds"] for r in hist if r["newRating"]>=level),None)
            milestone={str(level):first_reach(level) for level in (1400,1600,1800,1900,2100,2200,2400)}
            progression.append({"threshold":threshold,"handle":h,**{f"reach_{k}":v for k,v in milestone.items()}})
            summaries.append({"threshold":threshold,"handle":h,"crossing_date":dt.datetime.fromtimestamp(end,dt.timezone.utc).date().isoformat(),"start_rating":start_rating,"start_band":band(start_rating),"contests_6m":len(rated),"contests_3m":sum(1 for r in rated if contests[str(r["contestId"])]["startTimeSeconds"]>=end-90*86400),"contest_month_mean":len(rated)/6,"contest_month_median":percentile([x["rated_contests"] for x in monthly],.5),"estimated_suitable_opportunities_6m":len(opportunities),"estimated_participation_share":len(rated)/len(opportunities) if opportunities else None,"virtual_rounds_6m":len(virtual_rounds),"unique_solves_6m":len(unique),"unique_solves_3m":len(last3),"solves_month_mean":len(unique)/6,"active_days_6m":active_days,"solve_days_6m":solve_days,"longest_inactive_gap_days":get_days_gap(activity_times,window_start,window_end),"live_solves_6m":len(live),"other_solves_6m":len(practice),"upsolves_14d":sum(len(upsolves[r["contestId"]]) for r in evaluable),"evaluable_contests_for_upsolve":len(evaluable),"contests_upsolved_14d":sum(bool(upsolves[r["contestId"]]) for r in evaluable),"upsolve_contest_share":sum(bool(upsolves[r["contestId"]]) for r in evaluable)/len(evaluable) if evaluable else None,"positive_contest_share":sum(x>0 for x in changes_list)/len(changes_list) if changes_list else None,"loss_events_6m":len(losses),"recovered_losses_by_promotion":len(recovery_days),"median_recovery_days":percentile(recovery_days,.5),"continue_after_loss_30d":continued/len(losses) if losses else None,"last5_change_sd":st.pstdev(changes_list[-5:]) if len(changes_list)>=5 else None,"mean_rating_change":st.mean(changes_list) if changes_list else None,"avg_days_between_contests":st.mean(gaps) if gaps else None,"max_drawdown_6m":window_drawdown,"max_lifetime_drawdown":drawdown,"rating_gain_6m":crossing["newRating"]-start_rating if start_rating is not None else None,"reach_milestones":milestone})
    def write_csv(path,rows):
        if not rows:return
        with open(out/path,"w",newline="") as f:
            writer=csv.DictWriter(f,fieldnames=rows[0].keys(),extrasaction="ignore")
            writer.writeheader()
            writer.writerows({k:(json.dumps(v) if isinstance(v,dict) else v) for k,v in row.items()} for row in rows)
    write_csv("participants.csv",summaries)
    write_csv("participant_months.csv",month_rows)
    write_csv("unique_solves.csv",solve_rows)
    write_csv("rated_contests.csv",contest_rows)
    write_csv("progression.csv",progression)
    aggregate={}
    for threshold in ("1900","2100","2400"):
        rows=[x for x in summaries if x["threshold"]==threshold]
        solves=[x for x in solve_rows if x["threshold"]==threshold]
        contests_r=[x for x in contest_rows if x["threshold"]==threshold]
        aggregate[threshold] = {
            "n": len(rows),
            "dates": [min((x["crossing_date"] for x in rows), default=None),
                      max((x["crossing_date"] for x in rows), default=None)],
            "start_bands": dict(collections.Counter(x["start_band"] for x in rows)),
            "contests_month": desc([x["contest_month_mean"] for x in rows]),
            "monthly_contest_counts": dict(sorted(collections.Counter(x["rated_contests"] for x in month_rows if x["threshold"] == threshold).items())),
            "estimated_suitable_opportunities_6m": desc([x["estimated_suitable_opportunities_6m"] for x in rows]),
            "estimated_participation_share": desc([x["estimated_participation_share"] for x in rows]),
            "solves_month": desc([x["solves_month_mean"] for x in rows]),
            "monthly_solve_counts": desc([x["unique_solves"] for x in month_rows if x["threshold"] == threshold]),
            "active_days_month": desc([x["active_days"] for x in month_rows if x["threshold"] == threshold]),
            "upsolve_contest_share": desc([x["upsolve_contest_share"] for x in rows]),
            "upsolves_per_contest": desc([x["upsolves_14d"] / x["evaluable_contests_for_upsolve"] if x["evaluable_contests_for_upsolve"] else None for x in rows]),
            "offset_bands": dict(collections.Counter(x["offset_band"] for x in solves)),
            "offset": desc([x["offset"] for x in solves]),
            "problem_rating": desc([x["problem_rating"] for x in solves]),
            "solve_types": dict(collections.Counter(x["type"] for x in solves)),
            "topics": collections.Counter(t for x in solves for t in x["tags"].split(";") if t).most_common(20),
            "rating_changes": desc([x["change"] for x in contests_r]),
            "rank_percentile": desc([x["rank_percentile"] for x in contests_r]),
            "correlations": {k: spearman([x[k] for x in rows], [x["rating_gain_6m"] for x in rows]) for k in
                             ("contests_6m", "unique_solves_6m", "active_days_6m", "longest_inactive_gap_days", "upsolve_contest_share")},
            "claims": {
                "at_least_5_contests_month_last3": sum(x["contests_3m"] >= 15 for x in rows),
                "at_least_50_solves_month_6m": sum(x["solves_month_mean"] >= 50 for x in rows),
                "at_least_100_solves_month_6m": sum(x["solves_month_mean"] >= 100 for x in rows),
                "upsolved_half_contests": sum(x["upsolve_contest_share"] is not None and x["upsolve_contest_share"] >= .5 for x in rows),
            },
        }
    with open(out/"summary.json","w") as f:json.dump(aggregate,f,indent=2)
    print(json.dumps(aggregate,indent=2))

if __name__=="__main__":main()
