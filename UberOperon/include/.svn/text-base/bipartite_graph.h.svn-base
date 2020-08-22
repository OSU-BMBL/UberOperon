#ifndef GOST_BIPARTITE_GRAPH_H_
#define GOST_BIPARTITE_GRAPH_H_

#include <map>
#include <deque>
#include <iterator>
#include <vector>
#include <queue>
#include <stack>
#include "set_pair_calc.h"
#include "rbh.h"

template<typename T, typename M> class BipartiteGraph {
public:
  BipartiteGraph(const BipartiteGraph& b1, const BipartiteGraph& b2) : vertex_name_sets_(b1.vertex_name_sets_, b2.vertex_name_sets_) {
    set_union(b1.operon_name_set_pair_.first.begin(), b1.operon_name_set_pair_.first.end(), b2.operon_name_set_pair_.first.begin(), b2.operon_name_set_pair_.first.end(), inserter(operon_name_set_pair_.first, operon_name_set_pair_.first.begin()));
    set_union(b1.operon_name_set_pair_.second.begin(), b1.operon_name_set_pair_.second.end(), b2.operon_name_set_pair_.second.begin(), b2.operon_name_set_pair_.second.end(), inserter(operon_name_set_pair_.second, operon_name_set_pair_.second.begin()));
  }
  BipartiteGraph(const GeneSetPair& init_vertex_name_sets, const std::pair<std::set<OperonId>, std::set<OperonId> > & bipartite_graph_egde_name_set)
    : vertex_name_sets_(init_vertex_name_sets),
      operon_name_set_pair_(bipartite_graph_egde_name_set) {}
  BipartiteGraph(const GeneSetPair& set_pair) : vertex_name_sets_(set_pair) {}
  static BipartiteGraph* FromFirst(GeneSetPair set_pair, OperonId count) {
    BipartiteGraph* bipartiteGraph = new BipartiteGraph(set_pair);
    bipartiteGraph->operon_name_set_pair_.first.insert(count);
    return bipartiteGraph;
  }
  static BipartiteGraph* FromSecond(GeneSetPair set_pair, OperonId count) {
    BipartiteGraph* bipartiteGraph = new BipartiteGraph(set_pair);
    bipartiteGraph->operon_name_set_pair_.second.insert(count);
    return bipartiteGraph;
  }
  const std::pair<std::set<OperonId>, std::set<OperonId> > & operon_name_set_pair() const {
    return operon_name_set_pair_;
  }
  const GeneSetPair& vertex_name_sets() const {
    return vertex_name_sets_;
  }
  const std::set<std::pair<T, T> >& max_matching_vertex_name_set() const {
    return max_matching_vertex_name_set_;
  }
  void FindMaxMatching(const std::set<std::pair<gene_pair_t, WeightPair> >& edge_set) {
    SetMaxMatching();
    typename std::map<T, gene_set_t> adj;
    // for each edge, find their corresponding adjacencies
    for (typename std::set<std::pair<gene_pair_t, WeightPair> >::const_iterator pos_v = edge_set.begin(); pos_v != edge_set.end(); ++pos_v) {
      T vertex1 = pos_v->first.first, vertex2 = pos_v->first.second;
      adj[vertex1].insert(vertex2);
      adj[vertex2].insert(vertex1);  // add adjacent vertexes into the list
    }
    //Convention: We try to check free vertexes in V1. Thus, each time we find out an augmenting path, we always get the edge starting from V1
    // repeatedly find augmenting path
    while (free_vertex_set_1_.size() > 0)
      FindAugmentingPath(adj);
  }
public:
  BipartiteGraph() {}
  void FindAugmentingPath(const typename std::map<T, gene_set_t>& adj) {
    // run BFS
    T s = *(free_vertex_set_1_.begin());
    std::vector<T> bfs_array, bfs_parent_array;
    AGPath(adj, s, &bfs_array, &bfs_parent_array);

    // find a free vertex t (another unmatched node)
    // such that (s, t) are the two free vertexes of the augmenting path
    // if not found, just leave the path the first node
    bool freeNodeFound = false;
    T t;
    if (bfs_array.size() > 1)   {
      for (typename std::vector<T>::const_iterator pos_v = bfs_array.begin() + 1; pos_v != bfs_array.end(); ++pos_v) {
        if (free_vertex_set_.count(*pos_v) >= 1) {
          t = *pos_v;
          freeNodeFound = true;
          break;
        }
      }
    }

    if (!freeNodeFound) {
      free_vertex_set_1_.erase(s);
      free_vertex_set_.erase(s);
      return;
    }

    // construct the augmenting path if existing
    std::deque<T> path;
    BfsPath(bfs_array, bfs_parent_array, s, t, &path);

    // flip the edges by adding new edges and remove old edges
    if ((path.size() >= 4) || (path.size() == 2)) {
      if (path.size() > 4) printf("%d", path.size());
      for (int count = 0; count < static_cast<int>(path.size()) - 1; ++count) {
        if (count % 2 == 0) {
          std::pair<T, T> edge(path[count], path[count + 1]);
          max_matching_vertex_name_set_.insert(edge);
        } else {
          std::pair<T, T> edge(path[count + 1], path[count]);
          max_matching_vertex_name_set_.erase(edge);
        }
      }
    }

    // update the free V1 and free V
    free_vertex_set_1_.erase(path.front());
    free_vertex_set_.erase(path.front());
    free_vertex_set_.erase(path.back());
  }
  void SetMaxMatching() {
    // update the free_vertex_set_1_ and free_vertex_set_
    free_vertex_set_1_ = vertex_name_sets_.first;
    set_union(vertex_name_sets_.first.begin(), vertex_name_sets_.first.end(),
              vertex_name_sets_.second.begin(), vertex_name_sets_.second.end(),
              inserter(free_vertex_set_, free_vertex_set_.begin()));

    // remove those in the matching
    for (typename std::set<std::pair<T, T> >::const_iterator pos_s = max_matching_vertex_name_set().begin(); pos_s != max_matching_vertex_name_set().end(); ++pos_s) {
      // now remove vertexes from free_vertex_set_1_, and free_vertex_set_
      free_vertex_set_1_.erase(pos_s->first);
      free_vertex_set_.erase(pos_s->first);
      free_vertex_set_.erase(pos_s->second);
    }
  }
  /*
  * Implemented based on the algorithm book of CLR
  *
  * Precondition: the start vertex of the graph
  * Postcondition: an Array of vertexes of BFS and
  an Array of parent vertexes
  */
  void AGPath(const typename std::map<T, gene_set_t>& graph, const T& s, std::vector<T>* bfs_array, std::vector<T>* bfs_parent_array) {
    //if(s == "16130774")
    //  printf("What?");
    typedef bool ColorType;
    typename std::map<T, ColorType> color_map;
    const ColorType kGreen = false, kBlack = false, kWhite = true;
    // initialization
    for (typename std::map<T, gene_set_t>::const_iterator pos = graph.begin(); pos != graph.end(); ++pos)
      color_map[(*pos).first] = (s == (*pos).first) ? kGreen : kWhite;
    std::deque<T> q;
    q.push_back(s);
    T null_gene;
    bfs_parent_array->push_back(null_gene);
    // now the main loop
    while (!q.empty()) {
      const T u = q.front();
      typename std::map<T, gene_set_t>::const_iterator adj_iterator = graph.find(u);
      if (adj_iterator != graph.end()) {
        for (typename gene_set_t::iterator pos = adj_iterator->second.begin(); pos != adj_iterator->second.end(); ++pos) {
          if (color_map[*pos] != kWhite) continue;
          if (vertex_name_sets_.first.count(*pos) > 0 && free_vertex_set_1_.count(*pos) == 0) {
            for (typename std::set<std::pair<T, T> >::const_iterator pos_s = max_matching_vertex_name_set().begin(); pos_s != max_matching_vertex_name_set().end(); ++pos_s){
              if (pos_s->second == u && *pos == pos_s->first){
                color_map[*pos] = kGreen;
                bfs_parent_array->push_back(u);
                q.push_back(*pos);
              }
            }
          }
          if (vertex_name_sets_.second.count(*pos) > 0) {
              color_map[*pos] = kGreen;
              bfs_parent_array->push_back(u);
              q.push_back(*pos);
          }
        }
      }
      // add the vertex into the bfs array
      bfs_array->push_back(u);
      q.pop_front();
      color_map[u] = kBlack;
    }
  }
  /*
  * given a BFS tree and a intermediate vertex in the tree
  * return the path from the root to the intermediate vertex
  */
  void BfsPath(const std::vector<T>& bfs_array, const std::vector<T>& bfs_parent_array, const T& s, const T& t, std::deque<T>* path ) {
    // initialization
    T v = t;
    path->push_front(v);

    // find the bfs path between the root and the vertex
    while (v != s)  {
      for (int count = 0; count < static_cast<int>(bfs_array.size()); count++) {
        if (bfs_array[count] == v) {
          v = bfs_parent_array[count];
          path->push_front(v);
          break;
        }
      }
    }
  }
public:
  std::set<std::pair<T, T> > max_matching_vertex_name_set_;
private:
  std::pair<std::set<OperonId>, std::set<OperonId> > operon_name_set_pair_;
  GeneSetPair vertex_name_sets_;
  gene_set_t free_vertex_set_1_;
  gene_set_t free_vertex_set_;
};

