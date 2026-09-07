#define \
PROG : money
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

int N, V;
long long dp[200000];
int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> V >> N;
	dp[0] = 1;
	for(int i = 0; i < V; i++) {
		int v; cin >> v;
		for(int j = v; j <= N; j++) {
			dp[j] += dp[j - v];
		}
	}

	cout << dp[N] << '\n';

	return 0;
}
