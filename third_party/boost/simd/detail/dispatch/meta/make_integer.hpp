//==================================================================================================
/*!
  @file

  Defines the make_integer meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_MAKE_INTEGER_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_MAKE_INTEGER_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <cstdint>
#include <cstddef>

namespace boost { namespace dispatch
{
  namespace detail
  {
    template< std::size_t Size, typename Sign, typename Transform>
    struct  make_integer
    {
      static_assert ( Size >= sizeof(std::int8_t) && Size <= sizeof(std::int64_t)
                    , "boost::dispatch::make_integer: can't generate type of given Size"
                    );

      using type = nsm::no_such_type_;
    };

    template<typename Transform>
    struct make_integer<1u, unsigned, Transform>
    {
      using type = nsm::apply<Transform,std::uint8_t>;
    };

    template<typename Transform>
    struct make_integer<2u, unsigned, Transform>
    {
      using type = nsm::apply<Transform,std::uint16_t>;
    };

    template<typename Transform>
    struct make_integer<4u, unsigned, Transform>
    {
      using type = nsm::apply<Transform,std::uint32_t>;
    };

    template<typename Transform>
    struct make_integer<8u, unsigned, Transform>
    {
      using type = nsm::apply<Transform,std::uint64_t>;
    };

    template<typename Transform>
    struct make_integer<1u, signed, Transform>
    {
      using type = nsm::apply<Transform,std::int8_t>;
    };

    template<typename Transform>
    struct make_integer<2u, signed, Transform>
    {
      using type = nsm::apply<Transform,std::int16_t>;
    };

    template<typename Transform>
    struct make_integer<4u, signed, Transform>
    {
      using type = nsm::apply<Transform,std::int32_t>;
    };

    template<typename Transform>
    struct make_integer<8u, signed, Transform>
    {
      using type = nsm::apply<Transform,std::int64_t>;
    };
  }

  /*!
    @ingroup group-generation
    @brief Generate an integer type of a given size and sign

    For any given Size corresponding to a valid integer type and an optional Sign,
    return said type optionally transformed by a user-defined unary meta-function.

    @tparam Size      Size in bytes of the requested type
    @tparam Sign      Optional sign (unsigned by default) of the requested type.
    @tparam Transform Optional unary meta-function to apply to the generated type
  **/
  template< std::size_t Size
          , typename Sign       = unsigned
          , typename Transform  = nsm::identity<nsm::_1>
          >
  struct make_integer : detail::make_integer<Size,Sign,Transform>
  {};

  template< std::size_t Size
          , typename Sign       = unsigned
          , typename Transform  = nsm::identity<nsm::_1>
          >
  using make_integer_t = typename make_integer<Size,Sign,Transform>::type;
} }

#endif
