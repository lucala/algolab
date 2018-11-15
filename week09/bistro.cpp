#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <cassert>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;


int main(){
 int n, numberG, x, y, possibleNr;
 cout << fixed << setprecision(0);
 cin >> n;
 while(n != 0){

  vector<K::Point_2> pts(n);

  for(int i=0; i<n; i++){
   cin >> x >> y;
   K::Point_2 p(x,y);
   pts[i] = p;
  }

  Triangulation t;
  t.insert(pts.begin(), pts.end());

  cin >> possibleNr;
  for(int i=0; i<possibleNr; i++){
   cin >> x >> y;
   K::Point_2 possPt(x,y);
  
   K::Point_2 closest = t.nearest_vertex(possPt)->point();
   cout << CGAL::to_double(CGAL::squared_distance(closest, possPt)) << endl;

  }

  cin >> n;
 }
}
