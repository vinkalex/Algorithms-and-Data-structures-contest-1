#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

const long long INF = LLONG_MAX;

int main() {
    int n;
    cin >> n;

    vector<pair<int, pair<int, int>>> adj_list;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            if (w < 100000) {
                adj_list.emplace_back(make_pair(w, make_pair(i, j)));
            }
        }
    }

    vector<long long> distance(n, INF);
    vector<int> used(n, 0);
    vector<int> path(n, -1);
    int cycle = -1;

    for (int k = 0; k < n && cycle == -1; k++) {
        if (distance[k] == INF) {
            distance[k] = 0;
            for (int i = 0; i < n; i++) {
                cycle = -1;
                for (int j = 0; j < adj_list.size(); j++) {
                    if (distance[adj_list[j].second.first] < INF) {
                        if (distance[adj_list[j].second.second] >
                            distance[adj_list[j].second.first] + adj_list[j].first) {
                            distance[adj_list[j].second.second] =
                                    distance[adj_list[j].second.first] + adj_list[j].first;
                            path[adj_list[j].second.second] = adj_list[j].second.first;
                            cycle = adj_list[j].second.first;

                        }
                    }
                }
            }
        }
    }

    if (cycle == -1) {
        cout << "NO";
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < n; i++) {
            cycle = path[cycle];
        }
        int cycle_start = cycle;
        vector<int> p;
        p.push_back(cycle);
        cycle = path[cycle];
        while (cycle != cycle_start) {
            p.push_back(cycle);
            cycle = path[cycle];
        }
        p.push_back(cycle_start);
        cout << p.size() << endl;
        reverse(p.begin(), p.end());
        for (size_t i = 0; i < p.size(); i++) {
            cout << p[i] + 1 << ' ';
        }
    }

    return 0;
}