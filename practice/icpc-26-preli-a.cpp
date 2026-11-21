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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

struct Key {
    int x, y;

    bool operator==(const Key& other) const {
        return x == other.x && y == other.y;
    }
};

struct KeyHash {
    size_t operator()(const Key& k) const {
        uint64_t h1 = hash<int>{}(k.x);
        uint64_t h2 = hash<int>{}(k.y);
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

void solve(int) {
    int n, a, b;
    cin >> n >> a >> b;

    vi x(n), y(n), w(n);
    rep(i, 0, n) cin >> x[i];
    rep(i, 0, n) cin >> y[i];
    rep(i, 0, n) cin >> w[i];

    unordered_map<Key, int, KeyHash> sum;
    sum.reserve(n * n * 2);

    int ans = 0;
    rep(i, 0, n) {
        rep(j, 0, n) {
            Key k{
                x[j] - a * x[i] + b * y[i],
                y[j] - b * x[i] - a * y[i]
            };
            sum[k] += w[i];
            ans = max(ans, sum[k]);
        }
    }

    cout << ans << endl;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    cin >> tc;
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
