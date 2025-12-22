template <typename T>
T cdiv(T a, T b) {
    return a / b + ((a ^ b) > 0 && a % b);
}

template <typename T>
T fdiv(T a, T b) {
    return a / b - ((a ^ b) < 0 && a % b);
}

