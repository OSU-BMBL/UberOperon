#ifndef GOST_SRC_RBH_RBH_H_
#define GOST_SRC_RBH_RBH_H_
#include <map>
#include <set>
#include <string>
#include "vertix_with_weight.h"

typedef std::pair<double, double> WeightPair;

template<typename GT1, typename WeightT1> class Rbh { // Double Vertex with Weight and Vertex Map Class
public:
  Rbh() {}
  Rbh(const std::pair<std::set<GT1>, std::set<GT1> >& set_pair, const std::map<std::pair<GT1, GT1>, WeightPair>& reader_map) {
    LoadSubsetOfMap (set_pair, reader_map);
  }
  Rbh(const std::map<std::pair<GT1, GT1>, WeightPair>& reader) {
    LoadMap(reader);
  }
  bool Init() {
    assert(!init);
    assert(loaded);
    map_u_.Union(map_v_);
    return init = true;
  }
  void SaveEdges(const std::pair<std::set<GT1>, std::set<GT1> >& pair_set, std::set<std::pair<GT1, GT1> >* edge_set_pointer) const {
    map_u_.GetEdges(pair_set, edge_set_pointer);
  }
  void SaveGenePairSet(std::set<std::pair<GT1, GT1> >* gene_pair_set_pointer) {
    std::set<std::pair<GT1, GT1> > edge_set;
    this->GetAllEdges(&edge_set);
    for (typename std::set<std::pair<GT1, GT1> >::iterator it = edge_set.begin() ; it != edge_set.end(); it++) {
      std::pair<GT1, GT1> gp(it->first, it->second);
      gene_pair_set_pointer->insert(gp);
    }
  }
  bool LoadMap(const std::map<std::pair<GT1, GT1>, WeightPair>& reader_map) {
    assert(!loaded);
    for (typename std::map<std::pair<GT1, GT1>, WeightPair>::const_iterator it = reader_map.begin(); it != reader_map.end(); it++)
      AddEdgeSet(it->first.first, it->first.second, it->second.first, it->second.second);
    return loaded = true;
  }
  bool LoadSubsetOfMap(const std::pair<std::set<GT1>, std::set<GT1> >& pair_set, const std::map<std::pair<GT1, GT1>, WeightPair>& reader_map) {
    assert(!loaded);
    for (typename std::set<GT1>::const_iterator it = pair_set.first.begin(); it != pair_set.first.end(); it++) {
      for (typename std::set<GT1>::const_iterator jt = pair_set.second.begin(); jt != pair_set.second.end(); jt++) {
        std::pair<GT1, GT1> gp(*it, *jt);
        typename std::map<std::pair<GT1, GT1>, WeightPair>::const_iterator index;
        if ((index = reader_map.find(gp)) == reader_map.end()) continue;
        AddEdgeSet(*it, *jt, index->second.first, index->second.second);
      }
    }
    return loaded = true;
  }
private:
  void AddEdgeSet(const GT1& vertix_u, const GT1& vertix_v, const WeightT1& weight_u, const WeightT1& weight_v) {
    map_u_.Update(vertix_u, vertix_v, weight_u);
    map_v_.Update(vertix_v, vertix_u, weight_v);
  }
  void GetAllEdges(std::set<std::pair<GT1, GT1> >* edge_set_pointer) const {
    map_u_.GetAllEdges(edge_set_pointer);
  }
  void AddRbh(const GT1& vertix_u, const GT1& vertix_v, double weight_u, double weight_v);
  void UpdateRbh();
  VertexWithWeightAndVertexMapClass<GT1, WeightT1> map_u_;
  VertexWithWeightAndVertexMapClass<GT1, WeightT1> map_v_;
  bool init;
  bool loaded;
};
#endif  // GOST_SRC_RBH_RBH_H_ 
