#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1000000;
int parent[maxn];
int ranks[maxn];


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
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, pair<int, int>>> adj_list;

    for (int i = 0; i < m; i++) {
        int vertex1, vertex2, w;
        cin >> vertex1 >> vertex2 >> w;
        vertex1--;
        vertex2--;
        adj_list.emplace_back(make_pair(w, make_pair(vertex1, vertex2)));
    }

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int result = 0;
    sort(adj_list.begin(), adj_list.end(), [](const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) {
        if (a.first < b.first) {
            return true;
        } else return false;
    });

    for (int i = 0; i < m; i++) {
        if (find_set(adj_list[i].second.first) != find_set(adj_list[i].second.second)) {
            result += adj_list[i].first;
            union_sets(adj_list[i].second.first, adj_list[i].second.second);
        }
    }

    cout << result;

    return 0;
}