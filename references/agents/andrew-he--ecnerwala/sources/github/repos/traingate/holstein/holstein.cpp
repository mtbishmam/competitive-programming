#define \
PROG : holstein
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

	int V; cin >> V;
	int R[V];
	for(int i = 0; i < V; i++) cin >> R[i];

	int G; cin >> G;
	int F[G][V];
	for(int i = 0; i < G; i++) {
		for(int j = 0; j < V; j++) {
			cin >> F[i][j];
		}
	}

	for(int s = 1; s <= G; s++) {
		for(int m = (1 << G) - 1; m > 0; m--) {
			int dsum = 0;
			for(int i = m; i; i &= i - 1) dsum++;
			if(dsum != s) continue;

			bool good = true;
			for(int i = 0; i < V; i++) {
				int n = R[i];
				for(int j = 0; j < G; j++) {
					if(m & (1 << (G - j - 1))) {
						n -= F[j][i];
					}
				}
				if(n > 0) {
					good = false; break;
				}
			}
			if(good) {
				cout << s;
				for(int j = 0; j < G; j++) {
					if(m & (1 << (G - j - 1))) {
						cout << ' ' << j+1;
					}
				}
				cout << '\n';
				return 0;
			}
		}
	}

	return 0;
}
