mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());
template<typename T>
T rnd(T a, T b) {
    uniform_int_distribution<T> dist(a, b);
    return dist(RNG);
}
