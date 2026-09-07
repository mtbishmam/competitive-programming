#define \
PROG : barn1
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

	int M, S, C;
	cin >> M >> S >> C;

	if(M >= C) {
		cout << C << '\n';
		return 0;
	}

	vector<int> V;

	for(int i = 0; i < C; i++) {
		int v; cin >> v;
		V.push_back(v);
	}
	
	sort(V.begin(), V.end());

	int res = V.back() - V.front() + 1;

	for(int i = 0; i + 1 < C; i++) {
		V[i] = V[i + 1] - V[i] - 1;
	}

	V.pop_back();

	sort(V.begin(), V.end());

	for(int i = 0; i < M - 1; i++) {
		res -= V.back();
		V.pop_back();
	}

	cout << res << '\n';
	return 0;
}
