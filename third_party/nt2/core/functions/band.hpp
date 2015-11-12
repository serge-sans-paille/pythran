//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_BAND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_BAND_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief band generic tag

      Represents the band function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct band_ : ext::elementwise_<band_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<band_> parent;
    };
  }

  /*!
    @brief Apply a diagonal masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    diagonal of the expression.

    @param a0 Expression to mask

    @par Alias:
    diagonal
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::band_ , band    , 1 )

  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::band_ , diagonal, 1 )

  /*!
    @brief Apply a band masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on a band
    centered on the diagonal with a given width @c a1.

    @param a0 Expression to mask
    @param a1 Width of the centered band.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::band_ , band  , 2 )

  /*!
    @brief Apply a dual band masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on a
    band ranging from sub/super-diagonal @c a1 and @c a2

    @param a0 Expression to mask
    @param a1 Index of the lowest diagonal to include in the mask.
    @param a2 Index of the highest diagonal to include in the mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::band_ , band  , 3 )
}

#endif
