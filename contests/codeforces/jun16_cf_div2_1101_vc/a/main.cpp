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
	vi a(n); for (auto& i : a) cin >> i;
	sort(all(a));
	map<int, int> mp;
	for (auto& i : a) mp[i]++;

	int ans = 1e9;
	for (int k = 0; k < n; k++) {
		int x = a[k], cur = 0;
		for (int i = 0, j = n - 1; i < n && j >= 0; ) {
			if (a[i] == x || a[j] == x) {
				if (a[i] == x && a[j] == x) break;
				else if (a[i] == x) j--;
				else i++;
				cur++;
			} else {
				i++, j--;
				cur++;
			}
		}
		ans = min(ans, cur);
	}
	cout << ans << endl;
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