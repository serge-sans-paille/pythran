//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_MNORMEST_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_MNORMEST_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_mnormest mnormest
 *
 * \par Description
 * norm estimate
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mnormest.hpp>
 * \endcode
 *
 * normest name is here for Matlab naming compatibility
 * but mnormest is an estimate of mnorm (the 2-norm of the matrix).
 *
 * This function may be useful for large, full matrices.
 *
 * n = normest(a) returns an estimate of the 2-norm of the matrix S.
 *
 * n = normest(a,tol) uses relative error tol instead of the default tolerance 1.e-6.
 * The value of tol determines when the estimate is considered acceptable.
 *
 * normest(..., cnt) returns an estimate of the 2-norm and also gives
 *  in cnt the number of power iterations used.
 *
 * The tol default is sqrt(eps) for the current type used.
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag mnormest_ of functor mnormest
     *        in namespace nt2::tag for toolbox algebra
     **/
    struct mnormest_ :  tag::formal_ { typedef tag::formal_ parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnormest_, mnormest, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnormest_, mnormest, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mnormest_, mnormest,(A0 const&)(A1&),2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mnormest_, mnormest,(A0 const&)(A1 const&)(A2&),3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnormest_, normest, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::mnormest_, normest, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mnormest_, normest,(A0 const&)(A1&),2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::mnormest_, normest,(A0 const&)(A1 const&)(A2&),3)

}

#endif

