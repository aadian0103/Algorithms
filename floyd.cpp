for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
        }
    }
}