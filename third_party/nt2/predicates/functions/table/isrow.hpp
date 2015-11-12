//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_TABLE_ISROW_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_TABLE_ISROW_HPP_INCLUDED

#include <nt2/predicates/functions/isrow.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/extent.hpp>
#include <boost/fusion/include/at.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isrow_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0& a0) const
    {
      typedef typename meta::call<tag::extent_(A0 const&)>::type extent_t;
      extent_t ex = nt2::extent(a0);
      std::size_t nz = nt2::numel(ex);
      if (nz)
        return boost::fusion::at_c<1>(ex) == nz;
      else
        {
          if (boost::fusion::at_c<0>(ex) !=  1) return false;
          for(size_t i=2; i < ex.size(); ++i)
            {
              if (ex[i] !=  1u) return false;
            }
        }
      return true;
    }
  };
} }

#endif
