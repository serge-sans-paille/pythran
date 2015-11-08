//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_JORDBLOC_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_JORDBLOC_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/constants/one.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_jordbloc jordbloc
 *
 * \par Description
 * jordbloc matrix
 * is the n-by-n jordan block
 *   with eigenvalue lambda.  lambda = 1 is the default.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/jordbloc.hpp>
 * \endcode
 *
**/
//==============================================================================
// jordbloc actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag jordbloc_ of functor jordbloc
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct jordbloc_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::jordbloc_, jordbloc, 2)

  template<class T, class A0>
  typename meta::call<tag::jordbloc_(const A0 &, const T &)>::type
  jordbloc(const A0& n)
  {
    return nt2::jordbloc(n, nt2::One<T>());
  }
  template<class A0, class A1,  class Target>
  typename meta::call<tag::jordbloc_(const A0 &, typename Target::type const &)>::type
  jordbloc(const A0& n, const A1& lambda, const Target&)
  {
    typedef typename Target::type t_t;
    return nt2::jordbloc(n,t_t(lambda));
  }

}

#endif
