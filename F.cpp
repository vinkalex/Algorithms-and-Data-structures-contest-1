#include <iostream>
#include <vector>

using namespace std;

class Vertex {
public:
    int Color;
    int Comp;

    Vertex() : Color(0), Comp(0) {}

    Vertex(int color) {
        Color = color;
        Comp = 0;
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

void DFS(int vertex, Graph &in, vector<int> &list) {
    in.Data[vertex].Color = 1;
    for (auto u : in.Adj_list[vertex]) {
        if (in.Data[u].Color == 0) {
            DFS(u, in, list);
        }
    }
    in.Data[vertex].Color = 2;
    list.push_back(vertex);
}

void DFS2(int vertex, Graph &in, int &comp) {
    in.Data[vertex].Color = 1;
    in.Data[vertex].Comp = comp;
    for (auto i : in.Adj_list[vertex]) {
        if (in.Data[i].Color == 0) {
            DFS2(i, in, comp);
        }
    }
    in.Data[vertex].Color = 2;
}

int main() {
    int n, m;

    cin >> n >> m;

    vector<vector<int>> adj_list(n);
    vector<vector<int>> adj_list2(n);

    for (int i = 0; i < m; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        vertex1--;
        vertex2--;
        adj_list[vertex1].push_back(vertex2);
        adj_list2[vertex2].push_back(vertex1);
    }

    Graph graph(adj_list);
    Graph graph2(adj_list2);
    vector<int> list;


    for (int i = 0; i < n; i++) {
        if (graph.Data[i].Color == 0) {
            DFS(i, graph, list);
        }
    }

    int comp = 1;
    for (int i = list.size() - 1; i >= 0; i--) {
        if (graph2.Data[list[i]].Color == 0) {
            DFS2(list[i], graph2, comp);
            comp++;
        }
    }

    cout << comp - 1 << endl;

    for (auto i : graph2.Data) {
        cout << i.Comp << ' ';
    }

    return 0;

}