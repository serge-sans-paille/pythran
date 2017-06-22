//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MAKE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MAKE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/meta/hierarchy/logical.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <initializer_list>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // Some shared code between two specialisation
  template<typename Target, typename... Values>
  struct make_helper
  {
    using storage_t = typename Target::storage_type;

    static BOOST_FORCEINLINE storage_t do_ ( Values const&... vs
                                           , ::boost::simd::scalar_storage const&
                                           ) BOOST_NOEXCEPT
    {
      storage_t that{{ static_cast<typename Target::substorage_type>(vs)... }};
      return that;
    }

    static BOOST_FORCEINLINE Target do_( Values const&... vs
                                       , ::boost::simd::aggregate_storage const&
                                       ) BOOST_NOEXCEPT
    {
      using value_type = typename Target::value_type;
      std::initializer_list<value_type> lst{ static_cast<value_type>(vs)... };
      return load<Target>(lst.begin());
    }
  };

  template<typename Target, typename... Values>
  struct make_logical_helper
  {
    using storage_t = typename Target::storage_type;

    static BOOST_FORCEINLINE Target do_( Values const&... vs
                                       , ::boost::simd::aggregate_storage const&
                                       ) BOOST_NOEXCEPT
    {
      using value_type = typename Target::value_type;
      std::initializer_list<value_type> lst{ static_cast<value_type>(vs)... };
      return load<Target>(lst.begin());
    }

    template<typename K>
    static BOOST_FORCEINLINE Target do_( Values const&... vs
                                       , K const&
                                       ) BOOST_NOEXCEPT
    {
      using   target_t = as_arithmetic_t<Target>;
      using   value_t  = typename target_t::value_type;
      return  bitwise_cast<Target>( make( as_<target_t>{}, genmask<value_t>(vs)...));
    }
  };

  //------------------------------------------------------------------------------------------------
  // make from unspecified value
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bd::cpu_
                          , bd::target_<bs::pack_<bd::unspecified_<Target>,bs::simd_emulation_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;

    static_assert ( sizeof...(Values) == target_t::static_size
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return make_helper<target_t,Values...>::do_( vs..., typename target_t::storage_kind{});
    }
  };

  //------------------------------------------------------------------------------------------------
  // make from logical value in emulation mode - This is not duplicated code
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values, typename Ext)
                          , bd::cpu_
                          , bd::target_<bs::pack_<bs::logical_<Target>,Ext>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;

    static_assert ( sizeof...(Values) == target_t::static_size
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return make_logical_helper<target_t,Values...>::do_(vs..., typename target_t::storage_kind{});
    }
  };
} } }

#endif
