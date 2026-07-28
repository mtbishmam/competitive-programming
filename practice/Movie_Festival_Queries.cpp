#include <bits/stdc++.h>
using namespace std;
struct Movie { int a, b; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<Movie> movies(n);
    for (int i = 0; i < n; ++i) cin >> movies[i].a >> movies[i].b;

    // Sort by start time
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        if (movies[i].a != movies[j].a) return movies[i].a < movies[j].a;
        return movies[i].b < movies[j].b;
        });

    // build arrays in start-sorted order
    vector<int> starts(n), ends(n);
    for (int i = 0; i < n; ++i) {
        starts[i] = movies[idx[i]].a;
        ends[i] = movies[idx[i]].b;
    }

    // best[i] = index (in start-sorted order) of movie in suffix i..n-1 with minimal end
    vector<int> best(n);
    best[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        best[i] = (ends[i] <= ends[best[i + 1]] ? i : best[i + 1]);
    }

    // build up[0]: next chosen movie after finishing movie i
    const int LOG = 20; // enough for 2e5
    vector<vector<int>> up(LOG, vector<int>(n, -1));
    vector<vector<int>> cnt(LOG, vector<int>(n, 0));
    vector<vector<int>> endt(LOG, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        // find first movie starting >= ends[i]
        int pos = int(lower_bound(starts.begin(), starts.end(), ends[i]) - starts.begin());
        if (pos < n) up[0][i] = best[pos];
        else up[0][i] = -1;
        cnt[0][i] = 1;
        endt[0][i] = ends[i];
    }

    // binary lifting
    for (int k = 1; k < LOG; ++k) {
        for (int i = 0; i < n; ++i) {
            int mid = up[k - 1][i];
            if (mid == -1) {
                up[k][i] = -1;
                cnt[k][i] = cnt[k - 1][i];
                endt[k][i] = endt[k - 1][i];
            }
            else {
                up[k][i] = up[k - 1][mid];
                cnt[k][i] = cnt[k - 1][i] + cnt[k - 1][mid];
                endt[k][i] = endt[k - 1][mid];
            }
        }
    }

    // answer queries
    while (q--) {
        int A, B; cin >> A >> B;
        int pos = int(lower_bound(starts.begin(), starts.end(), A) - starts.begin());
        if (pos == n) { cout << 0 << '\n'; continue; }
        int idx0 = best[pos]; // start with the greedy earliest-end movie that starts >= A
        if (ends[idx0] > B) { cout << 0 << '\n'; continue; }

        int ans = 0;
        int cur = idx0;
        for (int k = LOG - 1; k >= 0; --k) {
            if (cur == -1) break;
            int next = up[k][cur];
            if (next == -1) {
                // if we cannot make a full 2^k jump from cur, check whether the chain (which may be smaller) still fits:
                if (endt[k][cur] <= B) {
                    ans += cnt[k][cur];
                    cur = -1; // we've consumed what's available in that block
                }
            }
            else {
                // full jump exists, check last endtime of that full jump
                if (endt[k][cur] <= B) {
                    ans += cnt[k][cur];
                    cur = next;
                }
            }
        }

        // if there's still a movie at cur not counted and it fits
        if (cur != -1 && ends[cur] <= B) ans++;

        cout << ans << '\n';
    }
    return 0;
}