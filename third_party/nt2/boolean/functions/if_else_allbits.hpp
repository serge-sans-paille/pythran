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
#ifndef NT2_BOOLEAN_FUNCTIONS_IF_ELSE_ALLBITS_HPP_INCLUDED
#define NT2_BOOLEAN_FUNCTIONS_IF_ELSE_ALLBITS_HPP_INCLUDED
#include <boost/simd/boolean/functions/if_else_allbits.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Bring the tag if_else_allbits_ of functor if_else_allbits
     *        in namespace nt2::tag for toolbox nt2.boolean
    **/
    using boost::simd::tag::if_else_allbits_;
  }

  using boost::simd::if_else_allbits;
  using boost::simd::ifelsenan;
  using boost::simd::if_else_nan;
  using boost::simd::ifnot_nan_else;
  using boost::simd::ifnotallbitselse;
  using boost::simd::ifelseallbits;
  using boost::simd::ifnot_allbits_else;
  using boost::simd::ifnotallbitselse;

}
#endif

// modified by jt the 25/12/2010
