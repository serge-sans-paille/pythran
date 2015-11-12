//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_NATIVE_TUPLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_NATIVE_TUPLE_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/details/soa_proxy.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_as.hpp>
#include <boost/simd/sdk/tuple.hpp>
#include <boost/simd/preprocessor/new.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    // Build the sequence of proper native
    template<class T, class X>
    struct make_soa
    {
      template<class Sig>
      struct result;

      template<class This, class U>
      struct result<This(U)>
      {
        typedef typename meta::vector_of<U, meta::cardinal_as<T, X>::value>::type type;
      };
    };
  }

  template<class T, class X>
  struct  native< T, X
                , typename  boost
                          ::enable_if < boost::fusion::traits::is_sequence<T>
                                      >::type
                >
        : meta::as_tuple<T, details::make_soa<T,X> >::type
  {
    typedef typename meta::as_tuple<T, details::make_soa<T,X> >::type    parent;
    typedef T value_type;

    native() {}

    #define M0(z, n, t)                                                        \
    template<BOOST_PP_ENUM_PARAMS(n, class A)>                                 \
    native(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))                        \
      : parent(BOOST_PP_ENUM_PARAMS(n, a))                                     \
    {                                                                          \
    }                                                                          \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_META_ARITY, M0, ~)
    #undef M0

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    typedef std::size_t                                          size_type;
    typedef soa_proxy<value_type, X>                             reference;
    typedef value_type const                                     const_reference;
    typedef soa_iterator<value_type, X>                          iterator;
    typedef soa_const_iterator<value_type, X>                    const_iterator;

    BOOST_FORCEINLINE
    iterator       begin()       { return iterator(*this);               };

    BOOST_FORCEINLINE
    iterator       end()         { return iterator(*this, size());       };

    BOOST_FORCEINLINE
    const_iterator begin() const { return const_iterator(*this);         };

    BOOST_FORCEINLINE
    const_iterator end()   const { return const_iterator(*this, size()); };

    ////////////////////////////////////////////////////////////////////////////
    // new/delete operator to force alignment on heap of native values
    ////////////////////////////////////////////////////////////////////////////
    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE_SIMD()

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    enum v_size { static_size = meta::cardinal_as<T, X>::value };

    static BOOST_FORCEINLINE  std::size_t size() { return static_size; }
    static BOOST_FORCEINLINE        bool empty() { return false; }

    reference operator[](std::size_t i)
    {
      return reference(*this, i);
    }

    const_reference operator[](std::size_t i) const
    {
      return reference(const_cast<native&>(*this), i);
    }
  };

} }

#endif
