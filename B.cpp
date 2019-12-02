#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Vertex {
public:
    int Color;
    int Coloring;
    int Cnt_in_comp;

    Vertex() : Color(0), Coloring(0), Cnt_in_comp(0) {}

    Vertex(int color) {
        Color = color;
        Coloring = 0;
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

void DFS(int vertex, Graph &in, int &flag, int &color_end) {
    in.Data[vertex].Color = 1;
    for (auto u : in.Adj_list[vertex]) {
        if (in.Data[u].Color == 0) {
            int color = in.Data[vertex].Coloring + 1;
            in.Data[u].Coloring = (color % 2);
            DFS(u, in, flag, color_end);
        } else {
            if (in.Data[vertex].Coloring == in.Data[u].Coloring) {
                flag = 1;
            }
        }
    }
    in.Data[vertex].Color = 2;
    color_end = in.Data[vertex].Coloring;
}


int main() {
    int n, m;

    cin >> n >> m;

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
    int flag = 0;
    int color_end = 0;

    for (int i = 0; i < n; i++) {
        if (graph.Data[i].Color == 0) {
            graph.Data[i].Coloring = (color_end + 1) % 2;
            DFS(i, graph, flag, color_end);
        }
    }

    if (flag == 0) {
        cout << "YES" << endl;
    } else cout << "NO" << endl;

    return 0;

}