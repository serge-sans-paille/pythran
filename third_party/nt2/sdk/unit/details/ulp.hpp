//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_ULP_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_ULP_HPP_INCLUDED

#include <nt2/sdk/unit/config.hpp>
#include <nt2/include/functions/value.hpp>
#include <nt2/sdk/unit/details/is_sequence.hpp>
#include <nt2/sdk/unit/details/smallest_type.hpp>
#include <nt2/sdk/unit/details/eval.hpp>
#include <nt2/sdk/unit/stats.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/current_function.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/foreach.hpp>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

namespace nt2 { namespace details
{
  /// Hold which value was faulty and by how much
  template<class A, class B> struct failed_value
  {
    A           value;
    B           desired_value;
    double      ulp_error;
    std::size_t index;
  };

  // NaN aware max
  template<typename T>
  T safe_max(T a, T b)
  {
    if(a != a) return a;
    if(b != b) return b;

    return std::max(a,b);
  }
  /// ULP test is a success
  NT2_TEST_UNIT_DECL void ulp_pass(const char* desc, double ulpd, double N);

  /// ULP test is a failure
  NT2_TEST_UNIT_DECL
  void ulp_fail ( const char* desc, const char* f, int line
                , std::size_t size, double N, bool ok
                );

  /// Default implementation of max_ulps forward to generic ulpdist
  template<class T>
  BOOST_FORCEINLINE double max_ulps(T const& a, T const& b)
  {
    typedef typename boost::dispatch::meta::as_unsigned<T>::type u_t;
    return (a<b) ? u_t(b-a) : u_t(a-b);
  }

  /// Precompiled implementation max_ulps on double
  NT2_TEST_UNIT_DECL double max_ulps(double a, double b);

  /// Precompiled implementation max_ulps on float
  NT2_TEST_UNIT_DECL double max_ulps(float  a, float  b);

  struct max_ulps_caller
  {
    typedef double result_type;
    template<class T>
    BOOST_FORCEINLINE double operator()(T const& a, T const& b) const
    {
      return max_ulps(a, b);
    }
  };

  /// Perform a test of equality on A and B with a given ulp tolerance
  /// Detects if A and/or B is actually a Fusion sequence or not
  template< class A, class B
          , bool IsAFusionSeq=boost::fusion::traits::is_sequence<A>::value
          , bool IsBFusionSeq=boost::fusion::traits::is_sequence<A>::value
          >
  struct max_ulp_value_;

  /// A and B are not Fusion Sequence, call distance_fn on the value
  template< class A, class B>
  struct max_ulp_value_<A,B,false,false>
  {
    typedef failed_value<A,B> failure_type;

    template<class VF, class F>
    BOOST_FORCEINLINE bool
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              , double& ru
              , F const& distance_fn
              ) const
    {
      double d = distance_fn ( nt2::details::smallest_a( nt2::value(a)
                                                       , nt2::value(b)
                                                       )
                             , nt2::details::smallest_b( nt2::value(a)
                                                       , nt2::value(b)
                                                       )
                             );
      if(!(d <= max_ulpd) )
      {
        typename VF::value_type f = { a, b, d, i };
        fails.push_back(f);
      }

      ru = d;

      return true;
    }
  };

  /// A and B are Fusion Sequence, call distance_fn on every elements and
  /// compute the maximum
  template< class A, class B>
  struct max_ulp_value_<A,B,true,true>
  {
    template<int I, int N> struct max_ulp_seq_
    {
      template<class X, class Y, class F>
      BOOST_FORCEINLINE double
      operator()( X const& a, Y const& b, double z, F const& distance_fn ) const
      {
        return max_ulp_seq_<I+1,N>()
              ( a , b
              , safe_max( z
                        , distance_fn( nt2::details::
                                       smallest_a( boost::fusion::at_c<I>(a)
                                                 , boost::fusion::at_c<I>(b)
                                                 )
                                     , nt2::details::
                                       smallest_b( boost::fusion::at_c<I>(a)
                                                 , boost::fusion::at_c<I>(b)
                                                 )
                                     )
                        )
              , distance_fn
              );
      }
    };

