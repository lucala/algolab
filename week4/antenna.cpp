#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <iostream>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <cmath>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

int main(){
 int z;
 int64_t px, py;
 bool hit;
 cin >> z;
 while(z != 0){
  K::Point_2 P[z];

  //nrHomes = c
  for(int i=0; i<z; i++){
   cin >> px;
   cin >> py;

   P[i] = K::Point_2(px,py);
  }  


  Min_circle mc(P, P+z, true);
  Traits::Circle c = mc.circle();
  cout << ceil(sqrt(c.squared_radius())) << endl;


  cin >> z;

 }

}
