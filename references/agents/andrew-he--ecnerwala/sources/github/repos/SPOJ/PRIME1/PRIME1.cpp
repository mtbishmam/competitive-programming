#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll V = 1e5;
bool prime[V + 20];
vector<ll> primes;

typedef pair<ll, ll> pii;

int main() {
	ios_base::sync_with_stdio(0);
	for(ll i = 1; i <= V; i++) prime[i] = true;
	prime[1] = false;
	for(ll i = 1; i <= V; i++) {
		if(prime[i]) {
			primes.push_back(i);
			for(ll j = i; j <= V; j+=i) {
				prime[j] = false;
			}
			prime[i] = true;
		}
	}
	int T; cin >> T;
	for(int t = 0; t < T; t++) {
		ll A, B; cin >> A >> B;
		priority_queue<pii> pq;
		for(int i = 0; i < int(primes.size()); i++) {
			ll p = primes[i];
			if(p * p > B) break;
			pq.push(pii(B / p * p, p));
		}
		vector<ll> res;
		if(A == 1) A++;
		for(ll v = B; v >= A; v--) {
			if(!pq.empty() && pq.top().first == v) {
				while(!pq.empty() && pq.top().first == v) {
					ll p = pq.top().second;
					pq.pop();
					if(v - p > p) pq.push(pii(v - p, p));
				}
			} else {
				res.push_back(v);
			}
		}
		reverse(res.begin(), res.end());
		if(t) cout << '\n';
		for(int i = 0; i < int(res.size()); i++) {
			cout << res[i] << '\n';
		}
	}
	return 0;
}
