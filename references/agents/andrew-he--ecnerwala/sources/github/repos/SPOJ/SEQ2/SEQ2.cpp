#include<bits/stdc++.h>
using namespace std;

const int MAXV = 5e6;
const int INF = 1e9;

int V;

int p[MAXV];
int c[MAXV][2];

int val[MAXV];
int sz[MAXV];

int sum[MAXV];

int msum[MAXV];
int ssum[MAXV][2];

bool lazy[MAXV];
int lval[MAXV];

bool flip[MAXV];

inline int d(int a) { return c[p[a]][1] == a; }

void update(int a) {
	if(!a) {
		return;
	}

	sz[a] = 1 + sz[c[a][0]] + sz[c[a][1]];

	if(lazy[a]) {
		val[a] = lval[a];
		sum[a] = lval[a] * sz[a];

		msum[a] = max(val[a], sum[a]);
		ssum[a][0] = ssum[a][1] = max(0, sum[a]);
	} else {
		sum[a] = val[a] + sum[c[a][0]] + sum[c[a][1]];

		msum[a] = max(ssum[c[a][0]][1] + val[a] + ssum[c[a][1]][0], max(msum[c[a][0]], msum[c[a][1]]));
		ssum[a][0] = max(ssum[c[a][0]][0], sum[c[a][0]] + val[a] + ssum[c[a][1]][0]);
		ssum[a][1] = max(ssum[c[a][1]][1], sum[c[a][1]] + val[a] + ssum[c[a][0]][1]);
	}

	if(flip[a]) {
		swap(ssum[a][0], ssum[a][1]);
	}
}

void propogate(int a) {
	if(!a) return;

	if(lazy[a]) {
		val[a] = lval[a];
		if(c[a][0]) {
			lazy[c[a][0]] = true;
			lval[c[a][0]] = lval[a];
		}
		if(c[a][1]) {
			lazy[c[a][1]] = true;
			lval[c[a][1]] = lval[a];
		}
		lazy[a] = false;
	}

	if(flip[a]) {
		if(c[a][0]) flip[c[a][0]] ^= true;
		if(c[a][1]) flip[c[a][1]] ^= true;
		swap(c[a][0], c[a][1]);
		flip[a] = false;
	}

	update(c[a][0]);
	update(c[a][1]);
	//update(a);
}

void rot(int a) {
	int x = d(a);
	int pa = p[a];
	int ch = c[a][!x];

	assert(pa);
	assert(a == c[pa][x]);

	propogate(pa);
	propogate(a);

	if(p[pa]) c[p[pa]][d(pa)] = a;
	p[a] = p[pa];

	c[pa][x] = ch;
	if(ch) p[ch] = pa;

	c[a][!x] = pa;
	p[pa] = a;

	update(pa);
	update(a);
}

void splay(int a, int r) {
	propogate(a);
	while(p[a] != r) {
		if(p[p[a]] != r) {
			if(d(p[a]) == d(a)) rot(p[a]);
			else rot(a);
		}
		rot(a);
	}
}

void updateall(int a, int r) {
	for(int n = a; n != r; n = p[n]) {
		update(n);
	}
	update(r);
	splay(a, r);
}

int nxt(int a, int t) {
	propogate(a);
	if(!t) return a;
	int n = c[a][1];
	while(true){
		assert(t <= sz[n]);
		propogate(n);
		if(t == sz[c[n][0]] + 1) break;
		else if(t <= sz[c[n][0]]) n = c[n][0];
		else t -= sz[c[n][0]] + 1, n = c[n][1];
	}
	splay(n, a);
	return n;
}

int getrange(int a, int i, int t) {
	assert(t);
	if(!i) {
		assert(t == sz[a]);
		propogate(a);
		return a;
	}
	int l = nxt(a, i - 1);
	if(sz[c[l][1]] == t) {
		int n = c[l][1];
		propogate(n);
		return n;
	}
	int r = nxt(l, t + 1);
	int n = c[r][0];
	propogate(n);
	return n;
}

int newnode(int v = 0) {
	int n = ++V;
	p[n] = 0;
	c[n][0] = c[n][1] = 0;
	val[n] = v;
	lazy[n] = false;
	flip[n] = false;
	update(n);
	return n;
}

int ROOT;

void init() {
	p[0] = 0;
	c[0][0] = c[0][1] = 0;
	val[0] = 0;
	sz[0] = 0;
	msum[0] = -INF;
	ssum[0][0] = ssum[0][1] = 0;
	lazy[0] = false;
	flip[0] = false;

	V = 0;

	ROOT = newnode(0); // create the root
}

void modify(int i, int t, int v) {
	if(!t) return;
	int n = getrange(ROOT, i, t);
	lazy[n] = true;
	lval[n] = v;
	updateall(n, ROOT);
}

void insert(int i, int n) {
	if(!n) return;
	if(i == sz[ROOT] - 1) {
		int pa = getrange(ROOT, i, 1);
		p[n] = pa;
		c[pa][1] = n;
	} else {
		int pa = getrange(ROOT, i+1, 1);
		p[n] = pa;
		c[pa][0] = n;
	}
	updateall(n, ROOT);
}

void remove(int i, int t) {
	if(!t) return;
	int n = getrange(ROOT, i, t);
	c[p[n]][d(n)] = 0;
	updateall(p[n], ROOT);
}

void reverse(int i, int t) {
	if(!t) return;
	int n = getrange(ROOT, i, t);
	flip[n] = true;
	updateall(n, ROOT);
}

int getsum(int i, int t) {
	if(!t) return 0;
	int n = getrange(ROOT, i, t);
	int res = sum[n];
	updateall(n, ROOT);
	return res;
}

int getmsum() {
	return msum[c[ROOT][1]];
}

int seq[1000000];

int maketree(int l, int r) {
	if(r < l) return 0;
	int m = (l + r) / 2;
	int n = newnode(seq[m]);
	c[n][0] = maketree(l, m - 1);
	if(c[n][0]) p[c[n][0]] = n;
	c[n][1] = maketree(m + 1, r);
	if(c[n][1]) p[c[n][1]] = n;
	update(n);
	return n;
}

char str[100];

int main() {
	int T;
	scanf("%d", &T);
	//T = 1;

	for(int z = 0; z < T; z++) {
		init();
		int N, M;
		scanf("%d %d", &N, &M);
		M++;
		for(int q = 0; q < M; q++) {
			if(q) {
				scanf(" %s", str);
			} else {
				str[0] = 'I';
			}

			if(str[0] == 'M' && str[2] == 'K') {
				int i, t, v;
				scanf("%d %d %d", &i, &t, &v);
				modify(i, t, v);
			} else if(str[0] == 'I') {
				int i, t;
				if(q) {
					scanf("%d %d", &i, &t);
				} else {
					i = 0;
					t = N;
				}
				for(int j = 0; j < t; j++) {
					scanf("%d", &(seq[j]));
				}
				int n = maketree(0, t - 1);
				insert(i, n);
			} else if(str[0] == 'D') {
				int i, t;
				scanf("%d %d", &i, &t);
				remove(i, t);
			} else if(str[0] == 'R') {
				int i, t;
				scanf("%d %d", &i, &t);
				reverse(i, t);
			} else if(str[0] == 'G') {
				int i, t;
				scanf("%d %d", &i, &t);
				printf("%d\n", getsum(i, t));
			} else {
				printf("%d\n", getmsum());
			}
		}
	}
}
