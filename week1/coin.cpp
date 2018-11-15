#include <iostream>
#include <vector>

using namespace std;

void test(int cases){
 for(int c=0; c < cases; c++){
  int n, k, nrCoinsPerSide, res = -1, resDiff = -1, tmp;
  char op;
  cin >> n;
  vector<bool> boolVecHeavy(n,true), boolVecLight(n,true);
  cin >> k;

  //different weighings
  for(int l=0; l < k; l++){
   cin >> nrCoinsPerSide;
   vector<int> left(nrCoinsPerSide), right(nrCoinsPerSide), noSuspect(n,false);

//fill left side
   for(int i=0; i<nrCoinsPerSide; i++){
    cin >> tmp;
    left[i] = tmp;
   }

//fill right side
   for(int i=0; i<nrCoinsPerSide; i++){
    cin >> tmp;
    right[i] = tmp;
   }

//check result of weighing
  cin >> op;
  
//if '=' set all values from left & right to false, if '<' set left values to false, else set right values to false
   if(op == '='){
    for(int i=0; i<nrCoinsPerSide; i++){
     boolVecHeavy[left[i]-1] = false;
     boolVecHeavy[right[i]-1] = false;
     boolVecLight[left[i]-1] = false;
     boolVecLight[right[i]-1] = false;
    }
   }else{
    //all that weren't considered in this weighing cannot be suspected
     for(int i=0; i<nrCoinsPerSide; i++){
      noSuspect[left[i]-1] = true;
      noSuspect[right[i]-1] = true;
     }

     if(op == '<'){
      for(int i=0; i<nrCoinsPerSide; i++){
       boolVecHeavy[left[i]-1] = false;
       boolVecLight[right[i]-1] = false;
      }
     }else{
      for(int i=0; i<nrCoinsPerSide; i++){
       boolVecHeavy[right[i]-1] = false;
       boolVecLight[left[i]-1] = false;
      }
     }

     for(int i=0; i<n; i++){
      boolVecHeavy[i] = boolVecHeavy[i] & noSuspect[i];
      boolVecLight[i] = boolVecLight[i] & noSuspect[i];
     }

   }

  }
 
 for(int i=0; i<n; i++){
  if(boolVecHeavy[i]==true && boolVecLight[i]==true){
   if(res == -1){
    res = i+1;
   }else{
    res = 0;
    break;
   }
  }
  
 }
 for(int i=0; i<n; i++){
  if((boolVecHeavy[i] ^ boolVecLight[i]) == 1){
   if(resDiff == -1){
    resDiff = i+1;
   }else{
    resDiff = 0;
    break;
   }
  }
  
 }

 if(resDiff == -1)
  cout << res << endl;
 else
  cout << resDiff << endl;
//Debug
/*
 for(int i = 0; i < n; i++){
  cout << boolVecHeavy[i];
  if(boolVecHeavy[i] == 1)
   cout << "(" << (i+1) << ")";
  cout << " ";
 }
 cout << endl << "Light" << endl;
 for(int i = 0; i < n; i++){
  cout << boolVecLight[i] << " ";
 }
 cout << endl;
*/
//end debug
 }
}

int main(void){
 std::ios_base::sync_with_stdio(false);
 int cases;
 cin >> cases;
 test(cases);
}
