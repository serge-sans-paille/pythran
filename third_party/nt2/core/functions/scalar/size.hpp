//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_SIZE_HPP_INCLUDED

#include <nt2/core/functions/size.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/extent.hpp>
#include <nt2/sdk/meta/make_dependent.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::size_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef container::
            table < typename meta::make_dependent<std::size_t,A0>::type
                  , settings(automatic_,of_size_<1,2>)
                  >                                         result_type;

    BOOST_FORCEINLINE result_type operator()(const A0&) const
    {
      result_type that;
      that.raw()[0] = that.raw()[1] = std::size_t(1);
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::size_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE result_type operator()(const A0&,const A1&) const
    {
      return 1;
    }
  };
} }

#endif
