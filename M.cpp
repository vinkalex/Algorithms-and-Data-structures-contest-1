#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Vertex {
public:
    int Color;
    int Children;

    Vertex() : Color(0), Children(0) {}

    Vertex(int color) {
        Color = color;
        Children = 0;
    }
};

class Graph {
public:
    vector<int> tin;
    vector<int> tup;
    vector<vector<int>> Adj_list;
    vector<Vertex> Data;

    Graph(vector<vector<int>> adj_list) {
        vector<int> curr;
        for (int i = 0; i < adj_list.size(); i++) {
            for (int j = 0; j < adj_list[i].size(); j++) {
                curr.push_back(adj_list[i][j]);
            }
            int x;
            Adj_list.push_back(curr);
            curr.clear();
            Data.emplace_back(Vertex(0));
            tin.push_back(0);
            tup.push_back(0);
        }
    }

};


void DFS(int vertex, Graph &in, int &timer, int& count, vector<int> &result, int p = -1) {
    in.Data[vertex].Color = 1;
    timer++;
    in.tin[vertex] = timer;
    in.tup[vertex] = timer;
    for (auto u : in.Adj_list[vertex]) {
        if (u == p) continue;
        if (in.Data[u].Color == 1) {
            in.tup[vertex] = min(in.tup[vertex], in.tin[u]);
        } else  if (in.Data[u].Color == 0){
            DFS(u, in, timer, count, result, vertex);
            in.tup[vertex] = min(in.tup[vertex], in.tup[u]);
            if (in.tup[u] >= in.tin[vertex] && p != -1) {
                if (find(result.begin(), result.end(), vertex) == result.end()) {
                    result.push_back(vertex);
                    count++;
                }
            }
            in.Data[vertex].Children++;
        }
    }
    if (p == -1 && in.Data[vertex].Children > 1) {
        if (find(result.begin(), result.end(), vertex) == result.end()) {
            result.push_back(vertex);
            count++;
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj_list(n);
    vector<int> result;

    for (int i = 0; i < m; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        vertex1--;
        vertex2--;
        adj_list[vertex1].push_back(vertex2);
        adj_list[vertex2].push_back(vertex1);
    }

    Graph graph(adj_list);

    int timer = 0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (graph.Data[i].Color == 0) {
            DFS(i, graph, timer, count, result);
        }
    }

    cout << count << endl;

    sort(result.begin(), result.end());

    for (auto i : result) {
        cout << i + 1 << endl;
    }

    return 0;
}