//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DECORATOR_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DECORATOR_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/functor.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd
{
  // decorator function hierarchy - simple specialization point
  template<typename Decorator> struct decorator_ : boost::dispatch::unspecified_<Decorator>
  {
    using parent = boost::dispatch::unspecified_<Decorator>;
  };

  namespace detail
  {
    template<typename Tag, typename Site, typename Decorator>
    struct decorated_functor : private dispatch::functor<Tag,Site>
    {
      using parent = dispatch::functor<Tag,Site>;

      template<typename... Args> BOOST_FORCEINLINE
      auto operator()(Args&&... args) const
          -> decltype(std::declval<parent const>()(Decorator(), std::forward<Args>(args)...) )
      {
        return static_cast<parent const&>(*this)( Decorator(), std::forward<Args>(args)... );
      }
    };

    template<typename Flag>
    struct decorator
    {
      template<typename Function, typename Site>
      detail::decorated_functor<Function,Site,Flag>
      operator()(dispatch::functor<Function,Site> const&) const
      {
        return {};
      }
    };
  }
} }

#endif
