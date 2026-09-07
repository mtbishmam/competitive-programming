#define \
PROG : sort3
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

int N;
int A[2000];
int B[2000];
int c[4][4];

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> N;
	for(int i = 0; i < N; i++) cin >> A[i], A[i] --, B[i] = A[i];
	sort(B, B + N);

	for(int i = 0; i < N; i++) {
		c[A[i]][B[i]] ++;
	}

	int res = 0;
	for(int i = 0; i < 3; i++) {
		for(int j = i + 1; j < 3; j++) {
			int v = min(c[i][j], c[j][i]);
			res += v;
			c[i][j] -= v;
			c[j][i] -= v;
			c[i][i] += v;
			c[j][j] += v;
		}
	}

	res += 2 * (c[0][1] + c[1][0]);
	cout << res << '\n';

	return 0;
}
