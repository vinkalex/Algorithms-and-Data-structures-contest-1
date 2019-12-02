#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

const long long INF = LLONG_MAX;

class Edge {
public:
    long long Start;
    long long Finish;
    long long Tin;
    long long Tup;

    Edge() : Start(0), Finish(0), Tin(0), Tup(0) {}

    Edge(long long start, long long tin, long long finish, long long tup) {
        Start = start;
        Finish = finish;
        Tin = tin;
        Tup = tup;
    }
};

int main() {
    long long n, s, f, m;
    cin >> n;
    cin >> s >> f;
    cin >> m;
    s--;
    f--;

    vector<Edge> edge_list(m);

    for (int i = 0; i < m; i++) {
        long long vertex1, tin, vertex2, tup;
        cin >> vertex1 >> tin >> vertex2 >> tup;
        vertex1--;
        vertex2--;
        edge_list[i] = Edge(vertex1, tin, vertex2, tup);
    }

    sort(edge_list.begin(), edge_list.end(), [](const Edge &e1, const Edge &e2) {
        if (e1.Tin > e2.Tin) {
            return true;
        } else return false;
    });

    long long distance[n];

    for (int i = 0; i < n; i++) {
        distance[i] = INF;
    }
    distance[s] = 0;


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edge_list.size(); j++) {
            if (distance[edge_list[j].Start] < INF) {
                if (edge_list[j].Tin >= distance[edge_list[j].Start] && distance[edge_list[j].Finish] > edge_list[j].Tup) {
                    distance[edge_list[j].Finish] = edge_list[j].Tup;
                }
            }
        }
    }


    cout << distance[f];

    return 0;
}