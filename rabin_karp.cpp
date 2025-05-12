#include <iostream>
#include <climits>
#include <string>
using namespace std;

void search(string text, string pattern, int q) {
	int M = pattern.size();
	int N = text.size();
	int h = 1;
	int d = 256;
	for(int i = 0; i < M-1; i++) {
		h = (h*d)%q;
	}
	int t = 0;
	int p = 0;
	for(int i = 0; i < M; i++) {
		p = ((p*d) + pattern[i])%q;
		t = ((t*d) + text[i])%q;
	}
	
	for(int i = 0; i <= N - M; i++) {
		if(p == t) {
			if(!pattern.compare(text.substr(i, M)))
				cout << "Pattern found at: " << i << endl;
		}

		if(i < N-M) {
			t = (d*(t - text[i]*h) + text[M+i]) % q;

			if (t < 0)
              t = (t + q);
		}
	}
}

int main() {

	string text =  "1234";
	string pattern = "123";
	int q = INT_MAX;
	search(text, pattern, q);

}