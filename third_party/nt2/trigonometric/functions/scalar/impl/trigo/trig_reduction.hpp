//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/rem_pio2_cephes.hpp>
#include <nt2/include/functions/simd/rem_pio2_straight.hpp>
#include <nt2/include/functions/simd/rem_pio2.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/split.hpp>
#include <nt2/include/functions/simd/group.hpp>
#include <nt2/include/functions/simd/fast_toint.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/if_else_allbits.hpp>
#include <nt2/include/functions/simd/is_not_greater.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/simd/inrad.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/_20_pi.hpp>
#include <nt2/include/constants/oneo_90.hpp>
#include <nt2/include/constants/_180.hpp>
#include <nt2/include/constants/oneo_180.hpp>
#include <nt2/include/constants/medium_pi.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>
#include <boost/simd/sdk/config/enforce_precision.hpp>
#include <boost/mpl/int.hpp>

#include <boost/utility/enable_if.hpp>

namespace nt2 { namespace details
{
  template< class A0
            , class unit_tag
            , class style
            , class mode
            , class base_A0 = typename meta::scalar_of<A0>::type
  >
  struct trig_reduction;

  // This class exposes the public static member:
  // reduce:                to provide range reduction
  //
  // unit_tag allows to choose statically the scaling  among radian_tag, pi_tag, degree_tag
  // meaning that the cosa function will (for example) define respectively
  // x-->cos(x)          (radian_tag),
  // x-->cos(p*x)        (pi_tag)
  // x-->cos((pi/180)*x) (degree_tag)
  //

  // trigonometric reduction strategies in the [-pi/4, pi/4] range.
  // these reductions are used in the accurate and fast
  // trigonometric functions with different policies

  template<class A0, class style, class mode>
  struct trig_reduction < A0, radian_tag, style, mode>
  {
    typedef typename meta::scalar_of<A0>::type                         base_A0;
    typedef typename meta::as_logical<A0>::type                        bA0;
    typedef typename meta::as_integer<A0, signed>::type                int_type;
    typedef typename boost::simd::meta::is_upgradable_on_ext<A0>::type conversion_allowed;

    static BOOST_FORCEINLINE bA0 is_0_pio4_reduced(const A0&a0) { return boost::simd::is_ngt(a0, nt2::Pio_4<A0>()); }
    static BOOST_FORCEINLINE bA0 is_0_pio2_reduced(const A0&a0) { return boost::simd::is_ngt(a0, nt2::Pio_2<A0>()); }
    static BOOST_FORCEINLINE bA0 is_0_20pi_reduced(const A0&a0) { return boost::simd::is_ngt(a0, _20_pi<A0>()); }
    static BOOST_FORCEINLINE bA0 is_0_mpi_reduced (const A0&a0) { return boost::simd::is_ngt(a0, Medium_pi<A0>()); }  //2^6pi
    static BOOST_FORCEINLINE bA0 is_0_dmpi_reduced(const A0&a0) { return boost::simd::is_ngt(a0, single_constant<A0,0x49490fdb>()); }  //2^18pi

    static BOOST_FORCEINLINE bA0 cot_invalid(const A0& ) { return False<bA0>(); }
    static BOOST_FORCEINLINE bA0 tan_invalid(const A0& ) { return False<bA0>(); }

    static BOOST_FORCEINLINE int_type reduce(const A0& x, A0& xr) { return inner_reduce(x, xr); }
  private:
    static BOOST_FORCEINLINE int_type inner_reduce(const A0& x, A0& xr)
    {
      A0 xx =  preliminary<mode>::clip(x);
      return select_mode(xx, xr, boost::mpl::int_<mode::start>());
    }

    template < class Mode, bool clipped = Mode::clipped>
    struct preliminary
    {
      static BOOST_FORCEINLINE A0 const& clip(const A0& x) { return x; }
    };


