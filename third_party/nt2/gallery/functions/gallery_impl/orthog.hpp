//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_ORTHOG_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_ORTHOG_HPP_INCLUDED
#include <nt2/gallery/functions/orthog.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/ric.hpp>
#include <nt2/include/functions/cic.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/twopi.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <boost/mpl/int.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace nt2
{
  namespace details
  {
    struct isij0
    {
      template < class I, class J> inline
      typename meta::as_logical<I>::type operator()(const I & i , const J& j) const
      {
        return nt2::is_eqz(i*j);
      }
    };
    struct isi0
    {
      template < class I, class J> inline
      typename meta::as_logical<I>::type operator()(const I & i , const J& ) const
      {
        return nt2::is_eqz(i);
      }
    };
    struct isdiagpos
    {
      template < class I, class J> inline
      typename meta::as_logical<I>::type operator()(const I & i , const J& j ) const
      {
        return nt2::logical_and(nt2::is_nez(i), nt2::eq(i, j));
      }
    };
    template < class A0, class K, class T > struct orthog_return{};
  }
#define NT2_ORTHOG(V, K, Body)                                      \
  namespace ext                                                     \
  {                                                                 \
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::orthog##K##_, tag::cpu_,  \
                                (A0)(T),                            \
                                (scalar_<integer_<A0> >)            \
                                (target_<scalar_<floating_<T> > > ) \
                              )                                     \
    {                                                               \
      typedef typename T::type t_t;                                 \
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n,  T const& t),    \
                                  (A0 const& n,  T const&  ),       \
                             Body                                   \
                            )                                       \
        };                                                          \
  }                                                                 \
  namespace details                                                 \
  {                                                                 \
    template < class A0, class T >                                  \
    struct orthog_return < A0,  boost::mpl::int_<V>, T>             \
      {                                                             \
        typedef typename nt2::meta::as_<T> Target;                  \
        typedef typename nt2::meta::call<nt2::tag::orthog##K##_(A0, \
                                               Target)>::type type; \
      };                                                            \
   }                                                                \
  template<class T>                                                 \
  typename details::orthog_return<ptrdiff_t,                        \
                                  boost::mpl::int_<V>, T>::type     \
                    orthog(ptrdiff_t n, const boost::mpl::int_<V>&) \
  {                                                                 \
    return nt2::orthog##K(n, meta::as_<T>());                       \
  }                                                                 \
/**/

  NT2_ORTHOG(1, 1, (nt2::sinpi(nt2::rif(n,T())*nt2::cif(n,T())/t_t(n+1))*nt2::sqrt(Two<t_t>()/t_t(n+1))))
  NT2_ORTHOG(2, 2, (nt2::sinpi(nt2::rif(n,T())*nt2::cif(n,T())*nt2::Two<t_t>()/t_t(2*n+1))*(Two<t_t>()/nt2::sqrt(t_t(2*n+1)))))
  NT2_ORTHOG(3, 3, (nt2::exp(nt2::mul_i(nt2::ric(n,T())*nt2::cic(n,T())*nt2::Twopi<t_t>()/t_t(n)))/nt2::sqrt(t_t(n))))
  NT2_ORTHOG(4, 4, (nt2::mtimes(nt2::from_diag(nt2::rec(nt2::sqrt(nt2::cath(t_t(n), _(t_t(1), t_t(n-1)))*_(t_t(1), t_t(n))))),
                                nt2::whereij(details::isdiagpos(),
                                             nt2::from_diag(nt2::oneminus(nt2::_(t_t(1), t_t(n)))),
                                             nt2::whereij(details::isi0(),
                                                          nt2::ones(n, T()),
                                                          nt2::tril(nt2::ones(n, T()))
                                                         )
                                            )
                               )
                   )
            )
  NT2_ORTHOG(5, 5,((nt2::cospi(nt2::ric(n,T())*nt2::cic(n,T())*nt2::Two<t_t>()/t_t(n))+
                    nt2::sinpi(nt2::ric(n,T())*nt2::cic(n,T())*nt2::Two<t_t>()/t_t(n)))/nt2::sqrt(t_t(n))))
  NT2_ORTHOG(6, 6, (nt2::cospi((nt2::rif(n, T())-Half<t_t>())*(nt2::cif(n, T())-Half<t_t>())/t_t(n))*nt2::sqrt(nt2::Two<t_t>()/t_t(n))))
  NT2_ORTHOG(7, 7, (nt2::whereij(details::isij0(), nt2::ones(n,T())/nt2::sqrt(t_t(n)),nt2::eye(n,T())-ones(n,T())*(1+rec(sqrt(t_t(n))))/t_t(n-1))))
  NT2_ORTHOG(-1, m1, (nt2::cospi(nt2::ric(n,T())*nt2::cic(n,T())*nt2::rec(nt2::max(t_t(1), t_t(n-1))))))
  NT2_ORTHOG(-2, m2, (nt2::cospi(nt2::ric(n,T())*(nt2::cic(n,T())+nt2::Half<t_t>())*nt2::rec(t_t(n)))))

#undef ORTHOG

  template<int K, class T>
  typename details::orthog_return<ptrdiff_t,  boost::mpl::int_<K>, T>::type
  orthog(ptrdiff_t n)
  {
    return nt2::orthog<T>(n, boost::mpl::int_<K>());
  }

}


#endif
