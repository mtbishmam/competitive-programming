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

void solve(int cs) {
    int n; cin >> n;
    vi a(n), b(n); 
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;

    int inv = 0;
    auto merge = [&](vi&a, vi&b) -> vi {
        int n = sz(a), m = sz(b);
        vi ret(n + m);
        int i = 0, j = 0, k = 0;
        while (i < n && j < m) {
            if (a[i] < b[j]) ret[k++] = a[i++];
            else ret[k++] = b[j++], inv += n - i;
        }
        while (i < n) ret[k++] = a[i++];
        while (j < m) ret[k++] = b[j++];
        return ret;
    };
    auto mergesort = [&](this auto&& f, int l, int r, vi& a) -> vi {
        if (l >= r) return {a[l]};
        int mid = (l + r) >> 1;
        auto L = f(l, mid, a);
        auto R = f(mid + 1, r, a);
        return merge(L, R);
    };
    int inva, invb; inva = invb = 0;
    a = mergesort(0, n - 1, a);
    inva = inv; inv = 0;
    b = mergesort(0, n - 1, b);
    invb = inv; inv = 0;
    if (inva % 2 == invb % 2 && a == b) cout << "YES";
    else cout << "NO";
    cout << "\n";
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
