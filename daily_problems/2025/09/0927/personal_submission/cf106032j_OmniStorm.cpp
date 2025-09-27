#include <bits/stdc++.h>
using i64 = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
#define MultiCases()   int t = 1; std::cin >> t; while(t--) 
#define SingleCase()   int t = 1; while(t--) 

void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    std::vector<int> cnt(m + 1, 0), r(m + 1, 0);

    
    for (int i = 1; i <= n; i++) {
        cnt[a[i]]++;
    }
    for (int i = 1; i <= m; i++) if (cnt[i] & 1) {
        r[i] = i;
    }

    for (int i = m - 1; i > 0; i--) {
        if ((cnt[i] & 1) == 0) {
            r[i] = r[i + 1];
        }
    }

    if ((cnt[m] & 1) == 0) {
        int mm = m;
        while (mm && (cnt[mm] & 1) == 0) {
            r[mm] = r[mm % m + 1];
            mm--;
        }
    }


    int sum = 0;
    for (int i = 0; i < q; i++) {
        int op;
        std::cin >> op;
        if (op == 1) {
            sum++;
        } else {
            int x;
            std::cin >> x;
            x = a[x];
            if (sum == 0 || r[x] == x) {
                std::cout << x << "\n";
                continue;
            }

            if (r[x]) {
                int t = r[x] - x;
                if (t < 0) t += m;
                if (sum >= t) {
                    std::cout << r[x] << "\n";
                } else {
                    int ans = 1 + (x + sum - 1) % m;
                    std::cout << ans << "\n";
                }
            } else {
                int ans = 1 + (x + sum - 1) % m;
                std::cout << ans << "\n";
            }
        }
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    MultiCases()
        solve();
    return 0;
}
