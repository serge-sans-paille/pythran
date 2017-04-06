//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSbd:E_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_TRIG_REDUCTION_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_TRIG_REDUCTION_HPP_INCLUDED

#include <boost/simd/arch/common/detail/generic/trig_reduction.hpp>
#include <boost/simd/function/rem_pio2_medium.hpp>
#include <boost/simd/function/rem_pio2_cephes.hpp>
#include <boost/simd/function/rem_pio2.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

#include <boost/simd/function/all.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/if_else_nan.hpp>
#include <boost/simd/function/if_one_else_zero.hpp>
#include <boost/simd/function/is_not_greater.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/all.hpp>
#include <boost/simd/function/inrad.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/pio_2.hpp>
#include <boost/simd/constant/pio_4.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/detail/constant/medium_pi.hpp>
#include <boost/simd/constant/false.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/real.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <utility>

namespace boost { namespace simd
{
  namespace detail
  {
    template<class A0, class mode>
    struct trig_reduction < A0, tag::radian_tag, tag::simd_type, mode>
    {
//      using i_t = bd::as_integer_t<A0, signed>;
      using l_t = bs::as_logical_t<A0>;
      using conversion_allowed_t = bd::is_upgradable<A0>;

      static BOOST_FORCEINLINE auto is_0_pio4_reduced(const A0&a0) BOOST_NOEXCEPT
      ->  decltype(is_not_greater(a0, Pio_4<A0>()))
      {
        return is_not_greater(a0, Pio_4<A0>());
      }
      static BOOST_FORCEINLINE auto is_0_pio2_reduced(const A0&a0) BOOST_NOEXCEPT
      ->  decltype(is_not_greater(a0, Pio_2<A0>()))
      {
        return is_not_greater(a0, Pio_2<A0>());
      }
      static BOOST_FORCEINLINE auto is_0_20pi_reduced(const A0&a0) BOOST_NOEXCEPT
      ->  decltype(is_not_greater(a0, Real<A0, 0X404F6A7A2955385EULL, 0X427B53D1UL>()))
      {
        return is_not_greater(a0, Real<A0, 0X404F6A7A2955385EULL, 0X427B53D1UL>()); //20 pi;
      }
      static BOOST_FORCEINLINE auto is_0_mpi_reduced (const A0&a0) BOOST_NOEXCEPT
      ->  decltype(is_not_greater(a0, Medium_pi<A0>()))
      {
        return is_not_greater(a0, Medium_pi<A0>()); //2^6 pi
      }
      static BOOST_FORCEINLINE auto is_0_dmpi_reduced(const A0&a0) BOOST_NOEXCEPT
      ->  decltype(is_not_greater(a0,A0(823549.664582643)))
      {
        return is_not_greater(a0, A0(823549.664582643)); //2^18 pi
      }

      static BOOST_FORCEINLINE l_t cot_invalid(const A0& )  BOOST_NOEXCEPT
      {
        return False<l_t>();
      }
      static BOOST_FORCEINLINE l_t tan_invalid(const A0& )  BOOST_NOEXCEPT
      {
        return False<l_t>();
      }

      static BOOST_FORCEINLINE A0 reduce(const A0& x, A0& xr)  BOOST_NOEXCEPT
      {
        return inner_reduce(x, xr);
      }

      static BOOST_FORCEINLINE A0 inner_reduce(const A0& x, A0& xr) BOOST_NOEXCEPT
      {
        A0 xx =  preliminary<mode>::clip(x);
        return select_mode(xx, xr, boost::mpl::int_<mode::start>());
      }

      template < class Mode, bool clipped = Mode::clipped>
      struct preliminary
      {
        static BOOST_FORCEINLINE A0 const& clip(const A0& x) BOOST_NOEXCEPT  { return x; }
      };


      template < class Mode>
      struct preliminary<Mode, true>
      {
        static BOOST_FORCEINLINE A0 clip(const A0& x) BOOST_NOEXCEPT
        {
          return clipto(x, boost::mpl::int_<Mode::range>());
        }
      private :
        static BOOST_FORCEINLINE A0 clipto(const A0& x
                                          , boost::mpl::int_<tag::r_0_pio4> const&) BOOST_NOEXCEPT
        {
          return if_else_nan(is_0_pio4_reduced(x), x);
        }
        static BOOST_FORCEINLINE A0 clipto(const A0& x
                                          , boost::mpl::int_<tag::r_0_20pi> const&) BOOST_NOEXCEPT
        {
          return if_else_nan(is_0_20pi_reduced(x), x);
        }
        static BOOST_FORCEINLINE A0 clipto(const A0& x
                                          , boost::mpl::int_<tag::r_0_mpi> const&) BOOST_NOEXCEPT
        {
          return if_else_nan(is_0_mpi_reduced(x), x);
        }
        static BOOST_FORCEINLINE A0 clipto(const A0& x
                                          , boost::mpl::int_<tag::r_0_dmpi> const&) BOOST_NOEXCEPT
        {
          return if_else_nan(is_0_dmpi_reduced(x), x);
        }
      };

