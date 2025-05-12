#include <iostream>
#include <vector>
using namespace std;

// Matrix addition/subtraction
vector<vector<int>> add(const vector<vector<int>> &mat1, const vector<vector<int>> &mat2, int sign = 1) {
    int n = mat1.size();
    vector<vector<int>> result(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = mat1[i][j] + sign * mat2[i][j];
    return result;
}

// Strassen's algorithm using your equations
vector<vector<int>> strassen(const vector<vector<int>> &mat1, const vector<vector<int>> &mat2) {
    int n = mat1.size();
    vector<vector<int>> res(n, vector<int>(n));

    if (n == 1) {
        res[0][0] = mat1[0][0] * mat2[0][0];
        return res;
    }

    int newS = n / 2;
    vector<vector<int>> a11(newS, vector<int>(newS));
    vector<vector<int>> a12(newS, vector<int>(newS));
    vector<vector<int>> a21(newS, vector<int>(newS));
    vector<vector<int>> a22(newS, vector<int>(newS));
    vector<vector<int>> b11(newS, vector<int>(newS));
    vector<vector<int>> b12(newS, vector<int>(newS));
    vector<vector<int>> b21(newS, vector<int>(newS));
    vector<vector<int>> b22(newS, vector<int>(newS));

    for (int i = 0; i < newS; i++) {
        for (int j = 0; j < newS; j++) {
            a11[i][j] = mat1[i][j];
            a12[i][j] = mat1[i][j + newS];
            a21[i][j] = mat1[i + newS][j];
            a22[i][j] = mat1[i + newS][j + newS];

            b11[i][j] = mat2[i][j];
            b12[i][j] = mat2[i][j + newS];
            b21[i][j] = mat2[i + newS][j];
            b22[i][j] = mat2[i + newS][j + newS];
        }
    }

    // Using alternative strassen formula
    vector<vector<int>> p = strassen(add(a11, a22), add(b11, b22));
    vector<vector<int>> q = strassen(add(a21, a22), b11);
    vector<vector<int>> r = strassen(a11, add(b12, b22, -1));
    vector<vector<int>> s = strassen(a22, add(b21, b11));
    vector<vector<int>> t = strassen(add(a12, a22, -1), b22);
    vector<vector<int>> u = strassen(add(a11, a12), add(b12, b22, -1));
    vector<vector<int>> v = strassen(add(a21, a11, -1), add(b11, b12));

    // Result quadrants
    vector<vector<int>> c11 = add(add(p, s), add(v, t, -1));
    vector<vector<int>> c12 = add(r, t);
    vector<vector<int>> c21 = add(q, s);
    vector<vector<int>> c22 = add(add(p, r), add(u, q, -1));

    // Combine into result matrix
    for (int i = 0; i < newS; i++) {
        for (int j = 0; j < newS; j++) {
            res[i][j] = c11[i][j];
            res[i][j + newS] = c12[i][j];
            res[i + newS][j] = c21[i][j];
            res[i + newS][j + newS] = c22[i][j];
        }
    }

    return res;
}

int main() {
    vector<vector<int>> arr = {{7, 8}, {2, 9}};
    vector<vector<int>> brr = {{14, 5}, {5, 18}};
    vector<vector<int>> res = strassen(arr, brr);

    for (const auto& row : res) {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }

    return 0;
}
