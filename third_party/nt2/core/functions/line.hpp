//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LINE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LINE_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief line generic tag

      Represents the line function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct line_ : ext::elementwise_<line_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<line_> parent;
    };
  }

  /*!
    @brief Oriented slice extraction

    Returns the oriented slice @c a1 along the first non-singleton dimension
    of @c a0.

    @param a0 Source table
    @param a1 Index of the slice to extract
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::line_ , line, 2)


  /*!
    @brief Oriented slice extraction

    Returns the oriented slice @c a1 along dimension @c a2 of @c a0.

    @param a0 Source table
    @param a1 Index of the slice to extract
    @param a2 Dimension to extract along
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::line_ , line, 3)
}

#endif
