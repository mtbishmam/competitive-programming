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

struct node {
    int x;
    node* l;
    node* r;
    node(int x) : x(x), l(nullptr), r(nullptr) {}
};
void solve(int cs) {
    int n; cin >> n;
    vi in(n + 1), pre(n + 1);
    rep(i, 1, n + 1) cin >> in[i];
    rep(i, 1, n + 1) cin >> pre[i];

    vi pos(n + 1);
    rep(i, 1, n + 1) pos[in[i]] = i;

    int ptr = 1;
    auto build = [&](this auto&& f, int l, int r) -> node* {
        if (l > r) return nullptr;

        int root = pre[ptr++];
        node* ret = new node(root);
        
        ret->l = f(l, pos[root] - 1);
        ret->r = f(pos[root] + 1, r);
        return ret;
    };
    node* head = build(1, n);
    auto post = [&](this auto&& f, node* u) -> void {
        if (u == nullptr) return;
        f(u->l);
        f(u->r);
        cout << u->x << " ";
    };
    post(head);
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
