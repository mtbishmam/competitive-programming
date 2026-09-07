#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100;

vector<int> arr;

int randval() {
	return rand() % 2001 - 1000;
}

int sum(int i, int t) {
	int res = 0;
	for(int j = 0; j < t; j++) {
		res += arr[i + j];
	}
	return res;
}

void rset(int i, int t, int v) {
	for(int j = 0; j < t; j++) {
		arr[i + j] = v;
	}
}

int seq[MAXN];

void insert(int i, int t) {
	arr.insert(arr.begin() + i, seq, seq + t);
}

void del(int i, int t) {
	arr.erase(arr.begin() + i, arr.begin() + i + t);
}

void reverse(int i, int t) {
	for(int j = 0; j < t - j - 1; j++) {
		swap(arr[i + j], arr[i + t - j - 1]);
	}
}

int msum() {
	int res = arr[0];
	int msum = 0;
	int sum = 0;
	for(int i = 0; i < int(arr.size()); i++) {
		sum += arr[i];
		res = max(res, sum - msum);
		msum = min(sum, msum);
	}
	return res;
}

int main() {
	srand(time(NULL));
	ofstream infile ("test.in");
	ofstream outfile ("test.out");
	infile << 1 << '\n';
	int N = 50;
	int M = 20000;
	infile << N << ' ' << M << '\n';
	arr.resize(N);
	for(int i = 0; i < N; i++) {
		arr[i] = randval();
		infile << arr[i] << ' ';
	}
	infile << '\n';
	for(int q = 0; q < M; q++) {
		if(q % 2 == 1) {
			infile << "MAX-SUM" << '\n';
			outfile << msum() << '\n';
		} else {
			int c = rand() % 5;
			if(c == 0) {
				int s = rand() % N;
				int t = rand() % N;
				if(t < s) swap(s, t);
				t++;
				t -= s;
				int v = randval();
				rset(s, t, v);

				infile << "MAKE-SAME" << ' ' << s+1 << ' ' << t << ' ' << v << '\n';
			} else if(c == 1) {
				int s = rand() % (N + 1);
				int t = rand() % (MAXN - N + 1);
				for(int j = 0; j < t; j++) seq[j] = randval();
				insert(s, t);
				N += t;
				
				infile << "INSERT" << ' ' << s << ' ' << t << ' ';
				for(int j = 0; j < t; j++) infile << seq[j] << ' ';
				infile << '\n';
			} else if(c == 2) {
				int s = rand() % N;
				int t = rand() % N;
				if(t < s) swap(s, t);
				t++;
				t -= s;
				if(t == N) {
					t = 0;
				}
				del(s, t);
				N -= t;

				infile << "DELETE" << ' ' << s+1 << ' ' << t << '\n';
			} else if(c == 3) {
				int s = rand() % N;
				int t = rand() % N;
				if(t < s) swap(s, t);
				t++;
				t -= s;
				reverse(s, t);

				infile << "REVERSE" << ' ' << s+1 << ' ' << t << '\n';
			} else if(c == 4) {
				int s = rand() % N;
				int t = rand() % N;
				if(t < s) swap(s, t);
				t++;
				t -= s;

				outfile << sum(s, t) << '\n';

				infile << "GET-SUM" << ' ' << s+1 << ' ' << t << '\n';
			}
		}
	}
}
