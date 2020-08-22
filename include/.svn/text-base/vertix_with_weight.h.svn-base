#ifndef SRC_RBH_VERTIX_WITH_WEIGHT_H_
#define SRC_RBH_VERTIX_WITH_WEIGHT_H_
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <string>
#include "gene_set_type.h"

template<typename GeneT, typename WeightT> class VertixWithWeight {
public:
  VertixWithWeight() : weight_(std::numeric_limits<WeightT>::max()) {}
  WeightT weight() const {
    return weight_;
  }
  GeneT vertix() const {
    return vertix_;
  }
  void set(const GeneT& vertix_value, const WeightT& weight_value) {
    weight_ = weight_value;
    vertix_ = vertix_value;
  }
private:
  WeightT weight_;
  GeneT vertix_;
};

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
#endif  // SRC_RBH_VERTIX_WITH_WEIGHT_H_
