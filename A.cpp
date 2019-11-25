#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Vertex {
public:
    int Color;
    vector<int> Path;
    int Cnt_in_comp;

    Vertex() : Color(0), Cnt_in_comp(0){}

    Vertex(int color) {
        Color = color;
        Cnt_in_comp = 0;
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
            Data.emplace_back(Vertex(0));
        }
    }
};


void DFS(int vertex_start, int vertex_current, Graph &in) {
    if (in.Data[vertex_current].Color == 0) {
        in.Data[vertex_start].Path.push_back(vertex_current + 1);
        in.Data[vertex_current].Color = 1;
        for (auto u : in.Adj_list[vertex_current]) {
            if (in.Data[u].Color == 0) {
                in.Data[vertex_start].Cnt_in_comp++;
                DFS(vertex_start, u, in);
            }
        }
        in.Data[vertex_current].Color = 2;
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj_list(n);
    vector<vector<int>> result;

    for (int i = 0; i < m; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        vertex1--;
        vertex2--;
        adj_list[vertex1].push_back(vertex2);
        adj_list[vertex2].push_back(vertex1);
    }

    Graph graph(adj_list);
    int cnt_comps = 0;

    for (int i = 0; i < n; i++) {
        if (graph.Data[i].Color == 0) {
            DFS(i, i, graph);
            cnt_comps++;
        }
    }

    cout << cnt_comps << endl;
    for (int i = 0; i < n; i++) {
        if (!graph.Data[i].Path.empty()) {
            cout << graph.Data[i].Path.size() << endl;
            for (int j = 0; j < graph.Data[i].Path.size(); j++) {
                cout << graph.Data[i].Path[j] << ' ';
            }
            cout << endl;
        }
    }

    return 0;
}