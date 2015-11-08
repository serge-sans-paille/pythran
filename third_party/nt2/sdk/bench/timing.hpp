//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_TIMING_HPP_INCLUDED
#define NT2_SDK_BENCH_TIMING_HPP_INCLUDED

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/protocol/until.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/details/process_functor.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/stats/median.hpp>
#include <nt2/sdk/meta/type_id.hpp>

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/cat.hpp>

/// INTERNAL ONLY
#define NT2_TIMING_TYPES(r,d,i,e)                                              \
BOOST_PP_COMMA_IF(i) BOOST_DISPATCH_PP_STRIP(BOOST_PP_TUPLE_ELEM(3,0,e))       \
/**/

/// INTERNAL ONLY
#define NT2_TIMING_RANGE_ELEM(r,d,i,e)                                         \
BOOST_PP_COMMA_IF(i) nt2::bench                                                \
                        ::fixed ( std::make_pair( BOOST_PP_TUPLE_ELEM(3,1,e)   \
                                                , BOOST_PP_TUPLE_ELEM(3,2,e)   \
                                                )                              \
                                )                                              \
/**/

/// INTERNAL ONLY
/// We generate a string externally so we're sure its .c_str() is valid all along
#define NT2_TIMING_IMPL(NAME, FUNC, CODE, RANGE )                              \
std::string const BOOST_PP_CAT(str_,NAME)                                      \
                    = nt2::type_id<FUNC                                        \
                            (BOOST_PP_SEQ_FOR_EACH_I(NT2_TIMING_TYPES,~,RANGE))\
                                  >();                                         \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,NAME)();                                     \
nt2::details::bench const                                                      \
BOOST_PP_CAT(NAME,NT2_UNIT_PREFIX)                                             \
                        ( &nt2::details::benchmarks                            \
                        , BOOST_PP_CAT(NT2_UNIT_PREFIX,NAME)                   \
                        , BOOST_PP_CAT(str_,NAME).c_str()                      \
                        );                                                     \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,NAME)()                                      \
{                                                                              \
  nt2::bench::run_until_with                                                   \
    <                                                                          \
      nt2::details::process_functor                                            \
      < CODE                                                                   \
      , BOOST_PP_SEQ_SIZE(RANGE)                                               \
      , BOOST_PP_SEQ_FOR_EACH_I(NT2_TIMING_TYPES,~,RANGE)                      \
      >                                                                        \
    >                                                                          \
    ( nt2::bench::args("duration",1.)                                          \
    , nt2::bench::args("iteration",1000000U)                                   \
    , nt2::bench::and_                                                         \
      ( nt2::bench::fixed(nt2::bench::args("samples",1024u))                   \
      , BOOST_PP_SEQ_FOR_EACH_I(NT2_TIMING_RANGE_ELEM,~,RANGE)                 \
      )                                                                        \
    , nt2::bench::cycles_per_element<nt2::bench::stats::median_>()             \
    );                                                                         \
}                                                                              \
/**/

/*!

**/
#define NT2_TIMING(FUNC, RANGE )                                               \
NT2_TIMING_IMPL ( BOOST_PP_CAT(timing_,__LINE__), FUNC                         \
                , boost::dispatch::functor<FUNC>, RANGE                        \
                )                                                              \
/**/

/*!

**/
#define NT2_TIMING_EXT(FUNC, RANGE )                                           \
NT2_TIMING_IMPL ( BOOST_PP_CAT(timing_,__LINE__), FUNC, FUNC, RANGE )          \
/**/

#endif
