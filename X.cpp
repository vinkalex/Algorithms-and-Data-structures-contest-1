#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

const long long INF = LLONG_MAX / 2;

int main() {
    int n, m, c;
    cin >> n >> m >> c;

    vector<vector<long long>> matrix(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(n);
    }
    vector<vector<int>> parents(n);
    int cities[c];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = INF;
            matrix[i][i] = 0;
            parents[i].push_back(0);
        }
    }

    vector<int> uu, vv;
    for (int i = 0; i < m; i++) {
        int vertex1, vertex2, w;
        cin >> vertex1 >> vertex2 >> w;
        vertex1--;
        vertex2--;
        uu.push_back(vertex1);
        vv.push_back(vertex2);
        matrix[vertex1][vertex2] = -w;
        parents[vertex1][vertex2] = i;
    }

    for (int i = 0; i < c; i++) {
        int x;
        cin >> x;
        x--;
        cities[i] = x;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    parents[i][j] = parents[i][k];
                }
            }
        }
    }

    int flag = 0;
    for (int i = 0; i < c; i++) {
        if (matrix[cities[i]][cities[i]] < 0) {
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        vector<int> path;
        for (int i = 0; i < c - 1; i++) {
            int v = cities[i];
            while (v != cities[i + 1]) {
                path.push_back(parents[v][cities[i + 1]]);
                v = vv[parents[v][cities[i + 1]]];
                if (path.size() > 10000000) {
                    cout << "infinitely kind";
                    return 0;
                }
            }
        }
        cout << path.size() << endl;
        for (auto p : path) {
            cout << p + 1 << " ";
        }
    } else cout << "infinitely kind";

    return 0;
}