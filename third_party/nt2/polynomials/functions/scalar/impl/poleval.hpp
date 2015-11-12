//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_SCALAR_IMPL_POLEVAL_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_SCALAR_IMPL_POLEVAL_HPP_INCLUDED

#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/splat.hpp>

///////////////////////////////////////////////////////////////////////////////
// unrolled polynomial evaluation
// coeff are stored in an array that can be any direct 0 based access
// eval_poly suppose that the coefs are in ascending powers
// reval_poly suppose that the coefs are in descending powers
// the implementation also works for simd evaluation
///////////////////////////////////////////////////////////////////////////////

namespace nt2
{
  struct ascending_ :boost::mpl::true_{};  // TO DO conflict with sort do a common define somewhere
  struct descending_:boost::mpl::false_{};

  namespace details
  {
    template <class T, class V, int N,  int M, class DIR>
    struct evaluate
    {
      static inline V eval(const T& a, const V& x)
      {
        return evaluate<T,V,N,M+1,DIR>::eval(a, x)*x+splat<V>(a[M-1]);
      }
    };

    template <class T, class V, int N> struct evaluate < T, V, N, N, ascending_>
    {
      static inline V eval(const T& a, const V& /*x*/)
      {
        return splat<V>(a[N-1]);
      }
    };


    template <class T, class V, int N,  int M> struct evaluate< T, V, N, M, descending_>
    {
      static inline V eval(const T& a, const V& x)
      {
        return evaluate<T,V,N,M+1,descending_>::eval(a, x)*x+splat<V>(a[N-M]);
      }
    };

    template <class T, class V, int N> struct evaluate < T, V, N, N, descending_>
    {
      static inline V eval(const T& a, const V&)
      {
        return splat<V>(a[0]);
      }
    };

  }

  template <int N, class T,  class V> inline V  eval_poly(const V& x, const T& a)
  {
    return details::evaluate<T, V, N, 1, ascending_ >::eval(a, x);
  }
  template <int N, class T,  class V> inline V reval_poly(const V& x, const T& a)
  {
    return details::evaluate<T, V, N, 1, descending_>::eval(a, x);
  }
  template <int N, class T,  class V,  class D> inline V deval_poly(const V& x, const T& a, const D&)
  {
    return details::evaluate<T, V, N, 1, D>::eval(a, x);
  }

}

#endif
