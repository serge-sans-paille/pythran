//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_COVER_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_COVER_HPP_INCLUDED

#include <nt2/sdk/unit/io.hpp>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/eval.hpp>
#include <nt2/sdk/unit/details/ulp.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/details/io_fix.hpp>
#include <boost/simd/operator/specific/utils.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

/// INTERNAL ONLY Grab an input type
#define NT2_COVER_TYPE(z,n,t) BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_SEQ_ELEM(n,t))  \
/**/

/// INTERNAL ONLY Grab an input type
#define NT2_COVER_VAR(z,n,t) BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_SEQ_ELEM(n,t))   \
/**/

#define NT2_COVER_INPUT_TYPES(z,n,t)                                           \
typedef typename boost::mpl::at_c<Types,n>::type type_##n;                     \
/**/

#define NT2_COVER_LOADS(z,n,t)                                                 \
nt2::load<type_##n>(&i##n[t])                                                  \
/**/

/// INTERNAL ONLY Display an input
#define NT2_COVER_DISP(z,n,t)                                                  \
<< ", " << boost::simd::details::display(NT2_COVER_LOADS(z,n,t))               \
/**/

#define NT2_COVER_TYPES_LIST(INPUTS)                                           \
boost::mpl::vector<BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(INPUTS)                    \
                                , NT2_COVER_TYPE                               \
                                , INPUTS                                       \
                                )>                                             \
/**/

#define NT2_COVER_VALUES_LIST(INPUTS)                                          \
BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(INPUTS), NT2_COVER_VAR, INPUTS )              \
/**/

#define NT2_COVER_STRING(r,d,e)                                                \
+ std::string(", ") + nt2::type_id<BOOST_PP_TUPLE_ELEM(2,0,e)>()               \
/**/

#define NT2_COVER_TEST_NAME(FUNC,INPUTS)                                       \
  nt2::type_id(FUNC)                                                           \
+ std::string("( ")                                                            \
+ nt2::type_id<BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_SEQ_HEAD(INPUTS))>()           \
  BOOST_PP_SEQ_FOR_EACH(NT2_COVER_STRING,~,BOOST_PP_SEQ_TAIL(INPUTS))          \
+ std::string(" )")                                                            \
/**/

#define NT2_COVER_CARD(z,n,t)                                                  \
meta::cardinal_of<BOOST_PP_CAT(type_,n)>::value                                \
/**/

#define NT2_COVER_CARDT(z,n,t)                                                 \
meta::cardinal_of<typename boost::mpl::at_c<Types,n>::type>::value             \
/**/

namespace nt2 { namespace details
{
  #define NT2_COVER_COMPUTE(z,n,t)                                             \
  template< typename Function, typename Data, typename Types                   \
          , BOOST_PP_ENUM_PARAMS(n,typename I)                                 \
          >                                                                    \
  inline                                                                       \
  Data compute_coverage ( Function f, Data const& ref, Types const&            \
                        , BOOST_PP_ENUM_BINARY_PARAMS(n,I, const& i)           \
                        )                                                      \
  {                                                                            \
    Data out(ref.size());                                                      \
                                                                               \
    BOOST_PP_REPEAT(n,NT2_COVER_INPUT_TYPES,~)                                 \
                                                                               \
    static  const std::size_t                                                  \
            cc = BOOST_DISPATCH_FOLD( n                                        \
                                    , boost::simd::ext::cardinal_common<       \
                                    , >::value                                 \
                                    , NT2_COVER_CARD, ~                        \
                                    );                                         \
                                                                               \
    for(std::size_t i=0; i<out.size(); i+=cc)                                  \
    {                                                                          \
      nt2::store( f(BOOST_PP_ENUM(n,NT2_COVER_LOADS,i)), &out[i]);             \
    }                                                                          \
                                                                               \
    return out;                                                                \
  }                                                                            \
  /**/

  BOOST_PP_REPEAT_FROM_TO ( 1
                          , BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY)
                          , NT2_COVER_COMPUTE
                          , ~
                          )

