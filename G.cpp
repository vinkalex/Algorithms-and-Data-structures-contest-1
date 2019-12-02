#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Vertex {
public:
    int Color;
    int Data;
    int Path;
    int Depth;

    Vertex() : Color(0), Data(0), Depth(0), Path(0) {}

    Vertex(int color, int data) {
        Color = color;
        Data = data;
        Depth = 0;
        Path = 0;
    }

    void inc_Depth(Vertex v) {
        Depth = v.Depth + 1;
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
            Data.emplace_back(Vertex(0, i));
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
                graph.Data[u].Path = vertex_data;
                graph.Data[u].inc_Depth(vertex);
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
    cin >> start >> finish;

    start--;
    finish--;

    vector<vector<int>> adj_list(n);

    for (int i = 0; i < m; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        vertex1--;
        vertex2--;
        adj_list[vertex1].push_back(vertex2);
        adj_list[vertex2].push_back(vertex1);
    }

    Graph graph(adj_list);

    BFS(graph, start);

    if (graph.Data[finish].Depth != 0) {
        cout << graph.Data[finish].Depth << endl;
        vector<int> path;
        int vertex = finish;
        while (vertex != start) {
            path.push_back(vertex);
            vertex = graph.Data[vertex].Path;
        }
        path.push_back(vertex);
        for (auto it = path.rbegin(); it < path.rend(); it++) {
            cout << *it + 1 << ' ';
        }
    } else if (start == finish) {
        cout << 0 << endl;
        cout << start++ << endl;
    } else cout << -1 << endl;

    return 0;
}