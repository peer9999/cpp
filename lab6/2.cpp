#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

vector<pair<int, int>> graph[100000];
int ans[100000];
int pr[100000];     //prev

int main() {
    //Ввод графа и вершин start и end.

    for (int i = 0; i < n; i++) {
        ans[i] = INF;
        pr[i] = -1;   //Значение, обозначающее что из этой вершины возвращаться некуда
    }

    ans[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    q.push({0, start});

    while (!q.empty()) {
        pair<int, int> c = q.top();
        q.pop();

        int dst = c.first, v = c.second;

        if (ans[v] < dst) {
            continue;
        }

        for (pair<int, int> e: graph[v]) {
            int u = e.first, len_vu = e.second;

            int n_dst = dst + len_vu;
            if (n_dst < ans[u]) {
                ans[u] = n_dst;
                pr[u] = v;
                q.push({n_dst, u});
            }
        }
    }

    vector<int> path;

    int cur = end;
    path.push_back(cur);

    while (pr[cur] != -1) {
        cur = pr[cur];
        path.push_back(cur);
    }

    reverse(path.begin(), path.end());

    cout << "Shortest path between vertices " << start + 1 << " and " << end + 1 << " is: " << endl;

    for (int v: path) {
        cout << v + 1 << ", ";
    }
}
