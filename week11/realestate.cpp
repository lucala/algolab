#include <iostream>
#include <cstdlib>

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
            property<edge_reverse_t, Traits::edge_descriptor,
                property <edge_weight_t, long> > > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type       EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::edge_iterator EdgeIt;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    void addEdge(int u, int v, long c, long w) {
        Edge e, reverseE;
        tie(e, tuples::ignore) = add_edge(u, v, G);
        tie(reverseE, tuples::ignore) = add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w;
        capacitymap[reverseE] = 0;
        weightmap[reverseE] = -w;
        revedgemap[e] = reverseE; 
        revedgemap[reverseE] = e; 
    }
};

void test(){
 int n,m,s;
 cin >> n >> m >> s;

 Graph G(n+m+s+2);
 EdgeCapacityMap capacitymap = get(edge_capacity, G);
 EdgeWeightMap weightmap = get(edge_weight, G);
 ReverseEdgeMap revedgemap = get(edge_reverse, G);
 ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
 EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

 vector<int> s_vec(s), m_vec(m);
 vector<vector<int> > n_vec(n, vector<int>(m));
 for(int i=0; i<s; i++){
  cin >> s_vec[i];
 } 

 for(int i=0; i<m; i++){
  cin >> m_vec[i];
 }

 int biggestPrice = 0;
 for(int i=0; i<n; i++){
  for(int j=0; j<m; j++){
   cin >> n_vec[i][j];
   if(n_vec[i][j] > biggestPrice)
    biggestPrice = n_vec[i][j];
  }
 }

 const int src = n+m+s;
 const int sink = n+m+s+1;

 for(int i=0; i<n; i++){
  for(int j=0; j<m; j++){
   eaG.addEdge(i,j+n,1,n_vec[i][j]*(-1) + biggestPrice);
  }
 }

 for(int i=0; i<m; i++){
  eaG.addEdge(i+n,n+m+m_vec[i]-1,1,0);
 }

 for(int i=0; i<s; i++){
  eaG.addEdge(i+n+m,sink,s_vec[i],0);
 }

 for(int i=0; i<n; i++){
  eaG.addEdge(src, i, 1, 0);
 }

 successive_shortest_path_nonnegative_weights(G, src, sink);
 int cost = find_flow_cost(G);
 int flow = 0;
 

 OutEdgeIt e, eend;
 for(tie(e, eend) = out_edges(vertex(src,G),G); e != eend; ++e) {
  flow += capacitymap[*e]-rescapacitymap[*e];
 }

 
 

 cout << flow << " " << -(cost - biggestPrice*flow) << endl;

}


int main(){
 int t;
 cin >> t;
 while(t--) test();
}
