#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// q2 平面最近点

struct Point {
    int x;
    int y;
};

int* a;

vector<Point*> pts;

inline double dist(Point* a, Point* b) {
    return sqrt((a->x - b->x)*(a->x-b->x)
                +(a->y-b->y)*(a->y-b->y));
}

inline double dist2(int i, int j) {
    return dist(pts[i], pts[j]);
}

auto compx = [](Point& a, Point& b) {
    return a.x < b.x;
};
auto compy = [](Point& a, Point& b) {
    return a.y < b.y;
};



double solve(int left, int right)
{
    double ans = 1e-7;
    if(left==right) {
        return ans;
    }
    if(left==right-1) {
        return dist(pts[left], pts[right]);
    }
    int mid = (left+right)>>1;
    double ans1 = solve(left,mid);
    //注意：不是mid+1
    double ans2 = solve(mid,right);
    ans = min(ans1,ans2);
    int j = 0;
    for(int i=left; i<=right; i++) {
        if(abs(pts[i]->y-pts[mid]->y)<=ans) {
            a[j++] = i;
        }
    }
    sort(a, a+j, compx);
    for(int i=0; i<j; i++) {
        for(int k=i+1; k<j&&abs(pts[a[i]]->x - pts[a[k]]->x)<ans; k++) {
            double dis = dist2(a[i], a[k]);
            if(ans>dis) {
                ans = dis;
            }
        }
    }
    return ans;
}

void ptInArea(const Point* locCoordinates, vector<Point*>& ptinArea,
              int x1, int x2, int y1, int y2, int type)
{
    switch (type) {
    case 1:
        for (int i = 0; i < num; ++i) {
            if (x1 <= locCoordinates[i].x && locCoordinates[i].x <= x2)
                pts.push_back(locCoordinates + i);
        }
        break;
    case 2:
        for (int i = 0; i < num; ++i) {
            if (y1 <= locCoordinates[i].y && locCoordinates[i].y <= y2)
                pts.push_back(locCoordinates + i);
        }
        break;
    case 3:
        for (int i = 0; i < num; ++i) {
            if (x1 <= locCoordinates[i].x && locCoordinates[i].x <= x2
                    && y1 <= locCoordinates[i].y && locCoordinates[i].y <= y2)
                pts.push_back(locCoordinates + i);
        }
        break;
    default:
        break;
    }
}

vector<int> nearestLoc(int num, Point* locCoordinates, int tripCount,
                       int** tripDetails)
{
    vector<int> distVec;
    a = new int[num];

    pts.reserve(num);


    distVec.reserve(tripCount);

    int x1, x2;
    int y1, y2;

    for (int iTrip = 0; iTrip < tripCount; iTrip++) {
        int type = tripDetails[iTrip][0];
        switch (type) {
        case 0:
            x1 = tripDetails[iTrip][1];
            x2 = tripDetails[iTrip][2];
            break;
        case 1:
            y1 = tripDetails[iTrip][1];
            y2 = tripDetails[iTrip][2];
            break;
        case 2:
            x1 = tripDetails[iTrip][1];
            x2 = tripDetails[iTrip][2];
            y1 = tripDetails[iTrip][1];
            y2 = tripDetails[iTrip][2];
            break;
        default:
            break;
        }
        pts.clear();
        ptInArea(locCoordinates, pts, x1, x2, y1, y2, type);
        solve(0, pts.size()-1);
    }
}

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    return 0;
}
