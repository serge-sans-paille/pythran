//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_DETAILS_RANDS_HPP_INCLUDED
#define NT2_CORE_UTILITY_DETAILS_RANDS_HPP_INCLUDED

#include <nt2/sdk/config/types.hpp>

#define NT2_DEF_RAND(NAME,TYPE)                                                \
void NAME(TYPE* data, std::size_t i0, std::size_t i1)                          \
/**/

#define NT2_DEF_RANDI(NAME,TYPE)                                               \
void NAME (TYPE* data , std::size_t i0, std::size_t i1                         \
                      , TYPE imin, TYPE imax                                   \
          )                                                                    \
/**/

#define NT2_ADD_RAND(STREAM,NAME,DIST,TYPE)                                    \
NT2_DEF_RAND(STREAM::NAME,TYPE)                                                \
{                                                                              \
  boost::random::DIST<TYPE> dist;                                              \
  for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);                   \
}                                                                              \
/**/

#define NT2_ADD_RANDI(STREAM,TYPE)                                             \
NT2_DEF_RANDI(STREAM::randi,TYPE)                                              \
{                                                                              \
  boost::random::uniform_int_distribution<TYPE> dist(imin,imax);               \
  for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);                   \
}                                                                              \
/**/

#define NT2_IMPLEMENT_RAND(STREAM)                                             \
void STREAM::seed(uint32_t s) { generator_.seed(s); }                          \
NT2_ADD_RAND(STREAM,randn,normal_distribution,double)                          \
NT2_ADD_RAND(STREAM,randn,normal_distribution,float)                           \
NT2_ADD_RAND(STREAM,rand,uniform_real_distribution,double)                     \
NT2_ADD_RAND(STREAM,rand,uniform_real_distribution,float)                      \
NT2_ADD_RANDI(STREAM,uint64_t)                                                 \
NT2_ADD_RANDI(STREAM,uint32_t)                                                 \
NT2_ADD_RANDI(STREAM,uint16_t)                                                 \
NT2_ADD_RANDI(STREAM,uint8_t)                                                  \
NT2_ADD_RANDI(STREAM,int64_t)                                                  \
NT2_ADD_RANDI(STREAM,int32_t)                                                  \
NT2_ADD_RANDI(STREAM,int16_t)                                                  \
NT2_ADD_RANDI(STREAM,int8_t)                                                   \
STREAM::~STREAM() {}                                                           \
/**/

#define NT2_DEFINE_RAND(STREAM)                                                \
virtual NT2_DEF_RAND(randn,double);                                            \
virtual NT2_DEF_RAND(randn,float);                                             \
virtual NT2_DEF_RAND(rand ,double);                                            \
virtual NT2_DEF_RAND(rand ,float);                                             \
virtual NT2_DEF_RANDI(randi,uint64_t);                                         \
virtual NT2_DEF_RANDI(randi,uint32_t);                                         \
virtual NT2_DEF_RANDI(randi,uint16_t);                                         \
virtual NT2_DEF_RANDI(randi,uint8_t);                                          \
virtual NT2_DEF_RANDI(randi,int64_t);                                          \
virtual NT2_DEF_RANDI(randi,int32_t);                                          \
virtual NT2_DEF_RANDI(randi,int16_t);                                          \
virtual NT2_DEF_RANDI(randi,int8_t);                                           \
virtual void seed(uint32_t s);                                                 \
virtual ~STREAM()                                                              \
/**/

#define NT2_DEFINE_RANDSTREAM(STREAM)                                          \
virtual NT2_DEF_RAND(randn,double) = 0;                                        \
virtual NT2_DEF_RAND(randn,float) = 0;                                         \
virtual NT2_DEF_RAND(rand ,double) = 0;                                        \
virtual NT2_DEF_RAND(rand ,float) = 0;                                         \
virtual NT2_DEF_RANDI(randi,uint64_t) = 0;                                     \
virtual NT2_DEF_RANDI(randi,uint32_t) = 0;                                     \
virtual NT2_DEF_RANDI(randi,uint16_t) = 0;                                     \
virtual NT2_DEF_RANDI(randi,uint8_t) = 0;                                      \
virtual NT2_DEF_RANDI(randi,int64_t) = 0;                                      \
virtual NT2_DEF_RANDI(randi,int32_t) = 0;                                      \
virtual NT2_DEF_RANDI(randi,int16_t) = 0;                                      \
virtual NT2_DEF_RANDI(randi,int8_t) = 0;                                       \
virtual void seed(uint32_t s) = 0;                                             \
virtual ~STREAM()                                                              \
/**/

#endif
