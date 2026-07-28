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
    int n, a, b; cin >> n >> a >> b;
    if (n <= 2) {
        cout << min(n * a, b) << '\n';
    }
    else if (a * 3 <= b) {
        cout << n * a << '\n';
    } else {
        int q = n / 3;
        int r = n % 3;
        cout << q * b + min(r * a, b) << '\n';
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