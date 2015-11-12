//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_VMX_ALTIVEC_SLIDE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/memory/functions/slide.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/mpl/char.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slide_
                                    , boost::simd::tag::vmx_
                                    , (A0)(N)
                                    , ((simd_ < arithmetic_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                      (mpl_integral_< scalar_< integer_<N> > >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, N const&) const
    {
      return eval ( a0
                  , boost::mpl::bool_<N::value==0>()
                  , boost::mpl::bool_ <   (N::value ==  A0::static_size)
                                      ||  (N::value == -A0::static_size)
                                      >()
                  );
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0
                    , boost::mpl::true_ const&, boost::mpl::false_ const&
                    ) const
    {
      return a0;
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const&
                    , boost::mpl::false_ const&, boost::mpl::true_ const&
                    ) const
    {
      return Zero<A0>();
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0
                    , boost::mpl::false_ const&, boost::mpl::false_ const&
                    ) const
    {
      return eval(a0, mpl::bool_<(N::value>=0)>());
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0, boost::mpl::true_ const& ) const
    {
      typedef boost::mpl::char_ < ( sizeof(typename meta::scalar_of<A0>::type)
                                  * N::value
                                  ) <<3
                                > v;

      __vector unsigned char s = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,v::value};
      return vec_slo( a0(), s );
    }

    BOOST_FORCEINLINE
    result_type eval( A0 const& a0, boost::mpl::false_ const& ) const
    {
      typedef boost::mpl::char_ < ( sizeof(typename meta::scalar_of<A0>::type)
                                  * (-N::value)
                                  ) <<3
                                > v;

      __vector unsigned char s = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,v::value};
      return vec_sro( a0(), s );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::slide_
                                    , boost::simd::tag::vmx_
                                    , (A0)(N)
                                    , ((simd_ < arithmetic_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
                                      ((simd_ < arithmetic_<A0>
                                              , boost::simd::tag::vmx_
                                              >
                                      ))
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
      typedef typename meta::scalar_of<result_type>::type scalar_type;
      return vec_sld( a0(), a1() , sizeof(scalar_type) * N::value );
    }
  };
} } }

#endif
#endif
