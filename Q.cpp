#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1000000;
int parent[maxn];

int find_set(int x) {
    if (x == parent[x])
        return x;
    return parent[x] = find_set(parent[x]);
}

int main() {
    int n;
    cin >> n;

    vector<pair<long long, pair<int, int>>> edge_list;
    vector<int> data(n+1);
    for (int i = 0; i <= n; i++) {
        data[i] = i;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long w;
            cin >> w;
            if (i > j) {
                edge_list.emplace_back(make_pair(w, make_pair(i, j)));
            }
        }
    }

    for (int i = 0; i < n; i++) {
        long long w;
        cin >> w;
        edge_list.emplace_back(make_pair(w, make_pair(i, n)));
    }

    long long min = 0;

    sort(edge_list.begin(), edge_list.end(), [](const pair<long long, pair<int, int>> &e1, const pair<long long, pair<int, int>> &e2){
        return e1.first < e2.first;
    });

    for (auto i: edge_list) {
        if(data[i.second.second] != data[i.second.first]) {
            min += i.first;
            int t = data[i.second.first];
            for (int j = 0; j <= n; j++) {
                if (data[j] == t) {
                    data[j] = data[i.second.second];
                }
            }
        }
    }

    cout << min;

    return 0;
}