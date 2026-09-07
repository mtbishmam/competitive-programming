#define \
PROG : milk3
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

const int N = 3;
int A[5];
int cur[5];
bool reached[30][30][30];

bool ans[30];

void dfs() {
	if(reached[cur[0]][cur[1]][cur[2]]) return;
	reached[cur[0]][cur[1]][cur[2]] = true;
	if(cur[0] == 0) ans[cur[2]] = true;
	for(int s = 0; s < N; s++) {
		for(int t = 0; t < N; t++) {
			if(s == t) continue;
			int v = min(cur[s], A[t] - cur[t]);
			if(!v) continue;
			cur[s] -= v;
			cur[t] += v;
			dfs();
			cur[s] += v;
			cur[t] -= v;
		}
	}
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> A[0] >> A[1] >> A[2];
	cur[0] = 0;
	cur[1] = 0;
	cur[2] = A[2];
	
	dfs();

	for(int i = 0; i < A[2]; i++) {
		if(ans[i]) {
			cout << i << ' ';
		}
	}

	cout << A[2] << '\n';
	return 0;
}
