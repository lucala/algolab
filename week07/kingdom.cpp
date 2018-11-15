#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <cassert>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_capacity_t, long, property<edge_residual_capacity_t, long, property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;

class EdgeAdder{
 Graph &G;
 EdgeCapacityMap &capacitymap;
 ReverseEdgeMap &revedgemap;

public:
 EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap): G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

 void addEdge(int from, int to, long capacity){
  Edge e, reverseE;
  bool success;
  tie(e,success) = add_edge(from, to, G);
  tie(reverseE, success) = add_edge(to, from, G);
  capacitymap[e] = capacity;
  capacitymap[reverseE] = 0;
  revedgemap[e] = reverseE;
  revedgemap[reverseE] = e;
 }
};




void test(){
 int l,p,g,d,f,t,c,C;
 cin >> l >> p;

 Graph G(l+2);

 EdgeCapacityMap capacitymap = get(edge_capacity, G);
 ReverseEdgeMap revedgemap = get(edge_reverse, G);
 ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
 EdgeAdder eaG(G, capacitymap, revedgemap);
 
 int resMust=0;
 //fill graph //first m are games, second n are players
 vector<int> vecStationHas(l), vecStationMust(l);
 for(int i=0; i<l; i++){
  cin >> g >> d;
  vecStationHas[i] = g;
  vecStationMust[i] = d;
 }

 for(int i=0; i<p; i++){
  cin >> f >> t >> c >> C;
  eaG.addEdge(f, t, C-c);
  //adjust for demands
  vecStationMust[f] += c;
  vecStationMust[t] -= c;
 }

 Vertex src = add_vertex(G);
 Vertex sink = add_vertex(G);
 for(int i = 0; i<l; i++){
  eaG.addEdge(src, i, vecStationHas[i]);
  if(vecStationMust[i] > 0){
   eaG.addEdge(i, sink, vecStationMust[i]);
   resMust += vecStationMust[i];
  }
 }


 long flow = push_relabel_max_flow(G, src, sink);
 //for(int i=0; i<n; i++){
 // if(edge_capacity
 //}
 if(flow == resMust)
  cout << "yes" << endl;
 else
  cout << "no" << endl;
 

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
