#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_iterator EdgeIt;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

void testcases(){
 int n,m;
 cin >> n >> m;
 Graph G(n);
 WeightMap weightmap = get(edge_weight, G);
 
 for(int i=0; i<m; i++){
  Edge e; bool success;
  Vertex u, v;
  cin >> u;
  cin >> v;
  tie(e, success) = add_edge(u,v,G);
  cin >> weightmap[e];
  assert(source(e,G) == u && target(e,G) == v);
 }
 
 //kruskal
 vector<Edge> mst;
 vector<Vertex> kruskalpredmap(n);
 vector<int> rankmap(n);
 kruskal_minimum_spanning_tree(G, back_inserter(mst),
	rank_map(make_iterator_property_map(rankmap.begin(), get(vertex_index, G))).
	predecessor_map(make_iterator_property_map(kruskalpredmap.begin(), get(vertex_index, G))));

 int totalWeight = 0;
 vector<Edge>::iterator mstbeg, mstend = mst.end();
 for(mstbeg = mst.begin(); mstbeg != mstend; ++mstbeg){
  totalWeight += weightmap[*mstbeg];
 }
 
/*
 for(size_t i=0; i<mst.size(), i++){
  Edge e = mst[i];
  Vertex u = source(e,G);
  Vertex v = target(e,G);
  
 }
*/


 vector<Vertex> predmap(n);
 vector<int> distmap(n);
 Vertex start = 0;
 dijkstra_shortest_paths(G, start, predecessor_map(make_iterator_property_map(predmap.begin(),get(vertex_index,G))).
	distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, G))));

 int maxdist = 0;
 Vertex furthest = start;
 int reachable = 0;
 for(int i=0; i<n; i++){
  if(distmap[i] < INT_MAX){
   reachable++;
   if(distmap[i] > maxdist){
    maxdist = distmap[i];
    furthest = i;
   }
  }
 }

 cout << totalWeight << " " << maxdist << endl;


}


int main(){
 ios_base::sync_with_stdio(false);
 int T;
 cin >> T;
 while(T--) testcases();
 return 0;
}
