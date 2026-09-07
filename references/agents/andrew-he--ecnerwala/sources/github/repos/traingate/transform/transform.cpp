#define \
PROG : transform
#define \
LANG : C++11
#define \
ID : hdrplpx1

#include<bits/stdc++.h>
using namespace std;

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

const string PRG = string(STR(PROG)).substr(2);

const string INFILE = PRG + ".in";
const string OUTFILE = PRG + ".out";

int N;
char S[100][100];
char T[100][100];

char tmp[100][100];

int goRot() {
	bool good;
	good = true;
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) 
		if(S[i][j] != T[j][N - 1 - i]) good = false;
	if(good) return 1;
	good = true;
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) 
		if(S[i][j] != T[N - 1 - i][N - 1 - j]) good = false;
	if(good) return 2;
	good = true;
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) 
		if(S[i][j] != T[N - 1 - j][i]) good = false;
	if(good) return 3;
	return 0;
}

int go() {
	int v = goRot();
	if(v > 0) return v;
	bool good;
	good = true;
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) 
		if(S[i][j] != T[i][N - 1 - j]) good = false;
	if(good) return 4;
	for(int i = 0; i < N; i++) for(int j = 0; j < N - 1 - j; j++) 
		swap(S[i][j], S[i][N - 1 - j]);
	if(goRot()) return 5;
	for(int i = 0; i < N; i++) for(int j = 0; j < N - 1 - j; j++) 
		swap(S[i][j], S[i][N - 1 - j]);
	good = true;
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) 
		if(S[i][j] != T[i][j]) good = false;
	if(good) return 6;
	return 7;
}

int main() {
	if(fopen(INFILE.c_str(), "r")) {
		freopen(INFILE.c_str(), "r", stdin);
		freopen(OUTFILE.c_str(), "w", stdout);
	}

	cin >> N;
	for(int i = 0; i < N; i++) {
		cin >> S[i];
	}
	for(int i = 0; i < N; i++) {
		cin >> T[i];
	}


	cout << go() << '\n';
	return 0;
}
