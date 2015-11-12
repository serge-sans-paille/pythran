//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_WORKER_OUTER_SCAN_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_WORKER_OUTER_SCAN_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker.hpp>
#include <nt2/sdk/shared_memory/worker/outer_scan_step.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{

  namespace tag
  {
    struct outer_scan_;
  }

  // Outer Fold worker
  template<class BackEnd, class Site, class Out, class In, class Neutral,class Bop,class Uop>
  struct worker<tag::outer_scan_,BackEnd,Site,Out,In,Neutral,Bop,Uop>
  {
      typedef typename boost::remove_reference<In>::type::extent_type extent_type;
      typedef typename Out::value_type value_type;

      worker(Out& out, In& in, Neutral const& n, Bop const& bop, Uop const& uop)
      : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
      {}

      void operator()(std::size_t begin, std::size_t size) const
      {
        extent_type ext = in_.extent();
        std::size_t ibound = boost::fusion::at_c<0>(ext);
        std::size_t mbound = boost::fusion::at_c<1>(ext);
        std::size_t obound = boost::fusion::at_c<2>(ext);
        std::size_t iboundxmbound =  ibound * mbound;

        std::size_t cache_line_size = nt2::config::top_cache_line_size(2); // in byte
        std::size_t grain  = cache_line_size;

        // Compute the lower multiple of grain of mbound
        std::size_t mmbound =  (mbound/grain)*grain;

         if( ibound < grain )
         {
          // Instanciate the spawner/worker associated to the mbound dimension

          nt2::spawner<tag::scan_, BackEnd, value_type> s;

          for(std::size_t o = 0, o_ = begin * iboundxmbound;
              o < size;
              ++o, o_+= iboundxmbound)
          {
            for(std::size_t i = 0,  i_ = o_;
                i < ibound;
                ++i, ++i_)
            {

              nt2::worker<tag::outer_scan_step_outcache_,BackEnd,Site,Out,In,Neutral,Bop>
              w(out_,in_,neutral_,bop_,i_);

              value_type s_out = neutral_(nt2::meta::as_<value_type>());

              if( (size == obound) && (grain < mmbound) )
               s_out = s( w, 0, mmbound, grain);

              else if (mmbound != 0)
               s_out = w(s_out, 0, mmbound, false);

              s_out = w(s_out, mmbound, mbound-mmbound, false);
            }
          }
         }

         else
         {
           // Instanciate the spawner/worker associated to the ibound dimension
           nt2::spawner<tag::transform_, BackEnd> s;

           for(std::size_t o = 0, o_ = begin * iboundxmbound;
               o < size;
               ++o, o_+= iboundxmbound)
           {
             nt2::worker<tag::outer_scan_step_incache_,BackEnd,Site,Out,In,Neutral,Bop>
             w(out_,in_,neutral_,bop_, o_);

             if( size == obound )
               s(w,0,ibound,grain);

             else
               w(0,ibound);
           }
         }
      }

      Out&                     out_;
      In&                      in_;
      Neutral const &          neutral_;
      Bop const &              bop_;
      Uop const &              uop_;

      private:
      worker& operator=(worker const&);
   };

}
#endif
