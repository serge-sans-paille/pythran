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
#ifndef NT2_BOOLEAN_FUNCTIONS_IF_ALLBITS_ELSE_HPP_INCLUDED
#define NT2_BOOLEAN_FUNCTIONS_IF_ALLBITS_ELSE_HPP_INCLUDED
#include <boost/simd/boolean/functions/if_allbits_else.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
     * \brief Bring the tag if_allbits_else_ of functor if_allbits_else
     *        in namespace nt2::tag for toolbox nt2.boolean
    **/
    using boost::simd::tag::if_allbits_else_;
  }

  using boost::simd::if_allbits_else;
  using boost::simd::ifnot_else_allbits;
  using boost::simd::ifnotelseallbits;
  using boost::simd::if_nan_else;
  using boost::simd::ifnanelse;
  using boost::simd::ifnot_else_nan;
  using boost::simd::ifnotelsenan;
}
#endif

// modified by jt the 25/12/2010
