import csv
import sys
from datetime import datetime, UTC

import requests

# Defaults
DEFAULT_HANDLE = "mtbishmam"
DEFAULT_RATING = 1600

# Parse command-line arguments
handle = sys.argv[1] if len(sys.argv) > 1 else DEFAULT_HANDLE
rating = int(sys.argv[2]) if len(sys.argv) > 2 else DEFAULT_RATING

url = f"https://codeforces.com/api/user.status?handle={handle}"

response = requests.get(url)
response.raise_for_status()
data = response.json()

if data["status"] != "OK":
    raise Exception(data["comment"])

solved = {}

for submission in data["result"]:
    if submission.get("verdict") != "OK":
        continue

    problem = submission["problem"]

    if problem.get("rating") != rating:
        continue

    contest_id = problem["contestId"]
    index = problem["index"]
    key = (contest_id, index)

    solved_time = datetime.fromtimestamp(
        submission["creationTimeSeconds"], UTC
    ).strftime("%Y-%m-%d")

    solved[key] = {
        "Contest ID": contest_id,
        "Index": index,
        "Name": problem["name"],
        "Rating": problem["rating"],
        "Tags": ", ".join(problem.get("tags", [])),
        "Date Solved": solved_time,
        "URL": f"https://codeforces.com/problemset/problem/{contest_id}/{index}",
    }

rows = sorted(solved.values(), key=lambda x: (x["Contest ID"], x["Index"]))

output_file = f"{handle}_{rating}_solves.csv"

with open(output_file, "w", newline="", encoding="utf-8") as f:
    writer = csv.DictWriter(
        f,
        fieldnames=[
            "Contest ID",
            "Index",
            "Name",
            "Rating",
            "Tags",
            "Date Solved",
            "URL",
        ],
    )
    writer.writeheader()
    writer.writerows(rows)

print(f"Saved {len(rows)} problems to {output_file}")
