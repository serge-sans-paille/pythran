//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_FIRST_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_FIRST_INDEX_HPP_INCLUDED

#include <nt2/core/functions/first_index.hpp>
#include <nt2/core/container/dsl.hpp>
#include <boost/dispatch/meta/mpl.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::first_index_,tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (mpl_integral_< scalar_< integer_<A1> > >)
                            )
  {
    typedef typename boost::mpl::
            at_c< typename A0::index_type::index_type, A1::value-1>::type
    result_type;

    BOOST_FORCEINLINE result_type operator()(const A0&, const A1&) const
    {
      result_type that;
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::first_index_,tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef std::ptrdiff_t result_type;

    BOOST_FORCEINLINE result_type operator()(const A0&, const A1& d) const
    {
      typedef typename A0::index_type::index_type idx_t;

      BOOST_ASSERT_MSG
      ( (d <= NT2_MAX_DIMENSIONS) && (d > 0)
      , "Dimension index is out of bound"
      );

      switch(d)
      {
        #define M0(z,n,t)                                                     \
        case BOOST_PP_INC(n): return boost::mpl::at_c<idx_t,n>::type::value;  \
        /**/
        BOOST_PP_REPEAT(NT2_MAX_DIMENSIONS,M0,~)
        #undef M0
        default : return 1;
      }
    }
  };
} }

#endif
