mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
T rnd(T a, T b) {
    uniform_int_distribution<T> dist(a, b);
    return dist(RNG);
}

namespace factorize {

    template <typename T>
    T gcd(T a, T b) {
        while (a) {
            b %= a;
            swap(a, b);
        }
        return b;
    }

    template <typename T>
    T mul_mod(T a, T b, T mod) {
        return (T)((__uint128_t)a * b % mod);
    }

    template <typename T>
    T power(T a, T b, T mod) {
        T res = 1;
        while (b) {
            if (b & 1) res = mul_mod(res, a, mod);
            a = mul_mod(a, a, mod);
            b >>= 1;
        }
        return res;
    }

    vector<int> pr, lp;
    int done = 1;

    void linear_sieve(int n) {
        assert(n >= 1);
        lp.assign(n + 1, 0);
        pr.clear();

        for (int i = 2; i <= n; i++) {
            if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back(i);
            }

            for (int x : pr) {
                if (x > lp[i] || i * x > n) break;
                lp[i * x] = x;
            }
        }

        done = n;
    }

    void sieve(int n) {
        assert(n >= 1);
        lp.assign(n + 1, 0);

        for (int i = 2; i * i <= n; i++) {
            if (lp[i] == 0) {
                for (int j = i * i; j <= n; j += i) {
                    if (lp[j] == 0) lp[j] = i;
                }
            }
        }

        pr.clear();
        for (int i = 2; i <= n; i++) {
            if (lp[i] == 0) {
                lp[i] = i;
                pr.push_back(i);
            }
        }

        done = n;
    }

    void run_sieve(int n) {
        linear_sieve(n);
    }

    template <typename T>
    bool is_prime(T n, const vector<T>& bases) {
        if (n < 2) return false;
        if (n <= done) return lp[n] == n;

        for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}) {
            if (n % p == 0) {
                return n == p;
            }
        }
        if (n < 31 * 31) return true;

        const int s = __builtin_ctzll(n - 1);
        const T d = (n - 1) >> s;

        for (T a : bases) {
            if (a % n == 0) continue;

            T x = power(a, d, n);
            if (x == 1 || x == n - 1) continue;

            bool witness = true;
            for (int r = 1; r < s; r++) {
                x = mul_mod(x, x, n);
                if (x == n - 1) {
                    witness = false;
                    break;
                }
            }

            if (witness) return false;
        }

        return true;
    }

    bool is_prime(int64_t n) {
        return is_prime<int64_t>(n, vector<int64_t>{2, 325, 9375, 28178, 450775, 9780504, 1795265022});
    }

    bool is_prime(int32_t n) {
        return is_prime<int32_t>(n, vector<int32_t>{2, 7, 61});
    }

    template<typename T>
    T rho(T n) {
        if (n % 2 == 0) return 2;

        T y = rnd(T(1), n - 1);
        T c = rnd(T(1), n - 1);
        T g = 1, r = 1, q = 1, x, ys;

        auto f = [&](T z) { return (mul_mod(z, z, n) + c) % n; };

        while (g == 1) {
            x = y;
            for (T i = 0; i < r; i++) y = f(y);

            T k = 0, m = 128;
            while (k < r && g == 1) {
                ys = y;
                T mn = min(m, r - k);

                for (T i = 0; i < mn; i++) {
                    y = f(y);
                    q = mul_mod(q, abs(x - y), n);
                }

                g = gcd(q, n);
                k += m;
            }
            r *= 2;
        }

        if (g == n) {
            do {
                ys = f(ys);
                g = gcd(abs(x - ys), n);
            } while (g == 1);
        }

        return g;
    }

    template<typename T>
    void factors(T n, vector<T>& res) {
        if (n <= 1) return;

        if (n <= done) {
            while (n > 1) {
                int p = lp[n], cnt = 0;
                for (; lp[n] == p; n /= p) cnt++;
                for (int i = 0; i < cnt; i++) res.push_back(p);
            }
            return;
        }

        if (is_prime(n)) {
            res.push_back(n);
            return;
        }

        T d = rho(n);
        factors(d, res);
        factors(n / d, res);
    }

    template<typename T>
    vector<T> factors(T n) {
        vector<T> res;
        factors(n, res);
        ranges::sort(res);
        return res;
    }

    template<typename T>
    vector<pair<T,int>> Factorize(T n) {
        vector<T> f = factors(n);
        vector<pair<T,int>> res;
        for (T x : f) {
            if (res.empty() || res.back().first != x) res.emplace_back(x, 1);
            else res.back().second++;
        }

        return res;
    }

    template <typename T>
    vector<T> divisors(const vector<pair<T,int>>& factors) {
        vector<T> res = {1};
        for (auto& [p, c] : factors) {
            int sz = (int)res.size();
            for (int i = 0; i < sz; i++) {
                T cur = res[i];
                for (int j = 0; j < c; j++) {
                    cur *= p;
                    res.push_back(cur);
                }
            }
        }
        ranges::sort(res);
        return res;
    }

}

