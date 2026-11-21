#include "bits/stdc++.h"
using namespace std;

#define int int64_t
#define endl '\n'

void solve(int cs) {
    (void)cs;
    int a, v, l, n;
    cin >> a >> v >> l >> n;
    cout << (a > n && v > n ? "YES" : "NO") << endl;
}

void run_operation_test(uint64_t operations) {
    uint64_t state = 1;

    for (uint64_t i = 0; i < operations; ++i) {
        state = state * 2862933555777941757ULL + i;
    }

    // Keep the computation observable to the compiler without runtime I/O.
    asm volatile("" : : "r"(state) : "memory");
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    cin >> tc;
    for (int cs = 1; cs <= tc; cs++) solve(cs);
    cout.flush();
    // Change this count between judge submissions: 1e8, 3e8, 5e8, etc.
    run_operation_test(750'000'000ULL);
}
