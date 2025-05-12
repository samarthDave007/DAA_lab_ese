#include <iostream>
#include <vector>
using namespace std;

int main() {
	
	int V = 7;

	vector<vector<int>> edges = {{0, 1},{0, 2},{1, 3},{3, 4},{4, 5},{5, 6}};
	
	vector<vector<int>> adjList(V);

	for(const auto& edge: edges) {
		int u = edge[0];
		int v = edge[1];
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	
	vector<bool> visited(V, false);

	for(int u = 0; u < V; u++) {
		if(!visited[u]) {
			for(auto v: adjList[u]) {
				if(!visited[v]) {
					visited[u]  = true;
					visited[v] = true;
					break;
				}
			}
		}
	}

	for(int i = 0; i < visited.size(); i++) {
		if(visited[i]) cout << i << " ";
	} 
	cout << endl;
	return 0;
}