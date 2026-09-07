#define \
PROG : hamming
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

int N, B, D;

int dig[500];

int ans[100];

bool dfs(int i = 0, int v = 0) {
	if(i == N) return true;
	if(v == (1 << B)) return false;
	bool good = true;
	for(int j = 0; j < i; j++) {
		if(dig[ans[j] ^ v] < D) {
			good = false;
			break;
		}
	}
	if(good) {
		ans[i] = v;
		if(dfs(i + 1, v + 1)) return true;
	}
	if(dfs(i, v + 1)) return true;
	return false;
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	for(int i = 1; i < 500; i++) {
		dig[i] = dig[i / 2] + i % 2;
	}

	cin >> N >> B >> D;

	dfs();
	for(int i = 0; i < N; i++) {
		cout << ans[i] << ((i % 10 == 9 || i + 1 == N) ? '\n' : ' ');
	}

	return 0;
}
