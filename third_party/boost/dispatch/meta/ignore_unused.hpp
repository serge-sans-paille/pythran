//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_IGNORE_UNUSED_HPP_INCLUDED
#define BOOST_DISPATCH_META_IGNORE_UNUSED_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>

/*!
  @file
  @brief Defines and implements the ignore_unused utility function
**/

namespace boost { namespace dispatch
{
  /*!
    @brief Silence 'unused parameters' warning

    In some SFINAE-based code, some functions parameters may be declared
    but not used in a given implementation. Calling this function on such
    parameters prevent compilers to generate spurious warnings.

    @param t Parameter to ignore.

    @par Example Usage:

    @code
    template<class T> void foo( T const& t )
    {
      boost::dispatch::ignore_unused(t);
    }
    @endcode

  **/
  template<class T>
  BOOST_FORCEINLINE void ignore_unused
  ( T const&
    #if defined(DOXYGEN_ONLY)
    t
    #endif
  ) {}
} }

#define BOOST_DISPATCH_IGNORE_GLOBAL(X)                                        \
namespace details                                                              \
{                                                                              \
    struct BOOST_PP_CAT(ignore_, X)                                            \
    {                                                                          \
        void ignore()                                                          \
        {                                                                      \
            boost::dispatch::ignore_unused(&X);                                \
        }                                                                      \
    };                                                                         \
}                                                                              \
/**/

#endif
