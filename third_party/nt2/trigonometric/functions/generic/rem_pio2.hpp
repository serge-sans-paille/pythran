//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_REM_PIO2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_GENERIC_REM_PIO2_HPP_INCLUDED

#include <nt2/trigonometric/functions/rem_pio2.hpp>
#include <nt2/trigonometric/functions/scalar/impl/trigo/selection_tags.hpp>
#include <nt2/include/functions/simd/rem_pio2_straight.hpp>
#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/rem_pio2_cephes.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_,  tag::cpu_,
                      (A0),
                      ((generic_ < floating_<A0> > ))
                    )
  {
    typedef typename meta::as_integer<A0>::type            itype;
    typedef boost::fusion::tuple<itype,A0,A0>        result_type;

    inline result_type operator()(A0 const& a0) const
    {
      A0 second, third;
      itype const first =
        nt2::rem_pio2(a0,
                      second,
                      third
                     );
      return result_type(first, second, third);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_, tag::cpu_,
                             (A0),
                             ((generic_ < floating_<A0> > ))
                             ((generic_ < floating_<A0> > ))
                            )
  {
    typedef typename meta::as_integer<A0>::type result_type;
    inline result_type operator()(A0 const& a0, A0 & xr) const
    {
      A0 xc;
      return nt2::rem_pio2(a0, xr, xc);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::rem_pio2_, tag::cpu_,
                             (A0)(A1),
                             ((generic_ <floating_<A0>  > ))
                             ((generic_ <floating_<A0>  > ))
                             ((target_ <unspecified_<A1> >))
                 )
  {
    typedef typename meta::as_integer<A0>::type result_type;
    inline result_type operator()(A0 const& a0, A0 & xr, A1 const&) const
    {
      typedef typename A1::type selector;
      return rempio2<selector, void>::rem(a0, xr);
    }
  private:
    template < class T, class dummy = void> struct rempio2
    {
      static inline result_type rem(A0 const&, A0 &)
      {
        BOOST_ASSERT_MSG(false, "wrong target for rem_pio2");
        return nt2::Zero<result_type>();
      }
    };

    template < class dummy> struct rempio2 < big_, dummy>
    {
      static inline result_type rem(A0 const& x, A0 & xr)
      {
        return nt2::rem_pio2(x, xr);
      }
    };

    template < class dummy> struct rempio2 < very_small_, dummy >
    {
      static inline result_type rem(A0 const& x, A0 & xr)
      {
        return nt2::rem_pio2_straight(x, xr);
      }
    };

    template < class dummy> struct rempio2 < small_, dummy >
    {
      static inline result_type rem(A0 const& x, A0 & xr)
      {
        return nt2::rem_pio2_cephes(x, xr);
      }
    };

    template < class dummy> struct rempio2 < medium_, dummy >
    {
      static inline result_type rem(A0 const& x, A0 & xr)
      {
        return nt2::rem_pio2_medium(x, xr);
      }
    };
  };

} }
#endif
