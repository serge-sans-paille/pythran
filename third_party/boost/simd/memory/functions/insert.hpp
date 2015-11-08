//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_INSERT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_INSERT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief insert generic tag

      Represents the insert function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct insert_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Generic value insertion for SIMD types

    Modify the value of the nth element of a mutable data.

    @par Semantic

    Depending on the type of its arguments, insert exhibits different semantics.
    For any value @c v of type @c Value, @c d of type @c Data and @c o of
    type @c Offset:

    @code
    insert(v,d,o);
    @endcode

    is equivalent to:

    - If @c Type is a scalar type:

      @code
      d = v;
      @endcode

    - If @c Type is a SIMD type:

      @code
      d[o] = v;
      @endcode

    @param value   Value to insert
    @param data    Data to insert into
    @param offset  Position where to insert

    @return The modified data
  **/
  template<typename Value, typename Data, typename Offset>
  BOOST_FORCEINLINE
  void insert(Value const& value, Data& data, Offset const& offset)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::insert_( Value const&
                                        , Data&
                                        , Offset const&
                                        )>::type          callee;
    callee(value,data,offset);
  }

  template<std::size_t Offset, typename Value, typename Data>
  BOOST_FORCEINLINE
  void insert(Value const& value, Data& data)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::insert_( Value const&
                                        , Data&
                                        , boost::mpl::size_t<Offset> const&
                                        )>::type          callee;
    boost::mpl::size_t<Offset> offset;
    callee(value,data,offset);
  }
} }

#endif
