// Suitable Operations: Min, Max, Gcd, Lcm, Bitwise AND, OR
// Any associative, idempotent function
// query result : f[l...r]
template <typename T, typename F>
struct SparseTable {
    int n;
    F func;
    vector<vector<T>> table;

    SparseTable(const vector<T>& a, const F& f) : n(int(a.size())), func(f) {
        int lg = bit_width(unsigned(n));
        table.resize(lg);
        table[0] = a;
        for (int j = 1, len = 1; j < lg; j++, len <<= 1) {
            table[j].resize(n - len * 2 + 1);
            for (int i = 0; i + 2 * len <= n; i++) {
                table[j][i] = func(table[j - 1][i], table[j - 1][i + len]);
            }
        }
    }

    T query(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        int lg = bit_width(unsigned(r - l + 1)) - 1;
        return func(table[lg][l], table[lg][r - (1 << lg) + 1]);
    }
};

// use from here
auto f = [](auto x, auto y) { return min(x, y); };
auto f = [](auto x, auto y) { return max(x, y); };
auto f = [](auto x, auto y) { return gcd(x, y); };
auto f = [](auto x, auto y) { return x & y; };
auto f = [](auto x, auto y) { return x | y; };
