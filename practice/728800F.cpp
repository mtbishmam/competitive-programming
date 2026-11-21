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

    auto merge = [&](vi& a, vi& b) -> vi {
        int n = sz(a), m = sz(b);
        vi ret(n + m);
        int i = 0, j = 0, k = 0;
        while (i < n && j < m) {
            if (a[i] < b[j]) ret[k++] = a[i++];
            else ret[k++] = b[j++];
        }
        while (i < n) ret[k++] = a[i++];
        while (j < m) ret[k++] = b[j++];
        return ret;
    };
    auto mergesort = [&](this auto&& f, int l, int r) -> vi {
        if (l >= r) return {a[l]};
        int mid = (l + r) >> 1;
        auto L = f(l, mid);
        auto R = f(mid + 1, r);
        return merge(L, R);
    };
    mergesort(0, n - 1);
    auto print = [&](this auto&& f, int l, int r) -> void {
        if (l > r);
        else if (l == r) cout << a[l] << " ";
        else {
            int mid = (l + r) >> 1;
            cout << a[mid] << " ";
            f(l, mid - 1);
            f(mid + 1, r);
        }
    };
    print(0, n - 1);
    cout << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
