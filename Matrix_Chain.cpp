#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void printP(vector<vector<int>> &split, int i, int j, char & ch)  {

	if(i + 1 == j) {
		cout << ch++;
	}else {
		cout << "(";
		printP(split, i, split[i][j],ch);
		printP(split,split[i][j],j,ch);
		cout << ")";
	}	

}

int matrix_mult(vector<int> &p) {
	int n = p.size();
	vector<vector<int>> dp(n, vector<int>(n, 0));
	vector<vector<int>> split(n, vector<int>(n, 0));
	
	for(int len = 2; len < n; len++) {
		for(int i = 0; i < n-len; i++) {
			int j = i+len;
			dp[i][j] = INT_MAX;
			for(int k = i+1; k < j; k++) {
				int cost = dp[i][k]+dp[k][j]+p[i]*p[k]*p[j];
				if(cost < dp[i][j]) {
					dp[i][j] = cost;
					split[i][j] = k;
				}
			} 
		}
	}


	char ch = 'A';
	cout << "The optimal parantthesis:\n";
	printP(split, 0, n-1, ch);
	
	return dp[0][n-1];

}

int main() {

	vector<int> p = {30, 35, 15, 5, 10, 20, 25};

	matrix_mult(p);
	
	return 0;

}