    template < class Mode>
    struct preliminary<Mode, true>
    {
      static BOOST_FORCEINLINE A0 clip(const A0& x)
      {
        return clipto(x, boost::mpl::int_<Mode::range>());
      }
    private :
      static BOOST_FORCEINLINE A0 clipto(const A0& x, boost::mpl::int_<r_0_pio4> const&)
      {
        return if_else_nan(is_0_pio4_reduced(x), x);
      }
      static BOOST_FORCEINLINE A0 clipto(const A0& x, boost::mpl::int_<r_0_20pi> const&)
      {
        return if_else_nan(is_0_20pi_reduced(x), x);
      }
      static BOOST_FORCEINLINE A0 clipto(const A0& x, boost::mpl::int_<r_0_mpi> const&)
      {
        return if_else_nan(is_0_mpi_reduced(x), x);
      }
      static BOOST_FORCEINLINE A0 clipto(const A0& x, boost::mpl::int_<r_0_dmpi> const&)
      {
        return if_else_nan(is_0_dmpi_reduced(x), x);
      }
    };

    static BOOST_FORCEINLINE int_type
    select_range( const A0& xx, A0& xr
                , boost::mpl::true_ const&
                , boost::mpl::int_<r_0_pio4> const&
                )
    {
      xr = xx;
      return Zero<int_type>();
    }

    static BOOST_FORCEINLINE int_type
    select_range( const A0& xx, A0& xr
                , boost::mpl::false_ const&
                , boost::mpl::int_<r_0_pio4> const& r
                )
    {
      if(nt2::all(is_0_pio4_reduced(xx)))
        return select_range(xx,xr,boost::mpl::true_(), r);

      return select_mode(xx,xr,boost::mpl::int_<r_0_pio2>());
    }

    static BOOST_FORCEINLINE int_type
    select_mode(const A0& xx, A0& xr, boost::mpl::int_<r_0_pio4> const& r)
    {
      return select_range(xx,xr,boost::mpl::bool_<mode::range == r_0_pio4>(),r);
    }

    static BOOST_FORCEINLINE int_type select_mode(const A0& xx, A0& xr, boost::mpl::int_<r_0_pio2> const&)
    {
      if(nt2::all(is_0_pio2_reduced(xx)))
        return rem_pio2_straight(xx, xr);
      return select_mode(xx,xr,boost::mpl::int_<r_0_20pi>());
    }

    static BOOST_FORCEINLINE int_type
    select_range( const A0& xx, A0& xr
                , boost::mpl::true_ const&
                , boost::mpl::int_<r_0_20pi> const&
                )
    {
      return rem_pio2_cephes(xx, xr);
    }

    static BOOST_FORCEINLINE int_type
    select_range( const A0& xx, A0& xr
                , boost::mpl::false_ const&
                , boost::mpl::int_<r_0_20pi> const& r
                )
    {
      if(nt2::all(is_0_20pi_reduced(xx)))
        return select_range(xx,xr,boost::mpl::true_(), r);

      return select_mode(xx,xr,boost::mpl::int_<r_0_mpi>());
    }

    static BOOST_FORCEINLINE int_type
    select_mode(const A0& xx, A0& xr, boost::mpl::int_< r_0_20pi> const& r)
    {
      return select_range(xx,xr,boost::mpl::bool_<mode::range == r_0_20pi>(),r);
    }



    static BOOST_FORCEINLINE int_type
    select_range( const A0& xx, A0& xr
                , boost::mpl::true_ const&
                , boost::mpl::int_<r_0_mpi> const&
                )
    {
      return rem_pio2_medium(xx, xr);
    }

    static BOOST_FORCEINLINE int_type
    select_range( const A0& xx, A0& xr
                , boost::mpl::false_ const&
                , boost::mpl::int_<r_0_mpi> const& r
                )
    {
      if(nt2::all(is_0_mpi_reduced(xx)))
        return select_range(xx,xr,boost::mpl::true_(), r);

      return select_mode(xx,xr,boost::mpl::int_<r_0_dmpi>());
    }

    static BOOST_FORCEINLINE int_type select_mode(const A0& xx, A0& xr, boost::mpl::int_< r_0_mpi> const& r)
    {
      return select_range(xx,xr,boost::mpl::bool_<mode::range == r_0_mpi>(),r);
    }

    static BOOST_FORCEINLINE int_type select_mode(const A0& xx, A0& xr, boost::mpl::int_< r_0_dmpi> const&)
    {
      if(nt2::all(is_0_dmpi_reduced(xx)))
        return use_conversion(xx, xr, style(), conversion_allowed());
      return rem_pio2(xx, xr);
    }

    static BOOST_FORCEINLINE int_type use_conversion(const A0 & xx,  A0& xr,  const style &, boost::mpl::false_)
    {
      return rem_pio2(xx, xr);
    }

