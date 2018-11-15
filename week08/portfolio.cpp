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
 int n,m;
 cin >> n >> m;
 while(n != 0 && m != 0){
  vector<int> cost(n), returnRate(n), C(m), R(m), V(m);  
  vector<vector<int> > covariance(n, vector<int>(n));
  for(int i=0; i<n; i++){
   cin >> cost[i];
   cin >> returnRate[i];   
  }

  for(int i=0; i<n; i++){
   for(int j=0; j<n; j++){
    cin >> covariance[i][j];
   }
  }

  for(int i=0; i<m; i++){
   cin >> C[i] >> R[i] >> V[i];
  }

  for(int p=0; p<m; p++){

   Program lp(CGAL::LARGER, true, 0, false, 0);
   for(int i=0; i<n; i++){
    lp.set_a(i, 0, returnRate[i]);
   }
   lp.set_b(0, R[p]);

   for(int i=0; i<n; i++){
     lp.set_a(i, 1, cost[i]);
   }
    lp.set_b(1, C[p]);
    lp.set_r(1, CGAL::SMALLER);

   for(int i=0; i<n; i++){
    for(int j=0; j<=i; j++){
     //objective function
     lp.set_d(i,j, 2*covariance[i][j]);
    }
   }

   Solution s = CGAL::solve_quadratic_program(lp, ET());
   assert(s.solves_quadratic_program(lp));

    if(s.is_optimal() && s.objective_value() <= V[p]){
     cout << "Yes." << endl;
    }else{
     cout << "No." << endl;
    }
  }

  cin >> n >> m;

 }
}
