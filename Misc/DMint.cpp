template <typename T>
constexpr T power(T a, int64_t b, T res = 1) {
    assert(b >= 0);
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

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

class Barrett {
public:
    Barrett(int32_t m_) : m(m_), im((int64_t)(-1) / m_ + 1) {}
 
    constexpr int32_t mod() const { return m; }

    constexpr int32_t mul(int32_t a, int32_t b) const {
        int64_t z = a;
        z *= b;

        int64_t x = int64_t((__int128_t(z) * im) >> 64);
        int32_t v = int32_t(z - x * m);
        if (m <= v) {
            v += m;
        }

        return v;
    }
 
private:
    int32_t m;
    int64_t im;
};

template <typename T>
class DMint {
public:
    using Type = typename decay<decltype(T::value)>::type;

    constexpr DMint() : value() {}
    template <typename U>
    DMint(const U& x) { value = normalize(x); }

    template <typename U>
    static Type normalize(const U& x) {
        Type v;
        if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
        else v = static_cast<Type>(x % mod());
        if (v < 0) v += mod();
        return v;
    }

    const Type& operator()() const { return value; }
    template <typename U> explicit operator U() const { return static_cast<U>(value); }
    static void setMod(int32_t m) { bt = m; }
    constexpr static Type mod() { return bt.mod(); }

    constexpr DMint operator-() const { return DMint(-value); }
    constexpr DMint& operator++() { return *this += 1; }
    constexpr DMint& operator--() { return *this -= 1; }
    constexpr DMint operator++(int) { DMint result(*this); *this += 1; return result; }
    constexpr DMint operator--(int) { DMint result(*this); *this -= 1; return result; }

    constexpr DMint& operator+=(const DMint& other) { value += other.value; value -= (value >= mod()) * mod(); return *this; }
    constexpr DMint& operator-=(const DMint& other) { value -= other.value; value += (value < 0) * mod(); return *this; }
    template <typename U> DMint& operator+=(const U& other) { return *this += DMint(other); }
    template <typename U> DMint& operator-=(const U& other) { return *this -= DMint(other); }

    constexpr DMint& operator*=(const DMint& other) { value = normalize(bt.mul(value, other.value)); return *this; }
    constexpr DMint& operator/=(const DMint& other) { return *this *= DMint(inverse(other.value, bt.mod())); }

    friend constexpr bool operator==(const DMint& lhs, const DMint& rhs) { return lhs.value == rhs.value; }
    template <typename U> friend constexpr bool operator==(const DMint& lhs, U rhs) { return lhs == DMint(rhs); }
    template <typename U> friend constexpr bool operator==(U lhs, const DMint& rhs) { return DMint(lhs) == rhs; }

    friend constexpr std::strong_ordering operator<=>(const DMint& lhs, const DMint& rhs) { return lhs.value <=> rhs.value; }
    template <typename U> friend constexpr std::strong_ordering operator<=>(const DMint& lhs, U rhs) {  return lhs.value <=> DMint(rhs).value; }
    template <typename U> friend constexpr std::strong_ordering operator<=>(U lhs, const DMint& rhs) { return DMint(lhs).value <=> rhs.value; }

    constexpr friend DMint operator+(DMint lhs, const DMint& rhs) { return lhs += rhs; }
    template <typename U> friend constexpr DMint operator+(DMint lhs, const U& rhs) { return lhs += rhs; }
    template <typename U> friend constexpr DMint operator+(const U& lhs, DMint rhs) { return rhs += lhs; }

    constexpr friend DMint operator-(DMint lhs, const DMint& rhs) { return lhs -= rhs; }
    template <typename U> friend constexpr DMint operator-(DMint lhs, const U& rhs) { return lhs -= rhs; }
    template <typename U> friend constexpr DMint operator-(const U& lhs, DMint rhs) { return DMint(lhs) -= rhs; }

    constexpr friend DMint operator*(DMint lhs, const DMint& rhs) { return lhs *= rhs; }
    template <typename U> friend constexpr DMint operator*(DMint lhs, const U& rhs) { return lhs *= rhs; }
    template <typename U> friend constexpr DMint operator*(const U& lhs, DMint rhs) { return rhs *= lhs; }

    constexpr friend DMint operator/(DMint lhs, const DMint& rhs) { return lhs /= rhs; }
    template <typename U> friend constexpr DMint operator/(DMint lhs, const U& rhs) { return lhs /= rhs; }
    template <typename U> friend constexpr DMint operator/(const U& lhs, DMint rhs) { return DMint(lhs) /= rhs; }


    constexpr friend std::ostream& operator<<(std::ostream& stream, const DMint& number) { return stream << number(); }
    template <typename U> friend U& operator>>(U& stream, DMint& number) {
        typename common_type<Type, int64_t>::type x;
        stream >> x;
        number.value = normalize(x);
        return stream;
    }

    constexpr friend const Type& abs(const DMint& x) { return x.value; }
    constexpr bool is_zero() const { return value == 0; }
    constexpr DMint inv() const { return DMint(inverse(value, mod())); }

private:
    Type value;
    static Barrett bt;
};

template <typename T>
string to_string(const DMint<T>& number) {
    return to_string(number());
}

template <typename T> Barrett DMint<T>::bt = Barrett(998244353);

template<int32_t T> using DynamicMint32 = DMint<integral_constant<int32_t, T>>;
using dmint = DynamicMint32<1000000007>;

vector<dmint> fact(1, 1);
vector<dmint> inv_fact(1, 1);

dmint C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    while ((int) fact.size() < n + 1) {
        fact.emplace_back(fact.back() * (int) fact.size());
        inv_fact.emplace_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}
