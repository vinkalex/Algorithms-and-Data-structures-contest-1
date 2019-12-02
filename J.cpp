#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Vertex {
public:
    int Color;
    int X, Y;
    int Data;
    int Number;
    int Depth;

    Vertex() {
        Color = 0;
        Number = 0;
        X = 0, Y = 0;
        Data = 0;
        Depth = 0;
    }

    Vertex(int c, int d, int n, int x, int y) {
        Color = c;
        Data = d;
        Depth = d == 1 ? 0 : 10000000;
        Number = n;
        X = x;
        Y = y;
    }

};


int main() {
    int n, m;
    cin >> n >> m;

    vector<Vertex> graph;

    int input[n][m];
    int number = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> input[i][j];
            graph.emplace_back(Vertex(0, input[i][j], number, i, j));
            number++;
        }
    }

    number = 0;
    queue<Vertex> q;
    while (number < m * n) {
        if (graph[number].Data == 1) {
            q.push(graph[number]);
        }
        number++;
    }

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        for (int i = 0; i < n * m; i++) {
            if (abs(graph[i].X - graph[v.Number].X) + abs(graph[i].Y - graph[v.Number].Y) == 1) {
                if (graph[i].Color == 0) {
                    graph[i].Color = 1;
                    graph[i].Depth = min(graph[v.Number].Depth + 1, graph[i].Depth);
                    q.push(graph[i]);
                }
            }
        }
        graph[v.Number].Color = 2;
    }

    number = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << graph[number].Depth << ' ';
            number++;
        }
        cout << endl;
    }

    return 0;
}