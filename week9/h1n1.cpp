#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <queue>
#include <cassert>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::All_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;


int main(){
 int n, x, y;
 cin >> n;
 while(n != 0){

  vector<K::Point_2> infected(n);

  for(int i=0; i<n; i++){
   cin >> x >> y;
   K::Point_2 p(x,y);
   infected[i] = p;
  }

  Triangulation t;
  t.insert(infected.begin(), infected.end());

  //not visited
  for(Face_iterator f = t.all_faces_begin(); f != t.all_faces_end(); ++f){
   f->info() = -1;
  }

  int nrEscapees;
  cin >> nrEscapees;

  long radius;
  for(int i=0; i<nrEscapees; i++){
   cin >> x >> y >> radius;
   K::Point_2 currLoc(x,y);
   
   K::Point_2 closest = t.nearest_vertex(currLoc)->point();
   double dist = CGAL::to_double(CGAL::squared_distance(currLoc, closest));
   
   if(dist < radius){
    cout << "n";
    continue;
   }

   queue<Face_handle> faceQ;
   Face_handle face = t.locate(currLoc);
   faceQ.push(face);
   face->info() = i;

   bool saved = false;

   while(!faceQ.empty()){
    Face_handle currF = faceQ.front();
    faceQ.pop();
    
    if(t.is_infinite(currF)){
     cout << "y";
     saved = true;
     break;
    }


    for(int j=0; j<3; j++){
     if(currF->neighbor(j)->info() < i && CGAL::to_double(t.segment(Triangulation::Edge(currF,j)).squared_length()) >= radius*4){
      faceQ.push(currF->neighbor(j));
      currF->neighbor(j)->info() = i;
     }
    }
   }
   if(!saved)
    cout << "n";
  }

  cout << endl;

  cin >> n;
 }
}
