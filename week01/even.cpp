#include <iostream>
#include <vector>

using namespace std;

void test(int cases){
 for(int c=0; c < cases; c++){
  int n,v,counter = 0;
  cin >> n;
  vector<int> partial(n), Odd(n), Even(n);
  cin >> v;

//partial sum
  partial[0] = v;
  for(int i=1; i<n; i++){
   cin >> v;
   partial[i] = v + partial[i-1];
  }

//calculate
 if(partial[0] % 2 == 1)
  Odd[0]++;
 else{
  Even[0]++;
  counter++;
 }

 for(int i=1; i<n; i++){
  Even[i] = Even[i-1];
  Odd[i] = Odd[i-1];
  if(partial[i] % 2 == 0){
   Even[i]++;
   counter += Even[i-1]+1;
  }else{
   Odd[i]++;
   counter += Odd[i-1];
  }
 }

//print result
 cout << counter << endl;

 }
}

int main(void){
 int cases;
 cin >> cases;
 test(cases);
}
