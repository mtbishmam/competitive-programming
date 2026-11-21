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

void solve(int cs) {
    int n; cin >> n;
    vi a(n); rep(i, 0, n) cin >> a[i];

    int inv = 0;
    auto merge = [&](vi& a, vi& b) -> vi {
        int i = 0, j = 0, k = 0; vi ret(sz(a) + sz(b));
        while (i < sz(a) && j < sz(b)) {
            if (a[i] <= b[j]) ret[k++] = a[i++];
            else {
                auto it  = upper_bound(all(a), b[j] * b[j]);
                inv += a.end() - it;
                ret[k++] = b[j++];
            }
        }
        while (i < sz(a)) ret[k++] = a[i++];
        while (j < sz(b)) ret[k++] = b[j++];
        return ret;
    };
    auto mergesort = [&](this auto&& mergesort, int l, int r) -> vi {
        if (l >= r) return {a[l]};
        else {
            int mid = (l + r) >> 1;
            auto L = mergesort(l, mid);
            auto R = mergesort(mid + 1, r);
            return merge(L, R);
        }
    };
    vi ans = mergesort(0, n - 1);
    cout << inv << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}

