template <typename T>
T dearrange(int n, bool mod = false) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    T prev2 = 0, prev1 = 1;
    for (int i = 3; i <= n; i++) {
        T curr = (i - 1) * (prev1 + prev2);
        prev2 = prev1;
        prev1 = mod ? curr % MOD : curr;
    }
    return prev1;
}