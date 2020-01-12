// SPDX-License-Identifier: LGPL-3.0-only
/*
* Author: Rongyang Sun <sun-rongyang@outlook.com>
* Creation Date: 2019-04-24 21:32
* 
* Description: GraceQ/tensor project. Unit tests fror quantum number object.
*/
#include "gtest/gtest.h"
#include "gqten/gqten.h"
#include "gqten/detail/vec_hash.h"

#include <string>
#include <fstream>

#include <cstdio>


using namespace gqten;


struct TestQN : public testing::Test {
  using DefaultQN = QN<>;
  DefaultQN qn_default = DefaultQN();
  using NormalQN = QN<NormalQNVal>;
  NormalQN qn_normal_default = NormalQN();
  NormalQN qn_normal_1 = NormalQN({QNNameVal("Sz", NormalQNVal(0))});
  NormalQN qn_normal_2 = NormalQN({QNNameVal("Sz", NormalQNVal(1))});
  NormalQN qn_normal_3 = NormalQN({QNNameVal("Sz", NormalQNVal(-1))});
  using NormalNormalQN = QN<NormalQNVal, NormalQNVal>;
  NormalNormalQN qn_normal_normal_default = NormalNormalQN();
  NormalNormalQN qn_normal_normal_1 = NormalNormalQN({
                                          QNNameVal("Sz", NormalQNVal(0)),
                                          QNNameVal("N",  NormalQNVal(0))});
  NormalNormalQN qn_normal_normal_2 = NormalNormalQN({
                                          QNNameVal("Sz", NormalQNVal(1)),
                                          QNNameVal("N",  NormalQNVal(2))});
};


TEST_F(TestQN, Hashable) {
  EXPECT_EQ(qn_default.Hash(), 0);
  EXPECT_EQ(qn_normal_1.Hash(), VecStdTypeHasher(std::vector<long>{0}));
  EXPECT_EQ(qn_normal_2.Hash(), VecStdTypeHasher(std::vector<long>{1}));
  EXPECT_EQ(qn_normal_3.Hash(), VecStdTypeHasher(std::vector<long>{-1}));
  EXPECT_EQ(qn_normal_normal_1.Hash(), VecStdTypeHasher(std::vector<long>{0, 0}));
  EXPECT_EQ(qn_normal_normal_2.Hash(), VecStdTypeHasher(std::vector<long>{1, 2}));
}


TEST_F(TestQN, Equivalent) {
  EXPECT_TRUE(qn_default == DefaultQN());
  EXPECT_TRUE(qn_normal_default == qn_default);
  EXPECT_TRUE(qn_normal_normal_default == qn_normal_default);
  EXPECT_TRUE(qn_normal_1 == qn_normal_1);
  EXPECT_TRUE(qn_normal_normal_1 == qn_normal_normal_1);
  EXPECT_TRUE(qn_normal_1 != qn_normal_2);
  EXPECT_TRUE(qn_normal_1 != qn_normal_normal_2);
}


TEST_F(TestQN, Negtivation) {
  EXPECT_EQ(-qn_default, DefaultQN());
  EXPECT_EQ(-qn_normal_1, NormalQN({QNNameVal("Sz", NormalQNVal(0))}));
  EXPECT_EQ(-qn_normal_2, NormalQN({QNNameVal("Sz", NormalQNVal(-1))}));
}


TEST_F(TestQN, Summation) {
  auto res0 = qn_default + qn_default;
  EXPECT_EQ(res0, DefaultQN());
  auto res1 = qn_normal_2 + qn_normal_2;
  EXPECT_EQ(res1, NormalQN({QNNameVal("Sz", NormalQNVal(2))}));
  auto res2 = qn_normal_normal_1 + qn_normal_normal_2;
  EXPECT_EQ(
      res2,
      NormalNormalQN(
          {QNNameVal("Sz", NormalQNVal(1)), QNNameVal("N", NormalQNVal(2))}));
}


//TEST_F(TestQN, Subtraction) {
  //auto res = qn_normal_1 - qn_normal_2;
  //EXPECT_EQ(res, qn_normal_3);
//}


//void RunTestQNFileIOCase(const QN &qn, QN &qn_empty) {
  //std::string file = "test.qn";
  //std::ofstream out(file, std::ofstream::binary);
  //bfwrite(out, qn);
  //out.close();
  //std::ifstream in(file, std::ifstream::binary);
  //bfread(in, qn_empty);
  //in.close();
  //std::remove(file.c_str());
  //EXPECT_EQ(qn_empty, qn);
//}


//TEST_F(TestQN, FileIO) {
  //RunTestQNFileIOCase(qn_default, qn_default);
  //RunTestQNFileIOCase(qn_normal_1, qn_normal_empty1);
  //RunTestQNFileIOCase(qn_normal_2, qn_normal_empty1);
  //RunTestQNFileIOCase(qn_normal_3, qn_normal_empty1);
  //RunTestQNFileIOCase(qn_normal_1, qn_normal_empty2);
  //RunTestQNFileIOCase(qn_normal_2, qn_normal_empty2);
  //RunTestQNFileIOCase(qn_normal_3, qn_normal_empty2);
  //RunTestQNFileIOCase(qn_normal_normal_1, qn_normal_normal_empty);
  //RunTestQNFileIOCase(qn_normal_normal_2, qn_normal_normal_empty);
//}
