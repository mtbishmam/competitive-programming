#define \
PROG : subset
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

long long dp[50][10000];
int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int N; cin >> N;

	dp[0][0] = 1;
	for(int i = 1; i <= N; i++) {
		for(int v = 0; v <= N * N; v++) {
			if(dp[i - 1][v]) {
				dp[i][v + i] += dp[i - 1][v]; 
				dp[i][abs(v - i)] += dp[i - 1][v]; 
			}
		}
	}

	cout << dp[N][0] / 2 << '\n';

	return 0;
}
