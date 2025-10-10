// only use for idempotent functions like min, max, gcd, etc.
// also the query gives the ans for [l,,,r] (inclusive)
template <typename T>
class SparseTable {
public:
    int n;
    vector<vector<T>> table;

    T func(const T &a, const T &b) const {
        return min(a, b);
    }
    SparseTable(const vector<T> &a) : n((int)a.size()) {
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
    T Query(const int l, const int r) const {
        assert(l >= 0 && l <= r && r <= n - 1);
        int lg = __lg(r - l + 1);
        return func(table[lg][l], table[lg][r - (1 << lg) + 1]);
    }
};