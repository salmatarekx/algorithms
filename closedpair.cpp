#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    int x, y;
};

// Comparator function to sort points by x-coordinate
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

// Comparator function to sort points by y-coordinate
bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

// Utility function to calculate the distance between two points
double dist(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute force method to find the closest pair in a small set of points
double bruteForce(const vector<Point>& points, int start, int end) {
    double minDist = numeric_limits<double>::max();
    for (int i = start; i < end; ++i) {
        for (int j = i + 1; j < end; ++j) {
            double d = dist(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
            }
        }
    }
    return minDist;
}

// Function to find the closest pair in a strip of points
double stripClosest(vector<Point>& strip, double d) {
    double minDist = d;
    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            double d = dist(strip[i], strip[j]);
            if (d < minDist) {
                minDist = d;
            }
        }
    }
    return minDist;
}

// Recursive function to find the closest pair of points
double closestUtil(vector<Point>& points, int start, int end) {
    if (end - start <= 3) {
        return bruteForce(points, start, end);
    }

    int mid = (start + end) / 2;
    Point midPoint = points[mid];

    double dl = closestUtil(points, start, mid);
    double dr = closestUtil(points, mid, end);
    double d = min(dl, dr);

    vector<Point> strip;
    for (int i = start; i < end; ++i) {
        if (abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    return min(d, stripClosest(strip, d));
}

// Main function to find the closest pair of points
double closestPair(vector<Point>& points) {
    sort(points.begin(), points.end(), compareX);
    return closestUtil(points, 0, points.size());
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    double minDist = closestPair(points);
    cout << "The smallest distance is " << minDist << endl;
    return 0;
}
