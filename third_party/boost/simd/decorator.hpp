//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DECORATOR_HPP_INCLUDED
#define BOOST_SIMD_DECORATOR_HPP_INCLUDED

namespace boost { namespace simd
{
#if defined(DOXYGEN_ONLY)
  /*!
    @ingroup group-functions
    @defgroup group-decorator  Decorators


    @par Rationale
       Up to now we have seven different decorators that can be used to
       modify the behaviour of some functors.

       These are accurate_, conformant_, fast_,  raw_, restricted_,  saturated_, std_

       if a decorator `foo_` has to be called to modify the functor `bar` the call

         @code
          z = bar( < bar parameters > );
         @endcode

         has to be replaced by

         @code
          z = foo_(bar)(< bar parameters >);
         @endcode
  **/
#endif

} }

#include <boost/simd/function/conformant.hpp>
#include <boost/simd/function/fast.hpp>
#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/restricted.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/function/std.hpp>

#endif
