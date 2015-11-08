//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_MAX_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_MAX_HPP_INCLUDED

#include <nt2/sdk/parameters.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace nt2 { namespace utility
{
  namespace result_of
  {
    template<class A, class B> struct max;

    template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D1)
            , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D2)
            >
    struct max< of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)>
              , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)>
              >
    {
      // Cmpute result type by keeping static informations
      #define M0(z,n,t) ( (D1##n < 0) || (D2##n < 0)              \
                        ? -1 : ((D1##n > D2##n) ? D1##n : D2##n)  \
                        )                                         \
      /**/
      typedef of_size_<BOOST_PP_ENUM(NT2_MAX_DIMENSIONS, M0, ~)> type;
      #undef M0

      // Perform max computation on a per dimension basis
      struct impl
      {
        template<class T,class A,class B>
        impl(T& t, A const& a, B const& b) : that(t), a0(a), a1(b)
        {}

        template<int N> void operator()()
        {
          typedef typename type::values_type values_t;
          eval<N> ( boost::mpl::bool_
                    <(boost::mpl::at_c<values_t,N>::type::value < 0)>()
                  );
        }

        template<int N> void eval(boost::mpl::true_ const&)
        {
          std::size_t a = boost::fusion::at_c<N>(a0);
          std::size_t b = boost::fusion::at_c<N>(a1);
          boost::fusion::at_c<N>(that) = std::max(a,b);
        }

        template<int N> void eval(boost::mpl::false_ const&) {}

        type& that;
        of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)> const& a0;
        of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)> const& a1;

        private:
        impl& operator=(impl const&);
      };

      template<class A, class B>
      BOOST_FORCEINLINE type operator()( A const& a0, B const& a1 )
      {
        type that;
        impl callee(that,a0,a1);
        boost::simd::meta::iterate<type::static_size>(callee);
        return that;
      }
    };
  }

  /*!
    @brief Maximum extent

    Computes an extent covering the maximum area between two other extents.

    @param a0 First extent
    @param a1 Second extent

    @return an extent value that, for every dimension, is greater or equal to
    the corresponding  dimension of both a0 and a1.
  **/
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D1)
          , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D2)
          >
  typename  result_of
            ::max < of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)>
                  , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)>
                  >::type
  max ( of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)> const& a0
      , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)> const& a1
      )
  {
    result_of::max< of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D1)>
                  , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D2)>
                  > callee;
    return callee(a0,a1);
  }
} }

#endif
