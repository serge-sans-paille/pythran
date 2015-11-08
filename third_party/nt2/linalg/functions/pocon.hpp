//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_POCON_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_POCON_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements lapack gecon function that estimates the
  reciprocal of the condition number of a matrix A in the 1-norm or infinity norm
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines gecon function tag
    struct pocon_ : boost::dispatch::tag::formal_
    {
      /// INTERNAL ONLY
      typedef boost::dispatch::tag::formal_  parent;
    };
  }

  /*!
    @brief

    @param
    @param

    @return
  **/

  NT2_FUNCTION_IMPLEMENTATION (tag::pocon_, pocon
                                  , 2
                                  );

}

#endif
