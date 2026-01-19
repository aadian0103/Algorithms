#include <ext/pb_ds/assoc_container.hpp>

struct Chash {
    static inline uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const noexcept {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return (size_t)splitmix64(x + FIXED_RANDOM);
    }

    template <typename A, typename B>
    size_t operator()(const pair<A, B> &p) const noexcept {
        uint64_t h1 = (*this)(p.first), h2 = (*this)(p.second);
        return (size_t)splitmix64(h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2)));
    }

    template <typename... Ts>
    size_t operator()(const tuple<Ts...>& t) const noexcept {
        size_t seed = 0;
        apply([&](const auto &... elems) {
            ((seed = (seed * 1315423911u) ^ (*this)(elems) ), ...);
        }, t);
        return (*this)(seed);
    }
};

template <typename K, typename V, typename Hash = Chash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = Chash>
using hash_set = HashMap<K, __gnu_pbds::null_type, Hash>;
