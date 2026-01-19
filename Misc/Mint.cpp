template <typename T>
constexpr T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <int32_t P>
constexpr int32_t mul_mod(int32_t a, int32_t b) {
    return (int32_t)(int64_t(a) * b % P);
}

template <int64_t P>
constexpr int64_t mul_mod(int64_t a, int64_t b) {
    return (int64_t)(__int128_t(a) * b % P);
}

template <typename T>
class Mint {
public:
    using Type = typename decay<decltype(T::value)>::type;

    constexpr Mint() : value() {}
    template <typename U>
    Mint(const U& x) { value = normalize(x); }

    template <typename U>
    constexpr static Type normalize(const U& x) {
        Type v;
        if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
        else v = static_cast<Type>(x % mod());
        if (v < 0) v += mod();
        return v;
    }

    const Type& operator()() const { return value; }
    template <typename U> explicit operator U() const { return static_cast<U>(value); }
    constexpr static Type mod() { return T::value; }

    constexpr Mint operator-() const { return Mint(-value); }
    constexpr Mint& operator++() { return *this += 1; }
    constexpr Mint& operator--() { return *this -= 1; }
    constexpr Mint operator++(int) { Mint result(*this); *this += 1; return result; }
    constexpr Mint operator--(int) { Mint result(*this); *this -= 1; return result; }

    constexpr Mint& operator+=(const Mint& other) { value += other.value; value -= (value >= mod()) * mod(); return *this; }
    constexpr Mint& operator-=(const Mint& other) { value -= other.value; value += (value < 0) * mod(); return *this; }
    template <typename U> Mint& operator+=(const U& other) { return *this += Mint(other); }
    template <typename U> Mint& operator-=(const U& other) { return *this -= Mint(other); }

    constexpr Mint& operator*=(const Mint& other) { value = normalize(mul_mod<mod()>(value, other.value)); return *this; }
    constexpr Mint& operator/=(const Mint& other) { return *this *= Mint(inverse(other.value, mod())); }

    friend constexpr bool operator==(const Mint& lhs, const Mint& rhs) { return lhs.value == rhs.value; }
    template <typename U> friend constexpr bool operator==(const Mint& lhs, U rhs) { return lhs == Mint(rhs); }
    template <typename U> friend constexpr bool operator==(U lhs, const Mint& rhs) { return Mint(lhs) == rhs; }

    friend constexpr std::strong_ordering operator<=>(const Mint& lhs, const Mint& rhs) { return lhs.value <=> rhs.value; }
    template <typename U> friend constexpr std::strong_ordering operator<=>(const Mint& lhs, U rhs) {  return lhs.value <=> Mint(rhs).value; }
    template <typename U> friend constexpr std::strong_ordering operator<=>(U lhs, const Mint& rhs) { return Mint(lhs).value <=> rhs.value; }

    constexpr friend Mint operator+(Mint lhs, const Mint& rhs) { return lhs += rhs; }
    template <typename U> friend constexpr Mint operator+(Mint lhs, const U& rhs) { return lhs += rhs; }
    template <typename U> friend constexpr Mint operator+(const U& lhs, Mint rhs) { return rhs += lhs; }

    constexpr friend Mint operator-(Mint lhs, const Mint& rhs) { return lhs -= rhs; }
    template <typename U> friend constexpr Mint operator-(Mint lhs, const U& rhs) { return lhs -= rhs; }
    template <typename U> friend constexpr Mint operator-(const U& lhs, Mint rhs) { return Mint(lhs) -= rhs; }

    constexpr friend Mint operator*(Mint lhs, const Mint& rhs) { return lhs *= rhs; }
    template <typename U> friend constexpr Mint operator*(Mint lhs, const U& rhs) { return lhs *= rhs; }
    template <typename U> friend constexpr Mint operator*(const U& lhs, Mint rhs) { return rhs *= lhs; }

    constexpr friend Mint operator/(Mint lhs, const Mint& rhs) { return lhs /= rhs; }
    template <typename U> friend constexpr Mint operator/(Mint lhs, const U& rhs) { return lhs /= rhs; }
    template <typename U> friend constexpr Mint operator/(const U& lhs, Mint rhs) { return Mint(lhs) /= rhs; }

    constexpr friend std::ostream& operator<<(std::ostream& stream, const Mint& number) { return stream << number(); }
    template <typename U> friend U& operator>>(U& stream, Mint& number) {
        typename common_type<Type, int64_t>::type x;
        stream >> x;
        number.value = normalize(x);
        return stream;
    }

    constexpr friend const Type& abs(const Mint& x) { return x.value; }
    constexpr bool is_zero() const { return value == 0; }

private:
    Type value;
};

template <typename T>
constexpr Mint<T> power(Mint<T> a, int64_t b) {
    assert(b >= 0);
    Mint<T> res = 1;
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template <typename T>
string to_string(const Mint<T>& number) {
    return to_string(number());
}

template<int32_t T> using static_mint32 = Mint<integral_constant<int32_t, T>>;
template<int64_t T> using static_mint64 = Mint<integral_constant<int64_t, T>>;

using mint = static_mint32<1000000007>;
using mint2 = static_mint32<998244353>;
using big_mint = static_mint64<1000000000000000003ULL>;

vector<mint> fact(1, 1), inv_fact(1, 1);

mint C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    while ((int)fact.size() < n + 1) {
        fact.push_back(fact.back() * (int)fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}
