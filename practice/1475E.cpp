#include "bits/stdc++.h"
using namespace std;

#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif

#define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;

const int N = 1e3 + 1;
const int MOD = 1e9 + 7;
vi fact(N), ifact(N);
void solve(int cs) {
    int n, k; cin >> n >> k;
    vi a(n); rep(i, 0, n) cin >> a[i];

    sort(all(a));
    map<int, int> taken, total;
    int K = k; for (int i = n - 1; i >= 0 && K--; i--) taken[a[i]]++; 
    rep(i, 0, n) total[a[i]]++;

    auto ncr = [&](int n, int r) -> int { return (fact[n] * ifact[r] % MOD) * ifact[n - r] % MOD; };
    int ans = 1;
    for (auto& [val, cnt] : taken) {
        ans = ans * ncr(total[val], cnt) % MOD;
    }
    cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    
    auto pw = [](int a, int b) -> int {
        int ret = 1;
        while (b) {
            if (b & 1) ret = ret * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return ret;
    };

    fact[0] = fact[1] = 1;
    rep(i, 2, N) fact[i] = fact[i - 1] * i % MOD;
    ifact[N - 1] = pw(fact[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) ifact[i] = ifact[i + 1] * (i + 1) % MOD;

    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
