template <typename F>
int max_right(int v, int l, int r, int x, int y, F pred, Info& sum) {
    if (l >= y || r <= x) {
        return y;
    }
    if (x <= l && r <= y) {
        Info new_sum = sum + info[v];
        if (pred(new_sum)) {
            sum = new_sum;
            return r;
        }
    }
    if (r - l == 1) {
        return l;
    }
    int m = (l + r) / 2;
    int res = max_right(2 * v, l, m, x, y, pred, sum);
    if (res < m) {
        return res;
    }
    return max_right(2 * v + 1, m, r, x, y, pred, sum);
}

template <typename F>
int max_right(int l, int r, F pred) {
    assert(0 <= l && l <= r && r <= n);
    Info sum;
    return max_right(1, 0, n, l, r, pred, sum);
}

template <typename F>
int min_left(int v, int l, int r, int x, int y, F pred, Info& sum) {
    if (l >= y || r <= x) {
        return x;
    }
    if (x <= l && r <= y) {
        Info new_sum = info[v] + sum;
        if (pred(new_sum)) {
            sum = new_sum;
            return l;
        }
    }
    if (r - l == 1) {
        return r;
    }
    int m = (l + r) / 2;
    int res = min_left(2 * v + 1, m, r, x, y, pred, sum);
    if (res > m) {
        return res;
    }
    return min_left(2 * v, l, m, x, y, pred, sum);
}

template <typename F>
int min_left(int l, int r, F pred) {
    assert(0 <= l && l <= r && r <= n);
    Info sum;
    return min_left(1, 0, n, l, r, pred, sum);
}

