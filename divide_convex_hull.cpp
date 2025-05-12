#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
    
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }

    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

// Orientation: returns 0 -> colinear, 1 -> clockwise, 2 -> counterclockwise
int orientation(Point a, Point b, Point c) {
    int val = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y);
    if (val == 0) return 0;         // colinear
    return (val > 0) ? 1 : 2;       // clock or counterclock wise
}

// Merges two convex hulls
vector<Point> mergeHulls(vector<Point>& left, vector<Point>& right) {
    int n1 = left.size(), n2 = right.size();
    int i = 0, j = 0;

    // Find rightmost point of left hull
    for (int k = 1; k < n1; k++)
        if (left[k].x > left[i].x) i = k;

    // Find leftmost point of right hull
    for (int k = 1; k < n2; k++)
        if (right[k].x < right[j].x) j = k;

    // Upper tangent
    int upperLeft = i, upperRight = j;
    bool done = false;
    while (!done) {
        done = true;
        while (orientation(right[upperRight], left[upperLeft], left[(upperLeft+1)%n1]) == 2)
            upperLeft = (upperLeft + 1) % n1;
        while (orientation(left[upperLeft], right[upperRight], right[(n2 + upperRight - 1)%n2]) == 1) {
            upperRight = (n2 + upperRight - 1) % n2;
            done = false;
        }
    }

    // Lower tangent
    int lowerLeft = i, lowerRight = j;
    done = false;
    while (!done) {
        done = true;
        while (orientation(left[lowerLeft], right[lowerRight], right[(lowerRight+1)%n2]) == 2)
            lowerRight = (lowerRight + 1) % n2;
        while (orientation(right[lowerRight], left[lowerLeft], left[(n1 + lowerLeft - 1)%n1]) == 1) {
            lowerLeft = (n1 + lowerLeft - 1) % n1;
            done = false;
        }
    }

    // Collect merged hull points
    vector<Point> merged;

    // From lowerLeft to upperLeft on left hull
    int ind = lowerLeft;
    merged.push_back(left[ind]);
    while (ind != upperLeft) {
        ind = (ind + 1) % n1;
        merged.push_back(left[ind]);
    }

    // From upperRight to lowerRight on right hull
    ind = upperRight;
    merged.push_back(right[ind]);
    while (ind != lowerRight) {
        ind = (ind + 1) % n2;
        merged.push_back(right[ind]);
    }

    return merged;
}

// Recursive function to find convex hull
vector<Point> divideAndConquer(vector<Point>& points, int left, int right) {
    // Base case
    if (right - left + 1 <= 3) {
        vector<Point> baseHull;
        for (int i = left; i <= right; ++i)
            baseHull.push_back(points[i]);
        // Sort and remove colinear points
        if (baseHull.size() == 3 && orientation(baseHull[0], baseHull[1], baseHull[2]) == 0)
            baseHull.erase(baseHull.begin() + 1); // Remove middle point
        return baseHull;
    }

    // Divide
    int mid = (left + right) / 2;
    vector<Point> leftHull = divideAndConquer(points, left, mid);
    vector<Point> rightHull = divideAndConquer(points, mid + 1, right);

    // Conquer (merge)
    return mergeHulls(leftHull, rightHull);
}

// Main convex hull function
vector<Point> convexHull(vector<Point>& points) {
    sort(points.begin(), points.end());
    return divideAndConquer(points, 0, points.size() - 1);
}

// Driver code
int main() {
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                            {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    vector<Point> hull = convexHull(points);

    cout << "Points on Convex Hull:\n";
    for (auto p : hull)
        cout << "(" << p.x << ", " << p.y << ")\n";

    return 0;
}
