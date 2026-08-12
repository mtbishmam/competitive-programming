#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
	#define dbg(...)
#endif

#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a;i<(b);++i)
using ll = long long; using pii = pair<int,int>;
using pll = pair<ll,ll>; using vi = vector<int>;
template<class T> using V = vector<T>;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// use mt19937_64 for long long

// uniform_int_distribution<int> dist1(lo, hi);
// uniform_real_distribution<> dist2(lo, hi);

#define rand(l,r) uniform_int_distribution<ll>(l, r)(rng)

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	return 0;
}
