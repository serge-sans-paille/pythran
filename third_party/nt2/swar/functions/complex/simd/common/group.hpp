//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_GROUP_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_COMPLEX_SIMD_COMMON_GROUP_HPP_INCLUDED

#include <nt2/swar/functions/group.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/sdk/complex/hierarchy.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::group_, tag::cpu_,
                          (A0)(X),
                          (boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::downgrade<A0>::type> >),
                          ((simd_<complex_<arithmetic_<A0> >,X>))
                          ((simd_<complex_<arithmetic_<A0> >,X>))
                        )
  {
    typedef typename boost::dispatch::meta::downgrade<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(group(nt2::real(a0), nt2::real(a1)),
                         group(nt2::imag(a0), nt2::imag(a1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::group_, tag::cpu_,
                          (A0)(X),
                          (boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::downgrade<A0>::type> >),
                          ((simd_<dry_<arithmetic_<A0> >,X>))
                          ((simd_<dry_<arithmetic_<A0> >,X>))
                        )
  {
    typedef typename boost::dispatch::meta::downgrade<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return bitwise_cast<result_type>(group(nt2::real(a0), nt2::real(a1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::group_, tag::cpu_,
                             (A0)(X),
                             ((simd_<complex_<arithmetic_<A0> >,X>))
                           )
  {
    typedef typename boost::dispatch::meta::downgrade<typename A0::value_type>::type base_t;
    typedef typename boost::simd::meta::vector_of< base_t
                                                 , A0::static_size
                                                 >::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      return result_type(group(nt2::real(a0)), group(nt2::imag(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::group_, tag::cpu_,
                             (A0)(X),
                             ((simd_<dry_<arithmetic_<A0> >,X>))
                           )
  {
    typedef typename boost::dispatch::meta::downgrade<typename A0::value_type>::type base_t;
    typedef typename boost::simd::meta::vector_of< base_t
                                                 , A0::static_size
                                                 >::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      return bitwise_cast<result_type>(group(nt2::real(a0)));
    }
  };
} }
#endif
