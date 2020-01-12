// SPDX-License-Identifier: LGPL-3.0-only
/*
* Author: Rongyang Sun <sun-rongyang@outlook.com>
* Creation Date: 2020-01-12 16:39
* 
* Description: GraceQ/tensor project. Implementation details for quantum number.
*/


#include "gqten/gqten.h"
#include "gqten/detail/vec_hash.h"

#include <assert.h>

#ifdef Release
  #define NDEBUG
#endif


namespace gqten {


template <typename... QNValTs>
QN<QNValTs...>::QN(void) { hash_ = CalcHash(); }


template<typename... QNValTs>
QN<QNValTs...>::QN(const QNNameValVec &nm_vals) {
  assert(nm_vals.size() == sizeof...(QNValTs));
  for (auto &nm_val : nm_vals) {
    pvalues_.push_back(nm_val.pval);
  }
  hash_ = CalcHash();
}


template <typename... QNValTs>
QN<QNValTs...>::QN(const QNValPtrVec &pqnvals) : pvalues_(pqnvals) {
  assert(pvalues_.size() == sizeof...(QNValTs));
  hash_ = CalcHash();
}


template <typename... QNValTs>
QN<QNValTs...>::QN(const QN &qn) : pvalues_(qn.pvalues_), hash_(qn.hash_) {
  assert(pvalues_.size() == sizeof...(QNValTs));
}


template <typename... QNValTs>
QN<QNValTs...> &QN<QNValTs...>::operator=(const QN &rhs) {
  assert(rhs.pvalues_.size() == sizeof...(QNValTs));
  pvalues_ = rhs.pvalues_;
  hash_ = rhs.hash_;
  return *this;
}


template <typename... QNValTs>
std::size_t QN<QNValTs...>::CalcHash(void) const {
  if (pvalues_.size() == 0) {
    return 0; 
  } else {
    return VecPtrHasher(pvalues_);
  }
}


template <typename... QNValTs>
QN<QNValTs...> QN<QNValTs...>::operator-(void) const {
  auto pqnvals_size = this->pvalues_.size();
  QNValPtrVec new_pqnvals(pqnvals_size);
  for (std::size_t i = 0; i < pqnvals_size; ++i) {
    new_pqnvals[i] = (this->pvalues_[i])->Minus();
  }
  return QN(new_pqnvals);
}


template <typename... QNValTs>
QN<QNValTs...> &QN<QNValTs...>::operator+=(const QN &rhs) {
  auto pqn_vals_size = this->pvalues_.size();
  assert(pqn_vals_size == rhs.pvalues_.size());
  for (std::size_t i = 0; i < pqn_vals_size; ++i) {
    (this->pvalues_[i])->AddAssign(rhs.pvalues_[i]);
  }
  hash_ = CalcHash();
  return *this;
}


template <typename... LhsQNValTs, typename... RhsQNValTs>
inline QN<LhsQNValTs...> operator+(
    const QN<LhsQNValTs...> &lhs, const QN<RhsQNValTs...> &rhs) {
  QN<LhsQNValTs...> sum(lhs);
  sum += rhs;
  return sum;
}


template <typename... LhsQNValTs, typename... RhsQNValTs>
inline QN<LhsQNValTs...> operator-(
    const QN<LhsQNValTs...> &lhs, const QN<RhsQNValTs...> &rhs) {
  return lhs + (-rhs);
}


template<typename... LhsQNValTs, typename... RhsQNValTs>
inline bool operator==(
    const QN<LhsQNValTs...> &lhs, const QN<RhsQNValTs...> &rhs) {
  return lhs.Hash() == rhs.Hash();
}


template<typename... LhsQNValTs, typename... RhsQNValTs>
inline bool operator!=(
    const QN<LhsQNValTs...> &lhs, const QN<RhsQNValTs...> &rhs) {
  return !(lhs == rhs);
}
} /* gqten */ 
