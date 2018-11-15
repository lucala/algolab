#include <iostream>
#include <vector>

using namespace std;

void test(int cases){
 for(int c=0; c<cases; c++){
  int n,v;
  cin >> n;
  vector<int> heights(n);
  
//load vector
  for(int i=0; i<n; i++){
   cin >> v;
   heights[i] = v;
  }

//calculate dominos
  int heighest = heights[0];
  int res = 1;
  int currHeight;
  if(heighest > 1){
   for(int i=1; i<n; i++){
    currHeight = heights[i];
    heighest--;
    if(heighest < currHeight)
     heighest = currHeight;

    if(heighest == 1){
     res++;
     break;
    }else{
     res++;
    }
   }

  }
  

 cout << res << endl;
 }

}

int main(void){
 std::ios_base::sync_with_stdio(false);
 int cases;
 cin >> cases;
 test(cases);
}
