
int ask(int x, int y) {
    std::cout << "? "<< x + 1 << " " << y << std::endl;
    std::string c;
    std::cin >> c;
    if (c == "=") return 0;
    else if (c == ">") return -1;
    return 1;
}
 
void solve() {
    int n;
    std::cin >> n;
    i64 l = 1;
    std::vector<i64> a(n);

    int p = 0;
    while (p < n) {
        int t = ask(p, l);
        while (t != 0) {
            t = ask(p, ++l);
        }
        a[p++] = l;
    }

    std::cout << "! ";
    for (int i = 0; i < n; i++) std::cout << a[i] << " \n"[i == n - 1];
}
