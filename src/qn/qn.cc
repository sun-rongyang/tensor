// SPDX-License-Identifier: LGPL-3.0-only
/*
* Author: Rongyang Sun <sun-rongyang@outlook.com>
* Creation Date: 2019-08-06 17:15
* 
* Description: GraceQ/tensor project. Implementation details about quantum number.
*/
#include "gqten/gqten.h"
#include "gqten/detail/vec_hash.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>

#ifdef Release
  #define NDEBUG
#endif


namespace gqten {


QN::QN(void) { hash_ = CalcHash(); }


QN::QN(const std::vector<QNNameVal> &nm_vals) {
  for (auto &nm_val : nm_vals) {
    pvalues_.push_back(nm_val.pval);
  }
  hash_ = CalcHash();
}


QN::QN(const QNValPtrVec &pqn_vals) : pvalues_(pqn_vals) {
  hash_ = CalcHash();
}


QN::QN(const QN &qn) : pvalues_(qn.pvalues_), hash_(qn.hash_) {}


QN &QN::operator=(const QN &rhs) {
  pvalues_ = rhs.pvalues_;
  hash_ = rhs.hash_;
  return *this;
}


std::size_t QN::Hash(void) const { return hash_; }


std::size_t QN::CalcHash(void) const {
  if (pvalues_.size() == 0) {
    return 0; 
  } else {
    return VecPtrHasher(pvalues_);
  }
}


QN QN::operator-(void) const {
  auto pqn_vals_size = this->pvalues_.size();
  QNValPtrVec new_pqn_vals(pqn_vals_size);
  for (std::size_t i = 0; i < pqn_vals_size; ++i) {
    new_pqn_vals[i] = (this->pvalues_[i])->Minus();
  }
  return QN(new_pqn_vals);
}


QN &QN::operator+=(const QN &rhs) {
  auto pqn_vals_size = this->pvalues_.size();
  assert(pqn_vals_size == rhs.pvalues_.size());
  for (std::size_t i = 0; i < pqn_vals_size; ++i) {
    (this->pvalues_[i])->AddAssign(rhs.pvalues_[i]);
  }
  hash_ = CalcHash();
  return *this;
}


QN operator+(const QN &lhs, const QN &rhs) {
  QN sum(lhs);
  sum += rhs;
  return sum;
}


QN operator-(const QN &lhs, const QN &rhs) {
  return lhs + (-rhs);
}


bool operator==(const QN &lhs, const QN &rhs) {
  return lhs.Hash() == rhs.Hash();
}


bool operator!=(const QN &lhs, const QN &rhs) {
  return !(lhs == rhs);
}


std::ifstream &bfread(std::ifstream &ifs, QN &qn_empty) {
  for (auto &pval : qn_empty.pvalues_) { pval->Load(ifs); }
  ifs >> qn_empty.hash_;
  return ifs;
}


std::ofstream &bfwrite(std::ofstream &ofs, const QN &qn) {
  for (auto &pval : qn.pvalues_) { pval->Dump(ofs); }
  ofs << qn.hash_ << std::endl;
  return ofs;
}
} /* gqten */ 
