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
	int n, p1, p2, p3, t1, t2;
	cin >> n >> p1 >> p2 >> p3 >> t1 >> t2;
	int ans = 0;
	auto get = [&](int x) {
		int ans = 0;
		int tt1 = t1, tt2 = t2;
		while (x) {
			if (tt1 > 0) {
				ans += p1;
				tt1--;
			} else if (tt2 > 0) {
				ans += p2;
				tt2--;
			} else ans += p3;
			x--;
		}
		return ans;
	};
	
	int L = -1;
	rep(i, 0, n) {
		int l, r; cin >> l >> r;
		ans += (r - l) * p1;
		if (!i) L = r + 1;
		else {
			ans += get(l - L + 1);
			L = r + 1;
		}		
	}	
	cout << ans;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int tc = 1;
// #ifdef DeBuG
	// cin >> tc;
// #endif
	for (int cs = 1; cs <= tc; cs++) solve(cs);
	return 0;
}