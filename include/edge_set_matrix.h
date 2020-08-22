#ifndef GOST_EDGE_SET_MATRIX_H_
#define GOST_EDGE_SET_MATRIX_H_
#include <map>
#include <vector>
#include "edge_file_reader.h"
#include "rbh.h"
const std::set<std::pair<gene_pair_t, WeightPair> > kNullSet;

class EdgeSetMatrix {
public:
  EdgeSetMatrix(const std::map<gene_pair_t, WeightPair>& reader) {
    this->Load(reader);
  }
  void Process(const std::map<gene_t, OperonId>& u, std::map<gene_t, OperonId>& v);
  const std::set<std::pair<gene_pair_t, WeightPair> >& bipartite_graph_edge_set_matrix(const OperonId i, const OperonId j) const {
    if ((bipartite_graph_edge_set_map_matrix_.find(i) != bipartite_graph_edge_set_map_matrix_.end()) && (bipartite_graph_edge_set_map_matrix_.at(i).find(j) != bipartite_graph_edge_set_map_matrix_.at(i).end())) {
      return bipartite_graph_edge_set_map_matrix_.at(i).at(j);
    } else {
      return kNullSet;
    }
  }
private:
  void Add(const std::string& vertix_u, const std::string& vertix_v, double weight_u, double weight_v);
  void AddEdgeSet(const std::string& vertix_u, const std::string& vertix_v, double weight_u, double weight_v);
  void Load(const std::map<gene_pair_t, WeightPair>& reader);
  void UpdateRbh();
  std::map<OperonId, std::map<OperonId, std::set<std::pair<gene_pair_t, WeightPair> > > > bipartite_graph_edge_set_map_matrix_;
  std::map<gene_pair_t, WeightPair> edge_map_;
};
#endif // GOST_EDGE_SET_MATRIX_H_
