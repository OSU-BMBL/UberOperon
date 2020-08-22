#include <gtest/gtest.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <iostream>
#include "../include/bipartite_graph.h"

template <typename Graph>
void print_bipartite (const Graph& g) {
  typedef boost::graph_traits <Graph> traits;
  typename traits::vertex_iterator vertex_iter, vertex_end;

  /// Most simple interface just tests for bipartiteness.

  bool bipartite = is_bipartite (g);

  if (bipartite) {
    typedef std::vector <boost::default_color_type> partition_t;
    typedef boost::vec_adj_list_vertex_id_map <boost::no_property, unsigned int> index_map_t;
    typedef boost::iterator_property_map <partition_t::iterator, index_map_t> partition_map_t;

    partition_t partition (num_vertices (g));
    partition_map_t partition_map (partition.begin (), get (boost::vertex_index, g));

    /// A second interface yields a bipartition in a color map, if the graph is bipartite.

    boost::is_bipartite (g, get (boost::vertex_index, g), partition_map);

    for (boost::tie (vertex_iter, vertex_end) = vertices (g); vertex_iter != vertex_end; ++vertex_iter) {
      std::cout << "Vertex " << *vertex_iter << " has color " << (get (partition_map, *vertex_iter) == boost::color_traits <
                boost::default_color_type>::white () ? "white" : "black") << std::endl;
    }
  } else {
    typedef std::vector <typename traits::vertex_descriptor> vertex_vector_t;
    vertex_vector_t odd_cycle;

    /// A third interface yields an odd-cycle if the graph is not bipartite.

    find_odd_cycle (g, get (boost::vertex_index, g), std::back_inserter (odd_cycle));

    std::cout << "Odd cycle consists of the vertices:";
    for (size_t i = 0; i < odd_cycle.size (); ++i) {
      std::cout << " " << odd_cycle[i];
    }
    std::cout << std::endl;
  }
}



TEST(Bfs, IntTest) {
  typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS> vector_graph_t;
  typedef std::pair <int, int> E;

  /**
   * Create the graph drawn below.
   *
   *       0 - 1 - 2
   *       |       |
   *   3 - 4 - 5 - 6
   *  /      \   /
   *  |        7
   *  |        |
   *  8 - 9 - 10
   **/

  E bipartite_edges[] = { E (0, 1), E (0, 4), E (1, 2), E (2, 6), E (3, 4), E (3, 8), E (4, 5), E (4, 7), E (5, 6), E (
                            6, 7), E (7, 8), E (10, 9)
                        };
  vector_graph_t bipartite_vector_graph (&bipartite_edges[0],
                                         &bipartite_edges[0] + sizeof(bipartite_edges) / sizeof(E), 11);

  /**
   * Create the graph drawn below.
   *
   *       2 - 1 - 0
   *       |       |
   *   3 - 6 - 5 - 4
   *  /      \   /
   *  |        7
   *  |       /
   *  8 ---- 9
   *
   **/

  E non_bipartite_edges[] = { E (0, 1), E (0, 4), E (1, 2), E (2, 6), E (3, 6), E (3, 8), E (4, 5), E (4, 7), E (5, 6),
                              E (6, 7), E (7, 9), E (8, 9)
                            };
  vector_graph_t non_bipartite_vector_graph (&non_bipartite_edges[0], &non_bipartite_edges[0]
      + sizeof(non_bipartite_edges) / sizeof(E), 10);

  /// Call test routine for a bipartite and a non-bipartite graph.

  print_bipartite (bipartite_vector_graph);

  print_bipartite (non_bipartite_vector_graph);

  std::vector<boost::graph_traits<vector_graph_t>::vertex_descriptor> mate(11);

  // find the maximum cardinality matching. we'll use a checked version
  // of the algorithm, which takes a little longer than the unchecked
  // version, but has the advantage that it will return "false" if the
  // matching returned is not actually a maximum cardinality matching
  // in the graph.

  assert(checked_edmonds_maximum_cardinality_matching(bipartite_vector_graph, &mate[0]));

  std::cout << "In the following graph:" << std::endl << std::endl;

  std::cout << std::endl << "Found a matching of size " << matching_size(non_bipartite_vector_graph, &mate[0]) << std::endl;

  std::cout << "The matching is:" << std::endl;

  boost::graph_traits<vector_graph_t>::vertex_iterator vi, vi_end;
  for (tie(vi,vi_end) = vertices(bipartite_vector_graph); vi != vi_end; ++vi)
    if (mate[*vi] != boost::graph_traits<vector_graph_t>::null_vertex() && *vi < mate[*vi])
      std::cout << "{" << *vi << ", " << mate[*vi] << "}" << std::endl;

  std::cout << std::endl;


}
