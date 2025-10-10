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
        if(x != y) {
            if(rank[x] > rank[y]) {
                swap(x, y);
            }
            p[x] = y;
            if(rank[x] == rank[y]) {
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