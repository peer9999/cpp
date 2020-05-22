#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;

vector<pair<int, int>> graph[100000];
int ans[100000];

int main() {
    //Ввод графа и вершины start.

    for (int i = 0; i < n; i++) {
        ans[i] = INF;
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
                q.push({n_dst, u});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "Shortest path from " << start + 1 << " to " << i + 1 << " has length " << ans[i] << endl;
    }
}
