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
	int n;
	cin >> n;
	vi a(n);
	for (auto& i : a) cin >> i;
	for (int i = n - 2; i >= 0; i--) {
		int x = a[i] + a[i + 1];
		if (x > a[i]) a[i] = x;
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += a[i] > 0;
	}
	cout << ans << endl;
	// cout << accumulate(all(a), (int)0) << endl;
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