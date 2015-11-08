//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_MAX_EXTENT_HPP_INCLUDED
#define NT2_CORE_UTILITY_MAX_EXTENT_HPP_INCLUDED

#include <nt2/core/utility/of_size.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace utility { namespace result_of
{
  template<class A0, class A1, class A2=void, class A3=void>
  struct max_extent;

  template<class A0, class A1> struct max_extent<A0,A1>
  {
    typedef typename meta::call<tag::extent_(A0 const&)>::type  rext0_t;
    typedef typename meta::call<tag::extent_(A1 const&)>::type  rext1_t;
    typedef typename meta::strip<rext0_t>::type                 ext0_t;
    typedef typename meta::strip<rext1_t>::type                 ext1_t;
    typedef typename result_of::max<ext0_t,ext1_t>::type        type;
  };

  template<class A0, class A1,class A2> struct max_extent<A0,A1,A2>
  {
    typedef typename result_of::max_extent<A0,A1>::type         ext01_t;
    typedef typename meta::call<tag::extent_(A2 const&)>::type  rext2_t;
    typedef typename meta::strip<rext2_t>::type                 ext2_t;
    typedef typename result_of::max<ext01_t,ext2_t>::type       type;
  };

  template<class A0, class A1,class A2,class A3> struct max_extent
  {
    typedef typename result_of::max_extent<A0,A1>::type           ext01_t;
    typedef typename result_of::max_extent<A2,A3>::type           ext23_t;
    typedef typename result_of::max<ext01_t,ext23_t>::type        type;
  };
} } }

namespace nt2 { namespace utility
{
  template<class A, class B>
  typename result_of::max_extent<A,B>::type max_extent(A const& a, B const& b)
  {
    return nt2::utility::max(nt2::extent(a),nt2::extent(b));
  }

  template<class A, class B, class C>
  typename result_of::max_extent<A,B,C>::type
  max_extent(A const& a, B const& b, C const& c)
  {
    return nt2::utility::max(nt2::utility::max_extent(a,b),nt2::extent(c));
  }

  template<class A, class B, class C,class D>
  typename result_of::max_extent<A,B,C,D>::type
  max_extent(A const& a, B const& b, C const& c, D const& d)
  {
    return nt2::utility::max(nt2::utility::max_extent(a,b),nt2::utility::max_extent(c,d));
  }
} }

#endif
