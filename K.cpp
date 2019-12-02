#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Vertex {
public:
    int Color;
    int Number;
    int Path;
    int Depth;

    Vertex() : Color(0), Number(0), Depth(0), Path(0) {}

    Vertex(int color, int data) {
        Color = color;
        Number = data;
        Depth = 0;
        Path = 0;
    }

};


class Graph {
public:
    vector<vector<int>> Adj_list;
    vector<Vertex> Data;

    Graph(vector<vector<int>> adj_list) {
        vector<int> curr;
        for (int i = 0; i < adj_list.size(); i++) {
            for (int j = 0; j < adj_list[i].size(); j++) {
                curr.push_back(adj_list[i][j]);
            }
            Adj_list.push_back(curr);
            curr.clear();
            Data.emplace_back(0, i);
        }
    }
};


void BFS(Graph &graph, int vertex_start) {
    queue<Vertex> q;
    graph.Data[vertex_start].Color = 1;
    q.push(graph.Data[vertex_start]);
    while (!q.empty()) {
        Vertex vertex = q.front();
        int vertex_data = vertex.Number;
        q.pop();
        for (auto u : graph.Adj_list[vertex_data]) {
            if (graph.Data[u].Color == 0) {
                graph.Data[u].Color = 1;
                graph.Data[u].Depth = graph.Data[vertex_data].Depth + 1;
                q.push(graph.Data[u]);
            }
        }
        graph.Data[vertex_data].Color = 2;
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    int start, finish;

    vector<vector<int>> adj_list(n * m);
    int table[n][m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char sym;
            cin >> sym;
            if (sym == 'S') {
                start = i * m + j;
                table[i][j] = 0;
            } else if (sym == 'T') {
                finish = i * m + j;
                table[i][j] = 0;
            } else if (sym == '#') {
                table[i][j] = 1;
            } else table[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i][j] == 0) {
                int board = i;
                while (board < n && table[board][j] != 1) {
                    board++;
                }
                if (i * m + j != (i + abs(board - i) / 2) * m + j) {
                    adj_list[i * m + j].push_back((i + abs(board - i) / 2) * m + j);
                }
                board = i;
                while (board >= 0 && table[board][j] != 1) {
                    board--;
                }
                if (i * m + j != (i - abs(board - i) / 2) * m + j) {
                    adj_list[i * m + j].push_back((i - abs(board - i) / 2) * m + j);
                }
                board = j;
                while (board < m && table[i][board] != 1) {
                    board++;
                }
                if (i * m + j != i * m + (j + abs(board - j) / 2)) {
                    adj_list[i * m + j].push_back(i * m + (j + abs(board - j) / 2));
                }
                board = j;
                while (board >= 0 && table[i][board] != 1) {
                    board--;
                }
                if (i * m + j != i * m + (j - abs(board - j) / 2)) {
                    adj_list[i * m + j].push_back(i * m + (j - abs(board - j) / 2));
                }
            }
        }
    }

    Graph graph(adj_list);

    BFS(graph, start);

    if (graph.Data[finish].Depth == 0) {
        cout << -1;
    } else cout << graph.Data[finish].Depth;

    return 0;
}