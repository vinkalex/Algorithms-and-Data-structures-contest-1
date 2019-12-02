#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

const long long INF = LLONG_MAX;

int main() {
    int n, m, k, s, f;
    cin >> n >> m >> k >> s >> f;
    s--;
    f--;

    vector<pair<int, pair<int, int>>> edge_list;

    vector<vector<int>> matrix(n);

    for (int i = 0; i < n; i++) {
        matrix[i].resize(n);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < m; i++) {
        int vertex1, vertex2, w;
        cin >> vertex1 >> vertex2 >> w;
        vertex1--;
        vertex2--;
        if (w < matrix[vertex1][vertex2]) {
            matrix[vertex1][vertex2] = w;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < INT_MAX) {
                edge_list.emplace_back(make_pair(matrix[i][j], make_pair(i, j)));
            }
        }
    }


    long long distance[n][k + 1];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            distance[i][j] = INF;
        }
    }
    distance[s][0] = 0;

    for (int nn = 0; nn < n; nn++) {
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < edge_list.size(); j++) {
                if (distance[edge_list[j].second.first][i] < INF) {
                    if (distance[edge_list[j].second.second][i + 1] >
                        distance[edge_list[j].second.first][i] + edge_list[j].first) {
                        distance[edge_list[j].second.second][i + 1] =
                                distance[edge_list[j].second.first][i] + edge_list[j].first;
                    }
                }
            }
        }
    }


    long long min = INF;
    for (int i = 0; i <= k; i++) {
        if (distance[f][i] < min) {
            min = distance[f][i];
        }
    }

    if (min == INF) {
        cout << -1;
    } else cout << min;

    return 0;
}