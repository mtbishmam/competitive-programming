#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct SegTree {
    int n;
    // store (minPrev, pos) for range
    vector<pair<int, int>> st;
    SegTree(int _n = 0) { init(_n); }
    void init(int _n) {
        n = _n;
        st.assign(4 * n + 5, { INF, -1 });
    }
    // tie-break: prefer smaller minPrev; if equal, prefer larger pos (rightmost)
    static pair<int, int> better(const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first < b.first) return a;
        if (b.first < a.first) return b;
        // equal prev -> prefer larger pos (rightmost) to match sample choices
        return (a.second > b.second) ? a : b;
    }
    void update(int idx, int l, int r, int pos, int val) {
        if (l == r) {
            st[idx] = { val, pos };
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(idx << 1, l, mid, pos, val);
        else update(idx << 1 | 1, mid + 1, r, pos, val);
        st[idx] = better(st[idx << 1], st[idx << 1 | 1]);
    }
    pair<int, int> query(int idx, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return { INF, -1 };
        if (ql <= l && r <= qr) return st[idx];
        int mid = (l + r) >> 1;
        auto L = query(idx << 1, l, mid, ql, qr);
        auto R = query(idx << 1 | 1, mid + 1, r, ql, qr);
        return better(L, R);
    }
    // wrappers
    void update(int pos, int val) { update(1, 1, n, pos, val); }
    pair<int, int> query(int l, int r) { return query(1, 1, n, l, r); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#if 0
    // Example test (uncomment for local quick test)
    // 6
    // 1 1 2 3 2 4
    // 2
    // 2 6
    // 1 2
#endif

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int q; cin >> q;
    // store queries grouped by right endpoint
    vector<vector<pair<int, int>>> queries(n + 1);
    vector<int> L(q), R(q);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        L[i] = l; R[i] = r;
        queries[r].push_back({ l, i });
    }

    // compute prev[i] (0 if none)
    int maxA = 500000; // constraint
    vector<int> lastOcc(maxA + 5, 0);
    vector<int> prevIdx(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        prevIdx[i] = lastOcc[x]; // 0 if none
        lastOcc[x] = i;
    }

    // segment tree and helper to track current last occurrence in prefix
    SegTree seg(n);
    vector<int> curLast(maxA + 5, 0); // current last occurrence while sweeping r

    vector<int> ans(q, 0);
    // sweep r = 1..n
    for (int r = 1; r <= n; ++r) {
        int val = a[r];
        if (curLast[val] != 0) {
            // previous last occurrence is no longer the last -> remove it (set INF)
            seg.update(curLast[val], INF);
        }
        // set current position r as last occurrence with value prevIdx[r]
        seg.update(r, prevIdx[r]); // store prev at position r
        curLast[val] = r;

        // answer queries with this r
        for (auto& pr : queries[r]) {
            int l = pr.first;
            int qi = pr.second;
            auto best = seg.query(l, r); // (minPrev, pos)
            if (best.first < l) {
                ans[qi] = a[best.second];
            }
            else ans[qi] = 0;
        }
    }

    // output answers in input order
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
    return 0;
}