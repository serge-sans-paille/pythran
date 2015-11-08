//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MTIMES_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MTIMES_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief mtimes generic tag

      Represents the mtimes function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct mtimes_ : ext::unspecified_<mtimes_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<mtimes_> parent;
    };
  }

  /*!
    @brief Matrix product

    Calls either of the \c GEMM, \c GEMV or \c DOT BLAS functions
    depending on the sizes of the inputs.

    Patterns such as
    @code
    s0*mtimes(transpose(a0), a1);
    @endcode
    will be recognized automatically and optimized to a single \c GEMM call.

    @param a0 Left-hand side of the matrix product of size NxM
    @param a1 Right-hand side of the matrix product of size MxP
    @param a2 Optional scalar that will be used when assigning the
              result to a value \c out so that
              \f$out \leftarrow a0 \times a1 + a2 \times out\f$

    @return A matrix of size NxP containing \f$a0 \times a1\f$
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mtimes_, mtimes, 3)

  /// @overload
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mtimes_, mtimes, 2)

  /// INTERNAL ONLY
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mtimes_, mtimes, 6)
}

#endif

