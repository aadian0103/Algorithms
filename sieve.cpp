vector<bool> sieve(n, false);
sieve[0] = sieve[1] = true;
for (int i = 2; i <= n; i++) {
    if (sieve[i]) {
        for (int j = i * i; j <= n; j++) {
            sieve[j] = false;
        }
    }
}