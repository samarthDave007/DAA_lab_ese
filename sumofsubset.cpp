#include <iostream>
#include <vector>
#include<chrono>
using namespace std;

void sumofsubset(vector<int> &arr, int m, int i, int sum, int totalsum, vector<int> list) {
	if(sum == m) {
		for(int i = 0; i < list.size(); i++)
			cout << list[i] << " ";
		cout << endl;
	}
	if(i == arr.size()) return;
	if(sum + arr[i] > m) return;
	if(sum + totalsum < m) return;
	
	list.push_back(arr[i]);
	sumofsubset(arr, m, i+1, sum+arr[i], totalsum-arr[i],list);
	list.pop_back();
	sumofsubset(arr, m, i+1, sum, totalsum-arr[i],list);
}

int main() {

	vector<int> arr = {1, 2, 3, 4, 5};
	int m = 5;
	int totalsum = 0;

	for(auto i : arr)
		totalsum += i;
	
	std::usingnamespacestd::chrono
	auto start=high_resolution_clock::now();
	sumofsubset(arr, m, 0, 0, totalsum, vector<int>());
	auto end=high_resolution_clock::now();
	duration<double> diff=end-start;
	cout<<diff.count()
}