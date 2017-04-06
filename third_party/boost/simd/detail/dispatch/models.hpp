//==================================================================================================
/*!
  @file

  Defines the models meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_MODELS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_MODELS_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace detail
  {
    namespace tt = nsm::type_traits;

    template<typename T, typename Hierarchy> struct models
    {
      template<typename U> using hierarchy_t  = nsm::apply<Hierarchy,U>;

      template<typename U> static tt::true_type  test( hierarchy_t<U> );
      template<typename  > static tt::false_type test( ... );

      using type = typename std::is_same< decltype(test<T>(boost::dispatch::hierarchy_of_t<T>{}))
                                        , tt::true_type
                                        >::type;
    };
  }

  /*!
    @ingroup group-hierarchy
    @brief Checks if a Type models a Hierarchy

    A type @c T models a @c Hierarchy if and only if @c Hierarchy<T> is present in
    @c T hierarchy inheritance tree.

    @par Models:

    @metafunction

    @tparam T         Type to check for
    @tparam Hierarchy Hierarchy @c T must model
  **/
  template<typename T, typename Hierarchy>
  struct  models
#if !defined(DOXYGEN_ONLY)
        : detail::models<T,Hierarchy>
#endif
  {};

  /*!
    @ingroup group-hierarchy
    Eager short-cut to boost::dispatch::models
  **/
  template<typename T, typename Hierarchy>
  using models_t = typename models<T,Hierarchy>::type;
} }

#endif
