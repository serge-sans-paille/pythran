//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_NATIVE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_NATIVE_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/details/native/meta.hpp>
#include <boost/simd/sdk/simd/details/operators.hpp>
#include <boost/simd/sdk/simd/details/logical.hpp>
#include <boost/simd/sdk/simd/details/soa_proxy.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/preprocessor/new.hpp>
#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Platform independent native SIMD type

    native is a portable wrapper around compiler and instruction set specific
    SIMD register types. It is designed to behave exactly as such types except
    with a proper type information and a correct value semantic. native also
    exhibits a Random Access Range interface and is adapted as a Random Access
    Fusion sequence.

    @tparam Scalar    Base scalar type to store in a register
    @tparam Extension SIMD extension tag
  **/
  template< typename Scalar
          , typename Extension
#if !defined(DOXYGEN_ONLY)
          , typename Enable
#endif
          >
  struct BOOST_SIMD_MAY_ALIAS native
  {
    //==========================================================================
    // native specific static interface
    //==========================================================================
    /// @brief Current extension tag type
    typedef Extension                                       extension_type;

    /// @brief Native extension specific register type
    typedef typename meta::as_simd<Scalar, Extension>::type    native_type;

    BOOST_MPL_ASSERT_MSG(
      (!is_same<native_type, dispatch::meta::na_>::value),
      BOOST_SIMD_NATIVE_TYPE_UNSUPPORTED_ON_EXTENSION,
      (Scalar, Extension)
    );

    BOOST_MPL_ASSERT_MSG(
      (!is_const<Scalar>::value && !is_reference<Scalar>::value),
      BOOST_SIMD_NATIVE_TYPE_MUST_NOT_BE_REF_OR_QUALIFIED,
      (Scalar)
    );

    // @brief underlying arithmetic type (if logical)
    typedef native<typename meta::as_arithmetic<Scalar>::type, Extension> type;

    //==========================================================================
    // native<S,E> models RandomAccessRange and FusionRandomAccessSequence
    //==========================================================================
    typedef Scalar                                               value_type;
    typedef std::size_t                                          size_type;
    typedef soa_proxy<value_type, Extension>                     reference;
    typedef value_type const                                     const_reference;
    typedef soa_iterator<value_type, Extension>                  iterator;
    typedef soa_const_iterator<value_type, Extension>            const_iterator;
    typedef boost::fusion::boost_array_tag                       fusion_tag;

    /*!
      @brief Internal type rebinder

      Rebind a native type to another base scalar type.

      @par Semantic:

      For any type @c T, @c U and any extension tag @c X, the following code:

      @code
      typedef native<T,X>::rebind<U>::type r;
      @endcode

      is equivalent to

      @code
      typedef native<U,X> r;
      @endcode

      @tparam U new base scalar type
    **/
    template<class U> struct rebind
    {
      typedef native<U, extension_type> type;
    };

    /// @brief Number of element stored in a native type
    enum v_size { static_size = meta::cardinal_of< native<Scalar, Extension> >::value };

    /// @brief Default constructor
    BOOST_FORCEINLINE native() {}

    /// @brief Constructs a native from a extension specific register
    BOOST_FORCEINLINE native(native_type s) : data_(s) {}

#if defined(BOOST_MSVC) || defined(DOXYGEN_ONLY)
    /// @brief Copy constructs a native from another one
    BOOST_FORCEINLINE native(native const& other) : data_(other.data_) {}
#endif

    /// @brief Assignment between native instances
    BOOST_FORCEINLINE native& operator=(native const& s)
    {
      // This operator= generates better code than the default-generated one
      data_ = s.data_;
      return *this;
    }

    /// @brief Assign an extension specific register to a native
    BOOST_FORCEINLINE native& operator=(native_type s)
    {
      data_ = s;
      return *this;
    }

    //==========================================================================
    // Typecasting operators for compatibility with intrinsics
    //==========================================================================
    /// @brief Conversion operator from native to the underlying register type
    BOOST_FORCEINLINE operator native_type &      ()        { return data_; }

    /// @overload
    BOOST_FORCEINLINE operator native_type const& ()  const { return data_; }

    /// @brief Explicit conversion from native to the underlying register type
    BOOST_FORCEINLINE native_type const&  operator()()  const { return data_; }

    /// @overload
    BOOST_FORCEINLINE native_type&        operator()()        { return data_; }

    //==========================================================================
    // new/delete operator to force alignment on heap of native values
    //==========================================================================
    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE_SIMD()

    //==========================================================================
    // RandomAccessSequence interface
    //==========================================================================

    /*!
      @brief Return the size in element of current native instance

      @return An unsigned integral equal to native::static_size
    **/
    static BOOST_FORCEINLINE std::size_t  size()  { return static_size; }

    /*!
      @brief Checks if a given native contains 0 element

      @return A boolean equals to @c false
    **/
    static BOOST_FORCEINLINE bool         empty() { return false; }

    /// @brief Access to the beginning of the native register data in memory
    BOOST_FORCEINLINE
    iterator       begin()       { return iterator(*this);               };

    /// @brief Access to past the end of the native register data in memory
    BOOST_FORCEINLINE
    iterator       end()         { return iterator(*this, size());       };

    /// @overload
    BOOST_FORCEINLINE
    const_iterator begin() const { return const_iterator(*this);         };

    /// @overload
    BOOST_FORCEINLINE
    const_iterator end()   const { return const_iterator(*this, size()); };

    /// @brief Random access to a given native scalar element
    BOOST_FORCEINLINE reference operator[](std::size_t i)
    {
      return reference(*this, i);
    }

    /// @overload
    BOOST_FORCEINLINE const_reference operator[](std::size_t i) const
    {
      return reference(const_cast<native&>(*this), i);
    }

    Scalar*       data()       { return reinterpret_cast<Scalar*>(&data_);       }
    Scalar const* data() const { return reinterpret_cast<Scalar const*>(&data_); }

    //==========================================================================
    // Inner data
    //==========================================================================
#if defined(BOOST_SIMD_COMPILER_GCC) && BOOST_SIMD_GCC_VERSION == 40603
    // workaround for GCC bug #52407 affecting GCC 4.6.3
    /// INTERNAL ONLY
    union
    {
#endif
      /// INTERNAL ONLY
      native_type data_;
#if defined(BOOST_SIMD_COMPILER_GCC) && BOOST_SIMD_GCC_VERSION == 40603
    };
#endif
  };
} }

#endif
