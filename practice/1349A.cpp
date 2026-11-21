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

const int N = 2e5 + 1;
void solve(int cs) {
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];

    vi spf(N);
    rep(i, 1, N) spf[i] = i;
    for (int i = 2; i < N; i += 2) spf[i] = 2;
    for (int i = 3; i < N; i += 2) {
        for (int j = i + i; j < N; j += i) 
            if (spf[j] == j) spf[j] = i;
    }
    vi primes;
    for (int i = 2; i < N; i++) if (spf[i] == i) primes.push_back(i);
    
    map<int, vi> mp;
    for (int x : a) {
        int X = x, pw = 0;
        map<int, int> mp2;
        while (X > 1) mp2[spf[X]]++, X /= spf[X];
        for (auto& [key, val] : mp2) mp[key].push_back(val);
    }

//    map<int, vi> mp;
//    for (int x : a) {
//        for (auto& p : primes) {
//            if (x % p == 0) {
//                int X = x, pw = 0;
//                while (X % p == 0) X /= p, pw++;
//                if (pw > 0) mp[p].push_back(pw);
//            }
//        }
//    }
    int ans = 1;
    for (auto& [key, v] : mp) {
        sort(all(v));
        int cur = 1, k;
        if (sz(v) == n) {
            k = v[1];
        }
        else if (sz(v) == n - 1) {
            k = v[0];    
        }
        else k = 0;
        while (k--) cur *= key;
        ans *= cur;
    }
    cout << ans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
