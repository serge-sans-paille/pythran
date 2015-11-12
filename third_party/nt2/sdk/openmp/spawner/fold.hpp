//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPENMP_SPAWNER_FOLD_HPP_INCLUDED
#define NT2_SDK_OPENMP_SPAWNER_FOLD_HPP_INCLUDED

#if defined(_OPENMP) && _OPENMP >= 200203 /* OpenMP 2.0 */

#include <omp.h>
#include <nt2/sdk/shared_memory/spawner.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2
{
  namespace tag
    {
      struct fold_;
      template<class T> struct openmp_;
    }

  template<class Site, class result_type>
  struct spawner< tag::fold_, tag::openmp_<Site> , result_type>
  {

    spawner() {}

    template<typename Worker>
    result_type operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t grain)
    {

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

      BOOST_ASSERT_MSG( size % grain == 0, "Reduce size not divisible by grain");
      std::ptrdiff_t nblocks  = size/grain;
      result_type reduced_out = w.neutral_(nt2::meta::as_<result_type>());

      #pragma omp parallel
      {
        // Dispatch group of blocks over each threads
        #pragma omp for schedule(static)
        for(std::ptrdiff_t n=0;n<nblocks;++n)
        {
          result_type out = w.neutral_(nt2::meta::as_<result_type>());

#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
            // Call operation
            out = w(out,begin+(std::size_t)n*grain,grain);

            #pragma omp critical
            reduced_out = w.bop_(reduced_out, out);

#ifndef BOOST_NO_EXCEPTIONS
          }
          catch(...)
          {

            #pragma omp critical
            exception = boost::current_exception();
          }
#endif

         }
      }

      return reduced_out;
    }
  };
}

#endif
#endif
