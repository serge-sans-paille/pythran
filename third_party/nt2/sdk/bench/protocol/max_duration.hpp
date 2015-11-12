#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_PROTOCOL_MAX_DURATION_HPP_INCLUDED
#define NT2_SDK_BENCH_PROTOCOL_MAX_DURATION_HPP_INCLUDED

#include <nt2/sdk/bench/details/display_metric.hpp>
#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/protocol.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

namespace nt2 { namespace bench
{
#if defined(DOXYGEN_ONLY)

  /*!

  **/
  template< typename Experiment, typename Metrics...>
  struct max_duration : protocol<Experiment,Metrics...>
  {
    max_duration( double d, const Metrics& m... );
                                  inline void run();
    template<typename Workbench>  inline void run(Workbench w);
  };

  /*!

  **/
  template< typename Experiment, typename Metrics...>
  void run_during ( double duration, Metrics const& m...);

  /*!

  **/
  template< typename Experiment, typename Workbench, typename Metrics...>
  void run_during_with(double duration, Workbench const& w, Metrics const& m...);

#else
  template< typename Experiment
          , typename M0       , typename M1 = void, typename M2 = void
          , typename M3 = void, typename M4 = void, typename M5 = void
          , typename M6 = void, typename M7 = void, typename M8 = void
          , typename M9 = void
          >
  struct max_duration;

  #define BOOST_PP_ITERATION_PARAMS_1 (3,(1,10,"nt2/sdk/bench/protocol/max_duration.hpp"))
  #include BOOST_PP_ITERATE()

#endif
} }

#endif

#else

  #define N BOOST_PP_ITERATION()

  template<typename Experiment, BOOST_PP_ENUM_PARAMS(N, typename M)>
  struct  max_duration
  #if (N < 10)
  <Experiment,BOOST_PP_ENUM_PARAMS(N,M)>
  #endif
        : protocol<BOOST_PP_ENUM_PARAMS(N,M)>
  {
    typedef protocol<BOOST_PP_ENUM_PARAMS(N,M)> parent;
    typedef typename parent::metrics_type       metrics_type;

    max_duration( double d, BOOST_PP_ENUM_BINARY_PARAMS(N,const M, & m) )
                : parent(metrics_type(BOOST_PP_ENUM_PARAMS(N,m))), duration_(d)
    {}

    inline void run() { run(fixed(0)); }

    template<typename Workbench> inline void run(Workbench w)
    {
      time_quantum_t const total_duration( to_timequantums(duration_*1000000) );

      do
      {
        time_quantum_t       duration(0);
        details::times_set  times_;
        details::cycles_set cycles_;

        Experiment e(w());

        do
        {
          duration += parent::run(e,times_,cycles_);
        } while( duration < total_duration );

        parent::display(e,times_,cycles_);
        w.step();

      } while(!w.done());
    }

    private:
    double  duration_;
  };

  template< typename Experiment, BOOST_PP_ENUM_PARAMS(N, typename M)>
  void run_during ( double duration
                  , BOOST_PP_ENUM_BINARY_PARAMS(N, const M, & m)
                  )
  {
    max_duration<Experiment,BOOST_PP_ENUM_PARAMS(N, M)>
    that(duration,BOOST_PP_ENUM_PARAMS(N,m));

    that.run();
  }
  template< typename Experiment, typename Workbench
          , BOOST_PP_ENUM_PARAMS(N, typename M)
          >
  void run_during_with( double duration, Workbench const& w
                      , BOOST_PP_ENUM_BINARY_PARAMS(N, const M, & m)
                      )
  {
    max_duration<Experiment,BOOST_PP_ENUM_PARAMS(N, M)>
    that(duration,BOOST_PP_ENUM_PARAMS(N,m));

    that.run(w);
  }

  #undef N

#endif
