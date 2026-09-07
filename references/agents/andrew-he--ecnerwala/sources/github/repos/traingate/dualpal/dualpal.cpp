#define \
PROG : dualpal
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

bool isPal(int v, int b) {
	long long t = 0;
	for(int i = v; i; i /= b) {
		t *= b, t += i % b;
	}
	return t == v;
}

bool isDualPal(int v) {
	bool found = false;
	for(int i = 2; i <= 10; i++) {
		if(isPal(v, i)) {
			if(found) return true;
			found = true;
		}
	}
	return false;
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int N, S; cin >> N >> S;
	S++;
	while(N) {
		if(isDualPal(S)) cout << S << '\n', N--;
		S++;
	}

	return 0;
}
