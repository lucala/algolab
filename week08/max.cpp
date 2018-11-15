#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


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


int main(){
 int p, a, b;
 cin >> p;
 while(p != 0){
  

  cin >> a >> b;

  if(p == 1){
   Program lp(CGAL::SMALLER, true, 0, false, 0);

   const int X = 0;
   const int Y = 1;
   lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);
   lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b);
   lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);
   lp.set_c(Y, -b); lp.set_d(X, X, 2*a);

   Solution s = CGAL::solve_nonnegative_quadratic_program(lp, ET());
   assert(s.solves_quadratic_program(lp));

   if(s.is_unbounded()){
    cout << "unbounded" << endl;
   }else if(s.is_infeasible()){
    cout << "no" << endl;
   }else{
    cout << floor_to_double(-s.objective_value()) << endl;
   }


  }else{
   Program lp(CGAL::LARGER, false, 0, false, 0);

   const int X = 0;
   const int Y = 1;
   const int Z = 2;

   //substitute z² = z
   lp.set_l(Z, true, 0);
   lp.set_u(X, true, 0);
   lp.set_u(Y, true, 0);

   lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, -4);
   lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_a(Z, 1, 1); lp.set_b(1, -(a*b));
   lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, -1);

   lp.set_d(X, X, 2*a);
   lp.set_d(Z, Z, 2);
   lp.set_c(Y, b);

   Solution s = CGAL::solve_quadratic_program(lp, ET());
   assert(s.solves_quadratic_program(lp));

   if(s.is_unbounded()){
    cout << "unbounded" << endl;
   }else if(s.is_infeasible()){
    cout << "no" << endl;
   }else{
    cout << ceil_to_double(s.objective_value()) << endl;
   }


  }

  cin >> p;

 }
}
