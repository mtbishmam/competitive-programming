#define \
PROG : preface
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

const char letters[] = "IVXLCDM";

int cnt[20];

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int N; cin >> N;
	for(int i = 1; i <= N; i++) {
		int v = i;
		for(int j = 0; v; j++, v /= 10) {
			int d = v % 10;
			cnt[2 * j] += ((d % 5 == 4) ? 1 : d % 5);
			if(d >= 4 && d <= 8) cnt[2 * j + 1] ++;
			if(d == 9) cnt[2 * j + 2] ++;
		}
	}

	for(int i = 0; i < 7; i++) {
		if(cnt[i]) {
			cout << letters[i] << ' ' << cnt[i] << '\n';
		}
	}

	return 0;
}
