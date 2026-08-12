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
    int n; cin >> n;
    vi a(n);
    map<int, int> idx;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (idx.count(a[i])) {
            idx[a[i]] = min(idx[a[i]], i);
        } else idx[a[i]] = i;
    }
    vi eles = a;
    sort(all(eles));
    eles.erase(unique(all(eles)), eles.end());
    for (int& x : eles) {
        int pos = idx[x];
        for (int i = pos; i < n; i++) {
            a[i] = min(a[i], x);
        }
    }
    cout << accumulate(all(a), (int)0) << endl;
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