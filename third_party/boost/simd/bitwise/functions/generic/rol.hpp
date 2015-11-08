//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_ROL_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_ROL_HPP_INCLUDED

#include <boost/simd/bitwise/functions/rol.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::rol_, tag::cpu_
                                       , (A0)(A1)
                                       , (boost::mpl::equal_to
                                           < boost::simd::meta::cardinal_of<A0>
                                           , boost::simd::meta::cardinal_of<A1>
                                           >
                                         )
                                       , (generic_< integer_<A0> >)
                                         (generic_< integer_<A1> >)
                                       )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      typedef typename meta::scalar_of<A0>::type s_t;
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "rol : rotation is out of range");

      s_t const width = sizeof(s_t)*CHAR_BIT;
      return shli(a0, a1) | shri(a0, (width-splat<A0>(a1)) & (width-1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::rol_, tag::cpu_
                                       , (A0)(A1)
                                       , (boost::mpl::equal_to
                                           < boost::simd::meta::cardinal_of<A0>
                                           , boost::simd::meta::cardinal_of<A1>
                                           >
                                         )
                                       , (generic_< floating_<A0> >)
                                         (generic_< integer_<A1> >)
                                       )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type itype;
      return bitwise_cast<result_type>( rol ( bitwise_cast<itype>(a0)
                                            , splat<itype>(a1)
                                            )
                                      );
    }
  };
} } }

#endif
