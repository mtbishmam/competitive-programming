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
	string s; cin >> s;
	int k; cin >> k;

	V<string> a = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	int idx = find(all(a), s) - a.begin();
	idx = (idx + k) % 12;
	cout << a[idx];
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