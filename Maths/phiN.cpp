vector<int> phi;
void phiN(int n) {
    phi.assign(n + 1);
    ranges::iota(phi, 0);

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
}
