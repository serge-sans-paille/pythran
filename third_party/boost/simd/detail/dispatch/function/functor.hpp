//==================================================================================================
/*
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_FUNCTION_FUNCTOR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_FUNCTION_FUNCTOR_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/default_site.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/dispatch/detail/declval.hpp>
#include <boost/config.hpp>
#include <utility>

#if defined(BOOST_INTEL_CXX_VERSION) && BOOST_INTEL_CXX_VERSION < 1600
// Bad variadic template support, use an ad hoc hack.
#include <boost/simd/detail/dispatch/detail/functor_icpc15_kludge.hpp>
#else

#define BOOST_DISPATCH_IMPL_TAG_CALL_TYPE(TAG,SITE,TS,AS)               \
TAG::dispatch_to( boost::dispatch::detail::declval<SITE>()                                          \
                , boost::dispatch::detail::declval<typename boost::dispatch::hierarchy_of<TS>::type>()...)( std::forward<TS>(AS)...) \
/**/

#define BOOST_DISPATCH_IMPL_TAG_CALL(TAG,SITE,TS,AS)                                                \
TAG::dispatch_to(SITE(),typename boost::dispatch::hierarchy_of<TS>::type()...)( std::forward<TS>(AS)...)         \
/**/

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-function
    @brief Adaptable dispatch-enabled function object

    @tparam Tag
    @tparam Site
  **/
  template<typename Tag, typename Site = boost::dispatch::default_site<Tag>>
  struct functor
  {
    /*!

    **/
    template<typename Other, typename... Args> BOOST_FORCEINLINE
    auto on(Args&&... args) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Other,Args,args)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Other,Args,args))
    {
      return BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Other,Args,args);
    }

    /*!
      @brief Architectural target rebinding

      Creates an instance of functor which shares current functor's tag but
      dispatched over a specific architecture hierarchy.

      @return a instance of functor dispatching specifically on architecture Other

      @tparam Other New architecture target to generate a functor for
    **/
    template<typename Other>
    static BOOST_FORCEINLINE functor<Tag,Other> rebind() BOOST_NOEXCEPT { return {}; }

    /*!

    **/
    template<typename... Args> BOOST_FORCEINLINE
    auto operator()(Args&&... args) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Site,Args,args)))
        -> decltype (BOOST_DISPATCH_IMPL_TAG_CALL_TYPE(Tag,Site,Args,args))
    {
      return BOOST_DISPATCH_IMPL_TAG_CALL(Tag,Site,Args,args);
    }
  };
  }
}
#endif 

namespace boost {namespace dispatch {
  namespace ext {
    template<typename F, typename S, typename Origin>
    struct hierarchy_of<boost::dispatch::functor<F,S>,Origin>
    {
      using type = F;
    };
  }
} }

#endif
