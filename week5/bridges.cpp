#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_iterator EdgeIt;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

class myComparator
{
public:
 bool operator() (pair<int,int> lhs, pair<int,int> rhs)
 {
  return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second));
 }
};

void test(){
 int n,m,s,t;
 cin >> n >> m;
 
 Graph G(n);
 for(int i=0; i<m; i++){
  cin >> s >> t;
  Edge e; bool success;
  tie(e,success) = add_edge(s,t,G);
 }
 
 WeightMap component = get(edge_weight, G);
 int ncc = biconnected_components(G, component);
//cout << "ncc=" << ncc << endl;
 if(ncc == 0){
  cout << 0 << endl;
 }else{

 vector<Vertex> art_points;
 articulation_points(G, back_inserter(art_points));

//cout << "size=" << art_points.size() << endl;
 EdgeIt ei, ei_end;
 vector<int> tmp(2), comInd(ncc), edVec(2*m);
 int result = 0;
 for(tie(ei, ei_end) = edges(G); ei != ei_end; ei++){
  tmp[0] = source(*ei, G);
  tmp[1] = target(*ei, G);
  //cout << component[*ei] << " with uv=" << tmp[0] << " " << tmp[1] << endl;
  if(comInd[component[*ei]] == 0){
  //cout << "equals0 " << component[*ei] << " with uv=" << tmp[0] << " " << tmp[1] << endl;
   sort(tmp.begin(), tmp.end());
   comInd[component[*ei]] = 1;
   edVec[2*component[*ei]] = tmp[0];
   edVec[2*component[*ei]+1] = tmp[1];
   result++;
  }else if(comInd[component[*ei]] != 2){
  //cout << "equals2 " << component[*ei] << " with uv=" << tmp[0] << " " << tmp[1] << endl;
   comInd[component[*ei]] = 2;
   result--;
  }
 }

 cout << result << endl;

 vector<pair<int,int> > tmpVec;
 for(int i=0; i<ncc; i++){
  if(comInd[i] == 1){
   tmpVec.push_back(make_pair(edVec[2*i],edVec[2*i+1]));
  }
 }
 
 sort(tmpVec.begin(), tmpVec.end(), myComparator());
 for(int i=0; i<tmpVec.size(); i++){
  cout<<tmpVec[i].first << " " << tmpVec[i].second << endl;
 }

 }

}


int main(){
 int n;
 cin >> n;
 while(n--) test();
}
