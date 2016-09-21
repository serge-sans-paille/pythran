//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_HMSB_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_HMSB_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-reduction
    Function object implementing hmsb capabilities

    Returns a std::size_t value composed by the highiest bits.
    of each vector element

    @par Semantic:

    @code
    std::size_t r = hmsb(x);
    @endcode

    is similar to:

    @code
      std::size_t r = 0;
      for(result_type i = 0; i != cardinal_of<T>; ++i)
      {
        r |= (bits(x[i]) >> (sizeof(stype)*8 - 1)) << i;
      }
    @endcode

  **/
  std::size_t hmsb(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/hmsb.hpp>
#include <boost/simd/function/simd/hmsb.hpp>

#endif
