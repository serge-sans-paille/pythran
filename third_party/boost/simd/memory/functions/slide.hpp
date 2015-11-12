//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SLIDE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief slide generic tag

      Represents the slide function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct slide_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Shifted truncation of two vectors

    Compute a vector made of the first elements of the vector obtained by
    shifting the concatenation of @c a0 and @c a1 by @c N elements on the left
    or on the right depending on the sign of @c N.

    @par Semantic:

    @tparam N
    @param  a0
    @param  a1
  **/
  template<int N, typename A0, typename A1>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::slide_( A0 const&, A1 const&
                                  , mpl::int_<N> const&
                                  )>::type
  slide(A0 const& a0, A1 const& a1)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::slide_ ( A0 const&, A1 const&
                                        , mpl::int_<N> const&
                                        )>::type          callee;

    return callee(a0, a1, mpl::int_<N>());
  }

  /*!
    @brief Global vector shifting

    Compute a vector made of the first elements of the vector obtained by
    shifting left the concatenation of @c a0 by @c N elements on the left or
    on the right depending on the sign of @c N.

    @tparam N
    @param  a0
  **/
  template<int N, typename A0>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::slide_(A0 const&, mpl::int_<N> const&)>::type
  slide(A0 const& a0)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::slide_ ( A0 const&
                                        , mpl::int_<N> const&
                                        )>::type          callee;

    return callee(a0, mpl::int_<N>());
  }
} }

#endif
