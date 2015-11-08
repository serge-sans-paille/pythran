//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_RELATION_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_RELATION_HPP_INCLUDED

#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/eval.hpp>
#include <nt2/sdk/unit/details/test_for_equality.hpp>
#include <boost/current_function.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace nt2
{
  namespace unit
  {
    template<class A, class B, class F>
    void test_relation( const char* A_str, A const& a, const char* B_str, B const& b
                      , unsigned line, const char* fn, const char* Op_str, F const& Op
                      )
    {
      std::ostringstream ss;
      ss << A_str << " " << Op_str << " " << B_str;
      std::string info = ss.str();

      nt2::unit::test_count()++;
      if( Op(a, b) )
      {
        nt2::unit::pass( info.c_str() );
      }
      else
      {
        nt2::unit::fail( info.c_str(), line, fn );
        std::cout << A_str << ": \n" << std::setprecision(20)
                  << a << std::endl;
        std::cout << B_str << ": \n" << std::setprecision(20)
                  << b << std::endl;
      }
    }
  }

  namespace details
  {
    struct equality
    {
      template<class A, class B>
      bool operator()(A const& a, B const& b) const
      {
        return nt2::unit::test_for_equality(a, b);
      }
    };

    struct not_equality
    {
      template<class A, class B>
      bool operator()(A const& a, B const& b) const
      {
        return !nt2::unit::test_for_equality(a, b);
      }
    };

    struct lesser
    {
      template<class A, class B>
      bool operator()(A const& a, B const& b) const
      {
        return a < b;
      }
    };

    struct greater
    {
      template<class A, class B>
      bool operator()(A const& a, B const& b) const
      {
        return a > b;
      }
    };

    struct lesser_equal
    {
      template<class A, class B>
      bool operator()(A const& a, B const& b) const
      {
        return a <= b;
      }
    };

    struct greater_equal
    {
      template<class A, class B>
      bool operator()(A const& a, B const& b) const
      {
        return a >= b;
      }
    };
  }
}

/*!
  @brief Check the equality of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c == @c B evaluates to @c true.

  @usage{test_equal.cpp}
**/
#define NT2_TEST_EQUAL(A,B)                                                    \
nt2::unit::test_relation( #A, nt2::unit::eval(A)                               \
                        , #B, nt2::unit::eval(B)                               \
                        , __LINE__, BOOST_CURRENT_FUNCTION                     \
                        , "==", nt2::details::equality()                       \
                        )                                                      \
/**/


/*!
  @brief Check the inequality of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c != @c B evaluates to @c true.

  @usage{test_not_equal.cpp}
**/
#define NT2_TEST_NOT_EQUAL(A,B)                                                \
nt2::unit::test_relation( #A, nt2::unit::eval(A)                               \
                        , #B, nt2::unit::eval(B)                               \
                        , __LINE__, BOOST_CURRENT_FUNCTION                     \
                        , "!=", nt2::details::not_equality()                   \
                        )                                                      \
/**/

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c < @c B evaluates to @c true.

  @usage{test_lesser.cpp}
**/
#define NT2_TEST_LESSER(A,B)                                                   \
nt2::unit::test_relation( #A, nt2::unit::eval(A)                               \
                        , #B, nt2::unit::eval(B)                               \
                        , __LINE__, BOOST_CURRENT_FUNCTION                     \
                        , "<", nt2::details::lesser()                          \
                        )                                                      \
/**/

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c > @c B evaluates to @c true.

  @usage{test_greater.cpp}
**/
#define NT2_TEST_GREATER(A,B)                                                  \
nt2::unit::test_relation( #A, nt2::unit::eval(A)                               \
                        , #B, nt2::unit::eval(B)                               \
                        , __LINE__, BOOST_CURRENT_FUNCTION                     \
                        , ">", nt2::details::greater()                         \
                        )                                                      \
/**/

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c <= @c B evaluates to @c true.

  @usage{test_lesser_equal.cpp}
**/
#define NT2_TEST_LESSER_EQUAL(A,B)                                             \
nt2::unit::test_relation( #A, nt2::unit::eval(A)                               \
                        , #B, nt2::unit::eval(B)                               \
                        , __LINE__, BOOST_CURRENT_FUNCTION                     \
                        , "<=", nt2::details::lesser_equal()                   \
                        )                                                      \
/**/

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c >= @c B evaluates to @c true.

  @usage{test_greater_equal.cpp}
**/
#define NT2_TEST_GREATER_EQUAL(A,B)                                            \
nt2::unit::test_relation( #A, nt2::unit::eval(A)                               \
                        , #B, nt2::unit::eval(B)                               \
                        , __LINE__, BOOST_CURRENT_FUNCTION                     \
                        , ">=", nt2::details::greater_equal()                  \
                        )                                                      \
/**/

#endif
