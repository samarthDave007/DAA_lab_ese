#include <iostream>
#include <set>
using namespace std;

struct Point {
    int x, y;

    // For storing in set
    bool operator<(const Point& p) const {
        return (x < p.x) || (x == p.x && y < p.y);
    }
};

// Function to get orientation of triplet (p, q, r)
int orientation(Point p, Point q, Point r) {
    return (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
}

// Brute-force convex hull using set
void convexHullBruteForce(Point points[], int n) {
    if (n < 3) {
        cout << "Convex hull not possible\n";
        return;
    }

    set<Point> hull;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {

            Point A = points[i], B = points[j];
            int pos = 0, neg = 0;

            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                int o = orientation(A, B, points[k]);

                if (o > 0) pos++;
                else if (o < 0) neg++;
            }

            if (pos == 0 || neg == 0) {
                hull.insert(A);
                hull.insert(B);
            }
        }
    }

    cout << "Points on the Convex Hull:\n";
    for (auto pt : hull)
        cout << "(" << pt.x << ", " << pt.y << ")\n";
}

// Driver code
int main() {
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);
    convexHullBruteForce(points, n);
    return 0;
}
