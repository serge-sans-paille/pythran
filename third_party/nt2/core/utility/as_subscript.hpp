//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_AS_SUBSCRIPT_HPP_INCLUDED
#define NT2_CORE_UTILITY_AS_SUBSCRIPT_HPP_INCLUDED

#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/modulo.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/int.hpp>

namespace nt2 { namespace result_of
{
  //============================================================================
  // Case for no base index
  //============================================================================
  template<class Size,class Position>
  struct as_subscript
  {
    typedef typename meta::strip<Position>::type                      base_t;
    typedef typename boost::dispatch::meta::as_unsigned<base_t>::type type_t;
    typedef boost::fusion::result_of::size<Size>                      dims_t;
    typedef boost::array<type_t,dims_t::value>                        type;

    BOOST_FORCEINLINE type
    operator()(const Size& size, const Position& pos) const
    {
      type sub;
      type_t p = bitwise_cast<type_t>(pos);

      eval( sub, p, size
          , boost::mpl::int_<0>()
          , boost::mpl::int_<dims_t::value>()
          , boost::mpl::bool_<dims_t::value==2>()
          );

      return sub;
    }

    // Normal case
    template<class N, class M>
    BOOST_FORCEINLINE void
    eval( type& sub, const type_t& p
        , Size const& s, N const&, M const& m
        , boost::mpl::false_ const&
        ) const
    {
      BOOST_AUTO_TPL(dim, boost::fusion::at_c<N::value>(s));
      type_t ls     = splat<type_t>(dim?dim:1);

      sub[N::value] = p % ls;
      eval( sub, p/ls, s
          , boost::mpl::int_<N::value+1>()
          , m
          , boost::mpl::bool_<(N::value+1 == M::value-2)>()
          );
    }

    template<class N, class M>
    BOOST_FORCEINLINE void
    eval( type& sub, type_t const& p
        , Size const& s, N const&, M const&
        , boost::mpl::true_ const&
        ) const

    {
      BOOST_AUTO_TPL(dim, boost::fusion::at_c<N::value>(s));
      type_t ls     = splat<type_t>(dim?dim:1);

      sub[N::value]   = p % ls;
      sub[N::value+1] = p / ls;
    }

    BOOST_FORCEINLINE void
    eval( type& sub, const type_t& p, Size const&
        , boost::mpl::int_<0> const &, boost::mpl::int_<1> const &
        , boost::mpl::false_ const&
        ) const
    {
      sub[0] = p;
    }
  };
} }

namespace nt2
{
  template<class Size,class Position>
  typename result_of::as_subscript<Size,Position>::type
  as_subscript(Size const& sz, Position const& p)
  {
    return result_of::as_subscript<Size,Position>()(sz,p);
  }
}
#endif
