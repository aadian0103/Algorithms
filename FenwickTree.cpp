template <typename T>
class Fenwick {
public:
    int n;
    vector<T> a;

    Fenwick(int n = 0) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }

    // optimized build - O(n)
    Fenwick(const vector<T> &b) : Fenwick(b.size()) {
        for (int i = 0; i < n; i++) {
            a[i] += b[i];
            int r = i | (i + 1);
            if (r < n) {
                a[r] += a[i];
            }
        }
    }

    void PointUpdate(int x, T v) {
        assert(x >= 0 && x < n);
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }

    // gives prefix sum : [0,,,,i) (exclusive)
    // for prefix sum [l, r] : RangeQuery(r + 1) - RangeQuery(l)
    T RangeQuery(int x) {
        assert(x >= 0 && x <= n);
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }

    // Find smallest index(0 based) idx with prefix sum > k
    // change k > a[x + i - 1] for sum >= k
    // Returns n if no such index exists
    int kth(T k) {
        int x = 0;
        for (int i = 1 << __lg(n); i; i >>= 1) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }

    // RUPQ implementaion
    // add v to the range [l ,r) (exclusive) and find the value of some element
    void RangeUpdate(int l, int r, T v) {
        assert(l >= 0 && l <= r && r <= n);
        PointUpdate(l, v);
        if (r < n) {
            PointUpdate(r, -v);
        }
    }
    T PointQuery(int x) {
        assert(x >= 0 && x < n);
        return RangeQuery(x + 1) - RangeQuery(x);
    }
};

template <typename T>
class RURQ {
private:
    int n;
    Fenwick<T> a1, a2;

    void range_add(int l, int r, T v) {
        a1.PointUpdate(l, v);
        if (r < n) {
            a1.PointUpdate(r, -v);
        }
        a2.PointUpdate(l, v * (l - 1));
        if (r < n) {
            a2.PointUpdate(r, -v * (r - 1));
        }
    }

    // Sum of [0, x) (exclusive)
    T prefix_sum(int x) {
        return a1.RangeQuery(x) * (x - 1) - a2.RangeQuery(x);
    }

public:
    RURQ(int size) : n(size), a1(size), a2(size) {}

    RURQ(const vector<T> &a) : n((int)a.size()), a1(n), a2(n) {
        for (int i = 0; i < n; i++) {
            RangeUpdate(i, i + 1, a[i]);
        }
    }

    // Add v to range [l, r) (exclusive) and find the prefix sum in range [l, r) (exclusive)
    void RangeUpdate(int l, int r, T v) {
        assert(l >= 0 && l <= r && r <= n);
        range_add(l, r, v);
    }

    T RangeQuery(int l, int r) {
        assert(l >= 0 && l <= r && r <= n);
        return prefix_sum(r) - prefix_sum(l);
    }
};