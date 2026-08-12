#include "bits/stdc++.h"
using namespace std;
//  #include <ext/pb_ds/assoc_container.hpp>
//  #include <ext/pb_ds/tree_policy.hpp>
//  using namespace __gnu_pbds;

#ifndef DeBuG
#define dbg(...)
#define TT template <typename T
#endif

#define int int64_t
#define endl '\n'
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for (int i = a; i < (b); ++i)
TT, class U> bool chmin(T&a,U b){return a>b?(a=b,1):0;}
TT, class U> bool chmax(T&a,U b){return a<b?(a=b,1):0;}
TT> using V = vector<T>; using vi = V<int>;
using ll = long long; using pii=pair<int,int>;
using vb = V<bool>; using vvi = V<vi>;
template <class T> using V = vector<T>;
// template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = 998244353;
struct mint {
  ll x;
  mint(ll _ = 0) : x((_ % MOD + MOD) % MOD) {}
  mint operator+(const mint&b)const{return x+b.x;}
  mint operator-(const mint&b)const{return x-b.x;}
  mint operator*(const mint&b)const{return x*b.x;}
  mint operator/(const mint&b)const{return*this*inv(b);}
  mint operator^(ll b) const { // a^b^c=(a^b)^c
    assert(b >= 0); // not (a^b)^c -> actual ord
    mint a = *this, ret = 1;
    while (b) {
      if (b & 1) ret = ret * a;
      a = a * a; b >>= 1;
    }
    return ret;
  }
  static mint inv(const mint&a) {
    assert(a.x != 0);
    return a ^ (MOD - 2);
  }
};
struct combi {
  int N; vector<mint> fac, ifac, inv;
  combi(int _) : N(_), fac(_), ifac(_), inv(_) {
    fac[0] = ifac[0] = 1;
    if (N > 1) inv[1] = 1;
    rep(i,2,N) inv[i] = inv[MOD % i]*(-MOD / i);
    rep(i,1,N) {
      fac[i] = fac[i - 1] * i;
      ifac[i] = ifac[i - 1] * inv[i];
    }
  }
  inline mint ncr(int n, int r) {
    assert(0 <= n && n < N);
    return n<r||r<0 ? 0 : fac[n]*ifac[r]*ifac[n-r];
  }
};
void solve(int cs) {
  // auto pw = [](ll a, ll b) {
  //   ll ret(1);
  //   while (b) {
  //     if (b & 1) ret = ret * a % MOD;
  //     a = a * a % MOD;
  //     b >>= 1;
  //   }
  //   return ret;
  // };

  // int N = 3e5 + 1;
  // vi fact(N), ifact(N);
  // fact[0] = 1;
  // for (int i = 1; i < N; i++)
  //   fact[i] = fact[i - 1] * i % MOD;
  // ifact[N - 1] = pw(fact[N - 1], MOD - 2);
  // for (int i = N - 2; i >= 0; i--)
  //   ifact[i] = ifact[i + 1] * (i + 1) % MOD;

  // auto C = [&](int n, int r) -> ll {
  //   if (r > n or r < 0) return 0;
  //   return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
  // };

  // int n; cin >> n;
  // int ans = C(n / 3, n / 6);
  // for (int i = 0; i < n / 3; i++) {
  //   int a, b, c; cin >> a >> b >> c;
  //   if (a == b && b == c) ans = (ans * 3) % MOD;
  //   else {
  //     vi vals = {a, b, c}; sort(all(vals));
  //     if (vals[0] == vals[1]) ans = (ans * 2) % MOD;
  //   }
  // }
  // cout << ans << endl;

  int n; cin >> n;
  int N = 3e5 + 1; combi C(N);
  mint ans = C.ncr(n / 3, n / 6);
  for (int i = 0; i < n / 3; i++) {
    int a, b, c; cin >> a >> b >> c;
    if (a == b && b == c) ans = ans * 3;
    else {
      vi vals = {a, b, c}; sort(all(vals));
      if (vals[0] == vals[1]) ans = ans * 2;
    }
  }
  cout << ans.x << endl;
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int tc = 1;
    #ifdef DeBuG
  cin >> tc;
    #endif
  for (int cs = 1; cs <= tc; cs++) solve(cs);
}