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
    string s; cin >> s;

    vi divs;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i != n / i) divs.push_back(n / i);
        }
    }

    int A = 26; vi cnts(A);
    rep(i, 0, n) cnts[s[i] - 'a']++;
    V<pii> vp; rep(i, 0, A) vp.push_back({cnts[i], i});
    sort(all(vp)); reverse(all(vp));

    int ans = n, bk = -1;
    for (auto& k : divs) {
        int grps = n / k;
        if (grps > A) continue;
        int cur = 0, i = 0;
        for (; i < min(grps, sz(vp)); i++) {
            auto& [cnt, c] = vp[i];
            cur += max((int)0, cnt - k);
        }
        for (; i < sz(vp); i++) cur += vp[i].first;
        if (cur < ans) {
            ans = cur;
            bk = k;
        }
    }
    dbg(bk);
    map<char, int> freq;
    for (int i = 0; i < min(n / bk, sz(vp)); i++) freq[vp[i].second + 'a'] = bk;
    //int nk = n / bk; map<char, int> freq;
    //for (int i = sz(vp) - 1; i >= 0; i--) {
    //    auto& [cnt, c] = vp[i];
    //    if (!freq.count(c + 'a')) {
    //        freq[c + 'a'] = bk;
    //        nk--;
    //    }
    //    if (nk == 0) break;
    //}
    dbg(freq);
    string sans = s; auto it = freq.begin();
    vi fixed(n);
    rep(i, 0, n) {
        int c = s[i];
        if (freq.count(c) && freq[c]) {
            freq[c]--;
            fixed[i] = 1;
        }
    }
    rep(i, 0, n) {
        if (fixed[i]) continue;
        int c = s[i];
        if (freq.count(c) && freq[c]) {
            freq[c]--;
        } else {
            while (it != freq.end() && it->second == 0) it++;
            sans[i] = it->first;
            it->second--;
        }
    }
    cout << ans << endl;
    cout << sans << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    // #ifdef DeBuG
    cin >> tc;
    // #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
