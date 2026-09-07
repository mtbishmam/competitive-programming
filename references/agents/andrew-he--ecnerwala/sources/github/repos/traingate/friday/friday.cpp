#define \
PROG : friday
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

int cnt[20];

int getLen(int m, int y) {
	switch(m) {
		case 9:
		case 4:
		case 6:
		case 11:
			return 30;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 2:
			if(y % 400 == 0) return 29;
			if(y % 100 == 0) return 28;
			if(y % 4 == 0) return 29;
			return 28;
	}
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int n; cin >> n;
	n += 1900; // year we should stop

	int d = 1;
	int m = 1;
	int y = 1900;

	int w = 2; // monday is day 2

	while(y < n) {
		if(d == 13) {
			cnt[w] ++;
		}

		d++;
		if(d > getLen(m, y)) {
			d = 1;
			m++;
			if(m > 12) m = 1, y++;
		}
		w ++;
		w %= 7;
	}

	cout << cnt[0];
	for(int i = 1; i < 7; i++) cout << ' ' << cnt[i];
	cout << '\n';

	return 0;
}
