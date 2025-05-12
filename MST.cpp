#include <iostream>
#include <queue>
#include <climits>
#include <vector>

using namespace std;

class DSU {
	
	vector<int> parent, rank;
	
	public:
		DSU(int V) {
			parent.resize(V);
			rank.resize(V);
			for(int i = 0; i < V; i++) {
				parent[i] = i;
				rank[i] = 1;
			}
		}

		int find(int x) {
		
			if(parent[x] == x) {
				return x;
			}

			return parent[x] = find(parent[x]);
		}


		void unite(int x, int y) {
		
			int s1 = find(x), s2 = find(y);

			if(rank[s1] > rank[s2]) {
				parent[s2] = s1;
			}else if(rank[s1] < rank[s2]) {
				parent[s1] = s2;
			}else {
				parent[s2] = s1;
				rank[s1]++;
			}

		}

};

bool comparator(vector<int>& a, vector<int>& b) {
	if(a[2]<=b[2])return true;
    return false;
}


int main() {

	int V = 4;
	int src = 0;
	vector<vector<int>> edges = {
        {0, 1, 10}, {1, 3, 15}, {2, 3, 4}, {2, 0, 6}, {0, 3, 5}
    };
	int cost = 0;
	//Kruskal
	/*sort(edges.begin(), edges.end(), comparator);
	DSU d(V);
	int count = 0;
	for(auto& edge: edges) {
		int u = edge[0];
		int v = edge[1];
		int w = edge[2];
		if(d.find(u) != d.find(v)) {
			d.unite(u, v);
			cost += w;
			cout << u << "---" << v << ": " << w << endl;
			if(++count == V-1) break;
		}
	}*/
	
	//Prim

	vector<vector<vector<int>>> adjList(V);
	for(const auto& edge: edges) {
		
		int u = edge[0];
		int v = edge[1];
		int w = edge[2];
		adjList[u].push_back({v, w});
		adjList[v].push_back({u, w});
	}
	
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> queue;
	queue.push({0, src, -1}); // {weight, current_vertex, parent}

	vector<bool> visited(V, false);
	cost = 0;

	while(!queue.empty()) {
		auto top = queue.top(); queue.pop();
		int w = top[0], u = top[1], parent = top[2];

		if(visited[u]) continue;
		visited[u] = true;
		cost += w;

		if(parent != -1) {
			cout << parent << "---" << u << ": " << w << endl;
		}

		for(const auto& edge: adjList[u]) {
			int v = edge[0], weight = edge[1];
			if(!visited[v]) {
				queue.push({weight, v, u});
			}
		}
	}

	cout << "Total cost: " << cost << endl;

	return 0;
}