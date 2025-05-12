#include <iostream>
#include <stack>
#include <cstdlib>
using namespace std;

struct Point {
    int x, y;
};

// Global reference point for sorting
Point p0;

// Utility: returns next-to-top element from the stack
Point nextToTop(stack<Point> S) {
    Point top = S.top(); S.pop();
    Point res = S.top();
    S.push(top);
    return res;
}

// Utility: calculates square of distance between two points
int distance(Point p1, Point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// Standard orientation function using cross product
// Returns 0 -> collinear, 1 -> clockwise, 2 -> counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Comparator function for sorting based on polar angle with p0
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);

    if (o == 0)
        return (distance(p0, *p2) >= distance(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

void convexHull(int n, Point points[]) {
    // Step 1: Find bottom-most point (or left-most in case of tie)
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        if ((points[i].y < ymin) || (points[i].y == ymin && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    // Place the bottom-most point at first position
    swap(points[0], points[min]);
    p0 = points[0];

    // Step 2: Sort remaining points by polar angle with p0
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Step 3: Remove duplicates (collinear points with same angle, keep farthest)
    int m = 1; // Index of modified array
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m++] = points[i];
    }

    if (m < 3) {
        cout << "Convex hull not possible\n";
        return;
    }

    // Step 4: Process points to build convex hull using stack
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    for (int i = 3; i < m; i++) {
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    // Step 5: Print convex hull
    cout << "Convex Hull:\n";
    while (!S.empty()) {
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y << ")\n";
        S.pop();
    }
}

// Driver code
int main() {
    Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                      {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(points) / sizeof(points[0]);
    convexHull(n, points);
    return 0;
}
