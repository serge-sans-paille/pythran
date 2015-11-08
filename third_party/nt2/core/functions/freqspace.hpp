//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FREQSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FREQSPACE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/generative/options.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the freqspace functor
    **/
    struct freqspace_ : ext::tieable_<freqspace_>
    {
      typedef ext::tieable_<freqspace_> parent;
    };
  }

  /*!
    @brief Frequency spacing for frequency responses.

    freqspace returns the implied frequency range for equally spaced
    frequency responses.

    @par 1D Semantic:

    For any integral @c N :

    @code
    f = freqspace(N);
    @endcoe

    returns the one-dimensional frequency vector @c f assuming @c N evenly
    spaced points around the unit circle. It is equivalent to:

    @code
    f = _(0,2/N,1);
    @endcode

    For any integral @c N :

    @code
    tie(f1,f2) = freqspace(N);
    @endcoe

    returns the two-dimensional frequency vectors @c f1 and @c f2 for an N-by-N
    matrix.

    For N odd, it is equivalent to :

    @code
    f1 = f2 = _(-N+1,2,N-1);
    @endcode

    For N even, it is equivalent to:

    @code
    f1 = f2 = _(-N,2,N-2);
    @endcode

    For any integral @c N :

    @code
    f = freqspace(N,whole_);
    @endcode

    is equivalent to :

    @code
    f = _(0,2/N,2*(N-1)/N);
    @endcode

    @par 2D Semantic:

    For any 2 dimensions size <tt>S = [m n]</tt>:

    @code
    tie(f1,f2) = freqspace(S);
    @endcode

    returns the two-dimensional frequency vectors @c f1 and @c f2
    for an m-by-n matrix.

    [x1,y1] = freqspace(...,'meshgrid') is equivalent to

    [f1,f2] = freqspace(...);
    [x1,y1] = meshgrid(f1,f2);
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace_, freqspace, 3)

  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace_, freqspace, 2)

  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace_, freqspace, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::freqspace_,Domain,N,Expr>
        : meta::boxed_size<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::freqspace_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type  c_t;
    typedef typename boost::proto::result_of::value<c_t>::value_type        t_t;
    typedef typename t_t::type                                              type;
  };
} }

#endif
