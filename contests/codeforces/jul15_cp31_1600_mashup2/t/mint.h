const ll MOD = 1e9 + 7;
struct mint {
    ll x;
    mint(ll _ = 0) : x((_ % MOD + MOD) % MOD) {}
    mint operator+(const mint& b) { return mint(x + b.x >= MOD ? x + b.x - MOD : x + b.x); }
    mint operator-(const mint& b) { return mint(x - b.x < 0 ? x - b.x + MOD : x - b.x); }
    mint operator*(const mint& b) { return mint((x * b.x) % MOD); }
    mint operator/(const mint& b) { return *this * invert(b); }
    static mint invert(const mint& a) {
        ll x, y, g = euclid(a.x, MOD, x, y);
        assert(g == 1); return mint((x + MOD) % MOD);
    }
    mint operator^(ll e) {
        if (!e) return mint(1);
        mint r = *this ^ (e / 2); r = r * r;
        return e & 1 ? *this * r : r;
    }
};