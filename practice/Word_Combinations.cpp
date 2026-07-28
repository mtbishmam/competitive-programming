#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)x.size()
#define rep(i,a,b) for(int i=a;i<b;i++)
const ll MOD = 1e9 + 7;

template<const ll M, const ll B>
struct Hash {
    int n; vector<ll> pw, h;
    Hash(const string& s) : n(sz(s)), pw(n + 1), h(n + 1) {
        pw[0] = 1;
        for (int i = 1;i <= n;i++) {
            pw[i] = (pw[i - 1] * B) % M;
            h[i] = (h[i - 1] * B + s[i - 1]) % M;
        }
    }
    ll eval(int l, int r) {
        ll val = (h[r + 1] - h[l] * pw[r - l + 1]) % M;
        if (val < 0) val += M;
        return val;
    }
};

struct double_hash {
    using H1 = Hash<1000000007, 101>;
    using H2 = Hash<1000000009, 103>;
    H1 h1; H2 h2;
    double_hash(const string& s) : h1(s), h2(s) {}
    pair<ll, ll> eval(int l, int r) { return { h1.eval(l,r), h2.eval(l,r) }; }
};

using ull = unsigned long long;
#include <chrono>
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // Source: Sebastiano Vigna's splitmix64
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// usage
// unordered_map<ull, bool, custom_hash> dict;

#include <bits/extc++.h>
struct chash {
    const uint64_t C = (ll)(4e18 * acos(0)) | 71;
    ll operator() (ll x) const { return __builtin_bswap64(x * C); }
};

__gnu_pbds::gp_hash_table<ull, int, custom_hash> dict({}, {}, {}, {}, { 1 << 19 });

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int n = sz(s);
    int m; cin >> m;

    int maxlen = 0;
    // unordered_set<ull, custom_hash> dict;
    // unordered_map<ull, bool> dict;
    // map<ull, bool> dict;
    rep(i, 0, m) {
        string t; cin >> t;
        if (sz(t) <= n) {
            maxlen = max(maxlen, sz(t));
            double_hash d(t);
            auto [h1, h2] = d.eval(0, sz(t) - 1);
            unsigned long long key = ((unsigned long long)h1 << 32) ^ h2;
            // dict.insert(key);
            dict[key] = 1;
        }
    }

    double_hash d(s);
    vector<ll> dp(n + 1);
    dp[n] = 1;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < min(n, i + maxlen); j++) {
            auto [h1, h2] = d.eval(i, j);
            unsigned long long key = ((unsigned long long)h1 << 32) ^ h2;
            if (dict.find(key) != dict.end()) {
                dp[i] += dp[j + 1];
                if (dp[i] >= MOD) dp[i] -= MOD;
            }
        }
    }

    cout << dp[0] << "\n";
}
