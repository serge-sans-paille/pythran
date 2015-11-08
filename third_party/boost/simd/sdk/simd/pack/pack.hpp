//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_PACK_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_PACK_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/pack/expression.hpp>

#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/simd/sdk/simd/pack/meta.hpp>
#include <boost/simd/sdk/simd/pack/fusion_iterator.hpp>
#include <boost/simd/sdk/simd/pack/fusion.hpp>

#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/simd/details/operators.hpp>
#include <boost/simd/sdk/simd/pack/call.hpp>

#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/include/functions/simd/aligned_load.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/make.hpp>

#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/meta/is_power_of_2.hpp>
#include <boost/simd/memory/is_aligned.hpp>

#include <boost/dispatch/meta/is_iterator.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/pointee.hpp>

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // pack, implemented in terms of simd::expr via non-inheritance to preserve
  // PODness of pack throughout the whole system.
  ////////////////////////////////////////////////////////////////////////////
  template<class Type, std::size_t Cardinal>
  struct BOOST_SIMD_MAY_ALIAS pack
    : expression< boost::proto::basic_expr< boost::proto::tag::terminal
                                          , boost::proto::term< typename
                                                                meta::vector_of< Type
                                                                               , Cardinal
                                                                               >::type
                                                              >
                                          , 0l
                                          >
                 , typename
                   meta::vector_of< Type
                                  , Cardinal
                                  >::type
                 >
  {
    static const std::size_t static_size = Cardinal;

    typedef typename meta::vector_of<Type, Cardinal>::type  data_type;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<data_type>, 0l > expr_type;

    typedef Type                                value_type;
    typedef typename data_type::reference       reference;
    typedef typename data_type::const_reference const_reference;
    typedef typename data_type::iterator        iterator;
    typedef typename data_type::const_iterator  const_iterator;

    typedef expression< expr_type, data_type > parent;

    //==========================================================================
    /*
     * SIMD pack instanciated with non-power of 2 Cardinal or a Cardinal of 1.
     */
    //==========================================================================
    BOOST_MPL_ASSERT_MSG
    ( (meta::is_power_of_2_c<Cardinal>::value && Cardinal > 1)
    , INVALID_SIMD_PACK_CARDINAL
    , (boost::mpl::int_<Cardinal>)
    );

    BOOST_FORCEINLINE pack() {}

    BOOST_FORCEINLINE pack(data_type const& p)
    {
      proto::value(*this) = p;
    }

#if defined(BOOST_MSVC) || defined(DOXYGEN_ONLY)
    BOOST_FORCEINLINE pack(pack const& other)
    {
      proto::value(*this) = proto::value(other);
    }
#endif

    template<class ScalarIterator>
    BOOST_FORCEINLINE pack( ScalarIterator i
        , typename enable_if< dispatch::meta::is_iterator<ScalarIterator> >::type* = 0)
    {
      typedef typename boost::pointee<ScalarIterator>::type v_type;
      BOOST_STATIC_ASSERT_MSG
      ( (boost::is_same<Type,v_type>::value)
      , "The constructor of pack<T,C> has been called on a iterator"
        "which value_type is different from T."
      );

      value_type* p = &(*i);

      BOOST_ASSERT_MSG
      ( boost::simd::is_aligned(p,sizeof(data_type))
      , "The constructor of pack<T,C> has been called on a iterator"
        "which alignment is not compatible with current SIMD extension."
      );

      proto::value(*this) = aligned_load<data_type >(p,0);
    }

    //==========================================================================
    // Constructor from scalar range
    //==========================================================================
    template<class ScalarIterator>
    BOOST_FORCEINLINE pack( ScalarIterator b, ScalarIterator e
        , typename enable_if< dispatch::meta::is_iterator<ScalarIterator> >::type* = 0)
    {
      BOOST_ASSERT_MSG
      ( ((e-b)==Cardinal)
      , "The constructor of pack<T,C> has been called on a iterator"
        "which alignment is not compatible with current SIMD extension."
      );

      for(int i=0;b!=e;++b,++i)
        (*this)[i] = *b;
    }

    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(Cardinal*sizeof(value_type))

    //==========================================================================
    // Constructor from unique scalar value -> splat the value
    //==========================================================================
    template<class T>
    BOOST_FORCEINLINE pack(T const& t, typename enable_if< is_arithmetic<T> >::type* = 0)
    {
      proto::value(*this) = simd::splat<data_type>(t);
    }

    //==========================================================================
    // Create constructors for pack according to the extension specification.
    //==========================================================================
    #define M1(z, n, arg)                                                      \
    template<class T>                                                          \
    BOOST_FORCEINLINE pack( BOOST_PP_ENUM_PARAMS(n, T const& a)                \
        , typename enable_if< is_arithmetic<T> >::type* = 0)                   \
    {                                                                          \
      proto::value(*this) = simd::make<data_type>(BOOST_PP_ENUM_PARAMS(n,a));  \
    }                                                                          \
    /**/

    BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM(2, M1, ~)
    #undef M1

    //==========================================================================
    // Constructor from expression -> evaluate using parent operator=
    //==========================================================================
    template<class T>
    BOOST_FORCEINLINE pack(T const& t, typename T::proto_is_expr_* = 0)
    {
      static_cast<parent&>(*this) = t;
    }

    //==========================================================================
    // operator= for pack
    //==========================================================================
    BOOST_FORCEINLINE pack& operator=(pack const& src)
    {
      boost::proto::value(*this) = boost::proto::value(src);
      return *this;
    }

    template<class Xpr>
    BOOST_FORCEINLINE
    typename boost::disable_if<boost::is_base_of<parent,Xpr>, pack&>::type
    operator=(Xpr const& xpr)
    {
      parent::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE
    reference operator[](std::size_t i)
    {
      return boost::proto::value(*this)[i];
    }

    BOOST_FORCEINLINE
    const_reference  operator[](std::size_t i) const
    {
      return boost::proto::value(*this)[i];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    BOOST_FORCEINLINE
    iterator       begin()       { return boost::proto::value(*this).begin(); }
    BOOST_FORCEINLINE
    const_iterator begin() const { return boost::proto::value(*this).begin(); }
    BOOST_FORCEINLINE
    iterator       end()         { return boost::proto::value(*this).end();   }
    BOOST_FORCEINLINE
    const_iterator end()   const { return boost::proto::value(*this).end();   }

    ////////////////////////////////////////////////////////////////////////////
    // Array like interface
    ////////////////////////////////////////////////////////////////////////////
    static BOOST_FORCEINLINE
    std::size_t size() { return data_type::size(); }

    static BOOST_FORCEINLINE
    bool empty() { return false; }

    ////////////////////////////////////////////////////////////////////////////
    // Fusion RandomAccessSequence interface
    ////////////////////////////////////////////////////////////////////////////
    typedef tag::pack_ fusion_tag;
  };
} }

#endif
