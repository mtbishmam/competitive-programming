#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
const int MOD = 1e9 + 7;
#define add(x, y) (((x) + (y)) >= MOD ? ((x) + (y)) - MOD : ((x) + (y)))

int n, m;
vector<vi> nextmask;   // precomputed transitions
int dp[1000][1 << 10];

// Generate all possible next masks for a given column mask
vi genmasks;
void gen(int i, int mask, int nmask) {
    if (i == n) {
        genmasks.push_back(nmask);
        return;
    }
    if (!(mask & (1 << i))) {
        // vertical domino (occupies this cell + next column)
        gen(i + 1, mask, nmask | (1 << i));
        // horizontal domino (occupies this cell + next row in same column)
        if (i + 1 < n && !(mask & (1 << (i + 1))))
            gen(i + 2, mask, nmask);
    }
    else {
        // skip already filled cell
        gen(i + 1, mask, nmask);
    }
}

// Recursive DP using precomputed nextmask
int f(int j, int mask) {
    if (j == m) return mask == 0;
    int& ret = dp[j][mask];
    if (ret != -1) return ret;

    ret = 0;
    for (int nmask : nextmask[mask])
        ret = add(ret, f(j + 1, nmask));
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int S = 1 << n;

    // Precompute transitions
    nextmask.assign(S, vi());
    for (int mask = 0; mask < S; mask++) {
        genmasks.clear();
        gen(0, mask, 0);
        nextmask[mask] = genmasks;
    }

    // Initialize DP
    memset(dp, -1, sizeof(dp));

    cout << f(0, 0) << "\n";
}