//==============================================================================
//         Copyright 2009 - 2014   LRI UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_SWAP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_SWAP_HPP_INCLUDED

#include <nt2/core/functions/swap.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/tie.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::swap_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0,nt2::container::domain>))
                              ((ast_<A1,nt2::container::domain>))
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      eval(a0,a1, boost::mpl::bool_ < meta::is_container_terminal<A0>::value
                                  &&  meta::is_container_terminal<A1>::value
                                    >()
          );
    }

    BOOST_FORCEINLINE result_type
    eval(A0& a0, A1& a1, boost::mpl::true_ const&) const
    {
      // Swapping real terminals require actual swap call
      memory::swap(boost::proto::value(a0),boost::proto::value(a1));
    }

    BOOST_FORCEINLINE result_type
    eval(A0& a0, A1& a1, boost::mpl::false_ const&) const
    {
      // Swapping sub-expression requires same number of elements
      BOOST_ASSERT_MSG( numel(a0) == numel(a1)
                      , "Swapping expression with incompatible sizes."
                      );

      nt2::tie(a1,a0) = nt2::tie(a0,a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::swap_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0,nt2::container::domain>))
                              (scalar_<unspecified_< A1 > >)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      BOOST_ASSERT_MSG( numel(a0) == 1u
                      , "Swapping non-scalar expression with a scalar"
                      );

      boost::swap(a0(first_index<1>(a0)),a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::swap_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_< A0 > >)
                              ((ast_<A1,nt2::container::domain>))
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      BOOST_ASSERT_MSG( numel(a1) == 1u
                      , "Swapping non-scalar expression with a scalar"
                      );

      boost::swap(a0, a1(first_index<1>(a1)) );
    }
  };
} }

#endif
