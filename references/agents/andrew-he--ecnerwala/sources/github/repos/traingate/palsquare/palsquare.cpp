#define \
PROG : palsquare
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

int rev(int v, int b) {
	int t = 0;
	for(int i = v; i; i /= b) {
		t *= b, t += i % b;
	}
	return t;
}

bool isPal(int v, int b) {
	return rev(v, b) == v;
}

void print(int v, int b) {
	for(int i = rev(v, b), j = v; j; i /= b, j /= b) {
		int a = i % b;
		if(a >= 10) cout << char('A' + a - 10);
		else cout << a;
	}
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int b;
	cin >> b;
	for(int i = 1; i <= 300; i++) {
		int v = i * i;
		if(isPal(v, b)) {
			cerr << i << '\n';
			print(i, b);
			cout << ' ';
			print(v, b);
			cout << '\n';
		}
	}

	return 0;
}
