#define \
PROG : sprime
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
	if(a <= 1) return false;
	if(a % 2 == 0) return a == 2;
	for(int i = 3; i * i <= a; i += 2) {
		if(a % i == 0) return false;
	}
	return true;
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int L; cin >> L;

	queue<int> v;
	v.push(0);

	for(int i = 0; i < L; i++) {
		for(int j = v.size(); j > 0; j--) {
			int a = v.front(); v.pop();
			for(int k = 1; k < 10; k++) {
				int b = a * 10 + k;
				if(isPrime(b)) v.push(b);
			}
		}
	}

	while(!v.empty()) {
		cout << v.front() << '\n';
		v.pop();
	}

	return 0;
}
