//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_TEST_FOR_EQUALITY_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_TEST_FOR_EQUALITY_HPP_INCLUDED

#include <nt2/sdk/unit/details/is_sequence.hpp>
#include <nt2/include/functions/value.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/detail/workaround.hpp>
#include <algorithm>

namespace nt2 { namespace details
{
  /// Check if a==b or if a and b are NaNs
  /// This function is meant to be called on scalar values only
  template<class A, class B>
  BOOST_DISPATCH_NOINLINE bool equaln(A const& va, B const& vb)
  {
    return (va==vb) || ( (va!=va) && (vb!=vb) );
  }

  /// Perform a test of equality on A and B
  /// Detects if A and/or B is actually a sequence and apply equaln on
  /// every elements of said sequences
  template< class A, class B
          , bool IsASeq=nt2::details::is_sequence<A>::value
          , bool IsBSeq=nt2::details::is_sequence<B>::value
          >
  struct test_for_equality
  {
    /// Main operator() checks of A and B are Fusion Sequence then
    /// jump into the proper eval() member functions depending on this
    /// status.
    BOOST_FORCEINLINE bool operator()(A const& a, B const& b) const
    {
      return eval ( a , b
                  , boost::mpl::
                    bool_ < boost::fusion::traits::is_sequence<A>::value
                        &&  boost::fusion::traits::is_sequence<B>::value
                          >()
                  );
    }

    /// A and B are not Fusion Sequence, just call equaln ont heir value
    BOOST_FORCEINLINE bool
    eval(A const& a, B const& b,boost::mpl::false_ const&) const
    {
      return equaln(nt2::value(a),nt2::value(b));
    }

    /// A and B are Fusion Sequence, call equaln on every elements
    BOOST_FORCEINLINE bool
    eval(A const& a, B const& b,boost::mpl::true_ const&) const
    {
      return (boost::fusion::size(a) == boost::fusion::size(b))
            && eval ( a , b
                    , typename boost::fusion::result_of::size<A>::type()
                    );
    }

    BOOST_FORCEINLINE bool
    eval(A const& a, B const& b,boost::mpl::int_<1> const&) const
    {
      return equaln(boost::fusion::at_c<0>(a),boost::fusion::at_c<0>(b));
    }

    template<class N>
    BOOST_FORCEINLINE bool
    eval(A const& a, B const& b,N const&) const
    {
      return  equaln( boost::fusion::at_c<N::value-1>(a)
                    , boost::fusion::at_c<N::value-1>(b)
                    )
          &&  eval(a,b,typename boost::mpl::prior<N>::type());
    }
  };

  /// Both A and B are sequence, so we use std::equal by using the single
  /// value version of test_for_equality
  template<class A, class B>
  struct  test_for_equality<A, B, true, true>
  {
    struct check_
    {
      template<class U,class V>
      BOOST_FORCEINLINE bool operator()(U const& a, V const& b ) const
      {
        return test_for_equality<U,V>()(a,b);
      }
    };

    BOOST_FORCEINLINE bool operator()(A const& a, B const& b) const
    {
      if(std::distance(a.begin(),a.end()) == std::distance(b.begin(),b.end()))
      {
#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400) && BOOST_WORKAROUND(BOOST_MSVC, < 1600)
        return stdext::unchecked_equal(a.begin(),a.end(),b.begin(),check_());
#elif BOOST_WORKAROUND(BOOST_MSVC, > 1500)

      return std::equal ( a.begin(), a.end()
                        , stdext::make_unchecked_array_iterator(b.begin())
                        , check_()
                        );
#else
      return std::equal(a.begin(),a.end(),b.begin(),check_());
#endif
      }

      return false;
    }
  };

  /// B is a sequence while A is not, this means B has exactly one element
  template<class A, class B>
  struct  test_for_equality<A, B, false, true>
  {
    BOOST_FORCEINLINE bool operator()(A const& a, B const& b) const
    {
      return  test_for_equality<A,typename B::value_type>()(a,*b.begin())
          &&  (std::distance(b.begin(),b.end()) == 1);
    }
  };

  /// A is a sequence while B is not, this means A has exactly one element
  template<class A, class B>
  struct  test_for_equality<A, B, true, false>
  {
    BOOST_FORCEINLINE bool operator()(A const& a, B const& b) const
    {
      return  test_for_equality<typename A::value_type,B>()(*a.begin(),b)
          &&  (std::distance(a.begin(),a.end()) == 1);
    }
  };
} }

namespace nt2 { namespace unit
{
  /// INTERNAL ONLY Main test for equality over any types A and B
  template<class A, class B>
  BOOST_FORCEINLINE bool test_for_equality(A const& a, B const& b)
  {
    return details::test_for_equality<A,B>()(a,b);
  }
} }

#endif
