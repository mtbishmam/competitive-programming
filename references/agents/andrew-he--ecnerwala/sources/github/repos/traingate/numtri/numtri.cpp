#define \
PROG : numtri
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

int R;
int V[1020][1020];

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> R;
	for(int i = 0; i < R; i++) {
		for(int j = 0; j <= i; j++) {
			cin >> V[i][j];
		}
	}

	for(int i = R - 2; i >= 0; i--) {
		for(int j = 0; j <= i; j++) {
			V[i][j] += max(V[i + 1][j], V[i + 1][j + 1]);
		}
	}

	cout << V[0][0] << '\n';
	return 0;
}
