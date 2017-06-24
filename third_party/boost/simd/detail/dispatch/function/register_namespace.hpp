//==================================================================================================
/*!
  @file

  Provides the macro performing namespace registration

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_FUNCTION_REGISTER_NAMESPACE_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_FUNCTION_REGISTER_NAMESPACE_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/default_site.hpp>
#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/hierarchy/base.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/simd/detail/dispatch/detail/auto_decltype.hpp>
#include <boost/simd/detail/dispatch/detail/declval.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/config.hpp>
#include <utility>

namespace boost { namespace dispatch
{
  namespace meta { struct adl_helper {}; }

  /*!
    @ingroup group-function
    @brief Error reporting utility dispatcher.

    Whenever a dispatchable function ends up with no suitable overloads, this dispatcher will cause
    a compilation error by producing an incomplete type which type contains the function tag used,
    the architecture hierarchy and the list of types passed as parameters.

    @par Usage:

  **/
  template<typename Tag, typename Site> struct error_
  {
    /// Error inducing information carrier
    template<typename... Call> struct no_such_overload {};

    template<typename... Ts>
    BOOST_FORCEINLINE no_such_overload<Tag(Site,Ts...)>
    operator()(Ts&& ...) const BOOST_NOEXCEPT { return {}; }
  };

  namespace meta
  {
    // The 'no luck Sherlock' case returns an incomplete type to emit an informative message
    template<typename F, typename A, typename... Ts>
    BOOST_FORCEINLINE error_<F,A>
    dispatching ( adl_helper const&, function_<F> const&, unspecified_<A> const&
                , ::boost::dispatch::unknown_<Ts> const&...
                )  BOOST_NOEXCEPT
    {
      return {};
    }
  }

  namespace detail
  {
    template<typename Discriminant,typename Tag> struct generic_dispatcher
    {
      // ICC also have to deal with underlying g++ libraries on linux, which can be quite old
      // on CentOS (often used on HPC clusters). g++ implementation of result_of rely on the
      // presence of nested 'result<T> type' (at least on 4.4.x) and boost's functional is no
      // better. As a result we need to avoid using it.
      template<typename Sig> struct result;

      template<typename This, typename... Args>
      struct result<This(Args...)>
      {
        static auto invoke(Args&&... args)
          -> decltype( dispatching ( Discriminant{}, Tag{}, default_site<Tag>{},
                                     typename ::boost::dispatch::hierarchy_of<Args&&>::type ()...
                                     )(std::forward<Args>(args)...));
        using type = decltype(invoke(detail::declval<Args>()...));
      };

      template<typename... Args>
      BOOST_FORCEINLINE typename result<generic_dispatcher(Args&&...)>::type
      operator()(Args&&... args) const
      BOOST_NOEXCEPT_IF ( BOOST_NOEXCEPT_EXPR(
                          dispatching ( Discriminant{}, Tag{}, default_site<Tag>{}
                                      , ::boost::dispatch::hierarchy_of_t<Args&&>()...
                                      )( std::forward<Args>(args)... )
                        ) )
      {
        return dispatching( Discriminant{}, Tag{}, default_site<Tag>{}
                          , typename ::boost::dispatch::hierarchy_of<Args&&>::type()...
                          )
                          ( std::forward<Args>(args)... );
      }
    };
  }

  /// Root generic_dispatcher instance
  template<typename Tag>
  using generic_dispatcher = detail::generic_dispatcher<meta::adl_helper,Tag>;
} }

/*!
  @ingroup group-function

  Make the current namespace able to house dispatchable function overloads and to use a @c FALLBAKC
  namespace if the current one fails to provide any viable overload.

  @param FALLBACK   Namespace to use in fallback situations
**/
#define BOOST_DISPATCH_REGISTER_NAMESPACE(FALLBACK)                                                 \
struct adl_helper {};                                                                               \
                                                                                                    \
template<typename Tag, typename Site, typename... Ts>                                               \
BOOST_FORCEINLINE FALLBACK::generic_dispatcher<Tag>                                                 \
dispatching ( adl_helper const&, ::boost::dispatch::function_<Tag> const&                           \
            , ::boost::dispatch::unspecified_<Site> const&                                          \
            , ::boost::dispatch::unknown_<Ts> const&...                                             \
            ) BOOST_NOEXCEPT                                                                        \
{                                                                                                   \
  return {};                                                                                        \
}                                                                                                   \
template<typename Tag>                                                                              \
using generic_dispatcher = ::boost::dispatch::detail::generic_dispatcher<adl_helper,Tag>            \
/**/

#endif
