//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DETAILS_TYPEOF_HPP_INCLUDED
#define BOOST_DISPATCH_DETAILS_TYPEOF_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/preprocessor/cat.hpp>

/// INTERNAL ONLY
/// Boost.Config isn't up to date for MSVC10 so we force it to be
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1600) && defined(BOOST_NO_DECLTYPE)
#undef BOOST_NO_DECLTYPE
#endif

/// INTERNAL ONLY
/// decltype in GCC 4.4 is FUBAR
#if defined(__GNUC__) && __GNUC__ == 4 && __GNUC_MINOR__ == 4 && !defined(BOOST_NO_DECLTYPE)
#define BOOST_NO_DECLTYPE
#endif

#include <boost/typeof/typeof.hpp>

#if defined(BOOST_NO_DECLTYPE) && !defined(BOOST_TYPEOF_NATIVE)
#error compiler supports neither decltype nor typeof
#endif

#ifdef BOOST_NO_DECLTYPE
#include <cstddef>
namespace boost { namespace dispatch { namespace details
{
  template<class T>
  char match_const(T &);

  template<class T>
  char (&match_const(T const &))[2];

  template<std::size_t N, class T> struct match_const_impl { typedef T& type; };
  template<class T> struct match_const_impl<2u, T> { typedef T const& type; };
} } }
#endif

/// INTERNAL ONLY
#ifndef BOOST_NO_DECLTYPE
#  define BOOST_DISPATCH_TYPEOF_(EXPR, TYPE) typedef decltype(EXPR) TYPE;
#  define BOOST_DISPATCH_TYPEOF(EXPR) decltype(EXPR)
#  define BOOST_DISPATCH_DECLTYPE(EXPR) decltype((EXPR))
#else
#  define BOOST_DISPATCH_TYPEOF_(EXPR, TYPE)                                                       \
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_, TYPE), (EXPR))                           \
    typedef typename BOOST_PP_CAT(nested_, TYPE)::type TYPE;                                       \
   /**/
#  define BOOST_DISPATCH_TYPEOF(EXPR) BOOST_TYPEOF_TPL(EXPR)
#  define BOOST_DISPATCH_DECLTYPE(EXPR)                                                            \
    typename boost::dispatch::details::                                                            \
             match_const_impl< sizeof( boost::dispatch::details::match_const((EXPR)))              \
                             , BOOST_TYPEOF_TPL(EXPR)                                              \
                             >::type                                                               \
    /**/
#endif

#endif
