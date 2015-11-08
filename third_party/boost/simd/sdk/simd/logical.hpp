//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_LOGICAL_HPP_INCLUDED

#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/details/aliasing.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/proxy.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/assert.hpp>
#include <climits>
#include <ostream>
#include <ios>

namespace boost { namespace simd
{
  //============================================================================
  /*!
   * logical<T> is a thin wrapper used to optimize bool-to-type conversion and
   * provide a scalar equivalent of typed boolean SIMD types. logical<T> is also
   * set up to work as a vectorizable type, beign mapped to proper register type
   * for any given extension
   */
  //============================================================================
  template<typename T> struct BOOST_SIMD_MAY_ALIAS logical
  {
    typedef T                                             value_type;
    typedef typename dispatch::meta::as_integer<T>::type  bits;

    //==========================================================================
    /*!
     * Default logical constructor
     **/
    //==========================================================================
    BOOST_FORCEINLINE logical() : value_(0) {}

    //==========================================================================
    /*!
     * Constructs a logical from a boolean value
     *
     * \param v Boolean value to convert to logical
     **/
    //==========================================================================
    template<class U>
    BOOST_FORCEINLINE explicit logical(U v, typename boost::disable_if< boost::dispatch::meta::is_proxy<U> >::type* =0)
                                      : value_(v != 0)
    {
    }

    BOOST_FORCEINLINE logical& operator=(bool v)
    {
      value_ = v;
      return *this;
    }

    friend BOOST_FORCEINLINE
    bool operator ==(logical<T> const& a0, logical<T> const& a1) { return a0.value() == a1.value(); }

    friend BOOST_FORCEINLINE
    bool operator !=(logical<T> const& a0, logical<T> const& a1) { return a0.value() != a1.value(); }

    friend BOOST_FORCEINLINE logical<T> operator ~(logical<T> const& a0) { return logical<T>(~a0.value()); }
    friend BOOST_FORCEINLINE logical<T> operator !(logical<T> const& a0) { return logical<T>(!a0.value()); }

    //==========================================================================
    /*!
     * Convert a logical value to a real boolean
     *
     * \return Value of type \c bool containing the state of the logical
     **/
    //==========================================================================
    BOOST_FORCEINLINE operator bool() const { return value_; }
    BOOST_FORCEINLINE bool value() const {return value_; }

  private:
    bool  value_;
  };

  ////////////////////////////////////////////////////////////////////////////
  // Stream insertion for logical<T>
  ////////////////////////////////////////////////////////////////////////////
  template<class T>
  BOOST_FORCEINLINE
  std::ostream& operator<<(std::ostream& os, logical<T> const& v )
  {
    return os << std::boolalpha << bool(v) << std::noboolalpha;
  }
} }

//==============================================================================
// Register logical<T> to various dispatch system
//==============================================================================
namespace boost { namespace dispatch { namespace meta
{
  template<class T, class Origin>
  struct  hierarchy_of< simd::logical<T>, Origin>
  {
    typedef typename remove_const<Origin>::type stripped;
    typedef typename mpl::if_< is_same< simd::logical<T>, stripped >, stripped, Origin >::type origin_;
    typedef meta::scalar_< simd::ext::logical_<origin_> >  type;
  };

  template<class T, class Origin>
  struct property_of< simd::logical<T>, Origin>
  {
    typedef simd::ext::logical_<Origin> type;
  };

  template<class T>
  struct value_of< simd::logical<T> >
  {
    typedef T type;
  };

  template<class T>
  struct model_of< simd::logical<T> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef simd::logical<X> type;
      };
    };
  };

  template<class T>
  struct scalar_of< simd::logical<T> >
  {
    typedef simd::logical<T> type;
  };
} } }

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct real_of;

  template<class T>
  struct real_of< simd::logical<T> >
  {
    typedef simd::logical<T> type;
  };
} } }

#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/simd/details/logical.hpp>
#endif
