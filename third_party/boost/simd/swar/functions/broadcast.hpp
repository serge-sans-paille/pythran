//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_BROADCAST_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief broadcast generic tag

      Represents the broadcast function in generic contexts.

      @par Models:

      Hierarchy
    **/
    struct broadcast_ : ext::unspecified_<broadcast_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<broadcast_> parent;
    };
  }

  /*!
    @brief Vector element broadcast

    Splat the Nth element of a SIMD register into a new register

    @par Semantic:

    For every parameter of type Type and any integer @c N

    @code
    Type r = broadcast<N>(value);
    @endcode

    is similar to:

    @code
    for(int i=0;i<Type::static_size;++i)
      r[i] = value[N];
    @endcode

    @param value SIMD register containing the value to broadcast
    @tparam N index of the value to broadcast everywhere

    @return A SIMD register full of <tt>value[N]</tt>
  **/
  template<std::size_t N, typename Type>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            result_of < typename boost::dispatch::meta::
                        dispatch_call < tag::broadcast_
                                      ( Type const&
                                      , boost::mpl::int_<N> const&
                                      )
                                      >::type
                        ( Type const&
                        , boost::mpl::int_<N> const&
                        )
                      >::type
  broadcast(Type const& value)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::broadcast_
                                  ( Type const&
                                  , boost::mpl::int_<N> const&
                                  )>::type          callee;

    BOOST_MPL_ASSERT_MSG( (N < meta::cardinal_of<Type>::value)
                        , BOOST_SIMD_INVALID_BROADCAST_INDEX
                        , ( typename meta::cardinal_of<Type>::type
                          , boost::mpl::int_<N>
                          )
                        );

    return callee(value,boost::mpl::int_<N>());
  }

} }

#endif
