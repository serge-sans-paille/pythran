//==================================================================================================
/*!
  @file

  Defines the make_floating meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_MAKE_FLOATING_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_MAKE_FLOATING_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <cstddef>

namespace boost { namespace dispatch
{
  namespace detail
  {
    template< std::size_t Size, typename Transform>
    struct  make_floating
    {
      static_assert ( Size <= sizeof(double)
                    , "boost::dispatch::make_floating: can't generate type of given Size"
                    );
      using type = nsm::apply<Transform,float>;
    };

    template<typename Transform>
    struct make_floating<sizeof(double),Transform>
    {
      using type = nsm::apply<Transform,double>;
    };
  }

  /*!
    @ingroup group-generation
    @brief Generate a floating point type of a given size

    For any given Size corresponding to a valid floating point type, return said type optionally
    transformed by an user-defined unary meta-function.

    @tparam Size      Size in bytes of the requested type
    @tparam Transform Optional unary meta-function to apply to the generated type
  **/
  template<std::size_t Size, typename Transform = nsm::identity<nsm::_1>>
  struct make_floating : detail::make_floating<Size,Transform>
  {};

  template<std::size_t Size, typename Transform = nsm::identity<nsm::_1>>
  using make_floating_t = typename make_floating<Size,Transform>::type;
} }

#endif
