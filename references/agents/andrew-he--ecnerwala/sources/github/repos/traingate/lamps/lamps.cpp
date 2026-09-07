#define \
PROG : lamps
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
int C;
vector<int> on;
vector<int> off;

const int S = (1 << 6) - 1;
const int T[] = {(1 << 6) - 1, 1 + 4 + 16, 2 + 8 + 32, 1 + 8};

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> N;
	cin >> C;
	while(true) {
		int v; cin >> v; v--;
		if(v < 0) break;
		on.push_back(v);
	}
	while(true) {
		int v; cin >> v; v--;
		if(v < 0) break;
		off.push_back(v);
	}

	vector<string> res;

	for(int m = 0; m < 16; m++) {
		int v = S;
		int num = 0;
		for(int i = 0; i < 4; i++) {
			if(m & (1 << i)) v ^= T[i], num++;
		}
		if(num > C) continue;
		if((C - num) % 2 != 0) continue;

		bool good = true;
		for(int i : on) {
			if(!(v & (1 << (i % 6)))) {
				good = false;
				break;
			}
		}
		if(!good) continue;
		for(int i : off) {
			if(v & (1 << (i % 6))) {
				good = false;
				break;
			}
		}

		if(!good) continue;
		string s;
		for(int i = 0; i < N; i++) {
			s.push_back((v & (1 << (i % 6))) ? '1' : '0');
		}
		res.push_back(s);
	}

	sort(res.begin(), res.end());
	for(string s : res) cout << s << '\n';
	if(res.empty()) cout << "IMPOSSIBLE\n";

	return 0;
}
