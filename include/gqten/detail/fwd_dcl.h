// SPDX-License-Identifier: LGPL-3.0-only
/*
* Author: Rongyang Sun <sun-rongyang@outlook.com>
* Creation Date: 2019-09-17 09:52
* 
* Description: GraceQ/tensor project. Forward declarations.
*/
#ifndef GQTEN_DETAIL_FWD_DCL_H
#define GQTEN_DETAIL_FWD_DCL_H


#include <fstream>


namespace gqten {


class QN;


class QNSector;


class QNSectorSet;


class Index;


template <typename> class QNBlock;

template <typename ElemType>
std::ifstream &bfread(std::ifstream &, QNBlock<ElemType> &);

template <typename ElemType>
std::ofstream &bfwrite(std::ofstream &, const QNBlock<ElemType> &);

template <typename TenElemType>
std::vector<QNBlock<TenElemType> *> BlocksCtrctBatch(
    const std::vector<long> &, const std::vector<long> &,
    const TenElemType,
    const std::vector<QNBlock<TenElemType> *> &,
    const std::vector<QNBlock<TenElemType> *> &);


template <typename> class GQTensor;

template <typename ElemType>
std::ifstream &bfread(std::ifstream &, GQTensor<ElemType> &);

template <typename ElemType>
std::ofstream &bfwrite(std::ofstream &, const GQTensor<ElemType> &);
} /* gqten */ 
#endif /* ifndef GQTEN_DETAIL_FWD_DCL_H */
