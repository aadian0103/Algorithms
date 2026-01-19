template <typename Mint>
constexpr Mint power(Mint a, int64_t b) {
    assert(b >= 0);
    Mint res = 1;
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template <int id, typename T, typename U>
class Montgomery {
public:
    using Mint = Montgomery;
    inline static T m, r, n2;
    static constexpr int W = std::numeric_limits<T>::digits;

    static void set_mod(T mod) {
        assert(mod & 1 && mod <= T(1) << (W - 2));
        m = mod, n2 = -U(m) % m, r = m;
        for (int i = 0; i < 5; i++) {
            r *= 2 - m * r;
        }
        r = -r;
        assert(r * m == T(-1));
    }

    static inline T reduce(U b) { return (b + U(T(b) * r) * m) >> W; }
    static constexpr T mod() { return m; }
    static T normalize(T v) { return v >= m ? v - m : v; }

    Montgomery() : x(0) {}
    Montgomery(T v) : x(reduce(U(v) * n2)) {}


    constexpr T val() const { return normalize(reduce(x)); }
    const T operator()() const { return val(); }
    template <typename V> explicit operator V() const { return (V)val(); }
    Mint inv() const { return power(*this, mod() - 2); }

    constexpr Mint operator-() const { Mint res; res.x = x ? m - x : 0; return res; }
    constexpr Mint& operator++() { return *this += 1; }
    constexpr Mint& operator--() { return *this -= 1; }
    constexpr Mint operator++(int) { Mint result(*this); *this += 1; return result; }
    constexpr Mint operator--(int) { Mint result(*this); *this -= 1; return result; }

    constexpr Mint& operator+=(const Mint& other) { x = ((x += other.x) >= m ? x - m : x); return *this; }
    constexpr Mint& operator-=(const Mint& other) { x -= (x >= other.x ? other.x : other.x - m); return *this; }
    template <typename V> Mint& operator+=(const V& other) { return *this += Mint(other); }
    template <typename V> Mint& operator-=(const V& other) { return *this -= Mint(other); }

    constexpr Mint& operator*=(const Mint& other) { x = reduce(U(x) * other.x); return *this; }
    constexpr Mint& operator/=(const Mint& other) { return *this *= other.inv(); }

    friend constexpr bool operator==(const Mint& lhs, const Mint& rhs) { return lhs.val() == rhs.val(); }
    template <typename V> friend constexpr bool operator==(const Mint& lhs, V rhs) { return lhs == Mint(rhs); }
    template <typename V> friend constexpr bool operator==(V lhs, const Mint& rhs) { return Mint(lhs) == rhs; }

    friend constexpr std::strong_ordering operator<=>(const Mint& lhs, const Mint& rhs) { return lhs.val() <=> rhs.val(); }
    template <typename V> friend constexpr std::strong_ordering operator<=>(const Mint& lhs, V rhs) {  return lhs.val() <=> Mint(rhs).val(); }
    template <typename V> friend constexpr std::strong_ordering operator<=>(V lhs, const Mint& rhs) { return Mint(lhs).val() <=> rhs.val(); }

    constexpr friend Mint operator+(Mint lhs, const Mint& rhs) { return lhs += rhs; }
    template <typename V> friend constexpr Mint operator+(Mint lhs, const V& rhs) { return lhs += rhs; }
    template <typename V> friend constexpr Mint operator+(const V& lhs, Mint rhs) { return rhs += lhs; }

    constexpr friend Mint operator-(Mint lhs, const Mint& rhs) { return lhs -= rhs; }
    template <typename V> friend constexpr Mint operator-(Mint lhs, const V& rhs) { return lhs -= rhs; }
    template <typename V> friend constexpr Mint operator-(const V& lhs, Mint rhs) { return Mint(lhs) -= rhs; }

    constexpr friend Mint operator*(Mint lhs, const Mint& rhs) { return lhs *= rhs; }
    template <typename V> friend constexpr Mint operator*(Mint lhs, const V& rhs) { return lhs *= rhs; }
    template <typename V> friend constexpr Mint operator*(const V& lhs, Mint rhs) { return rhs *= lhs; }

    constexpr friend Mint operator/(Mint lhs, const Mint& rhs) { return lhs /= rhs; }
    template <typename V> friend constexpr Mint operator/(Mint lhs, const V& rhs) { return lhs /= rhs; }
    template <typename V> friend constexpr Mint operator/(const V& lhs, Mint rhs) { return Mint(lhs) /= rhs; }

    constexpr friend std::ostream& operator<<(std::ostream& stream, const Mint& number) { return stream << number(); }
    template <typename V> friend V& operator>>(V& stream, Mint& number) {
        T v;
        stream >> v;
        number = Mint(v);
        return stream;
    }

    constexpr friend T abs(const Mint& a) { return a.val(); }
    constexpr bool is_zero() const { return x == 0; }

private:
    T x;
};

template <int id>
using Montgomery_32 = Montgomery<id, uint32_t, uint64_t>;
template <int id>
using Montgomery_64 = Montgomery<id, uint64_t, __uint128_t>;

using mint2 = Montgomery_32<0>;
using mint = Montgomery_64<0>;

