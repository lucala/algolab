#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>


using namespace boost;
using namespace std;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIt;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c) {
        Edge e, reverseE;
        bool success;
        tie(e, success) = add_edge(u, v, G);
        tie(reverseE, success) = add_edge(v, u, G);
        capacitymap[e] = c;
        capacitymap[reverseE] = 0;
        revedgemap[e] = reverseE; 
        revedgemap[reverseE] = e; 
    }
};

void test(){
 int m,n,tmp1, tmp2, tmpC;
 cin >> n >> m;

 Graph G(n);
 EdgeCapacityMap capacitymap = get(edge_capacity, G);
 ReverseEdgeMap revedgemap = get(edge_reverse, G);
 ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
 EdgeAdder eaG(G, capacitymap, revedgemap);

 for(int i=0; i<m; i++){
  cin >> tmp1 >> tmp2 >> tmpC;
  eaG.addEdge(tmp1, tmp2, tmpC);
 }

 int minFlow = numeric_limits<int>::max(), bestSource, bestSink;
 for(int i=1; i<n; i++){
  //find best sink
  int flow = push_relabel_max_flow(G, 0, i); 
  if(flow < minFlow){
   minFlow = flow;
   bestSource = 0;
   bestSink = i;
  }

  //find best source
  flow = push_relabel_max_flow(G, i, 0); 
  if(flow < minFlow){
   minFlow = flow;
   bestSource = i;
   bestSink = 0;
  }

 }


 push_relabel_max_flow(G, bestSource, bestSink);
 

 //bfs
 vector<int> vis(n, false);
 std::queue<int> Q;
 vis[bestSource] = true;
 Q.push(bestSource);
 while(!Q.empty()){
  const int u = Q.front();
  Q.pop();
  OutEdgeIt ebeg, eend;
  for(tie(ebeg, eend) = out_edges(u,G); ebeg != eend; ++ebeg){
   const int v = target(*ebeg, G);
   if(rescapacitymap[*ebeg] == 0 || vis[v]) continue;
   vis[v] = true;
   Q.push(v);
  }
 }

 cout << minFlow << endl << count(vis.begin(), vis.end(), true);
 for(int i = 0; i < n; i++){
  if(vis[i])
   cout << " " << i;
 }

 cout << endl;
}


int main(){
 int t;
 cin >> t;
 while(t--) test();
}
