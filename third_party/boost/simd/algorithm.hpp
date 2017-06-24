//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ALGORITHM_HPP_INCLUDED
#define BOOST_SIMD_ALGORITHM_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-api
    @defgroup group-std Algorithms and Ranges

    SIMD-aware Range adaptors and implementation of standard algorithms to
    simplify interactions with code written using the Standard Template Library.
  **/

  /*!
    @ingroup group-std
    @defgroup group-algo SIMD Standard Algorithms

    SIMD aware version of standard algorithms. Those algorithms try to maximize the usage of SIMD
    semantic within standard algorithm.
  **/
} }

#include <boost/simd/algorithm/all_of.hpp>
#include <boost/simd/algorithm/any_of.hpp>
#include <boost/simd/algorithm/copy.hpp>
#include <boost/simd/algorithm/copy_n.hpp>
#include <boost/simd/algorithm/count.hpp>
#include <boost/simd/algorithm/count_if.hpp>
#include <boost/simd/algorithm/equal.hpp>
#include <boost/simd/algorithm/fill.hpp>
#include <boost/simd/algorithm/find.hpp>
#include <boost/simd/algorithm/find_if.hpp>
#include <boost/simd/algorithm/find_if_not.hpp>
#include <boost/simd/algorithm/generate.hpp>
#include <boost/simd/algorithm/generate_n.hpp>
#include <boost/simd/algorithm/iota.hpp>
#include <boost/simd/algorithm/lexicographical_compare.hpp>
#include <boost/simd/algorithm/max_element.hpp>
#include <boost/simd/algorithm/max_val.hpp>
#include <boost/simd/algorithm/min_element.hpp>
#include <boost/simd/algorithm/min_val.hpp>
#include <boost/simd/algorithm/none_of.hpp>
#include <boost/simd/algorithm/not_all_of.hpp>
#include <boost/simd/algorithm/reduce.hpp>
#include <boost/simd/algorithm/replace.hpp>
#include <boost/simd/algorithm/replace_if.hpp>
#include <boost/simd/algorithm/transform.hpp>
#include <boost/simd/algorithm/transform_reduce.hpp>

#endif
