#define \
PROG : beads
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
int B[1000];

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> N;
	string s; cin >> s;
	for(int i = 0; i < N; i++) {
		B[i] = (s[i] == 'w') ? -1 : (s[i] == 'b');
	}

	int res = 0;
	for(int cl = 0; cl < 2; cl++) {
		for(int cr = 0; cr < 2; cr++) {
			for(int i = 0; i < N; i++) {
				int val = 0;
				for(int j = i; true; j = (j ? j : N) - 1) {
					if(B[j] != !cl) {
						val++;
						if(val >= N) {
							cout << N << '\n';
							return 0;
						}
					} else {
						break;
					}
				}
				for(int j = i + 1; true; j ++, j %= N) {
					if(B[j] != !cr) {
						val++;
						if(val >= N) {
							cout << N << '\n';
							return 0;
						}
					} else {
						break;
					}
				}
				if(val > res) res = val;
			}
		}
	}

	cout << res << '\n';

	return 0;
}
