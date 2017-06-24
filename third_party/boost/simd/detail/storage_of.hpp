//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_STORAGE_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_STORAGE_OF_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/forward.hpp>
#include <boost/simd/detail/as_simd.hpp>
#include <boost/simd/meta/expected_cardinal.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <array>

#if defined __GNUC__ && __GNUC__>=6
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace boost { namespace simd { namespace detail
{
  // Status for emulated SIMD storage via array of scalar
  using emulated_status   = nsm::int32_t<-1>;

  // Status for native SIMD storage
  using native_status     = nsm::int32_t<+0>;

  // Status for emulated SIMD storage via array of pack
  using aggregated_status = nsm::int32_t<+1>;

  // Status for SIMD storage to be determined
  using unknown_status    = nsm::int32_t<42>;

  //================================================================================================
  /*
    Determines how a given block of C elements of type T fit in hardware registers of extension X.
  **/
  //================================================================================================
  template< typename T, std::size_t C, typename X>
  struct storage_status : nsm::int32_t<   (expected_cardinal<T,X>::value != C)
                                          * ( (expected_cardinal<T,X>::value < C) ? +1 : -1)
                                          >
  {};

  // If ABI is not supported by current hardware, search for proper emulated storage later
  template< typename T, std::size_t C>
  struct  storage_status<T,C,simd_emulation_> : unknown_status
  {};

  //================================================================================================
  /*
    For a given couple Type x @c Cardinal, provides the type usable for storing a block
    containing Cardinal elements of type Type in an optimized way.
  */
  //================================================================================================
  template< typename Type, std::size_t Cardinal, typename ABI
          , typename Status = typename storage_status<Type,Cardinal,ABI>::type
          , typename Enable = void
          >
  struct storage_of
  {};

  // Unknown ABI requires checks on aggregation/emulation
  template< typename Type, std::size_t Cardinal>
  struct  storage_of<Type,Cardinal,simd_emulation_,unknown_status>
  #if !defined(BOOST_SIMD_STRICT_EMULATION)
        : storage_of<Type,Cardinal,BOOST_SIMD_DEFAULT_FAMILY>
  #else
        : storage_of<Type,Cardinal,boost::simd::simd_,emulated_status>
  #endif
  {};

  // If the cardinal requested is lower than the expected one,
  // then try to find a suitable storage in parent extension.
  template< typename Type, std::size_t Cardinal, typename ABI>
  struct  storage_of<Type,Cardinal,ABI,emulated_status>
        : storage_of<Type,Cardinal, typename limits<ABI>::parent>
  {};

  // If the cardinal requested is lower than the expected one then use an array of scalar.
  template< typename Type, std::size_t Cardinal>
  struct storage_of<Type,Cardinal,boost::simd::simd_,emulated_status>
  {
    using type = std::array<Type,Cardinal>;
  };

  // If the cardinal requested is OK but type is unsupported by this extension,
  // then use an array of scalar.
  template< typename Type, std::size_t Cardinal>
  struct storage_of<Type,Cardinal,boost::simd::simd_,native_status>
  {
    using type = std::array<Type,Cardinal>;
  };

  // If we match cardinals, use as_simd for current Family unless Type is no_such_type_
  template< typename Type, std::size_t Cardinal, typename ABI>
  struct storage_of<Type,Cardinal,ABI,native_status>
  {
    using parent = storage_of<Type,Cardinal,typename limits<ABI>::parent>;
    using base   = boost::simd::detail::as_simd<Type,ABI>;
    using type   = typename std::conditional< std::is_same< typename base::type
                                                          , nsm::no_such_type_
                                                          >::value
                                            , parent
                                            , base
                                            >::type::type;
  };

  // If we request more than needed, we aggregate exactly 2 smaller SIMD registers
  template< typename Type, std::size_t Cardinal, typename ABI>
  struct storage_of<Type,Cardinal,ABI,aggregated_status>
  {
    using base = pack<Type,Cardinal/2>;
    using type = std::array<base,2>;
  };
} } }

#if defined __GNUC__ && __GNUC__>=6
#pragma GCC diagnostic pop
#endif

#endif
