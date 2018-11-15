#include <iostream>
#include <vector>

using namespace std;

void test(int cases){
 for(int c=0; c < cases; c++){
  int n;
  double v, sum = 0;
  cin >> n;
  for(int i=0; i < n; i++){
   cin >> v;
   sum += v;
  }
 
 cout << sum << endl;
 }
}

int main(void){
 int cases;
 cin >> cases;
 test(cases);
}
