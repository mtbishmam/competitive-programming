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
	vi a(n);
	for (auto& i : a) cin >> i;
	auto chk = [&](vi& a) {
		bool ret = 1;
		for (int i = 1; i < sz(a); i++) if (a[i - 1] > a[i]) ret = 0;
		return ret;
	};
	bool good = chk(a);

	vi stk, prv(n, -1);
	for (int i = 0; i < n; i++) {
		while (sz(stk) && a[stk.back()] <= a[i]) stk.pop_back();
		if (sz(stk)) prv[i] = stk.back();
		stk.push_back(i);
	}

	int x = 0;
	for (int i = 1; i < n; i++) {
		if (a[i - 1] > a[i]) {
			x = max(x, a[prv[i]] - a[i]);
		}
	}
	for (int i = 1; i < n; i++) {
		if (a[i - 1] > a[i]) {
			a[i] += x;
		}
	}
	bool pos = chk(a);
	if (good || pos) cout << "YES";
	else cout << "NO";
	cout << "\n";
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