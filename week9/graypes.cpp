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
 int n, numberG, x, y;
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
  bool noTime = true;
  K::FT best;
  for(Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
   K::FT time = t.segment(e).squared_length();
   if(time < best || noTime){
    best = time;
    noTime = false;
   }
  }

  cout << ceil(sqrt(CGAL::to_double(best)) * 50.0) << endl;

  cin >> n;
 }
}
