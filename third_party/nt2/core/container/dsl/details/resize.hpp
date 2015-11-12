//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_RESIZE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_RESIZE_HPP_INCLUDED

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/core/functions/scalar/numel.hpp>
#include <nt2/core/settings/storage_size.hpp>
#include <nt2/core/settings/storage_duration.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/size.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // resize expression internal extension points
  // Specify how expression are meant to be resized
  //============================================================================
  template<class Tag, class Domain, int N, class Expr> struct resize
  {
    //==========================================================================
    //               ****NT2_INVALID_RESIZE_OF_RHS_EXPRESSION****
    // If this static assert triggers, a call to resize has been issued on a
    // RHS expression. Check for your code conformity at the expression level.
    //               ****NT2_INVALID_RESIZE_OF_RHS_EXPRESSION****
    //==========================================================================
    BOOST_MPL_ASSERT_MSG(0, NT2_INVALID_RESIZE_OF_RHS_EXPRESSION, (Tag));
  };

  //============================================================================
  // resize nullary expression - only make sense for container
  //============================================================================
  template<class Tag, class Domain, class Expr>
  struct resize<Tag, Domain, 0, Expr>
  {
    template<class Sz> BOOST_FORCEINLINE void operator()(Expr& x, Sz const& sz)
    {
      typedef typename meta::call<Tag(Expr&)>::type value;
      typedef typename meta::is_container_or_ref<value>::type status_t;
      return (*this)(x, sz, status_t());
    }

    template<class Sz>
    BOOST_FORCEINLINE void operator()(Expr& x, Sz const& sz, boost::mpl::true_)
    {
      #ifndef NDEBUG
      // Assert that we don't resize out of storage_size if
      // storage duration is not dynamic_
      typedef typename meta::option<Expr, tag::storage_size_>::type     ss_t;
      typedef typename meta::option<Expr, tag::storage_duration_>::type sd_t;
      typedef boost::is_same< typename sd_t::storage_duration_type
                            , nt2::dynamic_
                            >                                   is_dynamic_t;
      #endif

      BOOST_ASSERT_MSG
      (  is_dynamic_t::value || nt2::numel(sz) <= ss_t::storage_size_type::value
      , "Resizing over available storage size"
      );

      boost::proto::value(x).resize(sz);
    }

    template<class Sz>
    BOOST_FORCEINLINE void operator()(Expr&, Sz const& sz, boost::mpl::false_)
    {
      boost::dispatch::ignore_unused(sz);
      BOOST_ASSERT_MSG( sz == of_size_<>()
                      , "Resizing scalar to size other than 1"
                      );
    }
  };
} }

#endif
