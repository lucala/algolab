#include <iostream>
#include <vector>

using namespace std;

int evenPairs(vector<int> partial){
  int n = partial.size();
  int counter = 0;
  vector<int> Odd(n), Even(n);

//partial sum
  for(int i=1; i<n; i++){
   partial[i] += partial[i-1];
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

 return counter;
}

void test(int cases){
 for(int c=0; c < cases; c++){
  int n, v, counter = 0;
  cin >> n;
  vector< vector<int> > base(n+1,vector<int>(n));

//read matrix
  for(int i=1; i < n+1; i++){
   for(int j=0; j < n; j++){
    cin >> v;
    base[i][j] = v;
   }
  }


//partial sum
  for(int i=1; i<n+1; i++)
   base[i][0] += base[i-1][0];

  for(int i=1; i < n+1; i++){
   for(int j=1; j < n; j++){
    base[i][j] += base[i-1][j];
   }
  }

//calculate
  for(int i=1; i < n+1; i++){
   for(int j=i; j < n+1; j++){
    vector<int> tmp(n);

    for(int c=0; c<n; c++)
     tmp[c] = base[j][c] - base[i-1][c];

    counter += evenPairs(tmp);
   }
  }
 
 cout << counter << endl;
//debug
/*
cout << "partial" << endl;
  for(int i=0; i < n+1; i++){
   for(int j=0; j < n; j++){
    cout << base[i][j] << " ";
   }
    cout << endl;
  }
*/
//end debug
 }
}

int main(void){
 int cases;
 cin >> cases;
 test(cases);
}