      static BOOST_FORCEINLINE A0
      select_range( const A0& xx, A0& xr
                  , boost::mpl::true_ const&
                  , boost::mpl::int_<tag::r_0_pio4> const&
                  ) BOOST_NOEXCEPT
      {
        xr = xx;
        return Zero<A0>();
      }

      static BOOST_FORCEINLINE A0
      select_range( const A0& xx, A0& xr
                  , boost::mpl::false_ const&
                  , boost::mpl::int_<tag::r_0_pio4> const& r
                  ) BOOST_NOEXCEPT
      {
        if(all(is_0_pio4_reduced(xx)))
        {
          return select_range(xx,xr,boost::mpl::true_(), r);
        }

        return select_mode(xx,xr,boost::mpl::int_<tag::r_0_pio2>());
      }

      static BOOST_FORCEINLINE A0
      select_mode(const A0& xx, A0& xr
                 , boost::mpl::int_<tag::r_0_pio4> const& r) BOOST_NOEXCEPT
      {
        return select_range(xx,xr,boost::mpl::bool_<mode::range == tag::r_0_pio4>(),r);
      }

      static BOOST_FORCEINLINE A0
      select_mode(const A0& xx, A0& xr
                 , boost::mpl::int_<tag::r_0_pio2> const&) BOOST_NOEXCEPT
      {
        if(all(is_0_pio2_reduced(xx)))
        {
          auto test = is_greater(xx, Pio_4<A0>());
          xr = xx-Pio2_1<A0>();
          xr -= Pio2_2<A0>();
          xr -= Pio2_3<A0>();
          xr = if_else(test, xr, xx);
          return if_one_else_zero(test);
        }

        return select_mode(xx,xr,boost::mpl::int_<tag::r_0_20pi>());
      }

      static BOOST_FORCEINLINE A0
      select_range( const A0& xx, A0& xr
                  , boost::mpl::true_ const&
                  , boost::mpl::int_<tag::r_0_20pi> const&
                  ) BOOST_NOEXCEPT
      {
        A0 n;
        std::tie(n, xr) = rem_pio2_cephes(xx);
        return n;
      }

      static BOOST_FORCEINLINE A0
      select_range( const A0& xx, A0& xr
                  , boost::mpl::false_ const&
                  , boost::mpl::int_<tag::r_0_20pi> const& r
                  ) BOOST_NOEXCEPT
      {
        if(all(is_0_20pi_reduced(xx)))
          return select_range(xx,xr,boost::mpl::true_(), r);

        return select_mode(xx,xr,boost::mpl::int_<tag::r_0_mpi>());
      }

      static BOOST_FORCEINLINE A0
      select_mode(const A0& xx, A0& xr
                 , boost::mpl::int_< tag::r_0_20pi> const& r) BOOST_NOEXCEPT
      {
        return select_range(xx,xr,boost::mpl::bool_<mode::range == tag::r_0_20pi>(),r);
      }



      static BOOST_FORCEINLINE A0
      select_range( const A0& xx, A0& xr
                  , boost::mpl::true_ const&
                  , boost::mpl::int_<tag::r_0_mpi> const&
                  ) BOOST_NOEXCEPT
      {
        A0 n;
        std::tie(n, xr) = rem_pio2_medium(xx);
        return n;
      }

      static BOOST_FORCEINLINE A0
      select_range( const A0& xx, A0& xr
                  , boost::mpl::false_ const&
                  , boost::mpl::int_<tag::r_0_mpi> const& r
                  ) BOOST_NOEXCEPT
      {
        if(all(is_0_mpi_reduced(xx)))
          return select_range(xx,xr,boost::mpl::true_(), r);

        return select_mode(xx,xr,boost::mpl::int_<tag::r_0_dmpi>());
      }

      static BOOST_FORCEINLINE A0
      select_mode(const A0& xx, A0& xr
                 , boost::mpl::int_< tag::r_0_mpi> const& r) BOOST_NOEXCEPT
      {
        return select_range(xx,xr,boost::mpl::bool_<mode::range == tag::r_0_mpi>(),r);
      }

      static BOOST_FORCEINLINE A0
      select_mode(const A0& xx, A0& xr
                 , boost::mpl::int_< tag::r_0_dmpi> const&) BOOST_NOEXCEPT
      {
        A0 n;
        std::tie(n, xr) = rem_pio2(xx);
        return n;
      }
    };

  }
} }

#endif
