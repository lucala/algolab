#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

int main(){
 int c;
 int64_t x1, x2, y1, y2, px1, px2, py1, py2;
 bool hit;
 cin >> c;
 while(c != 0){
  
  cin >> x1;
  cin >> y1;
  cin >> x2;
  cin >> y2;
  K::Point_2 o(x1,y1), d(x2,y2);
  K::Ray_2 ray(o,d);
  vector<K::Segment_2> segments(c);

  for(int i=0; i<c; i++){
   cin >> px1;
   cin >> py1;
   cin >> px2;
   cin >> py2;
   K::Point_2 p1(px1,py1), p2(px2,py2);
   K::Segment_2 s(p1,p2);
   segments[i] = s;

  }  

  hit = false;
  for(int i=0; i < c; i++){
   if(CGAL::do_intersect(ray, segments[i])){
    hit = true;
    break;
   }
  }
  
  if(hit)
   cout << "yes" << endl;
  else
   cout << "no" << endl;

  cin >> c;
 }

}
