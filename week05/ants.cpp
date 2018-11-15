#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_iterator EdgeIt;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;
typedef property_map<Graph, edge_weight_t>::type WeightMap;


void test(){
 int n,e,s,a,b,w;
 cin >> n >> e >> s >> a >> b;
 WeightMap weightmap;
 vector<WeightMap> spWeights(s);
 vector<Graph> spGraphs(s);
 Vertex u,v;
 Edge ed;
 bool success;
 Graph totG(n);
 for(int i=0; i<s; i++){
  Graph G(n);
  weightmap = get(edge_weight, G);
  spGraphs[i] = G;
  spWeights[i] = weightmap;
 }

 for(int i = 0; i < e; i++){

  cin >> u >> v;
  for (int sp = 0; sp < s; sp++) {
  
   cin >> w;
   tie(ed, success) = add_edge(u, v, spGraphs[sp]);
   spWeights[sp][ed] = w;			
   //assert(source(e, G) == u && target(e, G) == v);
//cout << "uv " << u << v << " with weight " << spWeights[sp][ed] << endl;
  }

 }

 //hive indices
 vector<int> hive(s);
 for(int i = 0; i < s; i++){
  cin >> hive[i];
 }

 //create MST for each species
 //prim MST
 vector< vector<Vertex> > primpredmaps(s);
 for(int i = 0; i < s; i++){
 vector<Vertex> primpredmap(n);
 int start = hive[i];
 Graph G = spGraphs[i];
 prim_minimum_spanning_tree(G, make_iterator_property_map(primpredmap.begin(), get(vertex_index, G)), root_vertex(start));

 spGraphs[i] = G;
 primpredmaps[i] = primpredmap;

 }
 

 //build big graph
 WeightMap totWeightmap = get(edge_weight,totG), currWeightMap;
 for(int i = 0; i < s; i++){
  vector<Vertex> primpredmap = primpredmaps[i];
  Graph mst = spGraphs[i];
  currWeightMap = spWeights[i];
  for(int j=0; j<n; j++){
   u = j;
   OutEdgeIt oebeg, oeend;
   for(tie(oebeg, oeend) = out_edges(u, mst); oebeg != oeend; oebeg++){
    v = target(*oebeg, mst);
    if(primpredmap[u] == v){
     tie(ed, success) = add_edge(u,v,totG);
     totWeightmap[ed] = currWeightMap(*oebeg);
//cout << "vertices u/v=" << u << " " << v << " with weight " << currWeightMap(ed) << " and " << spWeights[i][ed] << endl;
    }

   }
  }


 }

 //dijkstra
 vector<Vertex> predmap(n);
 vector<int> distmap(n);
 Vertex startv = a;
 dijkstra_shortest_paths(totG, startv, predecessor_map(make_iterator_property_map(predmap.begin(),get(vertex_index,totG))).
  distance_map(make_iterator_property_map(distmap.begin(), get(vertex_index, totG))));
 int dist = distmap[b];
 
 cout << dist << endl;
 

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
