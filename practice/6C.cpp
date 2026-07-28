#include "bits/stdc++.h" /** keep-include */
using namespace std;

#ifndef DeBuG
	#define dbg(...)
#endif

#define int int64_t

#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
template<class T> using V = vector<T>;
using ll = long long; using pii=pair<int,int>;
using vi = V<int>; using vvi = V<vi>;
using vb = V<bool>;

void solve(int cs) {
    int n; cin >> n;
    vi v(n); for (auto& i : v) cin >> i;

    int a = 0, b = 0, as = 0, bs = 0;
    for (int i = 0, j = n - 1; i <= j; ) {
        if (as == bs) {
            if (i == j) as += v[i++], a++;
            else {
                as += v[i++];
                bs += v[j--];
                a++; b++;
            }
        } else if (as < bs) as += v[i++], a++;
        else bs += v[j--], b++;
    }
    cout << a << " " << b << endl;
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int tc = 1;
// #ifdef DeBuG
//	cin >> tc;
// #endif
	for (int cs = 1; cs <= tc; cs++) solve(cs);
}
