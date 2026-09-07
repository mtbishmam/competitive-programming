#define \
PROG : gift1
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

string names[100];
map<string, int> mp;

int m[100];

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int n; cin >> n;
	for(int i = 0; i < n; i++) cin >> names[i], mp[names[i]] = i;

	for(int i = 0; i < n; i++) {
		string s;
		cin >> s; int g = mp[s];
		int v, p; cin >> v >> p;
		if(p == 0) continue;
		m[g] -= v;
		m[g] += v % p;
		for(int j = 0; j < p; j++) {
			cin >> s; int r = mp[s];
			m[r] += v / p;
		}
	}
	cerr << "hi\n";

	for(int i = 0; i < n; i++) {
		cout << names[i] << ' ' << m[i] << '\n';
	}

	return 0;
}
