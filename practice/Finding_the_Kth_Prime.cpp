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
#define V vector
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define lb lower_bound
#define ub upper_bound
#define em emplace
// #define int int64_t
const int N = 9e7;
bool isprime[N];

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

    isprime[0] = isprime[1] = 1;
    for (int i = 2; i * i < N; i++) {
        if (!isprime[i])
            for (int j = i * i; j < N; j += i)
                isprime[j] = 1;
    }
    vector<int> primes; primes.eb(2);
    for (int i = 3; i < N; i += 2)
        if (!isprime[i]) primes.eb(i);


    int T(1);
    cin >> T;
    for (int Ti = 1; Ti <= T; Ti++) {
        int n; cin >> n;
        cout << primes[n - 1] << endl;
    }
    return 0;
}

//

/* Lemmas

*/

/* Solutions

*/

/* Analysis

*/