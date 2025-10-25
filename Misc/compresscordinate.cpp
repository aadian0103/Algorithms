vector<int> c = a;
ranges::sort(c);
c.erase(unique(c.begin(), c.end()), c.end());
for (int i = 0; i < n; i++) {
    a[i] = ranges::lower_bound(c, a[i]) - c.begin();
}
//original value of a[i] can be obtained through c[a[i]]
