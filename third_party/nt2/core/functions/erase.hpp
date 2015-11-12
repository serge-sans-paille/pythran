//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ERASE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ERASE_HPP_INCLUDED

#include <nt2/include/functions/function_index.hpp>
#include <nt2/include/functions/along_index.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/core/functions/aggregate.hpp>
#include <nt2/sdk/parameters.hpp>

namespace nt2
{
  template<std::size_t N, class A, class Phi>
  void erase_impl(A& a, Phi const& phi)
  {
    std::size_t m = nt2::numel(phi);
    if(!m)
      return;

    std::size_t j = nt2::run(phi, 0u, meta::as_<std::size_t>());
    std::size_t k = 0u;
    std::size_t i = 0u;

    typename A::value_type* p = a.raw();
    std::size_t n = nt2::numel(a);

    for(; i != n; ++i)
    {
      if(i != j)
      {
        p[k++] = p[i];
      }
      else
      {
        if(i-k+1 < m)
        {
          j = nt2::run(phi, i-k+1, meta::as_<std::size_t>());
        }
        else
        {
          ++i;
          break;
        }
      }
    }
    for(; i != n; ++i)
      p[k++] = p[i];

    // compute size: if only one size changes (+ trailing ones) then keep the shape, otherwise linearize
    typedef typename nt2::make_size<N>::type size_type;
    size_type sz     = a.extent();
    size_type phi_sz = phi.extent();

    std::ptrdiff_t found = -1;
    for(i=0; i!=sz.size(); ++i)
    {
      if(phi_sz[i] != sz[i])
      {
        if(found == -1)
        {
          sz[i] -= phi_sz[i];
          found = i;
        }
        else
        {
          found = -1;
          break;
        }
      }
    }

    if(found == -1 || found == 0)
      sz = nt2::of_size(1u, k);
    a.resize(sz);
  }

  template<class A, class Idx>
  void erase(A& a, Idx const& idx)
  {
    nt2::erase_impl<Idx::proto_arity_c>(a, nt2::function_index(idx, a.extent(), meta::as_<typename A::indexes_type>()));
  }

  template<class A, class Idx>
  void erase(A& a, Idx const& idx, std::size_t dim)
  {
    nt2::erase_impl<NT2_MAX_DIMENSIONS>(a, nt2::along_index(idx, dim, a.extent()));
  }
}

#endif
