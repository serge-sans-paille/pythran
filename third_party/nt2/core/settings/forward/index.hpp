//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_INDEX_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_INDEX_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/vector_c.hpp>
#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace nt2
{
  #define M0(z,n,t)                                                   \
  std::ptrdiff_t BOOST_PP_CAT(I,BOOST_PP_INC(n)) = BOOST_PP_CAT(I,n)  \
  /**/

  //============================================================================
  /*! index<I0,...,In> represents the base index over the Nth dimensions. By
   * default, index<I0> is equivalent to index<I0,I0,...,I0>.
   *
   * \tparam ID 32 byte multi-bytes character unique identifier
   **/
  //============================================================================
  template< std::ptrdiff_t I0 = NT2_DEFAULT_INDEX
          , BOOST_PP_ENUM(BOOST_PP_DEC(NT2_MAX_DIMENSIONS),M0,~)
          >
  struct  index_
  {
    typedef
    BOOST_PP_CAT(BOOST_PP_CAT(boost::mpl::vector,NT2_MAX_DIMENSIONS),_c)
              < std::ptrdiff_t
              , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,I)
              >                                                  index_type;
  };

  #undef M0

  //============================================================================
  /*!
   * C-style base index options. By using it, all indexes start at 0
   **/
  //============================================================================
  typedef index_<0> C_index_;

  //============================================================================
  /*!
   * Matlab style base index options. By using it, all indexes start at 1
   **/
  //============================================================================
  typedef index_<1> matlab_index_;

  namespace tag
  {
    //==========================================================================
    /*!
     * Option tag for the base index options
     **/
    //==========================================================================
    struct index_;
  }
}

#endif
