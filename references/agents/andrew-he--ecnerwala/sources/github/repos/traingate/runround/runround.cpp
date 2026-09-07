#define \
PROG : runround
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

vector<long long> vals;

bool isGood(const vector<int> &s) {
	int n = s.size();
	int cur = 0;
	for(int i = 0; i < n; i++) {
		if(i > 0 && cur == 0) return false;
		cur += s[cur];
		cur %= n;
	}
	return cur == 0;
}

long long val(const vector<int> &s) {
	long long res = 0;
	for(int i : s) res *= 10, res += i;
	return res;
}

void dfs(vector<int> s = vector<int>(), int used = 0) {
	if(!s.empty() && isGood(s)) vals.push_back(val(s));
	for(int i = 1; i <= 9; i++) {
		if(used & (1 << i)) {
			continue;
		}
		s.push_back(i);
		dfs(s, used | (1 << i));
		s.pop_back();
	}
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	dfs();

	sort(vals.begin(), vals.end());
	cerr << vals.size() << '\n';
	int M; cin >> M;
	cout << *(upper_bound(vals.begin(), vals.end(), M)) << '\n';

	return 0;
}
