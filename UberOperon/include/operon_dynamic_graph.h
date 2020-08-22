/* Author: Qin Ma <maqin@csbl.bmb.uga.edu>, May. 10, 2010
* Usage: used to define the bipartite graph
*/
#ifndef GOST_OPERON_DYNAMIC_GRAPH_H_
#define GOST_OPERON_DYNAMIC_GRAPH_H_

#include <list>
#include <map>
#include <string>
#include <vector>
#include "edge_weight.h"
#include "rbh.h"
#include "bipartite_graph.h"
#include "edge_set_matrix.h"
#include "operon_gene.h"

template<typename M> class OperonDynamicGraph {  // TODO: Split this big class into some small classes
public:
  OperonDynamicGraph(const std::map<gene_pair_t, WeightPair>& reader, const OperonsGenes& operons_array_u, OperonsGenes& operons_array_v) {
    EdgeSetMatrix edge(reader);
    edge.Process(operons_array_u.gene2operon, operons_array_v.gene2operon);
    Initialize(edge, operons_array_u.operon2gene, operons_array_v.operon2gene);
  }
  bool stop_sorting;
  void Init(bool slow_compare, bool sort) {
    while (edge_weight_list_.size() > 0) {
      typename std::list<EdgeWeight<M> >::iterator it;
      if (sort) {
        edge_weight_list_.sort(slow_compare ? EdgeWeight<M>::slow_compare : EdgeWeight<M>::compare);  // sort edge_weights decreasingly using insertion sort
        it = edge_weight_list_.begin();
      } else {
        it = min_element(edge_weight_list_.begin(), edge_weight_list_.end(), slow_compare ? EdgeWeight<M>::slow_compare : EdgeWeight<M>::compare);
      }
      MergeGeneBipartiteGraphs(*it);
      UpdateAdjacencyList(it);
      edge_weight_list_.erase(it);  // now remove the first bipartite_graph_edge_name_set after updating
    }
  }
  void GetGenePairSet(std::set<gene_pair_t>* gene_pair_set_pointer) {
    gene_pair_set_pointer->clear();
    for (typename std::list<BipartiteGraph<gene_t, M> >::const_iterator it = this->bipartite_graph_list().begin(); it != this->bipartite_graph_list().end(); it++) {
      for (typename std::set<std::pair<gene_t, gene_t> >::const_iterator pos_s = it->max_matching_vertex_name_set().begin(); pos_s != it->max_matching_vertex_name_set().end(); pos_s++) {
        gene_pair_t gp(pos_s->first, pos_s->second);
        gene_pair_set_pointer->insert(gp);
      }
    }
  }
  void GetEdgeSet(std::map<OperonId, std::pair<std::set<OperonId>, std::set<OperonId> > >* gp_set_pointer) {
    gp_set_pointer->clear();
    OperonId count = 0;
    for (typename std::list<BipartiteGraph<gene_t, M> >::const_iterator it = this->bipartite_graph_list().begin(); it != this->bipartite_graph_list().end(); it++) {
      count++;
      if (it->operon_name_set_pair().first.size() > 0 && it->operon_name_set_pair().second.size() > 0)
        (*gp_set_pointer)[count] = it->operon_name_set_pair();
    }
  }
  const std::list<BipartiteGraph<gene_t, M> >& bipartite_graph_list() const {
    return bipartite_graph_list_;
  }
private:
  void Initialize(const EdgeSetMatrix &edge_set_matrix, const std::vector<std::set<gene_t> >& operons_array_u, const std::vector<std::set<gene_t> >& operons_array_v) {
    const int size_of_operons_u = static_cast<int>(operons_array_u.size());
    const int size_of_operons_v = static_cast<int>(operons_array_v.size());
    // variable declarations

    gene_set_t empty_set;
    std::vector<OperonId> bpg_u;
    std::vector<OperonId> bpg_v;
    bpg_u.reserve(size_of_operons_u);
    bpg_v.reserve(size_of_operons_v);

    std::vector<typename std::list<BipartiteGraph<gene_t, M> >::iterator> u_list(size_of_operons_u);
    std::vector<typename std::list<BipartiteGraph<gene_t, M> >::iterator> v_list(size_of_operons_v);

    std::vector<std::set<OperonId> > u_operons(size_of_operons_u);
    std::vector<std::set<OperonId> > v_operons(size_of_operons_v);
    // initial vertices of gU and operonsInGenomes.operons_array_v.m_operons
    for (int i = 0; i < size_of_operons_u; i++) 	{
      GeneSetPair set_pair(operons_array_u[i], empty_set);
      BipartiteGraph<gene_t, M>* bipartite_graph_u = BipartiteGraph<gene_t, M>::FromFirst(set_pair, i);
      // update the vertices of the dynamic graph
      bipartite_graph_list_.push_back(*bipartite_graph_u);
      u_list[i] = bipartite_graph_list_.end();
      u_list[i]--;
      u_operons[i].insert(i);
    }
    for (int j = 0; j < size_of_operons_v; j++) 	{
      GeneSetPair set_pair(empty_set, operons_array_v[j]);
      BipartiteGraph<gene_t, M>* bipartite_graph_v = BipartiteGraph<gene_t, M>::FromSecond(set_pair, j);
      // update the vertices of the dynamic graph
      bipartite_graph_list_.push_back(*bipartite_graph_v);
      v_list[j] = bipartite_graph_list_.end();
      v_list[j]--;
      v_operons[j].insert(j);
    }
    int edge_num=0;
    // construct initial edge_set between gU and operonsInGenomes.operons_array_v.m_operons
    for (int i = 0; i < size_of_operons_u; i++) {
      for (int j = 0; j < size_of_operons_v; j++) {
        if (edge_set_matrix.bipartite_graph_edge_set_matrix(i, j).size() > 0) {
          GeneSetPair set_pair(operons_array_u[i], operons_array_v[j]);
          std::pair<std::set<OperonId>, std::set<OperonId> > bipartite_graph_edge_name_set(u_operons[i], v_operons[j]);
          BipartiteGraph<gene_t, M> bipartite_graph_u_v(set_pair, bipartite_graph_edge_name_set);
          bipartite_graph_u_v.FindMaxMatching(edge_set_matrix.bipartite_graph_edge_set_matrix(i, j));
          // update the edge_set of the dynamic graph
          EdgeWeight<M> edge_weight(bipartite_graph_edge_name_set, edge_set_matrix.bipartite_graph_edge_set_matrix(i, j), bipartite_graph_u_v.max_matching_vertex_name_set().size(), u_list[i], v_list[j]);
          edge_weight_list_.push_back(edge_weight);
          edge_num += static_cast<int>(bipartite_graph_u_v.max_matching_vertex_name_set().size());
        }
      }
    }
  }
  void MergeGeneBipartiteGraphs(const EdgeWeight<M>& edge_weight) {
    typename std::list<BipartiteGraph<gene_t, M> >::iterator it, graph_iterator_1, graph_iterator_2;
    // first find the indexes of the two vertices of the edge_name_set
    graph_iterator_1 = edge_weight.main_iterator_;
    graph_iterator_2 = edge_weight.secondary_iterator_;

    // now construct the new Bipartite Graph based on the connected merged_edge_name_set
    BipartiteGraph<gene_t, M> merged_bipartite_graph(*graph_iterator_1, *graph_iterator_2);
    M::MergeBp(*graph_iterator_1, *graph_iterator_2, &merged_bipartite_graph.max_matching_vertex_name_set_);

    merged_bipartite_graph.FindMaxMatching(edge_weight.edge_set());

    garbage_gene_bipartite_graph_list_.clear();
    // move the two Bipartite Graphs into garbage bipartite_graph_list_
    garbage_gene_bipartite_graph_list_.splice(garbage_gene_bipartite_graph_list_.end(), bipartite_graph_list_, graph_iterator_1);
    garbage_gene_bipartite_graph_list_.splice(garbage_gene_bipartite_graph_list_.end(), bipartite_graph_list_, graph_iterator_2);

    // add the new merged one
    bipartite_graph_list_.push_back(merged_bipartite_graph);
    edge_weight.main_iterator_ = bipartite_graph_list_.end();
    edge_weight.main_iterator_--;
  }
  void RemoveEdgeWeight(typename std::list<EdgeWeight<M> >::iterator& edge_weight_iterator) {
    edge_weight_iterator = edge_weight_list_.erase(edge_weight_iterator);
    edge_weight_iterator--;
  }
  void RemoveEmptyEdge( typename std::list<EdgeWeight<M> >::iterator& edge_weight_iterator ) {
    if (edge_weight_iterator->weight() < 0) {
      fprintf(stderr, "Impossible weight of %d. Program died!\n", edge_weight_iterator->weight());
      exit(1);
    }
    if (edge_weight_iterator->weight() == 0)
      RemoveEdgeWeight(edge_weight_iterator);
  }
  void debug_print(const std::set<OperonId> & p) {
    for (std::set<OperonId>::iterator it = p.begin(); it != p.end(); it ++)
      printf("%d ", *it);
    printf("\n");
  }
  void debug_print(const std::pair<std::set<OperonId>, std::set<OperonId> > & p) {
    printf("U:"); debug_print(p.first); 
    printf("V:"); debug_print(p.second);
  }
  void UpdateAdjacencyList(const typename std::list<EdgeWeight<M> >::iterator& top_edge_weight) {
    //printf("11111111111111111111111111111\n");
    //debug_print(top_edge_weight->edge_name_set());
    if (edge_weight_list_.size() <= 1) return;
    const std::pair<std::set<OperonId>, std::set<OperonId> > & edge1 = top_edge_weight->edge_name_set(); // get the edge of the whole edge array
    for (typename std::list<EdgeWeight<M> >::iterator edge_weight_iterator = edge_weight_list_.begin(); edge_weight_iterator != edge_weight_list_.end(); edge_weight_iterator++) {
      if (top_edge_weight == edge_weight_iterator) continue;
      
      const std::pair<std::set<OperonId>, std::set<OperonId> > & edge2 = (edge_weight_iterator->edge_name_set());
      // now find out the edge associated with
      if (!set_pair_calc::Assoicated(edge1, edge2)) continue;
      if (edge1 == edge2) {
        RemoveEdgeWeight(edge_weight_iterator);
        continue;
      }
      //printf("22222222222222222222222222222\n");
      //debug_print(edge_weight_iterator->edge_name_set());
      typename std::list<BipartiteGraph<gene_t, M> >::iterator graph_iterator_1 = top_edge_weight->main_iterator_, graph_iterator_2;

      if (set_pair_calc::Includes(edge1, edge_weight_iterator->secondary_iterator_->operon_name_set_pair()))
        graph_iterator_2 = edge_weight_iterator->main_iterator_;
      else
        graph_iterator_2 = edge_weight_iterator->secondary_iterator_;

      std::set<std::pair<gene_pair_t, WeightPair> > edge_set, edge_set_extend;

      // find out the two bpGraphs based on the merged_edge_name_set information
      AddVector(top_edge_weight->edge_set(), edge_weight_iterator->edge_set(), &edge_set);

      int size_sum = graph_iterator_1->max_matching_vertex_name_set().size() + graph_iterator_2->max_matching_vertex_name_set().size();

      BipartiteGraph<gene_t, M> merged_bipartite_graph(*graph_iterator_1, *graph_iterator_2);

      if (IsDuplicate(top_edge_weight, edge_weight_iterator, merged_bipartite_graph.operon_name_set_pair(), edge_set, &edge_set_extend)) {
        merged_bipartite_graph.FindMaxMatching(edge_set_extend);
        // update the top_edge_weight information
        edge_weight_iterator->Update(merged_bipartite_graph.operon_name_set_pair(), edge_set_extend, merged_bipartite_graph.max_matching_vertex_name_set().size() - size_sum, graph_iterator_2, graph_iterator_1);
      } else {
        //  M merged_bipartite_graph(vertex_name_sets_value, merged_edge_name_set);
        merged_bipartite_graph.FindMaxMatching(edge_set);
        // update the top_edge_weight information
        edge_weight_iterator->Update(merged_bipartite_graph.operon_name_set_pair(), edge_set, merged_bipartite_graph.max_matching_vertex_name_set().size() - size_sum, graph_iterator_1, graph_iterator_2);
      }
      RemoveEmptyEdge(edge_weight_iterator);
    }
  }
  bool IsDuplicate(const typename std::list<EdgeWeight<M> >::iterator& top_edge_weight, const typename std::list<EdgeWeight<M> >::iterator& edge_weight_iterator, const std::pair<std::set<OperonId>, std::set<OperonId> > & bipartite_graph_edge_name_set, const std::set<std::pair<gene_pair_t, WeightPair> >& edge_set, std::set<std::pair<gene_pair_t, WeightPair> >* edge_set_pointer ) {
    //#pragma omp parallel for num_threads(8)
    for (typename std::list<EdgeWeight<M> >::iterator edge_weight_iterator_extend = edge_weight_list_.begin(); edge_weight_iterator_extend  != edge_weight_iterator; edge_weight_iterator_extend ++) {
      if (edge_weight_iterator_extend == top_edge_weight) continue;
      if (edge_weight_iterator_extend ->edge_name_set() == bipartite_graph_edge_name_set) {
        AddVector(edge_weight_iterator_extend ->edge_set(), edge_set, edge_set_pointer);
        return true;
      }
    }
    return false;
  }
  bool IsAssoicated( std::set<gene_t> &edge1_set, std::set<gene_t> &edge2_set );
  static void AddVector( const std::set<std::pair<gene_pair_t, WeightPair> >& v1, const std::set<std::pair<gene_pair_t, WeightPair> >& v2, std::set<std::pair<gene_pair_t, WeightPair> >* s ) {
    s->clear(); // clear the vector first
    for (std::set<std::pair<gene_pair_t, WeightPair> >::const_iterator pos_s = v1.begin(); pos_s != v1.end(); ++pos_s) s->insert(*pos_s); // put into a set
    for (std::set<std::pair<gene_pair_t, WeightPair> >::const_iterator pos_s = v2.begin(); pos_s != v2.end(); ++pos_s) s->insert(*pos_s);
  }
  std::list<EdgeWeight<M> > edge_weight_list_; // TODO: I'm sure this is not a good data structure, but I have no time to rewrite them all. I have to rewrite now!!!!!!!!!!!!!!
  std::list<BipartiteGraph<gene_t, M> > bipartite_graph_list_;
  std::list<BipartiteGraph<gene_t, M> > garbage_gene_bipartite_graph_list_;
};
#endif // GOST_OPERON_DYNAMIC_GRAPH_H_
