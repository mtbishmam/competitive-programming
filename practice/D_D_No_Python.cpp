// Constructing Chimney - matrix exponentiation solution
// Author: mtbishmam
// Compile with: g++ -O2 -std=c++17

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <functional>
#include <chrono>
#include <climits>
using namespace std;
using int64 = long long;
using M = vector<vector<int64>>;
const int MOD = 1000000007;
const int S = 1 << 8; // 256 states

// adjacency on the ring (clockwise indices 0..7)
int neigh[8][2] = {
    {7,1}, // 0 adjacent to 7 and 1
    {0,2}, // 1 adjacent to 0 and 2
    {1,3},
    {2,4},
    {3,5},
    {4,6},
    {5,7},
    {6,0}
};

M trans; // trans[cur][next] = ways
// DFS to fill layer: pos_used tracks which cells already used in this layer (including cur bits)
// cur_mask: cells already occupied coming from previous verticals
// pos_used: bitmask of cells used in this layer so far (start = cur_mask)
// next_mask: bits set where we place vertical domino going up (these cells are used now and will be occupied next layer)
void dfs_fill(int cur_mask, int pos_used, int next_mask) {
    // find first free position in this layer (bit 0)
    if (pos_used == (S - 1)) { // all 8 cells used
        trans[cur_mask][next_mask] = (trans[cur_mask][next_mask] + 1) % MOD;
        return;
    }
    // find first zero bit
    int i = 0;
    while ((pos_used >> i) & 1) ++i;
    // try placing vertical brick (occupies this cell and the one above in next layer)
    // which means this cell is used now, and set bit in next_mask
    dfs_fill(cur_mask, pos_used | (1 << i), next_mask | (1 << i));
    // try placing horizontal domino with each neighbor (two choices but only one will be valid since neighbors are ring)
    for (int k = 0; k < 2; ++k) {
        int j = neigh[i][k];
        if (((pos_used >> j) & 1) == 0) {
            // place horizontal domino covering i and j
            dfs_fill(cur_mask, pos_used | (1 << i) | (1 << j), next_mask);
        }
    }
}

// matrix multiply (n x n)
M matMul(const M& A, const M& B) {
    int n = (int)A.size();
    M C(n, vector<int64>(n, 0));
    // naive triple loop but n = 256 -> acceptable with optimization -O2
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            if (A[i][k] == 0) continue;
            int64 aik = A[i][k];
            for (int j = 0; j < n; ++j) {
                if (B[k][j] == 0) continue;
                C[i][j] += aik * B[k][j];
                if (C[i][j] >= (1LL << 62)) C[i][j] %= MOD; // avoid overflow
            }
        }
        for (int j = 0; j < n; ++j) if (C[i][j]) C[i][j] %= MOD;
    }
    return C;
}

M matPow(M base, long long exp) {
    int n = (int)base.size();
    M res(n, vector<int64>(n, 0));
    for (int i = 0; i < n; ++i) res[i][i] = 1;
    while (exp > 0) {
        if (exp & 1) res = matMul(res, base);
        base = matMul(base, base);
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // prepare trans
    trans.assign(S, vector<int64>(S, 0));
    // for each cur_mask, start with pos_used = cur_mask (those cells already occupied)
    for (int cur = 0; cur < S; ++cur) {
        // but cur_mask should be consistent: bits set in cur come from previous verticals,
        // they are considered used in this layer already.
        dfs_fill(cur, cur, 0);
    }

    // build base matrix A where A[i][j] = trans[i][j]
    M A(S, vector<int64>(S, 0));
    for (int i = 0; i < S; ++i)
        for (int j = 0; j < S; ++j)
            A[i][j] = trans[i][j] % MOD;

    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        long long N; cin >> N;
        M AN = matPow(A, N);
        int64 ans = AN[0][0] % MOD; // start with mask 0, end with mask 0
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}