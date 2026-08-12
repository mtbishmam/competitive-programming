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
	vi a(n + 1), pre(n + 1), mn(n + 1); mn[0] = 1e9;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (i == 1) pre[i] = mn[i] = a[i];
		else pre[i] = pre[i - 1] + a[i], mn[i] = min(mn[i - 1], a[i]);
	}
	int cur = a[1];
	for (int i = 1; i <= n; i++) {
		if (a[i] >= cur) cout << cur << " ";
		else {
			int rem = pre[i] - cur * i;
			if (a[i] + rem >= cur);
			else cur = min(cur, pre[i] / i);
			cout << cur << " ";
		}
	}
	cout << '\n';
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