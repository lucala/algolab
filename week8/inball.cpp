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
 int n,d,a,b,tmpNorm;
 cin >> n;
 while(n != 0){
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  cin >> d;
  const int R = d;
  //optimization function
  lp.set_c(R,-1);

  for(int i=0; i<n; i++){
   tmpNorm = 0;
   for(int j=0; j<d; j++){
    cin >> a;
    lp.set_a(j,i,a);
    lp.set_a(j,i+n,a);
    tmpNorm += (a*a);
   }
   cin >> b;
   lp.set_b(i+n,b);
   tmpNorm = sqrt(tmpNorm);
   lp.set_a(R, i, tmpNorm);
   lp.set_b(i,b);
  }


   Solution s = CGAL::solve_linear_program(lp, ET());
   assert(s.solves_linear_program(lp));

    if(s.is_optimal()){
     cout << -1*ceil_to_double(s.objective_value()) << endl;
    }else if(s.is_unbounded()){
     cout << "inf" << endl;
    }else {
     cout << "none" << endl;
    }

   cin >> n;
  }

}
