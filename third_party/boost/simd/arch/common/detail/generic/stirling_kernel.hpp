//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_STIRLING_KERNEL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_STIRLING_KERNEL_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;

    template < class A0, class sA0 = bd::scalar_of_t<A0> >
    struct stirling_kernel;

    template < class A0 >
    struct stirling_kernel < A0, float >
    {
      static BOOST_FORCEINLINE A0 stirling1(const A0& x)
      {
        return  horn<A0,
                     0x3daaaaab,
                     0x3b638e39,
                     0xbb2fb930,
                     0xb970b359
                     >(x);
      }
    };

    template < class A0 >
    struct stirling_kernel < A0, double >
    {
      static BOOST_FORCEINLINE A0 stirling1(const A0& x)
      {
        return  horn<A0,
                     0x3fb5555555555986ll, //   8.33333333333482257126E-2
                     0x3f6c71c71b98c5fdll, //   3.47222221605458667310E-3
                     0xbf65f72607d44fd7ll, //  -2.68132617805781232825E-3
                     0xbf2e166b27e61d7cll, //  -2.29549961613378126380E-4
                     0x3f49cc72592d7293ll  //   7.87311395793093628397E-4
                     >(x);
      }
    };
  }
} }
#endif
