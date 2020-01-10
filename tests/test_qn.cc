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
  QN qn_default = QN();
  QN qn_normal_1 = QN({QNNameVal("Sz", NormalQNVal(0))});
  QN qn_normal_empty1 = QN({QNNameVal("Sz", NormalQNVal())});
  QN qn_normal_empty2 = QN({NormalQNVal().Clone()});
  QN qn_normal_2 = QN({QNNameVal("Sz", NormalQNVal(1))});
  QN qn_normal_3 = QN({QNNameVal("Sz", NormalQNVal(-1))});
  QN qn_normal_normal_1 = QN({
                              QNNameVal("Sz", NormalQNVal(0)),
                              QNNameVal("N",  NormalQNVal(0))});
  QN qn_normal_normal_empty = QN({
                                  QNNameVal("Sz", NormalQNVal()),
                                  QNNameVal("N",  NormalQNVal())});
  QN qn_normal_normal_2 = QN({
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
  EXPECT_TRUE(qn_default == QN());
  EXPECT_TRUE(qn_normal_1 == qn_normal_1);
  EXPECT_TRUE(qn_normal_normal_1 == qn_normal_normal_1);
  EXPECT_TRUE(qn_normal_1 != qn_normal_2);
  EXPECT_TRUE(qn_normal_1 != qn_normal_normal_2);
}


TEST_F(TestQN, Negtivation) {
  EXPECT_EQ(-qn_default, QN());
  EXPECT_EQ(-qn_normal_1, QN({QNNameVal("Sz", NormalQNVal(0))}));
  EXPECT_EQ(-qn_normal_2, QN({QNNameVal("Sz", NormalQNVal(-1))}));
}


TEST_F(TestQN, Summation) {
  auto res = qn_default + qn_default;
  EXPECT_EQ(res, QN());
  res = qn_normal_2 + qn_normal_2;
  EXPECT_EQ(res, QN({QNNameVal("Sz", NormalQNVal(2))}));
  res = qn_normal_normal_1 + qn_normal_normal_2;
  EXPECT_EQ(
      res,
      QN({QNNameVal("Sz", NormalQNVal(1)), QNNameVal("N", NormalQNVal(2))}));
}


TEST_F(TestQN, Subtraction) {
  auto res = qn_normal_1 - qn_normal_2;
  EXPECT_EQ(res, qn_normal_3);
}


void RunTestQNFileIOCase(const QN &qn, QN &qn_empty) {
  std::string file = "test.qn";
  std::ofstream out(file, std::ofstream::binary);
  bfwrite(out, qn);
  out.close();
  std::ifstream in(file, std::ifstream::binary);
  bfread(in, qn_empty);
  in.close();
  std::remove(file.c_str());
  EXPECT_EQ(qn_empty, qn);
}


TEST_F(TestQN, FileIO) {
  RunTestQNFileIOCase(qn_default, qn_default);
  RunTestQNFileIOCase(qn_normal_1, qn_normal_empty1);
  RunTestQNFileIOCase(qn_normal_2, qn_normal_empty1);
  RunTestQNFileIOCase(qn_normal_3, qn_normal_empty1);
  RunTestQNFileIOCase(qn_normal_1, qn_normal_empty2);
  RunTestQNFileIOCase(qn_normal_2, qn_normal_empty2);
  RunTestQNFileIOCase(qn_normal_3, qn_normal_empty2);
  RunTestQNFileIOCase(qn_normal_normal_1, qn_normal_normal_empty);
  RunTestQNFileIOCase(qn_normal_normal_2, qn_normal_normal_empty);
}
