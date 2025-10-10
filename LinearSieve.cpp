template <typename T>
vector<T> LinearSieve(T n) {
    vector<T> lp(n + 1); //gives the smalles prime factor for every element
    vector<T> pr;
    T counter = 0;
    for (T i = 2; i <= n; ++i) {
        if (lp[i] == 0){
            lp[i] = i;
            pr.push_back(i);
        }
        for (T j = 0; i * pr[j] <= n; ++j) {
            counter++;
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    // return pr;
    return lp;
}