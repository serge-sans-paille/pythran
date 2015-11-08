//==============================================================================
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_MAKE_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_MAKE_HPP_INCLUDED

#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/simd/memory/aligned_array.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

#define BOOST_SIMD_PP_DETAILS_MAKE(z, Cardinal, Args)                          \
BOOST_FORCEINLINE                                                              \
result_type eval( BOOST_PP_ENUM_BINARY_PARAMS ( BOOST_PP_TUPLE_ELEM(2,0,Args)  \
                                              , const A,& a                    \
                                              )                                \
                , boost::mpl::size_t<Cardinal> const&                          \
                ) const                                                        \
{                                                                              \
  return make<result_type>(BOOST_PP_ENUM( Cardinal                             \
                                        , BOOST_PP_TUPLE_ELEM(2,1,Args)        \
                                        , Cardinal                             \
                                        )                                      \
                          );                                                   \
}                                                                              \
/**/


#define BOOST_SIMD_PP_GENERIC_MAKE_ARGS(z,n,t) a ## n(p ## n)
#define BOOST_SIMD_PP_GENERIC_MAKE_TYPES(z,n,t) const X ## n & a ##n;
#define BOOST_SIMD_PP_GENERIC_MAKE_TPL(z,n,t) typename X ## n

/*!
  @brief make-based implementation generator

  Some SIMD functions can't be defined otherwise than as the explicit
  building of a SIMD register using make<T>(...). This macro facilitate
  the generation of regular, cardinal based use of make in this case for
  every valid cardinal.

  @param Args     Number of actual parameters to the inner call
  @param Function Preprocessor macro generating one element of the make call
**/
#define BOOST_SIMD_PP_IMPLEMENT_WITH_MAKE(Args,Function)                       \
BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM( 2                                        \
                                    , BOOST_SIMD_PP_DETAILS_MAKE               \
                                    , (Args,Function)                          \
                                    )                                          \
                                                                               \
template<typename T                                                            \
        ,std::size_t N                                                         \
        ,BOOST_PP_ENUM(Args,BOOST_SIMD_PP_GENERIC_MAKE_TPL,~)>                 \
struct generic_make                                                            \
{                                                                              \
  generic_make(BOOST_PP_ENUM_BINARY_PARAMS(Args, const X,& p), T& t)           \
             : that(t)                                                         \
             , BOOST_PP_ENUM(Args,BOOST_SIMD_PP_GENERIC_MAKE_ARGS,~) {}        \
                                                                               \
  template<int I> BOOST_FORCEINLINE void operator()() const                    \
  {                                                                            \
    that[I] = Function(~,I,N);                                                 \
  }                                                                            \
                                                                               \
  T&  that;                                                                    \
  BOOST_PP_REPEAT(Args, BOOST_SIMD_PP_GENERIC_MAKE_TYPES, ~)                   \
  private:                                                                     \
  generic_make& operator=(generic_make const&);                                \
};                                                                             \
                                                                               \
template<std::size_t N>                                                        \
result_type eval( BOOST_PP_ENUM_BINARY_PARAMS ( Args                           \
                                              , const A,& a                    \
                                              )                                \
                , boost::mpl::size_t<N> const&                                 \
                ) const                                                        \
{                                                                              \
  typedef typename meta::scalar_of<result_type>::type         s_t;             \
  typedef aligned_array<s_t,N,BOOST_SIMD_CONFIG_ALIGNMENT> data_t;             \
                                                                               \
  data_t that;                                                                 \
                                                                               \
  meta::iterate<N>( generic_make< data_t                                       \
                                 , N                                           \
                                 , BOOST_PP_ENUM_PARAMS(Args,A)                \
                                 >(BOOST_PP_ENUM_PARAMS(Args,a),that) );       \
  return aligned_load<result_type>(&that[0]);                                  \
}                                                                              \
/**/

#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/include/functions/simd/aligned_load.hpp>

#endif
