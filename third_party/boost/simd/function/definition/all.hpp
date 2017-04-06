//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_ALL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_ALL_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/function/definition/logical_and.hpp>
#include <boost/simd/constant/definition/true.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG ( ext, all_
                            , (boost::dispatch::reduction_<all_, logical_and_, true_>)
                            );
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, all_)
  }

  BOOST_DISPATCH_CALLABLE_DEFINITION(tag::all_,all);
} }

#endif