    template<int N> struct max_ulp_seq_<N,N>
    {
      template<class X, class Y, class F>
      BOOST_FORCEINLINE double
      operator()( X const&, Y const&, double z, F const& ) const
      {
        return z;
      }
    };

    typedef failed_value<A,B> failure_type;

    template<class VF, class F>
    BOOST_FORCEINLINE bool
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              , double& ru
              , F const& distance_fn
              ) const
    {
      double d =  max_ulp_seq_<0,boost::fusion::result_of
                                              ::size<A>::value>()(a,b,0.,distance_fn);

      if(!(d <=  max_ulpd))
      {
        failure_type f = {a, b, d, i};
        fails.push_back(f);
      }

      ru =  d;

      return true;
    }
  };

  /// Perform a test of equality on A and B with a given ulp tolerance
  /// Detects if A and/or B is actually a sequence and apply distance_fn on
  /// every elements of said sequences
  template< class A, class B
          , bool IsASeq=nt2::details::is_sequence<A>::value
          , bool IsBSeq=nt2::details::is_sequence<B>::value
          >
  struct max_ulp_;

  template< class A, class B>
  struct max_ulp_<A,B,false,false>
  {
    typedef typename max_ulp_value_<A,B>::failure_type failure_type;

    /// Main operator() checks of A and B are Fusion Sequence then
    /// jump into the proper eval() member functions depending on this
    /// status.
    template<class VF, class F>
    BOOST_FORCEINLINE bool
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              , double& ru
              , F const& distance_fn
              ) const
    {
      return max_ulp_value_<A,B>()(a, b, max_ulpd, fails, i, ru, distance_fn);
    }
  };

  /// Both A and B are sequence, so we iterate over elements using the single
  /// value version of max_ulp_
  template<class A, class B>
  struct max_ulp_< A, B, true,true>
  {
    typedef failed_value< typename A::value_type
                        , typename B::value_type
                        >                         failure_type;

    template<class VF, class F>
    BOOST_FORCEINLINE bool
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              , double& ru
              , F const& distance_fn
              ) const
    {
      if( std::distance(b.begin(),b.end()) == std::distance(a.begin(),a.end()))
      {
        double res(0);

        typename A::const_iterator ab = a.begin();
        typename A::const_iterator ae = a.end();
        typename B::const_iterator bb = b.begin();

        bool ok(true);
        while(ok && ab != ae)
        {
          double r(0);

          // Gather potential ULP errors from inside data
          typedef typename max_ulp_ < typename A::value_type
                                    , typename B::value_type
                                    >::failure_type local_failure_type;

          std::vector<local_failure_type> local_fails;

          ok = max_ulp_ < typename A::value_type
                        , typename B::value_type
                        >()(*ab,*bb,max_ulpd,local_fails,i,r,distance_fn);

          // Does inner check went ok and do we have fails ?
          if(ok && !local_fails.empty())
          {
            // Register current error
            typename VF::value_type f = { *ab,*bb, r, i };
            fails.push_back(f);
          }

          // Update global max ulp error
          res = safe_max(res,r);
          ab++;
          bb++;
          i++;
        }

        ru = res;

        return ok;
      }
      else
      {
        return false;
      }
    }
  };

  /// A is a sequence while B is not, this means B has exactly one element
  template<class A, class B>
  struct max_ulp_< A, B, true, false>
  {
    typedef failed_value<typename A::value_type, B> failure_type;

    template<class VF, class F>
    BOOST_FORCEINLINE bool
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails, std::size_t i
              , double& ru
              , F const& distance_fn
              ) const
    {
      if( std::distance(a.begin(),a.end()) == 1)
      {
        return max_ulp_<typename A::value_type,B>() ( *a.begin(),b
                                                    , max_ulpd,fails,i, ru
                                                    , distance_fn
                                                    );
      }
      else
      {
        return false;
      }
    }
  };

  /// B is a sequence while A is not, this means B has exactly one element
  template<class A, class B>
  struct max_ulp_< A, B, false, true>
  {
    typedef failed_value<A, typename B::value_type> failure_type;

    template<class VF, class F>
    BOOST_FORCEINLINE bool
    operator()( A const& a, B const& b
              , double max_ulpd, VF& fails , std::size_t i
              , double& ru
              , F const& distance_fn
              ) const
    {
      if( std::distance(b.begin(),b.end()) == 1)
      {
        return max_ulp_<A,typename B::value_type>() ( a,*b.begin()
                                                    , max_ulpd,fails,i, ru
                                                    , distance_fn
                                                    );
      }
      else
      {
        return false;
      }
    }
  };
} }

