#include "bits/stdc++.h"
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif
#define TU TT, typename U>

#define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for(int i=a; i<(b); ++i)
TU bool chmin(T&a,U b){return a>b?(a=b,1):0;}
TU bool chmax(T&a,U b){return a<b?(a=b,1):0;}
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;
using vb = V<bool>; using vvi = V<vi>;
// TT> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)
const int MOD = 676767677;
void solve(int cs) {
    int n; cin >> n;
    vi a(n); for (auto& i : a) cin >> i;

    vvi dp(n, vi(2, -1));
    auto f = [&](auto&& f, int i, int j, int right) -> int {
        if (i == n) return a[0] - 1 == right;
        auto& ret = dp[i][j];
        if (~ret) return ret;

        ret = 0;
        if (a[i - 1] == a[i]) {
            if (j == 0) ret = (ret + f(f, i + 1, 1, right + 1)) % MOD;
            if (j == 1) ret = (ret + f(f, i + 1, 0, right)) % MOD;
        } else if (a[i - 1] - 1 == a[i] && j == 1) {
            ret = (ret + f(f, i + 1, j, right + 1)) % MOD;
        } else if (a[i - 1] + 1 == a[i] && j == 0) {
            ret = (ret + f(f, i + 1, j, right)) % MOD;
        }
        return ret;
    };
    int ans = (f(f, 1, 0, 0) + f(f, 1, 1, 0)) % MOD;
    cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);

    auto brute = [](int n) -> void {
        string s;
        auto f = [&](auto&& f, string s) -> void {
            if (sz(s) == n) {
                for (int i = 0; i < sz(s); i++) cout << s[i] << " ";
                cout << endl;
                vi a(sz(s), 1);
                for (int i = 0; i < sz(s); i++) {
                    for (int j = i - 1; j >= 0; j--) if (s[j] == '(') a[i]++;
                    for (int j = i + 1; j < n; j++) if (s[j] == ')') a[i]++;
                    cout << a[i] << " ";
                }
                cout << endl;
                return;
            }
            f(f, s + '(');
            f(f, s + ')');
        }; f(f, "");
    };
    // brute(4);

    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
