#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Vertex {
public:
    int Color;
    int Number;
    int Path;
    int Depth;

    Vertex() {
        Color = 0;
        Number = 0;
        Path = 0;
        Depth = 0;
    }

    Vertex(int number) {
        Color = 0;
        Number = number;
        Path = 0;
        Depth = 0;
    }
};

class Graph {
public:
    vector<Vertex> Data;
};


Vertex operation1(Vertex num) {
    if (num.Number / 1000 != 9) {
        num.Number += 1000;
    }
    return num;
}

Vertex operation2(Vertex num) {
    if (num.Number % 10 != 1) {
        num.Number--;
    }
    return num;
}

Vertex operation3(Vertex num) {
    int last = num.Number / 10;
    int first = num.Number % 10;
    num.Number = first * 1000 + last;
    return num;
}

Vertex operation4(Vertex num) {
    int last = num.Number / 1000;
    int first = num.Number % 1000;
    num.Number = first * 10 + last;
    return num;
}


void BFS(Vertex &start, Graph &in, Vertex &finish, int &flag) {
    queue<Vertex> q;
    in.Data.push_back(start);
    q.push(start);
    int i = 1;
    int size = 0;
    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        int flag_curr = 0;
        for (int k = 0; k < in.Data.size() - 1; k++) {
            if (operation1(v).Number == in.Data[k].Number) {
                flag_curr = 1;
            }
        }
        if (flag_curr == 0) {
            in.Data.push_back(operation1(v));
            size++;
        }
        flag_curr = 0;
        for (int k = 0; k < in.Data.size() - 1; k++) {
            if (operation2(v).Number == in.Data[k].Number) {
                flag_curr = 1;
            }
        }
        if (flag_curr == 0) {
            in.Data.push_back(operation2(v));
            size++;
        }
        flag_curr = 0;
        for (int k = 0; k < in.Data.size() - 1; k++) {
            if (operation3(v).Number == in.Data[k].Number) {
                flag_curr = 1;
            }
        }
        if (flag_curr == 0) {
            in.Data.push_back(operation3(v));
            size++;
        }
        flag_curr = 0;
        for (int k = 0; k < in.Data.size() - 1; k++) {
            if (operation4(v).Number == in.Data[k].Number) {
                flag_curr = 1;
            }
        }
        if (flag_curr == 0) {
            in.Data.push_back(operation4(v));
            size++;
        }
        for (int j = i; j < i + size; j++) {
            if (flag != 1) {
                in.Data[j].Path = v.Number;
                in.Data[j].Depth = in.Data[v.Number].Depth + 1;
                q.push(in.Data[j]);
            }
            if (in.Data[j].Number == finish.Number) {
                flag = 1;
            }
        }
        i += size;
        size = 0;
        if (flag == 1) {
            break;
        }
    }
}


int main() {

    int start, finish;

    cin >> start >> finish;

    Vertex starts(start);
    Vertex finishies(finish);

    Graph graph;
    int flag = 0;

    BFS(starts, graph, finishies, flag);

    vector<int> p;
    int k = 0;
    for (int j = 0; j < graph.Data.size(); j++) {
        if (graph.Data[j].Number == finish) {
            k = j;
        }
    }
    Vertex v = graph.Data[k];
    while (v.Number != start) {
        p.push_back(v.Number);
        int i = 0;
        int path = v.Path;
        for (int j = 0; j < graph.Data.size(); j++) {
            if (graph.Data[j].Number == path) {
                i = j;
            }
        }
        v = graph.Data[i];
    }
    p.push_back(start);
    for (auto it = p.rbegin(); it < p.rend(); it++) {
        cout << *it << endl;
    }
    return 0;

}