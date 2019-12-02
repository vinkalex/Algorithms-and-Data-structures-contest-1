#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Vertex {
public:
    int Color;
    int Data;
    pair<int, int> Coords;
    pair<int, int> Path;
    int Depth;
    int Path_num;

    Vertex() {
        Color = 0;
        Data = 0;
        Depth = 0;
        Path = make_pair(0, 0);
        Coords.first = 0;
        Coords.second = 0;
        Path_num = 0;
    }

    Vertex(int color, int data, pair<int, int> coords) {
        Color = color;
        Data = data;
        Depth = 0;
        Path = make_pair(0, 0);
        Coords.first = coords.first;
        Coords.second = coords.second;
        Path_num = 0;
    }
};


class Graph {
public:
    vector<vector<int>> Adj_list;
    vector<Vertex> Data;

    Graph(vector<vector<int>> adj_list, int size) {
        vector<int> curr;
        for (int i = 0; i < adj_list.size(); i++) {
            for (int j = 0; j < adj_list[i].size(); j++) {
                curr.push_back(adj_list[i][j]);
            }
            Adj_list.push_back(curr);
            curr.clear();
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                Data.emplace_back(Vertex(0, i * size + j, make_pair(i, j)));
            }
        }
    }

};


void BFS(Graph &graph, int vertex_start) {
    queue<Vertex> q;
    graph.Data[vertex_start].Color = 1;
    q.push(graph.Data[vertex_start]);
    while (!q.empty()) {
        Vertex vertex = q.front();
        int vertex_data = vertex.Data;
        q.pop();
        for (auto u : graph.Adj_list[vertex_data]) {
            if (graph.Data[u].Color == 0) {
                graph.Data[u].Color = 1;
                graph.Data[u].Path = make_pair(graph.Data[vertex_data].Coords.first, graph.Data[vertex_data].Coords.second);
                graph.Data[u].Path_num = vertex_data;
                graph.Data[u].Depth = graph.Data[vertex_data].Depth + 1;
                q.push(graph.Data[u]);
            }
        }
        graph.Data[vertex_data].Color = 2;
    }
}


int main() {
    int n;
    cin >> n;

    int x1, x2, y1, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    x1--;
    x2--;
    y1--;
    y2--;

    vector<vector<int>> adj_list(n*n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + 2 < n && i + 2 >= 0) {
                if (j + 1 < n && j + 1 >= 0) {
                    adj_list[i * n + j].push_back((i + 2) * n + j + 1);
                }
                if (j - 1 < n && j - 1 >= 0) {
                    adj_list[i * n + j].push_back((i + 2) * n + j - 1);
                }
            }
            if (i - 2 < n && i - 2 >= 0) {
                if (j + 1 < n && j + 1 >= 0) {
                    adj_list[i * n + j].push_back((i - 2) * n + j + 1);
                }
                if (j - 1 < n && j - 1 >= 0) {
                    adj_list[i * n + j].push_back((i - 2) * n + j - 1);
                }
            }
            if (j + 2 < n && j + 2 >= 0) {
                if (i + 1 < n && i + 1 >= 0) {
                    adj_list[i * n + j].push_back((i + 1) * n + j + 2);
                }
                if (i - 1 < n && i - 1 >= 0) {
                    adj_list[i * n + j].push_back((i - 1) * n + j + 2);
                }
            }
            if (j - 2 < n && j - 2 >= 0) {
                if (i + 1 < n && i + 1 >= 0) {
                    adj_list[i * n + j].push_back((i + 1) * n + j - 2);
                }
                if (i - 1 < n && i - 1 >= 0) {
                    adj_list[i * n + j].push_back((i - 1) * n + j - 2);
                }
            }
        }
    }

    Graph graph(adj_list, n);

    int start = x1*n + y1;
    int finish = x2*n + y2;

    BFS(graph, start);

    if (graph.Data[finish].Depth != 0) {
        cout << graph.Data[finish].Depth << endl;
        vector<pair<int, int>> p;
        pair<int, int> v = (make_pair(graph.Data[finish].Coords.first, graph.Data[finish].Coords.second));
        while (v != make_pair(graph.Data[start].Coords.first, graph.Data[start].Coords.second)) {
            p.emplace_back(v);
            v = graph.Data[v.first * n + v.second].Path;
        }
        p.push_back(v);
        for (auto it = p.rbegin(); it < p.rend(); it++) {
            cout << (*it).first + 1 << ' ' << (*it).second + 1 << endl;
        }
    } else if (start == finish) {
        cout << 0 << endl;
        cout << x1 + 1 << y1 + 1 << endl;
    } else cout << -1 << endl;

    return 0;

}