#define \
PROG : frac1
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

void dfs(int a, int b, int c, int d) {
	if(b + d <= N) {
		dfs(a, b, a + c, b + d);
		cout << a + c << '/' << b + d << '\n';
		dfs(a + c, b + d, c, d);
	}
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> N;
	cout << "0/1" << '\n';
	dfs(0, 1, 1, 1);
	cout << "1/1" << '\n';

	return 0;
}
