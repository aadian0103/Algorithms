template <typename T>
vector<vector<T>> operator*(const vector<vector<T>>& a, const vector<vector<T>>& b) {
    if (a.empty() || b.empty()) {
        return {{}};
    }

    vector<vector<T>> c(a.size(), vector<T>(b[0].size()));
    for (int i = 0; i < (int)(c.size()); i++) {
        for (int j = 0; j < (int)(c[0].size()); j++) {
            for (int k = 0; k < (int)(b.size()); k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

template <typename T>
vector<vector<T>>& operator*=(vector<vector<T>>& a, const vector<vector<T>>& b) {
    return a = a * b;
}

template <typename T, typename U>
vector<vector<T>> power(const vector<vector<T>>& a, const U& b) {
    assert(b >= 0);

    vector<U> bits;
    U b1 = b;
    while (b1 > 0) {
        bits.push_back(b1 & 1);
        b1 >>= 1;
    }

    vector<vector<T>> ans(a.size(), vector<T>(a.size()));
    for (int i = 0; i < (int)(a.size()); i++) {
        ans[i][i] = 1;
    }

    for (int i = (int)(bits.size() - 1); i >= 0; i--) {
        ans *= ans;
        if (bits[i]) ans *= a;
    }

    return ans;
}
