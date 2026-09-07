#define \
PROG : castle
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

int N, M;
int W[100][100];

int sz[100][100];

const int dx[] = {0, -1, 0, 1}, dy[] = {-1, 0, 1, 0};

//return size, sets sz to v
int flood(int a, int b, int v = -1) {
	if(sz[a][b] == v) return 0;
	sz[a][b] = v;
	int res = 1;
	for(int d = 0; d < 4; d++) {
		if(W[a][b] & (1 << d)) continue;
		res += flood(a + dx[d], b + dy[d], v);
	}
	return res;
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> M >> N;

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			cin >> W[i][j];
		}
	}

	int cnt = 0;
	int mroom = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if(sz[i][j]) continue;
			int s = flood(i, j);
			flood(i, j, s * 10000 + cnt);
			cnt++;
			mroom = max(mroom, s);
		}
	}

	cout << cnt << '\n';
	cout << mroom << '\n';

	int mpair = 0;
	int x, y; char c;
	for(int j = 0; j < M; j++) {
		for(int i = N - 1; i >= 0; i--) {
			if(i > 0 && sz[i][j] != sz[i - 1][j]) {
				int v = sz[i][j] / 10000 + sz[i - 1][j] / 10000;
				if(v > mpair) {
					mpair = v;
					x = i;
					y = j;
					c = 'N';
				}
			}
			if(j + 1 < M && sz[i][j] != sz[i][j + 1]) {
				int v = sz[i][j] / 10000 + sz[i][j + 1] / 10000;
				if(v > mpair) {
					mpair = v;
					x = i;
					y = j;
					c = 'E';
				}
			}
		}
	}

	cout << mpair << '\n';
	cout << x+1 << ' ' << y+1 << ' ' << c << '\n';

	return 0;
}
