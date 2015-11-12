//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_ENUMERATE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_ENUMERATE_HPP_INCLUDED

#include <boost/simd/swar/functions/enumerate.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/include/functions/simd/fma.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (X)(T)
                                    , ((target_< simd_< arithmetic_<T>,X> >))
                                    )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE result_type operator()(T const& ) const
    {
      return eval(typename simd::meta::cardinal_of<result_type>::type());
    }

    BOOST_FORCEINLINE result_type eval(boost::mpl::size_t<2> const&) const
    {
      return make<result_type>(0,1);
    }

    BOOST_FORCEINLINE result_type eval(boost::mpl::size_t<4> const&) const
    {
      return make<result_type>(0, 1, 2, 3);
    }

    BOOST_FORCEINLINE result_type eval(boost::mpl::size_t<8> const&) const
    {
      return make<result_type>(0, 1, 2, 3, 4, 5, 6, 7);
    }

    BOOST_FORCEINLINE result_type eval(boost::mpl::size_t<16> const&) const
    {
      return make<result_type>( 0, 1,  2,  3,  4,  5,  6,  7
                              , 8, 9, 10, 11, 12, 13, 14, 15
                              );
    }

    BOOST_FORCEINLINE result_type eval(boost::mpl::size_t<32> const&) const
    {
      return make<result_type>(  0,  1,  2,  3,  4,  5,  6,  7
                              ,  8,  9, 10, 11, 12, 13, 14, 15
                              , 16, 17, 18, 19, 20, 21, 22, 23
                              , 24, 25, 26, 27, 28, 29, 30, 31
                              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(X)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      ((target_< simd_< arithmetic_<T>,X> >))
                                    )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const&) const
    {
      return enumerate<result_type>() + splat<result_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(A1)(X)(Y)
                                    , ((simd_< arithmetic_<A0>, X >))
                                      ((target_< simd_< arithmetic_<A1>, Y> >))
                                    )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& ) const
    {
      return splat<result_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(A1)(X)(T)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A1> >)
                                      ((target_< simd_< arithmetic_<T>,X> >))
                                    )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1, T const& ) const
    {
      return fma( enumerate<result_type>()
                , splat<result_type>(a1)
                , splat<result_type>(a0)
                );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::enumerate_, tag::cpu_
                                    , (A0)(A1)(X)(T)
                                    , ((simd_< arithmetic_<A0>, X >))
                                      (generic_< arithmetic_<A1> >)
                                      ((target_< simd_< arithmetic_<T>,X> >))
                                    )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const&, T const& ) const
    {
      return splat<result_type>(a0);
    }
  };
} } }

#endif
