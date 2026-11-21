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
    vector<int> in(n), post(n);
    for (auto& i : in) cin >> i, i--;
    for (auto& i : post) cin >> i, i--;

    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[in[i]] = i;

    int ptr = n - 1;
    auto build = [&](this auto&& f, int l, int r) -> node* {
        if (l > r) return nullptr;
        int root = post[ptr--];
        node* ret = new node(root);

        int mid = pos[root];
        ret->r = f(mid + 1, r);
        ret->l = f(l, mid - 1);
        return ret;
    };
    node* head = build(0, n - 1);

    auto pre = [&](this auto&& f, node* u) -> void {
        if (u == nullptr) return;
        cout << u->x + 1 << " ";
        f(u->l);
        f(u->r);
    };
    pre(head); cout << endl;
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    #ifdef DeBuG
    cin >> tc;
    #endif
    for (int cs = 1; cs <= tc; cs++) solve(cs);
}
