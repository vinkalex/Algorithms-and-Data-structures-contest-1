#include <iostream>
#include <vector>

using namespace std;

class Vertex {
public:
    int Color;
    int Used;

    Vertex() : Color(0), Used(0) {}

    Vertex(int color) {
        Color = color;
        Used = 0;
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


void DFS(int vertex_start, int vertex_current, Graph &in, int &count) {
    if (in.Data[vertex_current].Color == 0) {
        in.Data[vertex_current].Color = 1;
        for (auto u : in.Adj_list[vertex_current]) {
            if (in.Data[u].Color == 0) {
                DFS(vertex_start, u, in, count);
            } else if (in.Data[u].Used == 1) {
                count--;
            }
        }
        in.Data[vertex_current].Color = 2;
        in.Data[vertex_current].Used = 1;
    }
}


int main() {
    int n;

    cin >> n;

    vector<vector<int>> adj_list(n);

    for (int i = 0; i < n; i++) {
        int vertex;
        cin >> vertex;
        vertex--;
        adj_list[vertex].push_back(i);
    }

    Graph graph(adj_list);
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (graph.Data[i].Color == 0) {
            DFS(i, i, graph, count);
            count++;
        }
    }

    cout << count << endl;

    return 0;
}