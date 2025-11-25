// only use for idempotent functions like min, max, gcd, etc.
// also the query gives the ans for [l,,,r] (inclusive)
template <typename T, typename F>
class SparseTable {
public:
    int n;
    vector<vector<T>> table;
    F func;

    SparseTable(const vector<T> &a, const F &f) : n(static_cast<int>(a.size())), func(f) {
        int mxLg = __lg(n) + 1;
        table.resize(mxLg);
        table[0] = a;
        for (int j = 1; j < mxLg; j++) {
            table[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                table[j][i] = func(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) const {
        assert(0 <= l && l <= r && r <= n - 1);
        int lg = __lg(r - l + 1);
        return func(table[lg][l], table[lg][r - (1 << lg) + 1]);
    }
};
