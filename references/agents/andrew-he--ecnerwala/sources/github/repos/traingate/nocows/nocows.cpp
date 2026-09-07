#define \
PROG : nocows
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

int N, K;
int dp[500][500]; // number of trees with i nodes and depth <= j

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> N >> K;

	dp[1][1] = 1;
	for(int d = 2; d <= K; d++) {
		dp[1][d] = 1;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; i + j + 1 <= N; j++) {
				dp[i + j + 1][d] += dp[i][d - 1] * dp[j][d - 1];
				dp[i + j + 1][d] %= 9901;
			}
		}
	}

	cout << (dp[N][K] - dp[N][K - 1] + 9901) % 9901 << '\n';

	return 0;
}
