class dsu {
public:
    vector<int> p, rank, setsize;
    int n;
    int numset;

    dsu(int _n) : n(_n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        rank.resize(n, 0);
        setsize.assign(n, 1);
        numset = n;
    }

    int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }

    bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            if (rank[x] > rank[y]) {
                swap(x, y);
            }
            p[x] = y;
            if (rank[x] == rank[y]) {
                ++rank[y];
            }
            setsize[y] += setsize[x];
            numset--;
            return true;
        }
        return false;
    }

    int numDisSet() {
        return numset;
    }

    int sizeOfSet(int x) {
        return setsize[get(x)];
    }
};

vector<int> order(m);
iota(order.begin(), order.end(), 0);
sort(order.begin(), order.end(), [&](int a, int b) {
    return edges[a][2] < edges[b][2];
});
vector<int> ans_id;
dsu d(n);
ll ans = 0;
for (auto i : order) {
    int u = edges[i][0], v = edges[i][1], c = edges[i][2];
    if (d.unite(u, v)) {
        ans += c;
        ans_id.push_back(i);
        if ((int)ans_id.size() == n - 1) break;
    }
}

