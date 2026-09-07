#define \
PROG : milk
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

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int N, M;
	cin >> N >> M;
	vector<pair<int, int>> F;
	for(int i = 0; i < M; i++) {
		int p, a; cin >> p >> a;
		F.push_back(make_pair(p, a));
	}
	sort(F.begin(), F.end());
	reverse(F.begin(), F.end());

	int res = 0;
	while(N) {
		while(F.back().second == 0) F.pop_back();
		res += F.back().first;
		F.back().second --;
		N--;
	}

	cout << res << '\n';

	return 0;
}
