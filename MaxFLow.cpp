#include <iostream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

bool dfs(vector<vector<int>> &resGraph, int u, int t, vector<bool> &visited, vector<int> &parent) {
	
	visited[u] = true;
	if(u == t) 
		return true;
	
	int n = resGraph.size();
	for (int v = 0; v < n; v++) {
            if (!visited[v] && resGraph[u][v] > 0) {
                parent[v] = u;
                if (dfs(resGraph, v, t, visited, parent))
                    return true;
            }
     }
	
	return false;

}

int flow_dfs(vector<vector<int>> &g, int s, int t) {
    int n = g.size();
    vector<vector<int>> resGraph = g;
    vector<int> parent(n);
    int max_flow = 0;

    while (true) {
        vector<bool> visited(n, false);
        fill(parent.begin(), parent.end(), -1);

        if (!dfs(resGraph, s, t, visited, parent))
            break;

        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, resGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            resGraph[u][v] -= path_flow;
            resGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

bool bfs(vector<vector<int>> &resGraph, int s, int t, vector<int> &parent) {
    int n = resGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            if (!visited[v] && resGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == t)
                    return true;
            }
        }
    }

    return false;
}

int flow(vector<vector<int>> &g, int s, int t) {
    int n = g.size();
    vector<vector<int>> resGraph = g;
    vector<int> parent(n);
    int max_flow = 0;

    while (bfs(resGraph, s, t, parent)) {
        int path_flow = INT_MAX;

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, resGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            resGraph[u][v] -= path_flow;
            resGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    vector<vector<int>> graph = {
        { 0, 16, 13, 0, 0, 0 },
        { 0, 0, 10, 12, 0, 0 },
        { 0, 4, 0, 0, 14, 0 },
        { 0, 0, 9, 0, 0, 20 },
        { 0, 0, 0, 7, 0, 4 },
        { 0, 0, 0, 0, 0, 0 }
    };

    cout << "The maximum possible flow is " << flow_dfs(graph, 0, 5) << endl;
}
