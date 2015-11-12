//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CUMULATIVE_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CUMULATIVE_RUN_HPP_INCLUDED

#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/inner_scan.hpp>
#include <nt2/include/functions/outer_scan.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <boost/proto/traits.hpp>
#include <numeric>

namespace nt2 { namespace ext
{
  //============================================================================
  // Cumulative operations go to inner/outer scan
  // Note that MATLAB cumulative functions have a f(x) and a f(x,i) form
  // that we handle with reduction_dim
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)(N0)(A1)(T1)(O1)(Neutral1)(N1)
                            , ((node_<A0, elementwise_<T0>, N0, nt2::container::domain>))
                              ((node_<A1, cumulative_<T1,O1,Neutral1>, N1 , nt2::container::domain>))
                            )
  {
    typedef A0&                                                                result_type;
    typedef typename boost::proto::result_of::child_c<A1&, 0>::type            input_type;
    typedef typename boost::remove_reference<input_type>::type::extent_type    extent_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      a0.resize(a1.extent());

      input_type input = boost::proto::child_c<0>(a1);
      extent_type ext = input.extent();
      std::size_t dim = nt2::ndims(ext);
      std::size_t lo_dim = nt2::firstnonsingleton(ext);
      std::size_t red = reduction_dim(a1, boost::mpl::bool_<!(boost::proto::arity_of<A1>::value <= 1)>());

      std::size_t inner = red-1 < ext.size() ? ext[red-1] : 1;

      std::size_t lo = std::accumulate( ext.begin()
                                      , ext.begin()+std::min(red-1, dim)
                                      , std::size_t(1)
                                      , std::multiplies<std::size_t>()
                                      );

      std::size_t hi = std::accumulate( ext.begin()+std::min(red, dim)
                                      , ext.begin()+dim
                                      , std::size_t(1)
                                      , std::multiplies<std::size_t>()
                                      );

      if(red <= lo_dim)
      {
        nt2::inner_scan( container::as_view(a0)
                       , reshape(input, of_size(inner, hi))
                       , typename nt2::make_functor<Neutral1, A0>::type()
                       , typename nt2::make_functor<O1, A0>::type()
                       , typename nt2::make_functor<T1, A0>::type()
                       );
      }
      else
      {
        nt2::outer_scan( reshape(a0, of_size(lo, inner, hi))
                       , reshape(input, of_size(lo, inner, hi))
                       , typename nt2::make_functor<Neutral1, A0>::type()
                       , typename nt2::make_functor<O1, A0>::type()
                       , typename nt2::make_functor<T1, A0>::type()
                       );
      }

      return a0;
    }

    inline std::size_t reduction_dim(A1& a1, boost::mpl::false_) const
    {
      return nt2::firstnonsingleton(boost::proto::child_c<0>(a1).extent());
    }

    inline std::size_t reduction_dim(A1& a1, boost::mpl::true_) const
    {
      return nt2::run(boost::proto::child_c<1>(a1));
    }
  };
} }

#endif
