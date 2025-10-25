vector<int> LinearSieve(int n) {
    vector<T> lp(n + 1); //gives the smallest prime factor for every element
    vector<T> pr;
    for (int i = 2; i <= n; i++) {
        if (lp[i] == 0){
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    return ${1 : lp};
}

