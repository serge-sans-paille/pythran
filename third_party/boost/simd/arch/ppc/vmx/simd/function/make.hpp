//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_MAKE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_MAKE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::vmx_
                          , bd::target_<bs::pack_<bd::arithmetic_<Target>,bs::vmx_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == target_t::static_size
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      typename target_t::storage_type that = { static_cast<typename target_t::value_type>(vs)... };
      return that;
    }
  };
} } }

#endif
