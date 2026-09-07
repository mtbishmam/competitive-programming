#define \
PROG : ride
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

int val(string a) {
	int v = 1;
	for(char c : a) v *= c - 'A' + 1, v %= 47;
	return v;
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	string a, b; cin >> a >> b;

	cout << ((val(a) == val(b)) ? "GO" : "STAY") << '\n';

	return 0;
}
