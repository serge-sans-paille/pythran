//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_WORKER_INNER_SCAN_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_WORKER_INNER_SCAN_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker.hpp>
#include <nt2/sdk/shared_memory/spawner.hpp>
#include <nt2/core/functions/details/scan_step.hpp>

#include <nt2/include/functor.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <boost/simd/sdk/simd/native.hpp>

namespace nt2
{

  namespace tag
  {
    struct inner_scan_step_;
    struct scan_;
  }

  // Inner Scan Step worker
  template<class BackEnd, class Site, class Out, class In, class Neutral, class Bop>
  struct worker<tag::inner_scan_step_,BackEnd,Site,Out,In,Neutral,Bop>
  {
    worker(Out& out, In & in, Neutral const & neutral, Bop const & bop)
          :out_(out),in_(in),neutral_(neutral),bop_(bop)
    {}

    template<class Summary>
    Summary operator()(Summary summary, std::size_t begin, std::size_t size, bool prescan)
    {
      return details::scan_step(summary,out_,in_,bop_,begin,size,1,prescan);
    };

    Out & out_;
    In & in_;
    Neutral const & neutral_;
    Bop const & bop_;

    private:
    worker& operator=(worker const&);
  };

  // Inner Scan worker
  template<class BackEnd,class Site, class Out, class In, class Neutral,class Bop>
  struct worker<tag::inner_scan_,BackEnd,Site,Out,In,Neutral,Bop>
  {
    typedef typename boost::remove_reference<In>::type::extent_type           extent_type;
    typedef typename Out::value_type                                          value_type;

    worker(Out& out, In& in, Neutral const& n, Bop const& bop)
    : out_(out), in_(in), neutral_(n), bop_(bop)
    {}

    void operator()(std::size_t begin, std::size_t size) const
    {
      extent_type ext = in_.extent();
      std::size_t top_cache_line_size = config::top_cache_line_size(2)/sizeof(value_type);
      std::size_t grain  = top_cache_line_size;

      std::size_t ibound  = boost::fusion::at_c<0>(ext);
      std::size_t iibound = (ibound/grain) * grain;
      std::size_t obound = nt2::numel(boost::fusion::pop_front(ext));

      nt2::worker<tag::inner_scan_step_,BackEnd,Site,Out,In,Neutral,Bop>
      w(out_,in_,neutral_,bop_);

      nt2::spawner<tag::scan_, BackEnd, value_type> s;

      for(std::size_t j = begin, k=begin*ibound; j < begin+size; ++j, k+=ibound)
      {
        value_type s_out = neutral_(nt2::meta::as_<value_type>());

        if( (size == obound) && (8*grain < iibound) )
          s_out = s( w, k, iibound, grain );

        else if( iibound != 0 )
          s_out = w(s_out, k, iibound, false);

        w(s_out, k+iibound, ibound -iibound, false);
      }
    }

    Out&                     out_;
    In&                      in_;
    Neutral const &          neutral_;
    Bop const &              bop_;

    private:
    worker& operator=(worker const&);
   };

}
#endif
