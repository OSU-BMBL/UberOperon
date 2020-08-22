#ifndef GOST_EDGE_WEIGHT_H_
#define GOST_EDGE_WEIGHT_H_
#include <set>
#include "gene_set_type.h"
#include "bipartite_graph.h"
template <typename M> class EdgeWeight {
public:
  EdgeWeight(const std::pair<std::set<OperonId>, std::set<OperonId> > & name_set_value, const std::set<std::pair<gene_pair_t, WeightPair> >& edge_set_value, const size_t& weight_value, typename std::list<BipartiteGraph<gene_t, M> >::iterator temp1, typename std::list<BipartiteGraph<gene_t, M> >::iterator temp2) : edge_name_set_(name_set_value), weight_(weight_value), edge_set_(edge_set_value) {
    main_iterator_ = temp1;
    secondary_iterator_ = temp2;
  }
  //static bool slow_compare(const EdgeWeight& first, const EdgeWeight& second) {
  // if (first.weight_ > second.weight_) return true;
  // if (first.weight_ < second.weight_) return false;
  // if (first.weight_ == 1) return first.edge_set_.begin()->second.first < second.edge_set_.begin()->second.first;  // Unbearable slow!!!!!!!!!!
  // return (first.edge_set_.size() < second.edge_set_.size());
  //}
  static bool slow_compare(const EdgeWeight& first, const EdgeWeight& second) {
    if (first.weight_ > second.weight_) return true;
    if (first.weight_ < second.weight_) return false;
    if (first.weight_ == 1 && first.edge_set_.size() == second.edge_set_.size()) return first.edge_set_.begin()->second.first < second.edge_set_.begin()->second.first;  // Unbearable slow!!!!!!!!!!
    return (first.edge_set_.size() < second.edge_set_.size());
  }
  static bool compare(const EdgeWeight& first, const EdgeWeight& second) {
   if (first.weight_ > second.weight_) return true;
   if (first.weight_ < second.weight_) return false;
   return (first.edge_set_.size() < second.edge_set_.size());
  }
  void Update(const std::pair<std::set<OperonId>, std::set<OperonId> > & name_set_value, const std::set<std::pair<gene_pair_t, WeightPair> >& edge_set_value, const size_t& weight_value, typename std::list<BipartiteGraph<gene_t, M> >::iterator iterator1, typename std::list<BipartiteGraph<gene_t, M> >::iterator iterator2) {
    edge_name_set_ = name_set_value;
    weight_ = weight_value;
    edge_set_ = edge_set_value;
    main_iterator_ = iterator1;
    secondary_iterator_ = iterator2;
  }
  const std::pair<std::set<OperonId>, std::set<OperonId> > & edge_name_set() const {
    return edge_name_set_;
  }
  const std::set<std::pair<gene_pair_t, WeightPair> >& edge_set() const {
    return edge_set_;
  }
  size_t weight() const {
    return weight_;
  }
  mutable typename std::list<BipartiteGraph<gene_t, M> >::iterator main_iterator_, secondary_iterator_;
private:
  std::pair<std::set<OperonId>, std::set<OperonId> > edge_name_set_; // edge name between vertex 1 and 2 (operon code)
  std::set<std::pair<gene_pair_t, WeightPair> > edge_set_; // the true edge list of gene pairs
  size_t weight_; // weight between the vertices
};
#endif // GOST_EDGE_WEIGHT_H_
