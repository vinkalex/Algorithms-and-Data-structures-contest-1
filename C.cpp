#include<iostream>
#include<vector>

using namespace std;

class Vertex {
public:
    int Color;

    Vertex() : Color(0) {}

    Vertex(int color) {
        Color = color;
    }
};

class Graph {
public:
    vector<vector<int>> Adj_list;
    vector<Vertex> Data;
    vector<int> path;
    int pathSize;

    Graph(vector<vector<int>> adj_list) : pathSize(0) {
        path.resize(adj_list.size());
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

bool DFS(int vertex, Graph &in, int &cycle_end, int &cycle_start) {
    in.Data[vertex].Color = 1;
    for (auto u : in.Adj_list[vertex]) {
        if (in.Data[u].Color == 0) {
            in.path[in.pathSize] = u;
            in.pathSize++;
            if (DFS(u, in, cycle_end, cycle_start)) {
                return true;
            }
        } else if (in.Data[u].Color == 1) {
            cycle_start = u;
            cycle_end = vertex;
            return true;
        }
    }
    in.Data[vertex].Color = 2;
    in.pathSize--;
    return false;
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
    }

    Graph graph(adj_list);
    int cycle = 0;
    int cycle_end = 0;
    int cycle_start = 0;

    for (int i = 0; i < n; i++) {
        if (graph.Data[i].Color == 0) {
            graph.path[graph.pathSize] = i;
            graph.pathSize++;
            if (DFS(i, graph, cycle_end, cycle_start)) {
                cycle = 1;
                break;
            }
        }
    }

    if (cycle == 1) {
        cout << "YES" << endl;
        int iswrite = 0;
        for (int i = 0; i < graph.pathSize; i++) {
            if (graph.path[i] == cycle_start) {
                iswrite = 1;
            }
            if (iswrite == 1) {
                cout << graph.path[i] + 1 << ' ';
            }
        }
    } else cout << "NO" << endl;

    return 0;

}