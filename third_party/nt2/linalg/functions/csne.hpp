//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CSNE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CSNE_HPP_INCLUDED

/*!
  @file
  @brief Defines Semi-Normal Equations that solve R'(Rx) = A'b with a one-step
  iterative refinement
  (based on Qr factorization)
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines sne function tag
    struct csne_ : boost::dispatch::tag::formal_
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
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::csne_, csne
                                  , (A0 const&)(A1 const&)
                                  , 2
                                  );
}

#endif
