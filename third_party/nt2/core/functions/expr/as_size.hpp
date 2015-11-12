//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_AS_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_AS_SIZE_HPP_INCLUDED

#include <nt2/core/functions/as_size.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/core/container/dsl/forward.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::as_size_, tag::cpu_
                            , (A0)
                            , ((ast_< A0, nt2::container::domain >))
                            )
  {
    typedef of_size_max result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG
      ( nt2::isrow(a0)
      , "Error: Size vector must be a row vector."
      );

      std::size_t l = nt2::length(a0);

      if(l > 1)
      {
        std::size_t sz = std::min(of_size_max::size(),l);
        return result_type(a0.raw(), a0.raw()+sz);
      }
      else
      {
        return result_type(*a0.raw(), *a0.raw());
      }
    }
  };
} }

#endif
