#include <iostream>
#include <vector>

using namespace std;

void make_set(int x, int *parent, int *size) {
    parent[x] = x;
    size[x] = 1;
}

int find_set(int x, int *parent, int *size) {
    if (x == parent[x])
        return x;
    return parent[x] = find_set(parent[x], parent, size);
}

void union_sets(int x, int y, int *parent, int *size) {
    x = find_set(x, parent, size);
    y = find_set(y, parent, size);
    if (x != y) {
        if (size[x] < size[y])
            swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }
}


int main() {

    int n, m;

    cin >> n >> m;
    int parent[n];
    int size[n];

    for (int i = 0; i < n; i++) {
        make_set(i, parent, size);
    }

    int res = 0;
    int flag = 0;
    int count = n - 1;

    for (int i = 0; i < m; i++) {
        int first, second;
        cin >> first >> second;
        if (flag == 0 && (find_set(first, parent, size) != find_set(second, parent, size))) {
            union_sets(first, second, parent, size);
            count--;
            if (count == 0) {
                res = i;
                flag = 1;
            }
        }
    }

    cout << res + 1 << endl;

    return 0;

}