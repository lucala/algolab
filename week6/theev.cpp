#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <cmath>
#include <set>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

class myComparator
{
public:
 bool operator() (pair<K::Point_2,K::FT> lhs, pair<K::Point_2,K::FT> rhs)
 {
  return (lhs.second > rhs.second);
 }
};

int64_t ceil_to_double(const K::FT& x){
 double a = std::ceil(CGAL::to_double(x));
 while(a < x) a += 1;
 while(a-1 >= x) a -= 1;
 return (int64_t)a;
}

int main(){
 int z, nrCities;
 int64_t px, py;
 cin >> z;
 for(int cas = 0; cas < z; cas++){
  
  set<pair<K::Point_2,K::FT>, myComparator> mySet;

  cin >> nrCities;
  //TheirCity
  cin >> px >> py;
  K::Point_2 TCp(px,py);
  mySet.insert(make_pair(TCp,0));

  for(int i=0; i<nrCities-1; i++){
   cin >> px;
   cin >> py;
   K::Point_2 p(px,py);
   K::FT sqDist = CGAL::squared_distance(TCp,p);
   mySet.insert(make_pair(p, sqDist));
  }  

  //special case nrCities <= 2
  if(nrCities <= 2){
   cout << 0 << endl;
   continue;
  }


  K::FT currRadiusSq, boundingRadiusSq, bestRad;
  pair<K::Point_2,K::FT> curr, beforeCurr;
  //calculate

  //for first point
  curr = *(mySet.begin());
  K::Point_2 tmp(curr.first);
  Min_circle mc(tmp);
  bestRad = (++mySet.begin())->second;
  currRadiusSq = bestRad;
  boundingRadiusSq = 0;
  //for rest
  while(currRadiusSq > boundingRadiusSq){
   curr = *(mySet.begin());
   mc.insert(curr.first);
   mySet.erase(curr);
   beforeCurr = *(mySet.begin());
   currRadiusSq = beforeCurr.second;
   boundingRadiusSq = mc.circle().squared_radius();
   bestRad = min(bestRad, max(currRadiusSq,boundingRadiusSq));
  }


  cout << ceil_to_double(bestRad) << endl;


 }

}
