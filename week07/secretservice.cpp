#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <cassert>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_iterator EdgeIt;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;
typedef property_map<Graph, edge_weight_t>::type WeightMap;


struct Agent{
 int index;
 int start;
 int minDist;
 int selShelter;
 Agent(int index, int start): index(index), start(start){} 

 bool operator <(Agent rhs)
 {
  return (minDist < rhs.minDist);
 }
};


void test(){
 int n,m,a,s,c,d;
 cin >> n >> m >> a >> s >> c >> d;
 WeightMap weightmap;
 Graph G(n+s);
 Vertex u,v;
 
 //fill graph
 char w;
 int x,y,z;
 for(int i=0; i<m; i++){
  Edge e; bool success;
  cin >> w >> x >> y >> z;
  tie(e,success) = add_edge(x,y,G);
  weightmap[e] = z;
  if(w == 'L'){ //attach inverse edge
   tie(e,success) = add_edge(y,x,G);
   weightmap[e] = z;
  }
 }

 //fill agents vec
 //0=minimum distance, 1=agent index, 2=selected bunker, starting pos
 vector<Agent> agents;
 int tmpPos;
 for(int i=0; i<a; i++){
  cin >> tmpPos;
  agents.push_back(Agent(i,tmpPos));
 }

 //add dangling shelter node
 vector<int> availShelters(s,c);
 vector<Edge> shelterConn(s);
 int p;
 for(int i=0; i<s; i++){
  Edge e; bool success;
  cin >> p;
  tie(e,success) = add_edge(p,i+n,G);
  weightmap[e] = 0;
  shelterConn[i] = e;
 }

 vector<Agent> timer;
 int j=a;
 while(j > 0){
  
  for(int i=0; i<j; i++){
   //dijkstra
   vector<Vertex> predmap(n+s);
   vector<int> distmap(n+s);
   Vertex startv = agents[i].start;
   dijkstra_shortest_paths(G, startv, predecessor_map(make_iterator_property_map(predmap.begin(),get(vertex_index,G))).
    distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));
   int minDist = INT_MAX;
   for(int j=0; j<s; j++){
    if(availShelters[j]>0 && distmap[j+n]<minDist){
     agents[i].minDist = distmap[j+n];
     minDist = distmap[j+n];
     agents[i].selShelter = j;
    }
   }

  }


  //sort on maximum of minimum distance to find agent furthest away from shelter
  sort(agents.begin(), agents.end());
  
  Agent curr = agents[j-1];
  availShelters[curr.selShelter] -= 1;
//cout << "agent " << curr.index << " has route time=" << curr.minDist << " he is moving into shelter " << curr.selShelter+n <<endl;
  //plus time to log in himself
  timer.push_back(curr);

  //adjust graph
  weightmap[shelterConn[curr.selShelter]] += d;

  //remove agent from current list
  agents.pop_back();
  j--;

 }

 sort(timer.begin(), timer.end());
 Agent longA = timer[a-1];
 cout << longA.minDist + d << endl;
 

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
