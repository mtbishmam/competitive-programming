#define \
PROG : ariprog
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

bool bs[500000];

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	int N, M;
	cin >> N >> M;
	vector<int> b;
	for(int i = 0; i <= M; i++) {
		for(int j = i; j <= M; j++) {
			int v = i * i + j * j;
			if(!bs[v]) {
				bs[v] = true;
				b.push_back(v);
			}
		}
	}

	sort(b.begin(), b.end());

	int B = b.size();

	vector<pair<int, int>> seq;
	for(int i = 0; i < B; i++) {
		for(int j = i + 1; j < B; j++) {
			int x = b[i], y = b[j] - b[i];
			bool good = true;
			for(int k = 2; k < N; k++) {
				if(!bs[x + k * y]) {
					good = false;
					break;
				}
			}
			if(good) {
				seq.push_back(make_pair(y, x));
			}
		}
	}

	sort(seq.begin(), seq.end());
	for(auto i : seq) {
		cout << i.second << ' ' << i.first << '\n';
	}
	if(seq.empty()) cout << "NONE\n";

	return 0;
}