template<typename T> class BipartiteGraphMerger {
public:
  static void MergeBp(const BipartiteGraph<T, BipartiteGraphMerger>& b1, const BipartiteGraph<T, BipartiteGraphMerger>& b2, std::set<std::pair<T, T> >* s) {
    s->clear();
    s->insert(b1.max_matching_vertex_name_set().begin(), b1.max_matching_vertex_name_set().end());
    s->insert(b2.max_matching_vertex_name_set().begin(), b2.max_matching_vertex_name_set().end());
  }
};

template<typename T> class BipartiteGraphRbhMerger {
public:
  static Rbh<T, double> rbh_;
  static void MergeBp(const BipartiteGraph<T, BipartiteGraphRbhMerger>& b1, const BipartiteGraph<T, BipartiteGraphRbhMerger>& b2, std::set<std::pair<T, T> >* s) {
    s->clear();
    GeneSetPair set_pair(b1.vertex_name_sets(), b2.vertex_name_sets());
    rbh_.SaveEdges(set_pair, s);
  }
};

template<typename T> class BipartiteGraphCloseRbhMerger {
public:
  static void MergeBp(const BipartiteGraph<T, BipartiteGraphCloseRbhMerger>& b1, const BipartiteGraph<T, BipartiteGraphCloseRbhMerger>& b2, std::set<std::pair<T, T> >* s) {
    GeneSetPair set_pair(b1.vertex_name_sets(), b2.vertex_name_sets());
    Rbh<T, double> rbh(set_pair, reader_);
    rbh.Init();
    rbh.SaveEdges(set_pair, s);
  }
  static std::map<gene_pair_t, WeightPair> reader_;
};
#endif // GOST_BIPARTITE_GRAPH_H_
