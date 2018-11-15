#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

struct Triangle{
 K::Line_2 sides[3];
 bool left[3];
 vector<int> vec;
};

int main(){
 int z;
 cin >> z;
 for(int cas=0; cas < z; cas++){
  int64_t px, py;
 
  int nrLegs, nrMaps;
  cin >> nrLegs >> nrMaps;
  queue<K::Point_2> q;
  for(int i = 0; i < nrLegs; i++){
   cin >> px >> py;

   q.push(K::Point_2(px,py));
  }

  //build legs
  vector<K::Segment_2> vecSeg(nrLegs-1);
  K::Point_2 p1, p2;
  int ind = 0;
  while(!q.empty()){
   p1 = q.front();
   q.pop();
   if(q.empty())
    break;
   p2 = q.front();
   vecSeg[ind] = K::Segment_2(p1,p2);
   ind++;
  }

  //build side of triangle
  int px1,px2,px3,px4,px5,px6,py1,py2,py3,py4,py5,py6;
  Triangle T;
  vector<Triangle> vecTri(nrMaps);
  for(int i=0; i<nrMaps; i++){
   cin >> px1 >> py1 >> px2 >> py2 >> px3 >> py3 >> px4 >> py4 >> px5 >> py5 >> px6 >> py6;
   T = Triangle();  

   T.sides[0] = K::Line_2(K::Point_2(px1,py1), K::Point_2(px2,py2));
   T.sides[1] = K::Line_2(K::Point_2(px3,py3), K::Point_2(px4,py4));
   T.sides[2] = K::Line_2(K::Point_2(px5,py5), K::Point_2(px6,py6));

   if(T.sides[0].has_on_negative_side(K::Point_2(px3,py3)))
    T.left[0] = true;
   if(T.sides[1].has_on_negative_side(K::Point_2(px5,py5)))
    T.left[1] = true;
   if(T.sides[2].has_on_negative_side(K::Point_2(px1,py1)))
    T.left[2] = true;

   vecTri[i] = T;
  }


  for(int i=0; i<nrMaps; i++){
   T = vecTri[i];

   for(int j=0; j<nrLegs-1; j++){
    K::Point_2 t1 = vecSeg[j].source(), t2 = vecSeg[j].target();
    if((T.left[0] == T.sides[0].has_on_negative_side(t1) || T.sides[0].has_on(t1)) && (T.left[0] == T.sides[0].has_on_negative_side(t2) || T.sides[0].has_on(t2))
     && (T.left[1] == T.sides[1].has_on_negative_side(t1) || T.sides[1].has_on(t1)) && (T.left[1] == T.sides[1].has_on_negative_side(t2) || T.sides[1].has_on(t2))
     && (T.left[2] == T.sides[2].has_on_negative_side(t1) || T.sides[2].has_on(t1)) && (T.left[2] == T.sides[2].has_on_negative_side(t2) || T.sides[2].has_on(t2))){
     //leg is contained in this triangle
     T.vec.push_back(j);
//cout << "tri=" << i << " thinks leg nr " << j << " is contained in him" << endl;
    }
   }
   vecTri[i] = T;

  }


  //calculation
  int it = 0, goal = nrLegs-1, curr = 0, itU = 0, itL = 0, size, best = nrMaps;
  vector<int> pool(nrLegs-1), tmpVec;
  while(itL < nrMaps){
//cout << " itU=" << itU << " itL=" << itL << endl;
//cout << "curr=" << curr << endl;
   if(curr < goal && itU < nrMaps){
    T = vecTri[itU];
    tmpVec = T.vec;
    size = tmpVec.size();

//cout << "entering IF" << endl;
    for(int i = 0; i < size; i++){
     pool[tmpVec[i]] += 1;
     if(pool[tmpVec[i]] == 1)
      curr++;
    }
    itU++;
   }else{
//cout << " itU=" << itU << " itL=" << itL;
    if(curr == goal && (itU-itL+1) < best){
     best = itU-itL+1;
    }
//cout << "entering ELSE" << endl;
    T = vecTri[itL];
    tmpVec = T.vec;
    size = tmpVec.size();
//cout << "going to decrement by vec with size " << size << endl;
    for(int i = 0; i < size; i++){
     pool[tmpVec[i]] -= 1;
     if(pool[tmpVec[i]] == 0)
      curr--;
    }
    itL++;
   }


  }
  
cout << best-1 << endl;

 }

}
