//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_NORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_NORM_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag norm_ of functor norm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct norm_ :  tag::formal_ { typedef tag::formal_ parent; };
  }

  /*!
    @brief Matricial or vectorial norm

    norm mimicks the behaviour of the correponding Matlab function

    @code
    norm(x, p)
    @endcode

    computes

    @code
    |--------------|-------------------|-----------------------|----------------------|
    |    Matlab p  |      NT2 p        |     matrix            |     vector           |
    |--------------|-------------------|-----------------------|----------------------|
    |  1           | 1 or nt2::one_    | max(sum(abs(x)))      |     sum(abs(x))      |
    |  2           | 2 or nt2::two_    |   max(svd(x))         | sum(abs(x).^2)^(1/2) |
    |  q           | q                 |       _               | sum(abs(x).^q)^(1/q) |
    |  inf         | nt2::inf_         | max(sum(abs(x')))     |    max(abs(x))       |
    |  -inf        | nt2::minf_        |       _               |    min(abs(x))       |
    |  'fro'       | nt2::fro_         | sqrt(sum(diag(x'*x))) | sum(abs(x).^2)^(1/2) |
    |--------------|-------------------|-----------------------|----------------------|
    @endcode

    where q is numeric finite positive different from the other possible values

    except 1 2 and q the NT2 calls are statically chosen at compile time.
    If you know exactly what you need, use preferentially mnorm for matrices
    and globalnorm for vectors.

    @see{globalnorm}, @see{mnorm}
  **/



  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_, norm, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_, norm, 1)

}

#endif

