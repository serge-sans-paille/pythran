//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_SLIDE_HPP_INCLUDED

#include <boost/simd/memory/functions/slide.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slide_
                                    , boost::simd::tag::cpu_
                                    , (A0)(N)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                      (mpl_integral_< scalar_< integer_<N> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, N const&) const
    {
      return eval(a0,boost::mpl::bool_<(N::value>=0)>());
    }

    BOOST_FORCEINLINE
    result_type eval(A0 const& a0, boost::mpl::true_ const&) const
    {
      return slide<N::value>(a0,Zero<A0>());
    }

    BOOST_FORCEINLINE
    result_type eval(A0 const& a0, boost::mpl::false_ const&) const
    {
      return slide<meta::cardinal_of<A0>::value+N::value>(Zero<A0>(),a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slide_
                                    , boost::simd::tag::cpu_
                                    , (A0)(N)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                      ((simd_<arithmetic_<A0>, X>))
                                      (mpl_integral_< scalar_< integer_<N> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A0 const& a1, N const&) const
    {
      return side ( a0, a1
                  , boost::mpl::bool_< (N::value>=0) >()
                  );
    }

    BOOST_FORCEINLINE
    result_type side(A0 const& a0, A0 const& a1, boost::mpl::true_ const&) const
    {
      return eval ( a0, a1
                  , boost::mpl::bool_<N::value==0>()
                  , boost::mpl::bool_<N::value==A0::static_size>()
                  );
    }

    BOOST_FORCEINLINE
    result_type side(A0 const& a0, A0 const& a1, boost::mpl::false_ const&) const
    {
      return slide<A0::static_size + N::value>(a1,a0);
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0, A0 const&
                    , boost::mpl::true_ const&, boost::mpl::false_ const&
                    ) const
    {
      return a0;
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const&, A0 const& a1
                    , boost::mpl::false_ const&, boost::mpl::true_ const&
                    ) const
    {
      return a1;
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0, A0 const& a1
                    , boost::mpl::false_ const&, boost::mpl::false_ const&
                    ) const
    {
      result_type that;
      static const int limit = A0::static_size-N::value;

      for(int i=0;i<limit;++i) that[i] =a0[i+N::value];
      for(int i=limit;i<A0::static_size;++i) that[i] =a1[i-limit];

      return that;
    }
  };
} } }

#endif
