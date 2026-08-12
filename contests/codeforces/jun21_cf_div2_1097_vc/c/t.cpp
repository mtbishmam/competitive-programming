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

struct node {
    int val = 0;
    node() {}
    node(int val) : val(val) {}
};
template<class T>
struct segtree {
    // T f(T& a, T& b) { return a.val + b.val; }
    T f(T& a, T& b) { return a + b; }
    int n; vector<T> t;
    segtree(int n = 0) : n(n), t(4 * n, T()) {}
    T query(int L, int R, int i, int l, int r) {
        if (r < L || R < l || R < L) return T();
        if (L <= l && r <= R) return t[i];
        int mid = (l + r) >> 1;
        T lc = query(L, R, i << 1, l, mid);
        T rc = query(L, R, i << 1 | 1, mid + 1, r);
        return f(lc, rc);
    }
    void update(int pos, T val, int i, int l, int r) {
        if (l == r) return void(t[i] = val);
        int mid = (l + r) >> 1;
        if (pos <= mid) update(pos, val, i << 1, l, mid);
        else update(pos, val, i << 1 | 1, mid + 1, r);
        t[i] = f(t[i << 1], t[i << 1 | 1]);
    }
    T query(int L, int R) { return query(L, R, 1, 0, n - 1); }
    void update(int pos, int x) { update(pos, T(x), 1, 0, n - 1); }
};

void solve(int cs) {
	int n; cin >> n;
	string s, t;
	cin >> s >> t;
	string st = s + t;

	bool f = 1;
	auto chk = [&](string st) {
		vi stk;
		for (int i = 0; i < sz(st); i++) {
			if (st[i] == '(') stk.push_back(i);
			else {
				if (sz(stk)) {
					stk.pop_back();
				} else f = 0;
			}
		}
		return !sz(stk);
	};

	int per, imper; per = imper = 0;
	per += chk(s) + chk(t);
	imper += chk(s) + chk(t);

	if (per == 1 && imper == 1) {
		cout << "NO" << endl;
		return;
	}

	// f &= chk(st);
	// string st2 = t + s;
	// f &= chk(st2);

	segtree<int> tree1(n + 1), tree2(n + 1);
	s = '0' + s;
	t = '0' + t;
	for (int i = 1; i <= n; i++) {
		int sum1 = tree1.query(0, i - 1); //
		int sum2 = tree2.query(0, i - 1); //

		int off1, off2; off1 = off2 = 0;
		if (s[i] == ')') off1 = -1;
		else off1 = 1;
		if (t[i] == ')') off2 = -1;
		else off2 = 1;

		if (sum1 + off1 < 0 || sum2 + off2 < 0) {
			if (s[i] == t[i]) {
				f = 0;
				break;
			} else {
				tree1.update(i, off2);
				tree2.update(i, off1);

				if (tree1.query(0, i) < 0 || tree2.query(0, i) < 0) {
					f = 0;
					break;
				}
			}
		}
		else {
			tree1.update(i, off1);
			tree2.update(i, off2);

			if (tree1.query(0, i) < 0 || tree2.query(0, i) < 0) {
				f = 0;
				break;
			}
		}
	}

	if (f) cout << "YES";
	else cout << "NO";
	cout << endl;
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