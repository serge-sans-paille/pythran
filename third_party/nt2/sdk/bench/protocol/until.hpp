#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_PROTOCOL_UNTIL_HPP_INCLUDED
#define NT2_SDK_BENCH_PROTOCOL_UNTIL_HPP_INCLUDED

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
  struct until_ : protocol<Experiment,Metrics...>
  {
    until_( double d, std::size_t i, const Metrics& m... );
                                  inline void run();
    template<typename Workbench>  inline void run(Workbench w);
  };

  /*!

  **/
  template< typename Experiment, typename Metrics...>
  void run_until(double duration, std::size_t iteration, Metrics const& m...);

  /*!

  **/
  template< typename Experiment, typename Workbench, typename Metrics...>
  void run_until_with ( double duration, std::size_t iteration
                      , Workbench const& w, Metrics const& m...
                      );

#else
  template< typename Experiment
          , typename M0       , typename M1 = void, typename M2 = void
          , typename M3 = void, typename M4 = void, typename M5 = void
          , typename M6 = void, typename M7 = void, typename M8 = void
          , typename M9 = void
          >
  struct until_;

  #define BOOST_PP_ITERATION_PARAMS_1 (3,(1,10,"nt2/sdk/bench/protocol/until.hpp"))
  #include BOOST_PP_ITERATE()

#endif
} }

#endif

#else

  #define N BOOST_PP_ITERATION()

  template<typename Experiment, BOOST_PP_ENUM_PARAMS(N, typename M)>
  struct  until_
  #if (N < 10)
  <Experiment,BOOST_PP_ENUM_PARAMS(N,M)>
  #endif
        : protocol<BOOST_PP_ENUM_PARAMS(N,M)>
  {
    typedef protocol<BOOST_PP_ENUM_PARAMS(N,M)> parent;
    typedef typename parent::metrics_type       metrics_type;

    until_( double d, std::size_t i, BOOST_PP_ENUM_BINARY_PARAMS(N,const M, & m) )
                : parent(metrics_type(BOOST_PP_ENUM_PARAMS(N,m)))
                , duration_(d)
                , iteration_(i)
    {}

    inline void run() { run(fixed(0)); }

    template<typename Workbench> inline void run(Workbench w)
    {
      time_quantum_t const total_duration( to_timequantums(duration_*1000000) );

      do
      {
        std::size_t         iter(0);
        time_quantum_t      duration(0);
        details::times_set  times_;
        details::cycles_set cycles_;

        Experiment e(w());

        do
        {
          duration += parent::run(e,times_,cycles_);
          iter++;
        } while( duration < total_duration && iter < iteration_ );

        parent::display(e,times_,cycles_);
        w.step();

      } while(!w.done());
    }

    private:
    double      duration_;
    std::size_t iteration_;
  };

  template< typename Experiment, BOOST_PP_ENUM_PARAMS(N, typename M)>
  void run_until( double duration, std::size_t iteration
                , BOOST_PP_ENUM_BINARY_PARAMS(N, const M, & m)
                )
  {
    until_<Experiment,BOOST_PP_ENUM_PARAMS(N, M)>
    that(duration, iteration, BOOST_PP_ENUM_PARAMS(N,m));

    that.run();
  }
  template< typename Experiment, typename Workbench
          , BOOST_PP_ENUM_PARAMS(N, typename M)
          >
  void run_until_with ( double duration, std::size_t iteration
                      , Workbench const& w
                      , BOOST_PP_ENUM_BINARY_PARAMS(N, const M, & m)
                      )
  {
    until_<Experiment,BOOST_PP_ENUM_PARAMS(N, M)>
    that(duration,iteration,BOOST_PP_ENUM_PARAMS(N,m));

    that.run(w);
  }

  #undef N

#endif
