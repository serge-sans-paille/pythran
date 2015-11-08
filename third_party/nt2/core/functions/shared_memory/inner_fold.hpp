//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SHARED_MEMORY_INNER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SHARED_MEMORY_INNER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/transform.hpp>
#include <nt2/core/functions/inner_fold.hpp>
#include <nt2/sdk/shared_memory/shared_memory.hpp>
#include <nt2/sdk/shared_memory/worker/inner_fold.hpp>
#include <nt2/sdk/shared_memory/spawner.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::inner_fold_, (nt2::tag::shared_memory_<BackEnd,Site>)
                             , (Out)(In)(Neutral)(Bop)(Uop)(BackEnd)(Site)
                             , ((ast_< Out, nt2::container::domain>))
                               ((ast_< In, nt2::container::domain>))
                               (unspecified_<Neutral>)
                               (unspecified_<Bop>)
                               (unspecified_<Uop>)
                             )
  {
    typedef void                                                              result_type;
    typedef typename boost::remove_reference<In>::type::extent_type           extent_type;
    typedef typename Out::value_type                                          value_type;

    BOOST_FORCEINLINE result_type
    operator()(Out& out, In& in, Neutral const& neutral, Bop const& bop, Uop const& uop) const
    {

      extent_type ext = in.extent();
      std::size_t bound  = boost::fusion::at_c<0>(ext);
      std::size_t obound = nt2::numel(boost::fusion::pop_front(ext));
      std::size_t top_cache_line_size = config::top_cache_line_size(2)/sizeof(value_type);
      std::size_t grain = top_cache_line_size;

      nt2::worker<tag::inner_fold_,BackEnd,Site,Out,In,Neutral,Bop,Uop>
      w(out, in, neutral, bop, uop);

      if((obound > grain) && (8*grain < bound*obound))
      {
        nt2::spawner< tag::transform_, BackEnd > s;
        s(w,0,obound,grain);
      }

      else
      w(0,obound);

    }

  };
} }

#endif

