struct node {
    int val;
    node(int _ = INT_MIN) : val(_) {} // identity elem
    friend node operator+(const node &a, const node &b) {
        return node(max(a.val, b.val)); // associative func
    }
};
template <class T> struct segtree {
    int n; V<T> t;
    segtree(int _ = 0) { init(_); }
    void init(int _) { // init for HLD, Euler tours
        n = 1; while (n < _) n <<= 1;
        t.assign(2 * n, T());
    }
    void update(int i, T v) {
        for (t[i += n] = v; i >>= 1;)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    T query(int l, int r) { // [l, r]
        T lc, rc;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) lc = lc + t[l++];
            if (!(r & 1)) rc = t[r--] + rc;
        }
        return lc + rc;
    }
};