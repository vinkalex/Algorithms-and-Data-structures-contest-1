#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Vertex {
public:
    int Color;

    Vertex() : Color(0){
    }

    Vertex(int color) {
        Color = color;
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

bool check_cycle(int vertex, Graph &in) {
    in.Data[vertex].Color = 1;
    for (auto u : in.Adj_list[vertex]) {
        if (in.Data[u].Color == 0) {
            if (check_cycle(u, in)) {
                return true;
            }
        } else if (in.Data[u].Color == 1) {
            return true;
        }
    }
    in.Data[vertex].Color = 2;
    return false;
}

void DFS(int vertex, Graph &in, list<int> &list) {
    in.Data[vertex].Color = 1;
    for (auto u : in.Adj_list[vertex]) {
        if (in.Data[u].Color == 0) {
            DFS(u, in, list);
        }
    }
    in.Data[vertex].Color = 2;
    list.push_front(vertex);
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
    }

    Graph graph(adj_list);
    list<int> list;

    int cycle = 0;
    for (int i = 0; i < n; i++) {
        if (graph.Data[i].Color == 0) {
            if (check_cycle(i, graph)) {
                cycle = 1;
                break;
            }
        }
    }

    if (cycle == 1) {
        cout << -1 << endl;
    } else {
        for (int i = 0; i < graph.Data.size(); i++) {
            graph.Data[i].Color = 0;
        }
        for (int i = 0; i < n; i++) {
            if (graph.Data[i].Color == 0) {
                DFS(i, graph, list);
            }
        }
        for (auto i : list) {
            cout << i + 1 << ' ';
        }
    }

    return 0;
}