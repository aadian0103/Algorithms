// kahn's algorithm to find the topological order of DAG for any random order
// to find lex smallest replace queue with priority queue (priority_queue<int, vector<int>, greater<int>>)
queue<int> pq;
vector<int> res;
for (int i = 0; i < n; i++) {
    if (deg[i] == 0) {
        pq.push(i);
    }
}
while (!pq.empty()) {
    int u = pq.front(); pq.pop();
    res.pb(u);
    for (auto v : g[u]) {
        if (--deg[v] == 0) {
            pq.push(v);
        }
    }
}
if ((int) res.size() < n) {
    cout << "NOT A DAG" << nl;
}
