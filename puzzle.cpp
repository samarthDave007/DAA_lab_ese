#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <chrono>
using namespace std;

const int N = 4;

using namespace std;

vector<vector<int>> goal = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}};

//left,down,right,up
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};

struct State {

	vector<vector<int>> mat;
	int x,y;
	
	int g,f;
	
	bool operator>(const State&other)const {
		return f > other.f;
	}

};

void printPuzzle(vector<vector<int>> mat) {
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
}

bool isSafe(int x, int y) {

	return x >= 0 && x < N && y >= 0 && y < N;

}

int mismatch(vector<vector<int>> mat) {

	int cost = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(mat[i][j] != 0 && mat[i][j] != goal[i][j])
				cost++;
		}
	}

	return cost;

}



int main() {
	auto start_time = chrono::high_resolution_clock::now();
	vector<vector<int>> start= {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 11},
        {13, 14, 15, 12}};

	int startX = 1, startY = 2;
	
	State init;
	init.mat = start;
	init.x = startX;
	init.y = startY;
	init.g = 0;
	init.f = mismatch(start);
	priority_queue<State, vector<State>, greater<State>> queue;
	
	queue.push(init);

	while(!queue.empty()) {
		State top = queue.top();
		queue.pop();
		if(mismatch(top.mat) == 0) {
			printPuzzle(top.mat);	
			cout << "Total steps: " << top.g << endl;
			break;
		}

		for(int i = 0; i < 4; i++) {
			int newX = top.x + dx[i], newY = top.y + dy[i];
			if(isSafe(newX, newY)) {
				State newState;
				newState.mat = top.mat;
				swap(newState.mat[top.x][top.y], newState.mat[newX][newY]);
				newState.x = newX;
				newState.y = newY;
				newState.g = top.g + 1;
				newState.f = newState.g + mismatch(newState.mat);
				queue.push(newState);
			}
		}
	}

	auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " ms" << endl;

}