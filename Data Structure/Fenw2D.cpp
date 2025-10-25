template <typename T>
class Fenwick2D {
public:
    int n, m;
    vector<vector<T>> a;

    Fenwick2D(int n = 0, int m = 0) {
        init(n, m);
    }

    void init(int n, int m) {
        this->n = n;
        this->m = m;
        a.assign(n, vector<T>(m, T()));
    }

    // Optimized O(n*m) build from 2D array
    Fenwick2D(const vector<vector<T>>& b) : Fenwick2D((int)b.size(), (int)(b.empty() ? 0 : b[0].size())) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] += b[i][j];
                int ni = i | (i + 1);
                int nj = j | (j + 1);
                if (ni < n) a[ni][j] += a[i][j];
                if (nj < m) a[i][nj] += a[i][j];
                if (ni < n && nj < m) a[ni][nj] -= a[i][j];
            }
        }
    }

    // Point update: a[x][y] += v
    void PointUpdate(int x, int y, T v) {
        assert(0 <= x && x < n && 0 <= y && y < m);
        for (int i = x + 1; i <= n; i += i & -i) {
            for (int j = y + 1; j <= m; j += j & -j) {
                a[i - 1][j - 1] += v;
            }
        }
    }

    // Prefix sum from (0,0) to (x,y), exclusive
    // Sum over [0,x) x [0,y)
    T PrefixQuery(int x, int y) {
        assert(0 <= x && x <= n && 0 <= y && y <= m);
        T res = T();
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                res += a[i - 1][j - 1];
            }
        }
        return res;
    }

    // Rectangle sum over [x1, y1) x [x2, y2) (exclusive)
    T RectangleQuery(int x1, int y1, int x2, int y2) {
        assert(0 <= x1 && x1 <= x2 && x2 <= n);
        assert(0 <= y1 && y1 <= y2 && y2 <= m);
        return PrefixQuery(x2, y2) - PrefixQuery(x1, y2) - PrefixQuery(x2, y1) + PrefixQuery(x1, y1);
    }

    // Optional: get value at (x, y)
    T PointQuery(int x, int y) {
        return RectangleQuery(x, y, x + 1, y + 1);
    }
};
