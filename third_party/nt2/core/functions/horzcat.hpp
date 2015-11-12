//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_HORZCAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_HORZCAT_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief horzcat generic tag

     Represents the horzcat function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct  horzcat_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    Horizontal concatenation

    @par Semantic:

    For every table expressions:

    @code
    auto r = horzcat(a0,a1);
    @endcode

    is similar to:

    @code
    auto r = cat(2, a0, a1);
    @endcode

    @see @funcref{vertcat}, @funcref{cat}
    @par alias: @c cath
    @param a0
    @param a1

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, horzcat, 2)

  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, horzcat, 1)

  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, cath, 1)
  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::horzcat_, cath, 2)
}

#endif
