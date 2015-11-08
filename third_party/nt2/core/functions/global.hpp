//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBAL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBAL_HPP_INCLUDED

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the global functor
    **/
    struct global_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Apply a reduction operation with one or two parametersto
    every elements of an expression

    @param a0 Functor tag to apply
    @param a1 Expression to process
    @param a2 additionnal parameter if needed by a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::global_, global, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::global_, global, 2)
}

#endif
