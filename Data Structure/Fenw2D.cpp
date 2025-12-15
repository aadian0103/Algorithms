template <typename T>
class Fenwick2D {
public:
    int n, m;
    vector<vector<T>> bit;

    constexpr Fenwick2D() noexcept : n(0), m(0) {}
    explicit Fenwick2D(int n, int m) : n(n), m(m), bit(n, vector<T>(m, T{})) {}

    Fenwick2D(const vector<vector<T>>& b) : Fenwick2D(int(b.size()), b.empty() ? 0 : int(b[0].size()))  {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                add(i, j, b[i][j]);
            }
        }
    }

    // Add v at (x, y)
    inline void add(int x, int y, T v) {
        assert(0 <= x && x < n && 0 <= y && y < m);
        for (int i = x + 1; i <= n; i += i & -i) {
            for (int j = y + 1; j <= m; j += j & -j) {
                a[i - 1][j - 1] += v;
            }
        }
    }

    // Prefix sum on [0, x) × [0, y)
    inline T sum(int x, int y) {
        assert(0 <= x && x <= n && 0 <= y && y <= m);
        T res = T();
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                res += a[i - 1][j - 1];
            }
        }
        return res;
    }

    // Rectangle sum over [x1, y1) x [x2, y2)
    inline T RectangleQuery(int x1, int y1, int x2, int y2) {
        assert(0 <= x1 && x1 <= x2 && x2 <= n);
        assert(0 <= y1 && y1 <= y2 && y2 <= m);
        return sum(x2, y2) - sum(x1, y2) - sum(x2, y1) + sum(x1, y1);
    }
};
