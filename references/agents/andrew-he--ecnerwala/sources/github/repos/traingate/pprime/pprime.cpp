#define \
PROG : pprime
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

bool isPrime(int a) {
	//assert(a >= 5);
	if(a % 2 == 0) return false;
	for(int i = 3; i * i <= a; i += 2) {
		if(a % i == 0) return false;
	}
	return true;
}

int epal(int v) {
	int r = v;
	for(int i = v; i; i /= 10) {
		r *= 10, r += i % 10;
	}
	return r;
}

int opal(int v) {
	int r = v;
	for(int i = v / 10; i; i /= 10) {
		r *= 10, r += i % 10;
	}
	return r;
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int a, b;
	cin >> a >> b;
	vector<int> res;

	for(int i = 1; true; i++) {
		int v = opal(i);
		if(v > b) break;
		if(a <= v && isPrime(v)) res.push_back(v);

		v = epal(i);
		if(a <= v && v <= b && isPrime(v)) res.push_back(v);
	}

	sort(res.begin(), res.end());
	for(int i : res) cout << i << '\n';

	return 0;
}
