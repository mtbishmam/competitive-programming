#define \
PROG : namenum
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

char val(char c) {
	if(c == 'Q' || c == 'Z') return '\0';
	if(c > 'Q') c --;
	return '2' + (c - 'A') / 3;
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	string v; cin >> v;
	int N = v.size();
	ifstream dict("dict.txt");
	bool found = false;
	while(dict) {
		string d; dict >> d;
		bool good = d.size() == N;
		for(int i = 0; good && i < N; i++) {
			if(val(d[i]) != v[i]) good = false;
		}
		if(good) {
			found = true;
			cout << d << '\n';
		}
	}
	if(!found) cout << "NONE\n";

	return 0;
}
