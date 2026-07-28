// author: mtbishmam
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

#define endl "\n"
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define lb lower_bound
#define ub upper_bound
#define em emplace
#define int long long

template <typename T> istream& operator>>(istream& is, vector<T>& a) { for (auto& i : a) is >> i; return is; }
template <typename T> ostream& operator<<(ostream& os, vector<T>& a) { for (auto& i : a) os << i << " "; return os; };
template <typename T> ostream& operator<<(ostream& os, set<T>& s) { for (auto i : s) os << i << " "; return os; }
template <typename A, typename B> ostream& operator<<(ostream& os, pair<A, B>& i) { return os << i.ff << " " << i.ss; }
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using vi = vector<int>; using vvi = vector<vi>;
using vl = vector<ll>; using vvl = vector<vl>;
using vb = vector<bool>; using vvb = vector<vb>;
using vc = vector<char>; using vvc = vector<vc>;
using pii = pair<int, int>; using vpii = vector<pii>;
using pll = pair<ll, ll>; using vpll = vector<pll>;
using vs = vector<string>;
using tiii = tuple<int, int, int>; ; using vtiii = vector<tiii>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uniq(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define bug cerr << "!Bugged..." << endl
#define add(x, y) (x + y >= MOD ? x + y - MOD : x + y)
#define mul(x, y) (((x % MOD) * (y % MOD)) % MOD)
#define sz(x) (int)(x).size()

const string ny[] = { "NO", "YES" };
const int dx[8] = { -1,  0, 0, 1, 1,  1, -1, -1 };
const int dy[8] = { 0, -1, 1, 0, 1, -1,  1, -1 };
// const int INF = 2147483647;
// const ll LINF = 9223372036854775807;
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
const double EPS = 1e-9;
const double PI = acos(-1);
const int N = 1e5 + 1;

// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int32_t main()
{
#ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // freopen("error.txt", "a", stderr);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    // cout.tie(NULL);

    int T(1);
    // cin >> T;
    for (int Ti = 1; Ti <= T; Ti++) {
        int n; cin >> n;
        vs a(n); cin >> a;
        set<char> s;
        for (int i = 0; i < 26; i++) s.insert('a' + i);

        if (n == 1) for (auto c : s) cout << c;
        else {
            int time = 1;
            vi ord(26);
            auto solve = [&](string s1, string s2) {
                bool sw = 1;
                int mn = min(sz(s1), sz(s2));
                bool solved = 1, done = 0;
                for (int i = 0; i < mn; i++) {
                    int c1 = s1[i] - 'a';
                    int c2 = s2[i] - 'a';
                    while (i < mn && c1 == c2) {
                        if (!ord[c1]) ord[c1] = time++; // there's a problem here, we need to check finally whether there's any contradiction or not
                        i++;
                        c1 = s1[i] - 'a';
                        c2 = s2[i] - 'a';
                    }
                    if (i < mn) {
                        c1 = s1[i] - 'a';
                        c2 = s2[i] - 'a';
                        if (!ord[c1]) ord[c1] = time++;
                        if (!ord[c2]) ord[c2] = time++;
                        done = 1;
                        solved &= (ord[c1] < ord[c2]); // unless they are equal it has to be less
                        // debug(s1[i], s2[i], ord[c1], ord[c2]);
                        break;
                    }
                }
                if (!done && sz(s1) > sz(s2)) solved = 0;
                // if (sz(s1) == sz(s2)) solved = 1;
                // if (!solved && sz(s1) < sz(s2)) { // meaning one of them were shorter and their shorter length prefixes were same
                //     int lst = sz(s1);
                //     int c1 = s2[lst] - 'a';
                //     if (!ord[c1]) ord[c1] = time++;
                //     solved = 1;
                // }
                // debug(s1, s2, solved);
                return solved;
                };

            bool flag = 1;
            for (int i = 1; i < n; i++) {
                flag &= solve(a[i - 1], a[i]);
            }

            auto f = [&](auto&& f, string& s1, string& s2, int cur = 0) -> bool {
                if (cur >= min(sz(s1), sz(s2))) {
                    if (sz(s1) <= sz(s2)) return 1;
                    else return 0;
                }
                int c1 = s1[cur] - 'a';
                int c2 = s2[cur] - 'a';
                bool ret = 1;
                if (ord[c1] < ord[c2]) return 1;
                else if (ord[c1] == ord[c2])
                    ret &= f(f, s1, s2, cur + 1);
                else return 0;
                return ret;
                };
            for (int i = 0; i < 26; i++)
                if (!ord[i]) ord[i] = time++;
            for (int i = 1; i < n; i++) {
                string s1 = a[i - 1];
                string s2 = a[i];
                flag &= f(f, s1, s2, 0);
            }
            if (flag) {
                vpii ans;
                for (int i = 0; i < 26; i++)
                    ans.eb(ord[i], i);
                sort(all(ans));
                for (auto& [idx, c] : ans) cout << char('a' + c);
            }
            else cout << "Impossible";
        }

    }
    return 0;
}
// If two identical strings exist with an
/*
    1.


    2. convert all the letters and check?
        aivest
        bshamir
        cdleman
*/

/* Analysis
    rsa
*/

/*
    aaab -> abc...
    aaab
    b
    c

    aaab -> abc...
    abc

    aaab -> abc...
    aabc

    aabc -> no answer
    aaab


    aaaa
    aaaa
    aaaa


*/