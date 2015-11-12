//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef NT2_BOOLEAN_FUNCTIONS_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#define NT2_BOOLEAN_FUNCTIONS_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#include <boost/simd/boolean/functions/if_one_else_zero.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Bring the tag if_one_else_zero_ of functor if_one_else_zero
     *        in namespace nt2::tag for toolbox nt2.boolean
    **/
    using boost::simd::tag::if_one_else_zero_;
  }

  using boost::simd::if_one_else_zero;
  using boost::simd::ifoneelsezero;
  using boost::simd::sb2b;
}
#endif

