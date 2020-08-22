#include <gtest/gtest.h>
#include "../include/edge_file_reader.h"
#include "../include/matching_file_writer.h"
#include "../include/operons_in_genome.h"
#include "../include/operon_dynamic_graph.h"

Rbh<gene_t, double> BipartiteGraphRbhMerger<gene_t>::rbh_;
TEST(PairSetParamTest, HandleFileLoad) {
  OperonsGenes operon_set_array_u;
  file_handler::ReadOperonFile("../data_test/Escherichia_coli_K12.gi.operon", &operon_set_array_u);
  OperonsGenes operon_set_array_v;
  file_handler::ReadOperonFile("../data_test/NC_000853.gi.operon", &operon_set_array_v);

  std::map<gene_pair_t, WeightPair> reader;
  edge_file_reader::Read("../data_test/NC_000853.out", 0.001, &reader);
  BipartiteGraphRbhMerger<gene_t>::rbh_.LoadMap(reader);
  BipartiteGraphRbhMerger<gene_t>::rbh_.Init();
  OperonDynamicGraph<BipartiteGraphRbhMerger<gene_t> > dynamic_graph_rbh(reader, operon_set_array_u, operon_set_array_v);
  dynamic_graph_rbh.Init(false, true);

  std::set<gene_pair_t> gost_rbh_gp;
  dynamic_graph_rbh.GetGenePairSet(&gost_rbh_gp);
  EXPECT_EQ(1028, gost_rbh_gp.size());
}