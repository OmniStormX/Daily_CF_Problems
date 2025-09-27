#include <bits/stdc++.h>
using i64 = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
#define MultiCases()   int t = 1; std::cin >> t; while(t--) 
#define SingleCase()   int t = 1; while(t--) 
#define dbg(x)  std::cerr << #x << " = " << x << "\n"
class Graphic {
public:
    struct edge {
        int v;
        int cost;
        edge(int v = 0, int cost = 0) : v(v), cost(cost)
        {
        }
    };

    std::vector<std::vector<edge>> e;
    std::vector<int> color;
    std::vector<int> vis;

    Graphic(int n) : e(n + 1, std::vector<edge>())
    {
    }

    void addEdge(int u, int v, int cost = 0, bool f = 0) {
        e[u].push_back({v, cost});
        if (!f) e[v].push_back({u, cost});
    }

    void initDinic() {
        color = std::vector<int>(e.size(), 0);
        vis = std::vector<int>(e.size(), 0);
    }

    bool dinic(int u, int col) {
        if (vis[u] == col) return false;
        vis[u] = col;
        for (auto [v, c] : e[u]) {
            if (color[v] == 0 || dinic(color[v], col)) {
                color[v] = u;
                return true;
            }
        }
        return false;
    }
};


void solve() {
    int A, B, C, K;
    std::cin >> A >> B >> C >> K;

    auto f = [&](int x, int y, int z) {
        return (x - 1) * B * C + (y - 1) * C + z - 1;
    };

    std::set<int> p;
    for (int i = 0; i < K; i++) {
        int x, y, z;
        std::cin >> x >> y >> z;
        p.insert(f(x, y, z));
    }

    

    Graphic g(f(A, B, C));
    g.initDinic();

    std::vector<std::tuple<int, int, int>> d1 = {
        {1, 2, 0}, {-1, 2, 0}, {1, -2, 0}, {-1, -2, 0}, 
        {2, 1, 0}, {-2, 1, 0}, {2, -1, 0}, {-2, -1, 0}, 
        {0, 1, 2}, {0, -1, 2}, {0, 1, -2}, {0, -1, -2}, 
        {0, 2, 1}, {0, -2, 1}, {0, 2, -1}, {0, -2, -1}, 
        {1, 0, 2}, {-1, 0, 2}, {1, 0, -2}, {-1, 0, -2}, 
        {2, 0, 1}, {-2, 0, 1}, {2, 0, -1}, {-2, 0, -1},
    };

    std::vector<int> U;

    int N = 0;
    for (int i = 1; i <= A; i++) {
            for (int j = 1; j <= B; j++) {
                for (int k = 1; k <= C; k++) {
                    int cur = f(i, j, k);
                    
                    if (p.count(cur)) continue;
                    N++;

                    if ((i + j + k) % 2 == 0) {
                        U.push_back(cur);
                        for (auto [x1, y1, z1] : d1) {
                            int x = i + x1, y = j + y1, z = k + z1;
                            int nxt = f(x, y, z);
                            
                            if (x > 0 && x <= A && 
                                y > 0 && y <= B && 
                                z > 0 && z <= C && 
                                !p.count(nxt)
                            ) {
                                g.addEdge(cur, nxt, 0, 1);
                            }
                        }
                    }
                }
            }
        }


    int M = 0; 
    int ans = 0;
    for (int u : U) {
        g.dinic(u, u);
    }

    for (int u : U) {
        if (g.color[u] == 0) {
            ans++;
        }
    }
    int max = N - M;
    std::cout << ans << "\n";
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    SingleCase()
        solve();
    return 0;
}
