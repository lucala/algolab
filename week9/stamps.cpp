#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Gmpzf ET;
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


using namespace std;

int floor_to_double(const CGAL::Quotient<ET>& x){
 double a = floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}

int ceil_to_double(const CGAL::Quotient<ET>& x){
 double a = ceil(CGAL::to_double(x));
 while (a < x) a += 1;
 while (a-1 >= x) a -= 1;
 return a;
}


void test(){
 int l, s, w, x, y, M, a, b, c, d;
 cin >> l >> s >> w;
 vector<K::Point_2> lamps(l), stamps(s);
 for(int i=0; i<l; i++){
  cin >> x >> y;
  lamps[i] = K::Point_2(x,y);
 }

 vector<int> intensity(s);
 for(int i=0; i<s; i++){
  cin >> x >> y >> M;
  stamps[i] = K::Point_2(x,y);
  intensity[i] = M;
 }

 vector<K::Segment_2> walls(w);
 for(int i=0; i<w; i++){
  cin >> a >> b >> c >> d;
  walls[i] = K::Segment_2(K::Point_2(a,b),K::Point_2(c,d));
 }

 //define lp
 Program lp(CGAL::SMALLER, true, 1, true, 4096); //bounds?
 int constcount = 0;
 for(int i=0; i<s; i++){
  for(int j=0; j<l; j++){
   K::Segment_2 lightPath(lamps[j],stamps[i]);
   
   //check if lightPath intersects any wall
   bool occluded = false;
   for(int v=0; v<w; v++){
    if(CGAL::do_intersect(lightPath, walls[v])){
     occluded = true;
     break;
    }
   }

   if(!occluded){
    //set constraints
    float idist = 1.0/(CGAL::to_double(lightPath.squared_length()));
    lp.set_a(j, constcount, idist);
    lp.set_a(j, constcount+1, idist);
   }

  }

  //set rhs of constraints
  lp.set_b(constcount, intensity[i]);
  lp.set_b(constcount+1, 1);
  lp.set_r(constcount+1, CGAL::LARGER);
  constcount+=2;
   
 }

 for(int i=0; i<l; i++){
  lp.set_c(l,1);
 }
 
 Solution sol = CGAL::solve_nonnegative_linear_program(lp, ET());
 assert(sol.solves_linear_program(lp));

 if(!sol.is_infeasible()){
    cout << "yes" << endl;
   }else{
    cout << "no" << endl;
   }


}


int main(){
 int t;
 cin >> t;
 while(t--) test();
}
