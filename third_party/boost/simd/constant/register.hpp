//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_REGISTER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_REGISTER_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the BOOST_SIMD_CONSTANT_REGISTER_VALUE macro
 */

#include <boost/simd/meta/int_c.hpp>
#include <boost/simd/meta/float.hpp>
#include <boost/simd/meta/double.hpp>

//==============================================================================
/*!
 * Generate a named constant from an integral, float and double value set
 * and a default type
 * \param TAG    ID of the constant to generate
 * \param TYPE   Default type of the constant
 * \param INT    Integral value of the constant
 * \param FLOAT  Float value of the constant
 * \param DOUBLE Double value of the constant
 */
//==============================================================================
#if defined(DOXYGEN_ONLY)
#define BOOST_SIMD_CONSTANT_REGISTER(TAG,TYPE,INT,FLOAT,DOUBLE) \
struct TAG  : boost::simd::ext::pure_constant_<TAG>             \
{                                                               \
  typedef boost::simd::ext::pure_constant_<TAG> parent;         \
  typedef TYPE default_type;                                    \
};                                                              \
/**/
#else
#define BOOST_SIMD_CONSTANT_REGISTER(TAG,TYPE,INT,FLOAT,DOUBLE)             \
struct TAG : boost::simd::ext::pure_constant_<TAG>                          \
{                                                                           \
  typedef boost::simd::ext::pure_constant_<TAG> parent;                     \
  typedef TYPE default_type;                                                \
  template<class T, class D=void> struct apply                              \
    : boost::simd::meta::int_c<typename T::type,typename T::type(INT)> {};  \
};                                                                          \
template<class T, class D>                                                  \
struct  TAG::apply<boost::dispatch::meta::single_<T>,D>                     \
      : boost::simd::meta::single_<FLOAT> {};                               \
template<class T, class D>                                                  \
struct  TAG::apply<boost::dispatch::meta::double_<T>,D>                     \
      : boost::simd::meta::double_<DOUBLE> {};                              \
/**/
#endif

#endif
