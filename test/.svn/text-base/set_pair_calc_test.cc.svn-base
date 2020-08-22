#include "../include/set_pair_calc.h"
#include <gtest/gtest.h>

class PairSetParamTest : public ::testing::TestWithParam<std::pair<std::set<int>, std::set<int> > > {};

int myints[] = {75,23,65,42,13};
std::set<int> myset(myints, myints+5);

TEST_P(PairSetParamTest, HandleSameSizeReturn) {
  std::pair<std::set<int>, std::set<int> > pair = GetParam();
  EXPECT_EQ(pair.first.size(), pair.second.size());
}

INSTANTIATE_TEST_CASE_P(SameSizeReturn, PairSetParamTest, testing::Values(
                          std::pair<std::set<int>, std::set<int> >(),
                          std::pair<std::set<int>, std::set<int> >(std::set<int>(myints, myints + 5), std::set<int>(myints, myints + 5)),
                          std::pair<std::set<int>, std::set<int> >(std::set<int>(myints, myints + 4), std::set<int>(myints + 1, myints + 5))));

TEST(set_pair_calc, AssoicatedEmpty) {
  std::set<int> set_0;
  std::set<int> set_1(myints, myints + 4);
  std::pair<std::set<int>, std::set<int> > set_pair_int0, set_pair_int1(set_0, set_1), set_pair_int2(set_1, set_1);
  EXPECT_EQ(false, set_pair_calc::Assoicated(set_pair_int0, set_pair_int0));
  EXPECT_EQ(false, set_pair_calc::Assoicated(set_pair_int0, set_pair_int1));
  EXPECT_EQ(false, set_pair_calc::Assoicated(set_pair_int0, set_pair_int2));
  EXPECT_EQ(false, set_pair_calc::Assoicated(set_pair_int1, set_pair_int0));
  EXPECT_EQ(false, set_pair_calc::Assoicated(set_pair_int2, set_pair_int0));

  EXPECT_EQ(true, set_pair_calc::Assoicated(set_pair_int1, set_pair_int1));
  EXPECT_EQ(true, set_pair_calc::Assoicated(set_pair_int1, set_pair_int2));
  EXPECT_EQ(true, set_pair_calc::Assoicated(set_pair_int2, set_pair_int1));
  EXPECT_EQ(true, set_pair_calc::Assoicated(set_pair_int2, set_pair_int2));
}

TEST(set_pair_calc, Assoicated) {
  std::set<int> set_1(myints, myints + 4);
  std::set<int> set_2(myints + 1, myints + 5);
  std::set<int> set_3(myints, myints + 5);
  std::set<int> set_4(myints, myints + 2);
  std::set<int> set_5(myints + 2, myints + 5);
  std::pair<std::set<int>, std::set<int> > set_pair_int1(set_1, set_1), set_pair_int2(set_2, set_2), set_pair_int3(set_3, set_3), set_pair_int4(set_4, set_4), set_pair_int5(set_5, set_5);
  EXPECT_EQ(true, set_pair_calc::Assoicated(set_pair_int1, set_pair_int2));
  EXPECT_EQ(false, set_pair_calc::Assoicated(set_pair_int4, set_pair_int5));
  EXPECT_EQ(true, set_pair_calc::Assoicated(set_pair_int2, set_pair_int3));
}

TEST(set_pair_calc, Includes) {
  std::set<int> set_1(myints, myints + 4);
  std::set<int> set_2(myints + 1, myints + 5);
  std::set<int> set_3(myints, myints + 5);
  std::set<int> set_4(myints, myints + 2);
  std::set<int> set_5(myints + 2, myints + 5);
  std::pair<std::set<int>, std::set<int> > set_pair_int1(set_1, set_1), set_pair_int2(set_2, set_2), set_pair_int3(set_3, set_3), set_pair_int4(set_4, set_4), set_pair_int5(set_5, set_5);
  EXPECT_EQ(false, set_pair_calc::Includes(set_pair_int1, set_pair_int2));
  EXPECT_EQ(false, set_pair_calc::Includes(set_pair_int4, set_pair_int5));
  EXPECT_EQ(false, set_pair_calc::Includes(set_pair_int2, set_pair_int3));
  EXPECT_EQ(true, set_pair_calc::Includes(set_pair_int3, set_pair_int2));
}

