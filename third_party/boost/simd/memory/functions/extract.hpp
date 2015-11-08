//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_EXTRACT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief Extract generic tag

      Represents the extract function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct extract_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_  parent;
    };
  }

  /*!
    @brief Random-access extraction of a value subcomponent

    Extract a sub-element of a given value @c v

    @par Semantic

    Depending on the type of its arguments, extract exhibits different semantics.
    For any value @c v of type @c Value and @c o of type @c Offset:

    @code
    auto x = extract(v,o);
    @endcode

    is equivalent to:

    - If @c Value is a scalar type:

      @code
      x = v;
      @endcode

    - If @c Value is a SIMD type:

      @code
      x = v[o];
      @endcode

    @param value   Value to extract
    @param offset  Position to extract from

    @return The extracted value
  **/
  template<typename Value,typename Offset>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::extract_(Value const&, Offset const&)>::type
  extract(Value const& value, Offset const& offset)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::extract_ ( Value const&
                                          , Offset const&
                                          )>::type          callee;
    return callee(value,offset);
  }

  template<std::size_t Offset,typename Value>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::call<tag::extract_(Value const&, boost::mpl::size_t<Offset> const&)>::type
  extract(Value const& value)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::extract_ ( Value const&
                                          , boost::mpl::size_t<Offset> const&
                                          )>::type          callee;
    boost::mpl::size_t<Offset> offset;
    return callee(value,offset);
  }
} }

#endif
