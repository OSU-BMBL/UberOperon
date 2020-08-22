#include "../include/rbh.h"
#include <gtest/gtest.h>
#include "../include/edge_file_reader.h"

TEST(Rbh, IntTest) {
  std::map<std::pair<int, int>, WeightPair> reader;
  edge_file_reader::Read("../data_test/NC_000853.out", 0.001, &reader);
  Rbh<int, double> rbh(reader);
  rbh.Init();
  std::set<std::pair<int, int> > rbh_gp;
  rbh.SaveGenePairSet(&rbh_gp);
  EXPECT_EQ(819, rbh_gp.size());
}

TEST(Rbh, StringTest) {
  std::map<std::pair<std::string, std::string>, WeightPair> reader;
  edge_file_reader::Read("../data_test/NC_000853.out", 100.0, &reader);
  Rbh<std::string, double> rbh(reader);
  rbh.Init();
  std::set<std::pair<std::string, std::string> > rbh_gp;
  rbh.SaveGenePairSet(&rbh_gp);
  EXPECT_EQ(834, rbh_gp.size());
}

