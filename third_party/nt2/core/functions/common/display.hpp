//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_DISPLAY_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_DISPLAY_HPP_INCLUDED

#include <nt2/sdk/meta/type_id.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <iostream>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::display_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef void result_type;

    result_type operator()(A0 const& a0) const
    {
      std::cout << "ans = \n     " << a0 << std::endl;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::display_, tag::cpu_
                            , (Tag)(Site)
                            , ((unspecified_< nt2::functor<Tag, Site> >))
                            )
  {
    typedef void result_type;

    result_type operator()(nt2::functor<Tag, Site> const&) const
    {
      std::string tag = type_id<Tag>();
      std::size_t pos = tag.find_last_of(':')+1;
      std::size_t sz  = tag.size()-pos-1;
      std::cout << "ans = \n    @" << tag.substr(pos, sz) << std::endl;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::display_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)
                              (unspecified_<A1>)
                            )
  {
    typedef void result_type;

    result_type operator()(A0 const& a0, A1 const& a1) const
    {
      std::cout << a0 << " = \n     " << a1 << std::endl;
    }
  };
} }

#endif
