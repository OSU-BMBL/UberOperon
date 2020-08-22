#ifndef GOST_RBH_RBH_H_
#define GOST_RBH_RBH_H_
#include "vertix_with_weight.h"
#include <map>
#include "../edge_file_reader.h"

template<typename GT2, typename WeightT2> class VertexWithWeightAndVertexMapClass {
public:
  void Update(const GT2& vertix_u, const GT2& vertix_v, const WeightT2& weight_value) {
    if (map_[vertix_u].weight() > weight_value) map_[vertix_u].set(vertix_v, weight_value);
  }
  void GetAllEdges(std::set<std::pair<GT2, GT2> >* edge_set_pointer) const {
    for (typename std::map<GT2, VertixWithWeight<GT2, WeightT2> >::const_iterator it = map_.begin(); it != map_.end(); it++ ) {
      std::pair<GT2, GT2> edge(it->first, it->second.vertix());
      edge_set_pointer->insert(edge);
    }
  }
  void GetEdges(const std::pair<std::set<GT2>, std::set<GT2> >& pair_set, std::set<std::pair<GT2, GT2> >* edge_set_pointer) const {
    for (typename std::map<GT2, VertixWithWeight<GT2, WeightT2> >::const_iterator it = map_.begin(); it != map_.end(); it++ )
      if ((pair_set.first.count(it->first) > 0) && (pair_set.second.count(it->second.vertix()) > 0)) {
        std::pair<GT2, GT2> edge(it->first, it->second.vertix());
        edge_set_pointer->insert(edge);
      }
  }
  void Union(const VertexWithWeightAndVertexMapClass& compared_map) {
    typename std::map<GT2, VertixWithWeight<GT2, WeightT2> >::iterator it = map_.begin();
    while (it != map_.end()) {
      if (compared_map.map_.at(it->second.vertix()).vertix() == it->first)
        it++;
      else
        map_.erase(it++);
    }
  }
private:
  typename std::map<GT2, VertixWithWeight<GT2, WeightT2> > map_;
};

template<typename GT1, typename WeightT1> class Rbh { // Double Vertex with Weight and Vertex Map Class
public:
  Rbh() {}
  Rbh(const std::pair<std::set<GT1>, std::set<GT1> >& set_pair, const std::map<std::pair<GT1, GT1>, WeightPair>& reader_map) {
    LoadubsetOfMap (set_pair, reader_map);
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
  bool LoadubsetOfMap(const std::pair<std::set<GT1>, std::set<GT1> >& pair_set, const std::map<std::pair<GT1, GT1>, WeightPair>& reader_map) {
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
#endif // GOST_RBH_RBH_H_ 
