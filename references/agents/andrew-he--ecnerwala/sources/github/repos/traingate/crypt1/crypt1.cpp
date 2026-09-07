#define \
PROG : crypt1
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

bool has[20];

int check(int v) {
	int r = 0;
	for(int i = v; i; i /= 10) {
		if(!has[i % 10]) return -1;
		r++;
	}
	return r;
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int N;cin >> N;
	for(int i = 0; i < N; i++) {
		int v; cin >> v;
		has[v] = true;
	}

	int res = 0;
	for(int i = 100; i <= 999; i++) {
		for(int j = 1; j <= 9; j++) {
			for(int k = 1; k <= 9; k++) {
				if(check(i) == 3 && check(i * j) == 3 && check(i * k) == 3 && check(j * 10 + k) == 2 && check(i * (j * 10 + k)) == 4) {
					res++;
				}
			}
		}
	}
	cout << res << '\n';

	return 0;
}
