#include "../include/bipartite_graph.h"
#include <gtest/gtest.h>

TEST(BipartiteGraph, FindMaxMatching) {
  std::string fs[24] = {
    "16128427", "16129137", "16129138", "16129139", "16129472", 
    "16129473", "16129474", "16129475", "16129476", "16129477", 
    "16129478", "16129545", "16129547", "16129548", "16130315", 
    "16130316", "16130317", "16130318", "16130319", "16130773", 
    "16130774", "16130776", "16131737", "16131738"
  };
  std::string gs[17] = {
    "15643805", "15643806", "15643807", "15643808", "15643809", 
    "15643810", "15643811", "15643812", "15643813", "15644043", 
    "15644044", "15644045", "15644046", "15644047", "15644468", 
    "15644469", "15644470"
  };
  std::set<std::string> f(fs, fs + 24), g(gs, gs + 17);
  GeneSetPair set_pair(f, g);

  OperonId fo[7] = {234, 643, 859, 905, 1356, 1602, 2156}, so[3] = {377, 447, 574};
  std::set<OperonId> of(fo, fo + 7), og(so, so + 3);
  std::pair<std::set<OperonId>, std::set<OperonId> > operon_name_set_pair(of, og);

  BipartiteGraph<gene_t, BipartiteGraphMerger<gene_t> > bp_graph(set_pair, operon_name_set_pair);

  std::pair<gene_t, gene_t> p1("16128427", "15643810"), p2("16129139", "15643805"), p3("16131738", "15643808");
  std::set<std::pair<gene_t, gene_t> > max_matching_vertex_name_set;
  max_matching_vertex_name_set.insert(p1);
  max_matching_vertex_name_set.insert(p2);
  max_matching_vertex_name_set.insert(p3);

  //EXPECT_EQ(30, bp_graph.vertex_name_sets().first.size());
  EXPECT_EQ(17, bp_graph.vertex_name_sets().second.size());
  EXPECT_EQ(3, max_matching_vertex_name_set.size());

  std::pair<gene_t, gene_t> e1("16128427", "15643810"), e2("16129138", "15644046"), 
      e3("16129139", "15643805"), e4("16129472", "15643812"), e5("16129547", "15644044"), 
      e6("16130316", "15643806"), e7("16130316", "15643807"), e8("16130316", "15643808"), 
      e9("16130774", "15643808"), e10("16131738", "15643806"), e11("16131738", "15643807"), 
      e12("16131738", "15643808"), e13("90111504", "15644470");
  std::set<std::pair<gene_pair_t, WeightPair> > s_pair;
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e1, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e2, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e3, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e4, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e5, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e6, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e7, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e8, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e9, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e10, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e11, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e12, WeightPair(0.0, 0.0)));
  s_pair.insert(std::pair<gene_pair_t, WeightPair> (e13, WeightPair(0.0, 0.0)));

  EXPECT_EQ(13, s_pair.size());

  bp_graph.FindMaxMatching(s_pair);
  EXPECT_EQ(8, bp_graph.max_matching_vertex_name_set_.size());
  EXPECT_EQ(0, bp_graph.max_matching_vertex_name_set_.count(e7));
  EXPECT_EQ(0, max_matching_vertex_name_set.count(e7));
}
