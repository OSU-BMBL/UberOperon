#include "../include/operons_in_genome.h"
#include <gtest/gtest.h>

TEST(PairSetParamTest, HandleFileLoad) {
  OperonsGenes operons;
  file_handler::ReadOperonFile("../../data_test/Escherichia_coli_K12.gi.operon", &operons);
  const std::vector<std::set<gene_t> >& operons_in_genome = operons.operon2gene;
  const std::map<gene_t, OperonId>& genes_in_genome = operons.gene2operon;
  EXPECT_EQ(2462, operons_in_genome.size());
  EXPECT_EQ(4, operons_in_genome[0].size());
  EXPECT_EQ("16127995", *operons_in_genome[0].begin());
  EXPECT_EQ(1, operons_in_genome[2461].size());
  EXPECT_EQ("16132220", *operons_in_genome[2461].begin());

  EXPECT_EQ(4141, genes_in_genome.size());
  EXPECT_EQ(1, genes_in_genome.at("16127995"));
  EXPECT_EQ(2462, genes_in_genome.at("16132220"));
}