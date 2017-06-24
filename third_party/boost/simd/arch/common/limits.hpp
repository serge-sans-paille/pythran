//==================================================================================================
/*!
  @file

  Aggregate SIMD numerical and type limits

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_LIMITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_LIMITS_HPP_INCLUDED

#include <boost/simd/arch/x86/tags.hpp>
#include <boost/simd/detail/dispatch/meta/make_integer.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api
    @brief Type informations for SIMD extensions

    This aggregate traits gathers informations about available types and cardinals for any given
    SIMD extension.

    @tparam Tag SIMD Extension tag
  **/
  template<typename Tag> struct limits
  {
    using parent = boost::simd::simd_;

    /// @brief Retrieves largest integer supported by current extension
    struct largest_integer
    {
      template<typename Sign> struct apply : boost::dispatch::make_integer<8,Sign> {};
    };

    /// @brief Retrieves smallest integer supported by current extension
    struct smallest_integer
    {
      template<typename Sign> struct apply : boost::dispatch::make_integer<1,Sign> {};
    };

    /// @brief Retrieves largest real supported by current extension
    using largest_real  = double;

    /// @brief Retrieves smallest integer supported by current extension
    using smallest_real = float;

    /// @brief Type size informations
    enum  {
            bits  = 128 ///<  SIMD Register size in bits
          , bytes = 16  ///<  SIMD Register size in bytes
          };

    using supported_types = nsm::list < float, double
                                      , std::int8_t , std::int16_t , std::int32_t , std::int64_t
                                      , std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t
                                      >;
  };
} }

#endif

