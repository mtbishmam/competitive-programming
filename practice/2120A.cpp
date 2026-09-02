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

void solve(int cs) {
    array<pii, 3> r;
    for (auto &[l, b] : r) cin >> l >> b;

    int area = 0;
    for (auto [l, b] : r) area += l * b;

    int side = sqrtl((long double) area);
    if (side * side != area) {
        cout << "NO" << endl;
        return;
    }

    bool ok = false;
    for (int i = 0; i < 3 && !ok; ++i) {
        for (int j = i + 1; j < 3 && !ok; ++j) {
            int k = 3 - i - j;

            auto joins_square = [&](int width, int height) {
                bool beside = height == r[k].second && width + r[k].first == side;
                bool below = width == r[k].first && height + r[k].second == side;
                return (beside && height == side) || (below && width == side);
            };

            if (r[i].second == r[j].second &&
                joins_square(r[i].first + r[j].first, r[i].second)) {
                ok = true;
            }
            if (r[i].first == r[j].first &&
                joins_square(r[i].first, r[i].second + r[j].second)) {
                ok = true;
            }
        }
    }

    cout << (ok ? "YES" : "NO") << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
