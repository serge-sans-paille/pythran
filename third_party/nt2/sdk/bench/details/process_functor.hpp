#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NM4_SDK_BENCH_WORKBENCH_PROCESS_FUCNTOR_HPP_INCLUDED
#define NM4_SDK_BENCH_WORKBENCH_PROCESS_FUCNTOR_HPP_INCLUDED

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <nt2/include/functions/aligned_load.hpp>
#include <nt2/include/functions/aligned_store.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <vector>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

namespace nt2 { namespace details
{
  /*
    process_functor is an Experiment used to bench arbitrary functor
  */
  template< typename Function, std::size_t Arity
          , typename Arg0       , typename Arg1 = void, typename Arg2 = void
          , typename Arg3 = void, typename Arg4 = void, typename Arg5 = void
          >
  struct process_functor;

  #define BOOST_PP_ITERATION_PARAMS_1 (3,(1,6,"nt2/sdk/bench/details/process_functor.hpp"))
  #include BOOST_PP_ITERATE()

  template< typename Function, std::size_t Arity
          , typename Arg0, typename Arg1, typename Arg2
          , typename Arg3, typename Arg4, typename Arg5
          >
  std::ostream& operator<<( std::ostream& os
                          , process_functor < Function,Arity
                                            , Arg0, Arg1, Arg2, Arg3, Arg4, Arg5
                                            > const& p
                          )
  {
    return os << "(" << p.size() << ")";
  }
} }

#endif

#else

  #define N BOOST_PP_ITERATION()

  #define M0(z,n,t)                                                            \
  typedef typename boost::dispatch::meta::scalar_of<Arg##n>::type type_##n;    \
  typedef boost::simd::allocator<type_##n> alloc_##n;                          \
  /**/

  #define M1(z,n,t)                                                            \
   (boost::simd::meta::cardinal_of<Arg##n>::value != 1)                        \
  ? boost::simd::meta::cardinal_of<Arg##n>::value                              \
  :                                                                            \
  /**/

  #define M2(z,n,t) in##n(size_)

  #define M3(z,n,t) nt2::roll ( in##n                                          \
                              , boost::fusion::at_c<n+1>(args).first           \
                              , boost::fusion::at_c<n+1>(args).second          \
                              );                                               \
  /**/                                                                         \

  #define M4(z,n,t) nt2::aligned_load<Arg##n>(&in##n[i])
  #define M5(z,n,t) std::vector<type_##n,alloc_##n> in##n;

  template< typename Function,BOOST_PP_ENUM_PARAMS(N,typename Arg)>
  struct process_functor<Function,N,BOOST_PP_ENUM_PARAMS(N,Arg)>
  {
    typedef void experiment_is_immutable;

    // Computes scalar version of Args so we know what to store in in_i
    BOOST_PP_REPEAT(N,M0,~)

    // Result type
    typedef typename boost::dispatch::meta
            ::result_of<Function(BOOST_PP_ENUM_PARAMS(N,Arg))>::type   out_t;
    typedef boost::simd::allocator<out_t> alloc_out;

    // How many stuff to process
    static const std::size_t card = BOOST_PP_REPEAT(N, M1, ~) 1;

    template<typename Args>
    process_functor ( Args const& args )
                    : size_(boost::fusion::at_c<0>(args))
                    , result_(size_/card)
                    , BOOST_PP_ENUM(N,M2,~)
    {
      BOOST_PP_REPEAT(N,M3,~)
    }

    void operator()()
    {
      for(std::size_t i=0, j=0;i<size_;i+=card, j++)
        result_[j] = f_( BOOST_PP_ENUM( N, M4, ~) );
    }

    std::size_t size() const { return size_; }

    friend std::ostream&
    operator<<( std::ostream& os
              , process_functor<Function,N,BOOST_PP_ENUM_PARAMS(N,Arg)> const& p
              )
    {
      return os << p.size_;
    }

    private:
    Function                       f_;
    std::size_t                    size_;
    std::vector<out_t, alloc_out>  result_;
    BOOST_PP_REPEAT(N,M5,~)
  };

  #undef N
  #undef M0
  #undef M1
  #undef M2
  #undef M3
  #undef M4
  #undef M5

#endif
