template <typename T>
T binpow(T a, T b) {
    T ans = 1;
    while (b) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}
