	#include <iostream>
	#include <queue>
	#include <climits>
	#include <vector>

	using namespace std;

	int main() {
		
		int V = 5;
		int src = 0;
		vector<vector<int>> edges =  {
			{1, 3, 2}, 
			{4, 3, -1},
			{2, 4, 1}, 
			{1, 2, 1},
			{0, 1, 5} 
		};

		vector<int> dist(V, INT_MAX);
		dist[src] = 0;
		
		//Dijkstra’s
		/*vector<vector<vector<int>>> adjList(V);
		for(const auto& edge: edges) {
			
			int u = edge[0];
			int v = edge[1];
			int w = edge[2];
			adjList[u].push_back({v, w});
			adjList[v].push_back({u, w});
		}
		
		priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> queue;
		queue.push({0, src});

		while(!queue.empty()) {
			int d = queue.top()[0];
			int u = queue.top()[1];
			queue.pop();
			for(auto &[v, w]:adjList[u]) {
				if(dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					queue.push({dist[v], v});

				}
			}

		}

		*/
		
		//Bellman-Ford

		
		/*for(int i = 0; i < V-1; i++) {
		
			for(const auto& edge: edges) {
			
				int u = edge[0];
				int v = edge[1];
				int w = edge[2];
				
				if(dist[u] != INT_MAX && (dist[v] > dist[u] + w)) {
					dist[v]= dist[u] + w;
				}
			
			}
		
		}*/

		for(int i = 0; i < V; i++) {
			
			cout << dist[i] << " ";

		}
		
		cout << endl;
		
		return 0;
	}
