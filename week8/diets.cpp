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
 int n,m,min,max;
 cin >> n >> m;
 while(n != 0 && m != 0){
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  vector<int> minVec(n), maxVec(n), price(m);  
  vector<vector<int> > nutInFood(m, vector<int>(n));

  for(int i=0; i<n; i++){
   cin >> minVec[i];
   cin >> maxVec[i];   
  }
  for(int i=0; i<m; i++){
   cin >> price[i];
   for(int j=0; j<n; j++){
    cin >> nutInFood[i][j];
   }
  }
  
  
  for(int i=0; i<m; i++){
   for(int j=0; j<n; j++){
    //maximum total nutrition of type j
    lp.set_a(i, j, nutInFood[i][j]);
    //minimum total nutrition of type j
    lp.set_a(i, j+n, -nutInFood[i][j]);
   }
   
   //set objective function
   lp.set_c(i, price[i]);
  }

  //set rhs for nutrition constraints
  for(int j=0; j<n; j++){
   lp.set_b(j, maxVec[j]);
   lp.set_b(j+n, -minVec[j]);
  }

  Solution s = CGAL::solve_nonnegative_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));

   if(s.is_optimal()){
    cout << floor_to_double(s.objective_value()) << endl;
   }else{
    cout << "No such diet." << endl;
   }

  cin >> n >> m;

 }
}
