#define \
PROG : zerosum
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

void recurse(int dig = 2, int cur = 1, int sign = 1, int sum = 0, string s = "1") {
	if(dig > N) {
		sum += cur * sign;
		if(sum == 0) {
			cout << s << '\n';
		}
		return;
	}
	recurse(dig + 1, cur * 10 + dig, sign, sum, s + " " + char(dig + '0'));
	sum += cur * sign;
	recurse(dig + 1, dig, 1, sum, s + "+" + char(dig + '0'));
	recurse(dig + 1, dig, -1, sum, s + "-" + char(dig + '0'));
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> N;
	recurse();

	return 0;
}
