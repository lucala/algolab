#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void testQuad(int cases){
 for(int c=0; c < cases; c++){
  int n,k,v;
  cin >> n;
  cin >> k;
  vector<int> base(n);
  for(int i=0; i<n; i++){
   cin >> v;
   base[i] = v;
  }

//partial sum
  for(int i=1; i<n; i++){
   base[i] += base[i-1];
  }

int s;
vector<int> bestSoFar(3);
bestSoFar[0] = 0;
bestSoFar[1] = n-1;
bestSoFar[2] = abs(base[n-1] - k);

  for(int i=0; i<n; i++){
   for(int j=i; j<n; j++){
    if(i==0)
     s = base[j];
    else
     s = base[j] - base[i-1];
    
    if(abs(s-k) < bestSoFar[2]){
     bestSoFar[0] = i;
     bestSoFar[1] = j;
     bestSoFar[2] = abs(s-k);
    }else if(abs(s-k) == bestSoFar[2]){ //lexicographical solution
     if(i < bestSoFar[0] || (i == bestSoFar[0] && j < bestSoFar[1])){
      bestSoFar[0] = i;
      bestSoFar[1] = j;
     }
    }

   }
  }

 cout << bestSoFar[0] << " " << bestSoFar[1] << endl;

 }
}

//----------

void testLin(int cases){
 for(int c=0; c < cases; c++){
  int n,k,v;
  cin >> n;
  cin >> k;
  vector<int> base(n), partial(n);
  for(int i=0; i<n; i++){
   cin >> v;
   base[i] = v;
  }

//partial sum
  partial[0] = base[0];
  for(int i=1; i<n; i++){
   partial[i] = partial[i-1] + base[i];
  }

//int s, curr = 0, startIndex = 0;
vector<int> bestSoFar(3);
bestSoFar[0] = 0;
bestSoFar[1] = 0;
bestSoFar[2] = abs(partial[0]-k);

 int i=0,j=0,x;
 while(i < n && j < n){
 
  if(i==0)
   x = partial[j];
  else
   x = partial[j] - partial[i-1];

  if(abs(x - k) < bestSoFar[2]){
//cout << " old_i=" << bestSoFar[0] << " old_j=" << bestSoFar[1] << " old_dist=" << bestSoFar[2] << endl;
//cout << " i=" << i << " j=" << j << " abs(x-k)=" << abs(x-k) << endl;
   bestSoFar[0] = i;
   bestSoFar[1] = j;
   bestSoFar[2] = abs(x - k);
  }

  if(x == k){
   break;
  }

  if(i == j){
   j++;
  }else{
   if(x < k){
    j++;
   }else if(x > k){
    i++;
   }
  }


 }
 cout << bestSoFar[0] << " " << bestSoFar[1] << endl;

 }
}


int main(void){
 int cases;
 cin >> cases;
 //testQuad(cases);
 testLin(cases);
}