namespace nt2 { namespace unit
{
  /// INTERNAL ONLY
  /// Main test for equality over any types A and B within a given ulp tolerance
  template<class A, class B, class VF, class F>
  BOOST_FORCEINLINE
  bool max_ulp( A const& a, B const& b, double max_ulpd, VF& fails, double& ru, F const& distance_fn )
  {
    return details::max_ulp_<A,B>()(a,b,max_ulpd,fails,0,ru,distance_fn);
  }

  /// INTERNAL ONLY
  /// Main test for equality over any types A and B within a given ulp tolerance
  template<class A, class B, class VF>
  BOOST_FORCEINLINE
  bool max_ulp( A const& a, B const& b, double max_ulpd, VF& fails, double& ru )
  {
    return max_ulp(a, b, max_ulpd, fails, ru, details::max_ulps_caller());
  }
} }

namespace nt2 { namespace details
{

  template<typename Fails>
  BOOST_FORCEINLINE
  void report_ulp_unit_error( const char* desc, const char* func, int line
                            , Fails const& ulps, double ulpd, double N
                            , bool
                            )
  {
    if( ulps.empty() )
    {
      ::nt2::details::ulp_pass( desc, ulpd, N );
    }
    else
    {
      ::nt2::details::ulp_fail( desc, func, line, ulps.size(),N, true);

      BOOST_FOREACH ( typename Fails::const_reference f, ulps )
      {
        std::cout << std::setprecision(20)
                  << "\tlhs: "  << f.value
                  << ", rhs: "  << f.desired_value
                  << ", ULP: "  << f.ulp_error
                  << ", @( "    << f.index << " )";
        std::cout << std::endl;
      }

      std::cout << std::endl;
    }
  }


  template<typename A, typename B, class F>
  BOOST_FORCEINLINE
  void test_ulp_equal ( const char* desc, const char* func, int line
                      , A const& a, B const& b
                      , double N
                      , F const& distance_fn
                      )
  {
    typedef BOOST_TYPEOF(nt2::unit::eval(a))                        a_t;
    typedef BOOST_TYPEOF(nt2::unit::eval(b))                        b_t;
    typedef typename nt2::details::max_ulp_<a_t,b_t>::failure_type  f_t;

    std::vector< f_t > ulps;
    double ulpd = 0;
    bool ok = find_ulp_error(a,b,ulps,ulpd,N,distance_fn);

    if(ok)
    {
      ::nt2::details::report_ulp_unit_error(desc, func, line, ulps, ulpd, N, true);
    }
    else
    {
      ::nt2::details::ulp_fail( desc, func, line, ulps.size(), N, false);
    }
  }

  template<typename A, typename B, typename Fails, class F>
  BOOST_FORCEINLINE
  bool find_ulp_error ( A const& a, B const& b
                      , Fails& ulps, double& ulpd, double N
                      , F const& distance_fn
                      )
  {
    bool ok = nt2::unit::max_ulp( nt2::unit::eval(a)
                                , nt2::unit::eval(b)
                                , N, ulps, ulpd
                                , distance_fn
                                );
    return ok;
  }
} }

#endif
