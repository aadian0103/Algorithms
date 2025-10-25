bool cmp(const pair<int,int> &a, const pair<int,int> &b) {
    if (a.first == b.first) {
        return a.second > b.second; // Sort by second value in descending order if first values are equal
    }
    return a.first < b.first; // Sort by first value in ascending order
}
