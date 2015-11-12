#if !BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_SETUP_COMBINATION_HPP_INCLUDED
#define NT2_SDK_BENCH_SETUP_COMBINATION_HPP_INCLUDED

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/strip.hpp>

namespace nt2 { namespace bench
{
#if defined(DOXYGEN_ONLY)

  /*!
    @brief Setup combinator

    Gather a variable amount of Setup into a single conglomerate that returns
    a Fusion Sequence of each of its components step when required, update
    their state synchronously and is defined as done as soon as one of its
    component is done.

    @tparam Data Types of Setup used in the combination
  **/
  template< typename Data...>
  struct combination_
  {
    /*!
      Initialize a combination from a variable amount of Setup instances

      @param d Instances of setup to agglomerate
    **/
    combination_(Data const& d...);

    typedef boost::fusion::vector<Data...> result_type;

    /// @brief Current value of the combination
    result_type  operator()();

    /// @brief Update combination state
    void step();

    /// @brief Status of the combination
    bool done() const;
  };

  /*!
    @brief Combination setup generator

    Generate a combination setup object from a set of other Setups.

    @param d Setups to agglomerate

    @return a combination_ object containing copies of d
  **/

  template<typename Data...>
  combination_<Data...> and_(Data const& d...);

#else

  template< BOOST_PP_ENUM_BINARY_PARAMS ( 10
                                        , typename Data
                                        , = void BOOST_PP_INTERCEPT
                                        )
          >
  struct combination_;

  #define   BOOST_PP_FILENAME_1 "nt2/sdk/bench/setup/combination.hpp"
  #define   BOOST_PP_ITERATION_LIMITS (1, 10)
  #include  BOOST_PP_ITERATE()

#endif

} }

#endif

#else

  #define N BOOST_PP_ITERATION()

  template<BOOST_PP_ENUM_PARAMS(N, typename Data)>
  struct  combination_
#if N < 10
  <BOOST_PP_ENUM_PARAMS(N, Data)>
#endif
  {
    typedef boost::fusion::vector<BOOST_PP_ENUM_PARAMS(N, Data)>  data_type;

    struct do_value
    {
      template<typename Sig> struct result;

      template<typename This, typename T>
      struct result<This(T)>
      {
        typedef typename boost::dispatch::meta
                                        ::strip<T>::type::result_type type;
      };

      template<typename T>
      BOOST_FORCEINLINE
      typename result<do_value(T const&)>::type operator()(T& t) const
      {
        return t();
      }
    };

    typedef typename boost::fusion::result_of
                          ::transform<data_type const, do_value>::type  result_type;

    // N Data = N parameters in ctor
    inline combination_ ( BOOST_PP_ENUM_BINARY_PARAMS(N,Data,const& d))
                        : steps_(BOOST_PP_ENUM_PARAMS(N,d))
    {}

    BOOST_FORCEINLINE result_type  operator()() const
    {
      return boost::fusion::transform(steps_,do_value());
    }

    struct do_step
    {
      template<typename T>
      BOOST_FORCEINLINE void operator()(T& t) const { t.step(); }
    };

    BOOST_FORCEINLINE void step()
    {
      boost::fusion::for_each(steps_, do_step());
    }

    struct do_done
    {
      typedef bool result_type;

      template<typename T>
      BOOST_FORCEINLINE result_type operator()(bool s, const T& t) const
      {
        return s || t.done();
      }
    };

    BOOST_FORCEINLINE bool done() const
    {
      return boost::fusion::fold(steps_,false, do_done());
    }

    data_type steps_;
  };

  template<BOOST_PP_ENUM_PARAMS(N, typename Data)>
  BOOST_FORCEINLINE combination_<BOOST_PP_ENUM_PARAMS(N, Data)>
  and_(BOOST_PP_ENUM_BINARY_PARAMS(N, Data, const& a))
  {
    return combination_<BOOST_PP_ENUM_PARAMS(N, Data)>(BOOST_PP_ENUM_PARAMS(N,a));
  }

#undef N

#endif
