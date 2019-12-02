#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

    int distance[n];

    for (int i = 1; i < n; i++) {
        distance[i] = 30000;
    }
    distance[0] = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (distance[adj_list[j].second.first] < 30000) {
                if (distance[adj_list[j].second.second] > distance[adj_list[j].second.first] + adj_list[j].first) {
                    distance[adj_list[j].second.second] = distance[adj_list[j].second.first] + adj_list[j].first;
                }
            }
        }
    }


    for (int i = 0; i < n; i++) {
        cout << distance[i] << ' ';
    }

    return 0;
}