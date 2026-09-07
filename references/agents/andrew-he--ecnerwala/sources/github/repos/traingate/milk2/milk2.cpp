#define \
PROG : milk2
#define \
LANG : C++11
#define \
ID : hdrplpx1

#include<bits/stdc++.h>
using namespace std;

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

const string PRG = string(STR(PROG)).substr(2);

const string INFILE = PRG + ".in";
const string OUTFILE = PRG + ".out";

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int N; cin >> N;
	vector<pair<int, int>> evt;
	for(int i = 0; i < N; i++) {
		int l, r; cin >> l >> r;
		evt.push_back(make_pair(l, -2)); // insert should come first
		evt.push_back(make_pair(r, -1));
	}

	sort(evt.begin(), evt.end());

	int prv = evt[0].first;
	int cnt = 0;

	int maxHas = 0;
	int maxNot = 0;

	for(int i = 0; i < 2 * N; i++) {
		int t = evt[i].first;
		int v = evt[i].second;
		if(v == -2) {
			if(cnt == 0) {
				maxNot = max(maxNot, t - prv);
				prv = t;
			}
			cnt ++;
		} else {
			if(cnt == 1) {
				maxHas = max(maxHas, t - prv);
				prv = t;
			}
			cnt--;
		}
	}

	cout << maxHas << ' ' << maxNot << '\n';

	return 0;
}
