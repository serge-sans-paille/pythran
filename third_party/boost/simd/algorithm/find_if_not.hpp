//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_FIND_IF_NOT_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_FIND_IF_NOT_HPP_INCLUDED

#include <boost/simd/range/segmented_aligned_range.hpp>
#include <boost/simd/function/all.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <algorithm>

namespace boost { namespace simd
{
  /*!
    @ingroup group-algo

    Returns an iterator to the first element in the range [first,last)
    for which pred returns false.
    If no such element is found, the function returns last.

    @param first  Beginning of the range of elements
    @param last   End of the range of elements
    @param pred   Predicate to apply to each element in the range.

    @par Requirement

      - @c first, @c last and @c out must be pointer to Vectorizable type.


    @par Example:

      @snippet find_if_not.cpp find_if_not

    @par possible output:

      @snippet find_if_not.txt find_if_not
  **/
  template<typename T, typename Pred>
  T const* find_if_not(T const* first, T const* last, Pred const& pred)
  {
    auto pr = segmented_aligned_range(first,last);
    auto safe_pred = [&pred](T x){ return pred(x); };

    auto r = std::find_if_not(pr.head.begin(), pr.head.end(), safe_pred);
    if (r != pr.head.end()) return r;

    auto rv = std::find_if_not( pr.body.begin(), pr.body.end()
                              , [&pred](pack<T> const& x){return all(pred(x)); }
                              );
    if (rv != pr.body.end())
    {
      auto z =  std::find_if_not(rv->begin(), rv->end(), safe_pred);
      return  pr.head.end()
            + std::distance(pr.body.begin(), rv)*pack<T>::static_size
            + std::distance(rv->begin(), z);
    }

    return std::find_if_not(pr.tail.begin(), pr.tail.end(), safe_pred);
  }
} }

#endif
