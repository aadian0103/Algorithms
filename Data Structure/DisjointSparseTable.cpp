// Suitable Operations: Sum, Product, XOR (Any associative Operationss)
// query result : f[l...r)
template <typename T, typename F>
struct DisjointSparseTable {
    int n;
    F func;
    vector<vector<T>> table;

    DisjointSparseTable(const vector<T>& a, const F& f) : n(int(a.size())), func(f) {
        int lg = bit_width(unsigned(n));
        table.assign(lg, vector<T>(n));
        table[0] = a;
        for(int p = 1, len = 1; p < lg; p++, len <<= 1) {
            for(int mid = len; mid < n; mid += len << 1) {
                table[p][mid - 1] = a[mid - 1];
                for(int j = mid - 2; j >= mid - len; j--) {
                    table[p][j] = f(a[j], table[p][j + 1]);
                }
                if(mid < n) {
                    table[p][mid] = a[mid];
                    for(int j = mid + 1; j < min(n, mid + len); j++) {
                        table[p][j] = f(table[p][j - 1], a[j]);
                    }
                }
            }
        }
    }

    T query(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        if (r - l == 1) return table[0][l];
        int p = bit_width(unsigned(l ^ (r - 1))) - 1;
        return func(table[p][l], table[p][r - 1]);
    }
};
