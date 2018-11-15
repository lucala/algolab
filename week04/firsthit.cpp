#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <CGAL/Ray_2.h>
#include <CGAL/Segment_2.h>
#include <limits.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kin;

int64_t floor_to_double(const K::FT& x){
 double a = std::floor(CGAL::to_double(x));
 while(a > x) a -= 1;
 while(a+1 <= x) a += 1;
 return (int64_t)a;
}


int main(){
 int c;
 long x1, x2, y1, y2, px1, px2, py1, py2;
 K::FT dist, dist1, dist2, bestX, bestY, best;
 bool hit, firstEncounteredHit;
 K::Segment_2 seg;
 Kin::Segment_2 segIn;

 cin >> c;
 while(c != 0){
  
  cin >> x1;
  cin >> y1;
  cin >> x2;
  cin >> y2;
  K::Point_2 o(x1,y1), d(x2,y2);
  K::Ray_2 ray(o,d);
  Kin::Point_2 oIn(x1,y1), dIn(x2,y2);
  Kin::Ray_2 rayIn(oIn,dIn);
  vector<K::Segment_2> segments(c);
  vector<Kin::Segment_2> segmentsIn(c);
  vector<int> indexVec(c);

  for(int i=0; i<c; i++){
   indexVec[i] = i;
   cin >> px1;
   cin >> py1;
   cin >> px2;
   cin >> py2;
   K::Point_2 p1(px1,py1), p2(px2,py2);
   K::Segment_2 s(p1,p2);
   segments[i] = s;

 //inexact
   Kin::Point_2 pin1(px1,py1), pin2(px2,py2);
   Kin::Segment_2 sin(pin1,pin2);
   segmentsIn[i] = sin;
  }

  random_shuffle(indexVec.begin(), indexVec.end());

  hit = false;
  K::Segment_2 bestSeg;
  int ind, i;
  for(i=0; i < c; i++){
   ind = indexVec[i];
   segIn = segmentsIn[ind];
   if(CGAL::do_intersect(rayIn, segIn)){
    hit = true;
    seg = segments[ind];
    auto its = CGAL::intersection(ray, seg);
    if(const K::Point_2 *itsP = boost::get<K::Point_2>(&*its)){
     dist = CGAL::squared_distance(o,*itsP);
     bestX = itsP->x();
     bestY = itsP->y();
     best = dist;
     bestSeg = K::Segment_2(o,K::Point_2(bestX,bestY));
     break;
      
    }else{
     const K::Segment_2 *itsS = boost::get<K::Segment_2>(&*its);
     dist1 = CGAL::squared_distance(o, itsS->source());
     dist2 = CGAL::squared_distance(o, itsS->target());
     if(dist1 < dist2){
      bestX = itsS->source().x();
      bestY = itsS->source().y();
      best = dist1;
      bestSeg = K::Segment_2(o,K::Point_2(bestX,bestY));
      break;
     }else{
      bestX = itsS->target().x();
      bestY = itsS->target().y();
      best = dist2;
      bestSeg = K::Segment_2(o,K::Point_2(bestX,bestY));
      break;
     }
    }
 
   }
  }
  

//---

  //continue where i left off
  for(int j = i; j < c; j++){
   ind = indexVec[j];
   seg = segments[ind];
   if(CGAL::do_intersect(bestSeg, seg)){
    auto its = CGAL::intersection(bestSeg, seg);
    if(const K::Point_2 *itsP = boost::get<K::Point_2>(&*its)){
      bestX = itsP->x();
      bestY = itsP->y();
      best = dist;
      bestSeg = K::Segment_2(o,K::Point_2(bestX,bestY));
      
    }else{
     const K::Segment_2 *itsS = boost::get<K::Segment_2>(&*its);
     dist1 = CGAL::squared_distance(o, itsS->source());
     dist2 = CGAL::squared_distance(o, itsS->target());
     if(dist1 < dist2){
       bestX = itsS->source().x();
       bestY = itsS->source().y();
       best = dist1;
       bestSeg = K::Segment_2(o,K::Point_2(bestX,bestY));
     }else{
       bestX = itsS->target().x();
       bestY = itsS->target().y();
       best = dist2;
       bestSeg = K::Segment_2(o,K::Point_2(bestX,bestY));
     }

    }
 
   }
  }
  

  if(!hit)
   cout << "no" << endl;
  else
   cout << floor_to_double(bestX) << " " << floor_to_double(bestY) << endl;

  cin >> c;
 }

}
