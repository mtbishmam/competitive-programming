#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<int> tree;

    SegTree(string& s) {
        n = s.size();
        tree.resize(4 * n);
        build(s, 1, 0, n - 1);
    }

    void build(string& s, int node, int l, int r) {
        if (l == r) {
            tree[node] = 1 << (s[l] - 'a');
            return;
        }
        int mid = (l + r) >> 1;
        build(s, node * 2, l, mid);
        build(s, node * 2 + 1, mid + 1, r);
        tree[node] = tree[node * 2] | tree[node * 2 + 1];
    }

    void update(int pos, char c, int node, int l, int r) {
        if (l == r) {
            tree[node] = 1 << (c - 'a');
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(pos, c, node * 2, l, mid);
        else update(pos, c, node * 2 + 1, mid + 1, r);
        tree[node] = tree[node * 2] | tree[node * 2 + 1];
    }

    int query(int ql, int qr, int node, int l, int r) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) >> 1;
        return query(ql, qr, node * 2, l, mid) |
            query(ql, qr, node * 2 + 1, mid + 1, r);
    }

    int query(int ql, int qr) { return query(ql, qr, 1, 0, n - 1); }
    void update(int pos, char c) { update(pos, c, 1, 0, n - 1); }
};

struct node_or {
    int val;
    node_or(int val = 0) : val(val) {}
    node_or operator+(const node_or& r) const {
        return node_or(val | r.val);
    }
};
template<class T>
struct segment_tree {
    int n;
    vector<T> sg;
    segment_tree(int _n) {
        n = _n;
        sg.assign(4 * _n, T());
    }
    void build(int i, int l, int r, vector<int>& a) {
        if (l == r) {
            sg[i] = T(a[l]);
        }
        else {
            int mid = (l + r) >> 1;
            build(i * 2, l, mid, a);
            build(i * 2 + 1, mid + 1, r, a);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
    }
    T query(int L, int R, int i, int l, int r) {
        if (R < L) return T();
        if (r < L || R < l) return T();
        if (L <= l && r <= R) return sg[i];
        int mid = (l + r) >> 1;
        T left = query(L, R, i * 2, l, mid);
        T right = query(L, R, i * 2 + 1, mid + 1, r);
        return left + right;
    }
    void update(int pos, T cur, int i, int l, int r) {
        if (l == r) {
            sg[i] = cur;
        }
        else {
            int mid = (l + r) >> 1;
            if (pos <= mid) update(pos, cur, i * 2, l, mid);
            else update(pos, cur, i * 2 + 1, mid + 1, r);
            sg[i] = sg[i * 2] + sg[i * 2 + 1];
        }
    }
    // Wrappers
    void build(vector<int>& a) { build(1, 0, n - 1, a); }
    T query(int L, int R) { return query(L, R, 1, 0, n - 1); }
    void update(int pos, int x) { update(pos, T(x), 1, 0, n - 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int n = s.size();
    // SegTree st(s);
    segment_tree<node_or> st(s.size());
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = 1 << (s[i] - 'a');
    st.build(a);
    int q; cin >> q;
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int pos; char c;
            cin >> pos >> c;
            pos--; // make 0-based
            st.update(pos, 1 << (c - 'a'));
        }
        else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int mask = st.query(l, r).val;
            cout << __builtin_popcount(mask) << "\n";
        }
    }
}