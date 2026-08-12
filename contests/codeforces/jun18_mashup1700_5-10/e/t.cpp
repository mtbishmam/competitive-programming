#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
	#define dbg(...)
#endif

#define int int64_t

#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a;i<(b);++i)
using ll = long long; using pii = pair<int,int>;
using pll = pair<ll,ll>; using vi = vector<int>;
template<class T> using V = vector<T>;

void solve(int cs) {
	int n; cin >> n;
	vi a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}

	V<vi> cycles; V<bool> vis(n + 1);
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {

			int s = i; vi cyc;
			while (!vis[s]) {
				vis[s] = 1;
				cyc.push_back(s);
				s = a[s];
			}
			cycles.push_back(cyc);

		}
	}
	sort(all(cycles)); // just in case
	// for (auto& cyc : cycles) {
	// 	for (auto& i : cyc) cout << i << " ";
	// 	cout << endl;
	// }

	int id = 0;
	map<int, vi> idd; map<int, int> sz;
	vi cycid(n + 1);
	for (auto& cyc : cycles) {
		idd[id] = cyc;
		sz[id] = sz(cyc);
		for (auto& x : cyc) cycid[x] = id;
		id++;
	}

	// think about the -1 case
	auto get_pos = [&](int x, int id) {
		auto& v = idd[id];
		for (int i = 0; i < sz(v); i++) {
			if (v[i] == x) return i;
		}
		return (int)-1;
	};

	auto do_fill = [&](int L, int R, int start, int pos, int n, vi& a) {
		int nn = n;
		int i = pos;
		int j = start;
		while (nn) {
			b[j] = 	a[i];
			j++; i++;
			if (i >= n) i = 0;
			if (j > R) j = start;
			nn--;
		}
	};
	bool f = 1;
	int L = 1;
	map<int, bool> viscyc;
	for (int i = 1; i <= n; i++) {
		if (b[i] != -1) {
			int cid = cycid[b[i]];
			if (!viscyc[cid]) {
				int pos = get_pos(b[i], cid);
				if (pos == -1) { // assert
					f = 0;
				}
				int R = L + sz[cid];
				int start = i;
				do_fill(L + 1, R, start, pos, sz[cid], idd[cid]);

				viscyc[cid] = 1;
				L = R;
			}
		}
	}

	if (f) {
		for (int i = 1; i <= n; i++) {
			cout << b[i] << " ";
		}
		cout << endl;
	} else {
		cout << "NO" << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int tc = 1;
// #ifdef DeBuG
	cin >> tc;
// #endif
	for (int cs = 1; cs <= tc; cs++) solve(cs);
	return 0;
}