    static BOOST_FORCEINLINE int_type use_conversion(const A0 & xx,  A0& xr,  const tag::not_simd_type &, boost::mpl::true_)
    {
      // all of x are in [0, 2^18*pi],  conversion to double is used to reduce
      typedef typename meta::upgrade<A0>::type uA0;
      typedef trig_reduction< uA0, radian_tag,  tag::not_simd_type, mode, double> aux_reduction;
      uA0 ux = xx, uxr;
      int_type n = static_cast<int_type>(aux_reduction::reduce(ux, uxr));
      xr = static_cast<A0>(uxr);
      return n;
    }

    static BOOST_FORCEINLINE int_type use_conversion(const A0 & x,  A0& xr,  const tag::simd_type &, boost::mpl::true_)
    {
      // all of x are in [0, 2^18*pi],  conversion to double is used to reduce
      typedef typename meta::upgrade<A0>::type uA0;
      typedef typename meta::upgrade<int_type>::type uint_type;
      typedef trig_reduction< uA0, radian_tag,  tag::simd_type, mode, double> aux_reduction;
      uA0 ux1, ux2, uxr1, uxr2;
      nt2::split(x, ux1, ux2);
      uint_type n1 = aux_reduction::reduce(ux1, uxr1);
      uint_type n2 = aux_reduction::reduce(ux2, uxr2);
      xr = nt2::group(uxr1, uxr2);
      nt2::split(xr, ux1, ux2);
      return nt2::group(n1, n2);
    }
  };

  template<class A0, class style>
  struct trig_reduction<A0,degree_tag, style, big_>
  {
    typedef typename meta::as_logical<A0>::type              bA0;
    typedef typename meta::as_integer<A0, signed>::type int_type;

    static BOOST_FORCEINLINE bA0 cot_invalid(const A0& x) { return logical_and(nt2::is_nez(x), is_flint(x*nt2::Oneo_180<A0>())); }
    static BOOST_FORCEINLINE bA0 tan_invalid(const A0& x) { return nt2::is_flint((x-nt2::_90<A0>())*nt2::Oneo_180<A0>()); }

    static BOOST_FORCEINLINE int_type reduce(const A0& x, A0& xr)
    {
      A0 xi = nt2::round2even(x*nt2::Oneo_90<A0>());
      A0 x2 = x - xi * nt2::_90<A0>();

      xr =  nt2::inrad(x2);
      return nt2::fast_toint(xi);
    }
  };

  #ifdef BOOST_SIMD_HAS_X87
  template<class A0>
  struct trig_reduction<A0,degree_tag, tag::not_simd_type, big_>
  {
    typedef typename meta::as_logical<A0>::type              bA0;
    typedef typename meta::as_integer<A0, signed>::type int_type;

    static BOOST_FORCEINLINE bA0 cot_invalid(const A0& x) { return logical_and(nt2::is_nez(x), is_flint(x/nt2::_180<A0>())); }
    static BOOST_FORCEINLINE bA0 tan_invalid(const A0& x) { return nt2::is_flint((x-nt2::_90<A0>())/nt2::_180<A0>()); }

    static BOOST_FORCEINLINE int_type reduce(const A0& x, A0& xr)
    {
      A0 xi = nt2::round2even(x*nt2::Oneo_90<A0>());
      A0 x2 = x - xi * nt2::_90<A0>();

      xr =  nt2::inrad(x2);
      return nt2::fast_toint(xi);
    }
  };
  #endif

  template < class A0, class style>
  struct trig_reduction < A0, pi_tag,  style, big_>
  {
    typedef typename meta::as_logical<A0>::type              bA0;
    typedef typename meta::as_integer<A0, signed>::type int_type;

    static BOOST_FORCEINLINE bA0 cot_invalid(const A0& x) { return logical_and(nt2::is_nez(x), nt2::is_flint(x)); }
    static BOOST_FORCEINLINE bA0 tan_invalid(const A0& x) { return nt2::is_flint(x-nt2::Half<A0>()) ; }

    static BOOST_FORCEINLINE int_type reduce(const A0& x,  A0& xr)
    {
      A0 xi = nt2::round2even(x*nt2::Two<A0>());
      A0 x2 = x - xi * nt2::Half<A0>();
      xr = x2*nt2::Pi<A0>();
      return nt2::fast_toint(xi);
    }
  };
} }

#endif
