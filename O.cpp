#include <iostream>
#include <vector>

using namespace std;

const int maxn = 1000000;
int parent[maxn];
int ranks[maxn];
int weight[maxn];


int find_set(int x) {
    if (x == parent[x])
        return x;
    return parent[x] = find_set(parent[x]);
}

void union_sets(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
        if (ranks[x] < ranks[y])
            swap(x, y);
        parent[y] = x;
        if (ranks[x] == ranks[y]) {
            ranks[x]++;
        }
        weight[x] += weight[y];
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    int flag, x, y, w;
    for (int i = 0; i < m; i++) {
        cin >> flag;
        if (flag == 1) {
            cin >> x >> y >> w;
            x--;
            y--;
            union_sets(x, y);
            x = find_set(x);
            weight[x] += w;
        } else {
            cin >> x;
            x--;
            cout << weight[find_set(x)] << "\n";
        }
    }

    return 0;

}