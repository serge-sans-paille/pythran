//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-std
    @defgroup group-range Ranges adaptors

    Provides range adaptors to convert arbitrary ranges into SIMD-aware ranges that allow
    the processing of data with automatic support for SIMD semantic.
  **/
} }

#include <boost/simd/range/range.hpp>
#include <boost/simd/range/aligned_range.hpp>
#include <boost/simd/range/segmented_input_range.hpp>
#include <boost/simd/range/segmented_output_range.hpp>

#endif
