#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> grid;
bitset<3001 * 3001> reachable;

int index(int r, int c) {
    return r * 3000 + c; // mapping 2D to 1D
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    grid.resize(n);
    for (auto& row : grid) cin >> row;

    reachable.reset();
    reachable.set(0); // start at (0,0)

    // d = r + c
    for (int d = 0; d < 2 * n - 1; d++) {
        char min_char = 'Z' + 1;

        // Find min char on diagonal d among reachable
        for (int r = max(0, d - (n - 1)); r < n; r++) {
            int c = d - r;
            if (c < 0 || c >= n) continue;
            if (reachable[index(r, c)]) {
                min_char = min(min_char, grid[r][c]);
            }
        }

        bitset<3001 * 3001> next_reachable;

        // Update next reachable based on minimal char
        for (int r = max(0, d - (n - 1)); r < n; r++) {
            int c = d - r;
            if (c < 0 || c >= n) continue;
            if (reachable[index(r, c)] && grid[r][c] == min_char) {
                if (c + 1 < n)
                    next_reachable.set(index(r, c + 1));
                if (r + 1 < n)
                    next_reachable.set(index(r + 1, c));
            }
        }

        reachable = next_reachable;
        cout << min_char;
    }

    cout << "\n";
    return 0;
}