  #define NT2_COVER_FAILURES(z,n,t)                                            \
  template< typename Function, typename Data, typename ULPs                    \
          , typename Types                                                     \
          , BOOST_PP_ENUM_PARAMS(n,typename I)                                 \
          >                                                                    \
  inline                                                                       \
  void display_cover_fails( const char* , Function f                           \
                          , Data const& out, Data const& ref                   \
                          , ULPs const& ulps, Types const&                     \
                          , BOOST_PP_ENUM_BINARY_PARAMS(n,I, const& i)         \
                          )                                                    \
  {                                                                            \
    int ib = -1;                                                               \
    static  const std::size_t                                                  \
            cc = BOOST_DISPATCH_FOLD( n                                        \
                                    , boost::simd::ext::cardinal_common<       \
                                    , >::value                                 \
                                    , NT2_COVER_CARDT, ~                       \
                                    );                                         \
                                                                               \
    BOOST_PP_REPEAT(n,NT2_COVER_INPUT_TYPES,~)                                 \
                                                                               \
    boost::dispatch::ignore_unused(f);                                         \
    typedef BOOST_TYPEOF_TPL(f( BOOST_PP_ENUM(n,NT2_COVER_LOADS,0) )) r_t;     \
                                                                               \
    BOOST_FOREACH ( typename ULPs::const_reference ff, ulps )                  \
    {                                                                          \
      int ii = static_cast<int>((ff.index/cc)*cc);                             \
      if(ii > ib)                                                              \
      {                                                                        \
                                                                               \
        std::cout << std::setprecision(20)                                     \
                  << "    ("                                                   \
                  << boost::simd::details::display(NT2_COVER_LOADS(~,0,ii))    \
                  BOOST_PP_REPEAT_FROM_TO( 1, n, NT2_COVER_DISP, ii)           \
                  << ") = "                                                    \
                  << boost::simd::details::                                    \
                     display(nt2::load<r_t>(&out[ii]))                         \
                  << " while expecting "                                       \
                  << boost::simd::details::                                    \
                     display(nt2::load<r_t>(&ref[ii]))                         \
                  << " (i.e "   << ff.ulp_error << " ULPs)"                    \
                  << std::endl;                                                \
        ib = ii;                                                               \
      }                                                                        \
    }                                                                          \
    std::cout << std::endl;                                                    \
  }                                                                            \
  /**/

  BOOST_PP_REPEAT_FROM_TO ( 1
                          , BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY)
                          , NT2_COVER_FAILURES
                          , ~
                          )

  #define NT2_COVER_PERFORM(z,n,t)                                             \
  template< typename Function, typename Data, typename Types                   \
          , BOOST_PP_ENUM_PARAMS(n,typename I)                                 \
          >                                                                    \
  inline                                                                       \
  void perform_coverage ( const char* desc, const char* file, int line         \
                        , Function f                                           \
                        , Data const& out, Data const& ref, double N           \
                        , Types const& types                                   \
                        , BOOST_PP_ENUM_BINARY_PARAMS(n,I, const& i)           \
                        )                                                      \
  {                                                                            \
    typedef typename Data::value_type                               t_t;       \
    typedef typename nt2::details::max_ulp_<t_t,t_t>::failure_type  f_t;       \
                                                                               \
    std::vector< f_t > ulps;                                                   \
    double ulpd = 0;                                                           \
    find_ulp_error(out,ref,ulps,ulpd,N,details::max_ulps_caller());            \
                                                                               \
    if(ulps.empty())                                                           \
    {                                                                          \
      std::cout << "For " << out.size() << " samples: \n";                     \
      ::nt2::details::ulp_pass(desc, ulpd, N);                                 \
    }                                                                          \
    else                                                                       \
    {                                                                          \
      std::cout << " *** Cover tests failed with a maximum of "                \
                << ulpd << " ULPs. ***\n";                                     \
      ::nt2::details::ulp_fail( desc, file, line, ulps.size(), N, true );      \
      display_cover_fails ( desc, f                                            \
                          , out, ref                                           \
                          , ulps, types, BOOST_PP_ENUM_PARAMS(n, i)            \
                          );                                                   \
    }                                                                          \
  }                                                                            \
  /**/

  BOOST_PP_REPEAT_FROM_TO ( 1
                          , BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY)
                          , NT2_COVER_PERFORM
                          , ~
                          )

  #define NT2_COVER_TEST_PP(z,n,t)                                             \
  template< typename Function, typename Data, typename Types                   \
          , BOOST_PP_ENUM_PARAMS(n,typename I)                                 \
          >                                                                    \
  inline                                                                       \
  void test_cover_ulp ( const char* desc, const char* file, int line           \
                      , Function f, Data const& ref, Types const& types        \
                      , double ulpd                                            \
                      , BOOST_PP_ENUM_BINARY_PARAMS(n,I, const& i)             \
                      )                                                        \
        {                                                                      \
    Data out  = ::nt2::details                                                 \
                ::compute_coverage( f, ref, types                              \
                                  , BOOST_PP_ENUM_PARAMS(n, i)                 \
                                  );                                           \
                                                                               \
    ::nt2::details::                                                           \
    perform_coverage( desc, file, line, f                                      \
                    , out , ref , ulpd, types                                  \
                    , BOOST_PP_ENUM_PARAMS(n, i)                               \
                    );                                                         \
  }                                                                            \
  /**/

  BOOST_PP_REPEAT_FROM_TO ( 1
                          , BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY)
                          , NT2_COVER_TEST_PP
                          , ~
                          )
} }

#endif
