#include <gtest/gtest.h>

//TEST(TestSubset1, SimpleInput)
//{
//  EXPECT_EQ(1, 1);
//}

//
//class TestSubset : public::testing::TestWithParam<int>
//{
//
//};
//
////bool subset(string a, string b)
////{
////	return subset(string2set(a),string2set(b));
////}
//
//TEST(TestSubset, SimpleInput)
//{
//	//EXPECT_FALSE(subset("a", "b"));
//	//EXPECT_FALSE(subset("a", "b c"));
//	//EXPECT_FALSE(subset("b c", "b"));
//	//EXPECT_TRUE(subset("b", "b c"));
//	//EXPECT_TRUE(subset("b c", "b c"));
//	//EXPECT_TRUE(subset("b c", "c b"));
//}
//
//TEST(TestSubset, MoreInput)
//{
//	//EXPECT_TRUE(subset("b", "b c"));
//}
//
//class EdgeWeightArrayParamTest : public ::testing::TestWithParam<EdgeWeightList>
//{
//
//};
//
//void SetupEdgeWeightArray(EdgeWeightList &e)
//{
//	const vector<VertexName> v;
//	//e.GetLast().Set("aa", v, 1);e.Inc();
//	//e.GetLast().Set("a9", v, 1);e.Inc();
//	//e.GetLast().Set("a8", v, 2);e.Inc();
//	//e.GetLast().Set("a7", v, 2);e.Inc();
//	//e.GetLast().Set("a6", v, 3);e.Inc();
//	//e.GetLast().Set("a5", v, 1);e.Inc();
//	//e.GetLast().Set("a4", v, 1);e.Inc();
//	//e.GetLast().Set("a3", v, 2);e.Inc();
//	//e.GetLast().Set("a2", v, 2);e.Inc();
//	//e.GetLast().Set("a1", v, 3);e.Inc();
//	//e.GetLast().Set("a0", v, 1);e.Inc();
//}
//
//void Output(const VertexEdgeName &e)
//{
//	cout << e << "|"/* << e.vSet.size()*/ <<endl;
//	//for(int i = 0; i < e.size(); i++)
//	//	cout << e[i].m_edgeName << endl;
//}
//
//TEST(VertexEdgeNameParamTest, SimpleArray)
//{
//	VertexEdgeName e1, e2, e3, e4;
//	//e1.SetU();
//	//e2.SetV();
//	e3.Union(e1,e2);
//	e4.Union(e3,e3);
//	Output(e1);
//	Output(e2);
//	Output(e3);
//	Output(e4);
//	EXPECT_EQ("U1_V1", e3.Str());
//}


//class IsPrimeParamTest : public::testing::TestWithParam<int>
//{
//
//};
//
//// 不使用参数化测试，就需要像这样写五次
//TEST(IsPrimeTest, HandleTrueReturn)
//{
//	EXPECT_TRUE(IsPrime(3));
//	EXPECT_TRUE(IsPrime(5));
//	EXPECT_TRUE(IsPrime(11));
//	EXPECT_TRUE(IsPrime(23));
//	EXPECT_TRUE(IsPrime(17));
//}
//
//// 使用参数化测试，只需要：
//TEST_P(IsPrimeParamTest, HandleTrueReturn)
//{
//	int n =  GetParam();
//	EXPECT_TRUE(IsPrime(n));
//}
//
//// 定义参数
//INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, testing::Values(3, 5, 11, 23, 17));
//
//
//// -----------------------
//// 更复杂一点的参数结构
//
//struct NumberPair
//{
//	NumberPair(int _a, int _b)
//	{
//		a = _a;
//		b = _b;
//	}
//	int a;
//	int b;
//};
//
//class FooParamTest : public ::testing::TestWithParam<NumberPair>
//{
//
//};
//
//TEST_P(FooParamTest, HandleThreeReturn)
//{
//	FooCalc foo;
//	NumberPair pair = GetParam();
//	EXPECT_EQ(3, foo.Calc(pair.a, pair.b));
//}
//
//INSTANTIATE_TEST_CASE_P(ThreeReturn, FooParamTest, testing::Values(NumberPair(12, 15), NumberPair(18, 21)));