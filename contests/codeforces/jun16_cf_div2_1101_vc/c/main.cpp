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

void solve(int cs) {
	int n, X, S; cin >> n >> X >> S;
	string s; cin >> s;
	int I = count(all(s), 'I');
	int E = count(all(s), 'E');
	int A = count(all(s), 'A');
	int Ilim = min(I, X);
	int ans = 0;
	for (int CI = 0; CI <= Ilim; CI++) {
		int cur = 0, ci = CI;
		int x = X, cs = S;
		multiset<int> ms;
		for (int i = 0; i < n; i++) {
			if (s[i] == 'E') {
				if (sz(ms)) {
					bool f = 0;
					while (sz(ms)) {
						auto it = ms.begin();
						int seats = *it;
						if (seats) {
							if (seats - 1) ms.insert(seats - 1);
							ms.erase(it);
							f = 1;
							break;
						} else {
							ms.erase(it);
						}
					}
					if (f) cur++;
				}
			} else if (s[i] == 'I') {
				if (ci && x) {
					if (cs - 1) ms.insert(cs - 1);
					x--;
					ci--;
					cur++;
				}
			} else {
				int remtables = max(x - ci, (int)0);
				if (remtables >= 1) {
					if (x) {
						if (cs - 1) ms.insert(cs - 1);
						x--;
						cur++;
					}
				} else { // fit ambivert to occupied table
					bool f = 0;
					while (sz(ms)) {
						auto it = ms.begin();
						int seats = *it;
						if (seats) {
							if (seats - 1) ms.insert(seats - 1);
							ms.erase(it);
							f = 1;
							break;
						} else {
							ms.erase(it);
						}
					}
					if (f) cur++;
				}
			}
		}
		ans = max(ans, cur);
	}
	cout << ans << endl;
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