#include <iostream>

using namespace std;


void insertion(int n, int arr[n]) {
	
	for(int i = 1; i < n; i++) {
		int key = arr[i];
		int j = i-1;
		while(j >= 0 && arr[j] > key) {
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1]=key;
	}

}

void selection(int n, int arr[n]) {
	
	for(int i = 0; i < n-1; i++) {
		int min = i;
		for(int j = i+1; j < n;j++) {
			if(arr[j] < arr[min])
				min = j;
		}
		swap(arr[i], arr[min]);
	}

}

int partion(int n, int arr[n], int s, int e) {
	
	int key = arr[e];
	
	int i = s-1;
	for(int j = s; j < e; j++) {
		if(arr[j] < key) {
			i++;
			swap(arr[j], arr[i]);
		}
	}
	swap(arr[i+1], arr[e]);
	return i+1;
}

void quick(int n, int arr[n], int s, int e) {
	
	if(s < e) {
		int q = partion(n, arr, s, e);
		quick(n, arr, s, q-1);
		quick(n, arr, q+1, e);
	}
}

void merge(int n, int arr[n], int s,int m, int e) {
	
	int n1 = m - s+1;
	int n2 = e - m;
	int L[n1],R[n2];
	
	for(int i = 0; i < n1; i++) 
		L[i] = arr[i+s];
	for(int i = 0; i < n2; i++)
		R[i] = arr[i+m+1];

	int i = 0, j= 0, k = s;
	
	while(i != n1 && j != n2) {
		if(L[i] < R[j]) {
			arr[k] = L[i];
			i++;
		}else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while(i != n1) {	
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j != n2) {	
		arr[k] = R[j];
		j++;
		k++;
	}
	
}

void mergesort(int n, int arr[n], int s, int e) {

	if(s < e) {
		int m = (s+e) / 2;
		mergesort(n, arr, s, m);
		mergesort(n, arr, m+1, e);
		merge(n, arr, s, m, e);
	}

}

int main() {

	int arr[] = {2, 4, 1, 3};

	int n = sizeof(arr) / sizeof(arr[0]);

	//insertion(n, arr);
	//selection(n, arr);
	//quick(n ,arr, 0, n-1);
	mergesort(n, arr, 0, n-1);
	for(auto i: arr) 
		cout << i << " ";
	cout << endl;

}