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
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vi b = a; sort(all(b));
	b.erase(unique(all(b)), b.end());
	int mex = 0;
	for (int x : b) {
	    if (x == mex) mex++;
	    else break;
	}
	int mx = b.back();


	int pos = max_element(all(a)) - a.begin();
	swap(a[pos], a[0]);
	if (n > 1) sort(a.begin() + 1, a.end());

	dbg(a);

	set<int> s; int ans1 = 0, cmex = 0;
	for (int i = 0; i < n; i++) {
		s.insert(a[i]);
		int szz = sz(s);
		if (szz == *s.rbegin() + 1) {
			cmex = szz;
		}

		ans1 += mx + cmex;
	}

	int ans2 = 0;
	int mex_sum = (mex * (mex + 1)) / 2 + mex * max((int)0, n - mex);
	int mx_sum = mx * n;

	int mex_1 = max((int)0, mex - 1);
	ans2 = (mex * (mex + 1)) / 2 + (mex_1 * (mex_1 + 1)) / 2;
	int rem = max((int)0, n - mex);
	ans2 += rem * mex + rem * mx;
	cout << max(ans1, ans2) << endl;

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