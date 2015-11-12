#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_PROTOCOL_HPP_INCLUDED
#define NT2_SDK_BENCH_PROTOCOL_HPP_INCLUDED

#include <nt2/sdk/bench/details/display_metric.hpp>
#include <nt2/sdk/bench/details/measure.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

namespace nt2 { namespace details
{
  template<class Experiment, class Enable = void>
  struct experiment_copy
  {
    typedef Experiment type;
  };

  template<class Experiment>
  struct experiment_copy<Experiment, typename Experiment::experiment_is_immutable>
  {
    typedef Experiment& type;
  };
} }

namespace nt2 { namespace bench
{
#if defined(DOXYGEN_ONLY)

  /*!

  **/
  template< typename Metrics...>
  struct protocol
  {
    typedef boost::fusion::vector<BOOST_PP_ENUM_PARAMS(N, M)> metrics_type;

    protocol();
    protocol(metrics_type const& m);

    template<typename Experiment>
    inline time_quantum_t run ( Experiment& e
                              , details::times_set&  t
                              , details::cycles_set& c
                              ) const;

    template<typename Experiment>
    inline void display ( Experiment& e
                        , details::times_set&  t, details::cycles_set& c
                        ) const;
  };

#else

  template< typename M0                       , typename M1 = boost::fusion::void_
          , typename M2 = boost::fusion::void_, typename M3 = boost::fusion::void_
          , typename M4 = boost::fusion::void_, typename M5 = boost::fusion::void_
          , typename M6 = boost::fusion::void_, typename M7 = boost::fusion::void_
          , typename M8 = boost::fusion::void_, typename M9 = boost::fusion::void_
          >
  struct protocol;

  #define BOOST_PP_ITERATION_PARAMS_1 (3,(1,10,"nt2/sdk/bench/protocol.hpp"))
  #include BOOST_PP_ITERATE()

#endif

} }

#endif

#else

  #define N BOOST_PP_ITERATION()

  template<BOOST_PP_ENUM_PARAMS(N, typename M)>
  struct protocol
  #if (N < 10)
  <BOOST_PP_ENUM_PARAMS(N, M)>
  #endif
  {
    typedef boost::fusion::vector<BOOST_PP_ENUM_PARAMS(N, M)> metrics_type;

    protocol() {}
    protocol(metrics_type const& m) : metrics_(m) {}

    template<typename Experiment>
    inline time_quantum_t run ( Experiment& e
                              , details::times_set&  t
                              , details::cycles_set& c
                              ) const
    {
      /* We copy reference experiment depending on whether they have
       * experiment_is_immutable or not */
      typename details::experiment_copy<Experiment>::type local(e);

      time_quantum_t const time_start  ( time_quantum() );
      cycles_t       const cycles_start( read_cycles() );

      local();

      cycles_t       const cycles_end( read_cycles() );
      time_quantum_t const time_end  ( time_quantum() );

      cycles_t       const burned_cycles( cycles_end - cycles_start );
      time_quantum_t const elapsed_time ( time_end   - time_start   );

      t(to_microseconds(elapsed_time));
      c(burned_cycles);

      return elapsed_time;
    }

    template<typename Experiment>
    inline void display ( Experiment& e
                        , details::times_set&  t, details::cycles_set& c
                        ) const
    {
      boost::fusion::for_each ( metrics_
                              , details::display_metric<Experiment>(e,t,c)
                              );
    }

    protected:
    metrics_type  metrics_;
  };


  #undef N

#endif
