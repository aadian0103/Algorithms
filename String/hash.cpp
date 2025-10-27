struct Hash {
    static constexpr uint64_t MOD = (1ULL << 61) - 1;
    inline static uint64_t base = [] {
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        return (MOD >> 2) + (rng() % (MOD >> 1));
    }();

    inline static vector<uint64_t> pw = {1};
    vector<uint64_t> pref;
    int n = 0;

    static constexpr uint64_t addmod(uint64_t a, uint64_t b) noexcept {
        a += b;
        if (a >= MOD) a -= MOD;
        return a;
    }

    static constexpr uint64_t submod(uint64_t a, uint64_t b) noexcept {
        a += MOD - b;
        if (a >= MOD) a -= MOD;
        return a;
    }

    static constexpr uint64_t mulmod(uint64_t a, uint64_t b) noexcept {
        __uint128_t z = (__uint128_t)a * b;
        uint64_t low = (uint64_t)z & MOD, high = (uint64_t)(z >> 61);
        uint64_t res = low + high;
        if (res >= MOD) res -= MOD;
        return res;
    }

    static void compute_pw(int sz) {
        int cur = (int)pw.size();
        if (cur < sz) {
            pw.resize(sz);
            for (int i = cur; i < sz; i++) {
                pw[i] = mulmod(pw[i - 1], base);
            }
        }
    }

    template <typename T>
    explicit Hash(const T& s) {
        n = (int)s.size();
        compute_pw(n + 1);
        pref.resize(n + 1);
        pref[0] = 1;
        for (int i = 0; i < n; i++) {
            pref[i + 1] = addmod(mulmod(pref[i], base), (uint64_t)s[i]);
        }
    }

    uint64_t operator()(int l, int r) const noexcept {
        assert(0 <= l && l <= r && r < n);
        uint64_t res = submod(pref[r + 1], mulmod(pref[l], pw[r - l + 1]));
        return res;
    }
};
