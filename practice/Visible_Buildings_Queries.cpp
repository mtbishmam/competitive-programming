#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define REPB(i, a, b) for(int i = a; i >= b; i--)
#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())

template<typename T1, typename T2>
using P = pair<T1, T2>;
template<typename T>
using V = vector<T>;
template<typename T>
using VV = V<V<T>>;

using S = string;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vii = vector<pair<int, int>>;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

const int N = 2e5 + 10;
int a[N], prv[N];
vi tree[4 * N];

inline namespace MST {
    void pull(int u, int l, int r) {
        int i = 0, j = 0;
        while (i < sz(tree[u << 1]) && j < sz(tree[u << 1 | 1])) {
            if (tree[u << 1][i] <= tree[u << 1 | 1][j]) tree[u].emplace_back(tree[u << 1][i++]);
            else tree[u].emplace_back(tree[u << 1 | 1][j++]);
        }
        while (i < sz(tree[u << 1])) tree[u].emplace_back(tree[u << 1][i++]);
        while (j < sz(tree[u << 1 | 1])) tree[u].emplace_back(tree[u << 1 | 1][j++]);
    }

    void build(int u, int l, int r) {
        if (l == r) {
            tree[u] = { prv[l] };
            return;
        }
        int mid = l + (r - l) / 2;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pull(u, l, r);
    }

    int query(int u, int l, int r, int ql, int qr, int x) {
        if (l > qr || r < ql)
            return 0;
        if (l >= ql && r <= qr) {
            auto it = lower_bound(all(tree[u]), x);
            return it - tree[u].begin();
        }
        int mid = l + (r - l) / 2;
        return query(u << 1, l, mid, ql, qr, x) + query(u << 1 | 1, mid + 1, r, ql, qr, x);
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    REP(i, 1, n) cin >> a[i];
    stack<int> st;

    a[0] = 1e9 + 1; st.push(0);
    REP(i, 1, n) {
        while (a[st.top()] < a[i]) st.pop();
        prv[i] = st.top();
        st.push(i);
    }

    // a[n + 1] = 1e9 + 5;
    // st.push(n + 1);
    // for (int i = n; i >= 1; i--) {
    //     while (a[i] >= a[st.top()]) st.pop();
    //     prv[i] = st.top();
    //     st.push(i);
    // }

    // REPB(i, n, 1) {
    //     while (!st.empty() && a[st.top()] <= a[i]) {
    //         prv[st.top()] = i;
    //         st.pop();
    //     }
    //     st.emplace(i);
    // }

    // REP(i, 1, n) cout << prv[i] << " ";
    // cout << nl;

    // a =   [4  1  2  2  3]
    // prv = {0  1  1  3  1}

    build(1, 1, n);
    // REP(i,1,sz(tree[1])-1) cout << tree[1][i] << " ";
    // cout << nl;

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << query(1, 1, n, l, r, l) << nl;
    }
}

void OJ() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    // OJ();

    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; i++)
        solve();
    return 0;
}