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

// max lcm means min gcd
// g = max gcd(a, b)
// g | a && g | b
// a + b = n
// gx + gy = n
// g(x + y) = n
auto brute = [](int n) {    
    for (int i = 1; i <= n - i; i++) {
        cout << i << " " << n - i << " " << lcm(i, n - i) << endl;
    }
    cout << endl << endl;
};
void solve(int cs) {
    int n; cin >> n;

    int d = -1;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) {
            d = i;
            break;
        }

    if (d == -1) cout << 1 << " " << n - 1 << endl;
    else {
        int a = n / d;
        cout << a << " " << n - a << endl;
    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    
//   for (int i : {36, 7}) brute(i);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
