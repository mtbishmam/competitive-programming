#define \
PROG : prefix
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

vector<string> P;
int L;
char S[300000];
bool vis[300000];
int res = 0;

void dfs(int pos = 0) {
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	while(true) {
		string p; cin >> p;
		if(p == ".") break;
		P.push_back(p);
	}

	while(cin) {
		cin >> (S + L);
		L += strlen(S + L);
	}

	assert(L <= 300000);

	vis[0] = true;
	for(int pos = 0; pos <= L; pos++) {
		if(vis[pos]) {
			res = max(res, pos);
			for(string p : P) {
				if(pos + p.size() > L) continue;
				bool good = true;
				for(int i = 0; i < int(p.size()); i++) {
					if(p[i] != S[pos + i]) {
						good = false;
						break;
					}
				}
				if(good) vis[pos + p.size()] = true;
			}
		}
	}

	cout << res << '\n';

	return 0;
}
