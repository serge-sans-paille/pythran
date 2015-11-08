//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_BASE_CASE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_BASE_CASE_HPP_INCLUDED

#include <cstdio>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/config/type_lists.hpp>
#include <nt2/sdk/error/assert_as_exceptions.hpp>

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/filter_view.hpp>

#define NT2_TEST_BASE_CASE(Name,TestType,Suite,Suffix)                         \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)();                                     \
TestType const                                                                 \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)                                             \
                        ( &Suite                                               \
                        , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)                   \
                        , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,Suffix))        \
                        );                                                     \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)()                                      \
/**/

/// Generate one given instanciation of a template test case
#define NT2_PP_TPL_CASES(r,name,type)                           \
printf( "With T = [%s]\n"                                       \
      , nt2::type_id<BOOST_DISPATCH_PP_STRIP(type)>().c_str()); \
BOOST_PP_CAT(tpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX,name))          \
                  <BOOST_DISPATCH_PP_STRIP(type)>();            \
/**/

namespace nt2 { namespace details
{
  inline void report_empty(boost::mpl::true_ const&)
  {
    std::cout << "Test skipped: Types PP sequence is empty.\n";
    ::nt2::unit::test_count()++;
  }

  inline void report_empty(boost::mpl::false_ const&) {}
} }

#define NT2_TEST_BASE_CASE_TPL(Name, Types,TestType,Suite,Suffix)              \
template<class T> void BOOST_PP_CAT ( tpl_                                     \
                                    , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)       \
                                    )();                                       \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)();                                     \
                                                                               \
TestType const                                                                 \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)                                             \
            ( &Suite                                                           \
            , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)                               \
            , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,Suffix))                    \
            );                                                                 \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)()                                      \
{                                                                              \
  nt2::details::report_empty(boost::mpl::bool_<!BOOST_PP_SEQ_SIZE(Types)>());  \
  BOOST_PP_SEQ_FOR_EACH(NT2_PP_TPL_CASES,Name,Types);                          \
}                                                                              \
                                                                               \
template<class T> void BOOST_PP_CAT ( tpl_                                     \
                                    , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)       \
                                    )()                                        \
/**/

#define NT2_TEST_BASE_CASE_TPL_MPL(Name, TypeList,TestType,Suite,Suffix)       \
template<class T> void BOOST_PP_CAT ( tpl_mpl_                                 \
                                    , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)       \
                                    )();                                       \
struct BOOST_PP_CAT( tpl_fun_mpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX, Name) )       \
{                                                                              \
  template<class T>                                                            \
  void operator()(T const&) const                                              \
  {                                                                            \
    printf("With T = [%s]\n", nt2::type_id<T>().c_str());                      \
    BOOST_PP_CAT( tpl_mpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX,Name) )<T>();         \
  }                                                                            \
};                                                                             \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)();                                     \
                                                                               \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,BOOST_PP_CAT(Name,_impl))                    \
                                  (boost::mpl::true_ const&)                   \
{                                                                              \
  std::cout << "Test skipped: Types MPL list is empty.\n";                     \
  ::nt2::unit::test_count()++;                                                 \
}                                                                              \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,BOOST_PP_CAT(Name,_impl))                    \
                                  (boost::mpl::false_ const&)                  \
{                                                                              \
  using namespace boost::mpl;                                                  \
  boost::mpl::for_each<BOOST_DISPATCH_PP_STRIP(TypeList)>                      \
  (BOOST_PP_CAT( tpl_fun_mpl_, BOOST_PP_CAT(NT2_UNIT_PREFIX, Name) )());       \
}                                                                              \
                                                                               \
TestType const                                                                 \
BOOST_PP_CAT(Name,NT2_UNIT_PREFIX)                                             \
            ( &Suite                                                           \
            , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)                               \
            , BOOST_PP_STRINGIZE(BOOST_PP_CAT(Name,Suffix))                    \
            );                                                                 \
void BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)()                                      \
{                                                                              \
  using namespace boost::mpl;                                                  \
  static const int sz = boost::mpl                                             \
                             ::size<BOOST_DISPATCH_PP_STRIP(TypeList)>::value; \
  BOOST_PP_CAT(NT2_UNIT_PREFIX,BOOST_PP_CAT(Name,_impl))                       \
              ( boost::mpl::bool_<!sz>());                                     \
}                                                                              \
                                                                               \
template<class T> void BOOST_PP_CAT ( tpl_mpl_                                 \
                                    , BOOST_PP_CAT(NT2_UNIT_PREFIX,Name)       \
                                    )()                                        \
/**/

#endif
