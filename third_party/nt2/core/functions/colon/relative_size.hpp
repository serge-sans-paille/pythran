//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COLON_RELATIVE_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COLON_RELATIVE_SIZE_HPP_INCLUDED

#include <nt2/core/functions/relative_size.hpp>
#include <nt2/core/container/colon/category.hpp>
#include <nt2/core/functions/details/colon.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Compute indexing size using _
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_size_, tag::cpu_
                            , (Idx)(Arity)(Size)(Base)
                            , ((expr_ < colon_< Idx >
                                      , nt2::tag::terminal_
                                      , Arity
                                      >
                              ))
                              (scalar_< unspecified_<Size> >)
                              (scalar_< unspecified_<Base> >)
                            )
  {
    typedef Size result_type;

    BOOST_FORCEINLINE result_type
    operator()(const Idx&, const Size& sz, const Base&) const
    {
      return sz;
    }
  };

  //============================================================================
  // Compute indexing size using relative mark-up (begin_ and/or end_)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_size_, tag::cpu_
                            , (Idx)(Size)(Base)
                            , ((node_ < Idx
                                      , nt2::tag::relative_colon_
                                      , boost::mpl::long_<1>
                                      ,nt2::container::domain>
                              ))
                              (scalar_< unspecified_<Size> >)
                              (scalar_< unspecified_<Base> >)
                            )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE result_type
    operator()(const Idx& i, const Size& sz, const Base& b) const
    {
      return  details::
              unity_colon_size( boost::proto::value(boost::proto::child_c<0>(i))
                                .lower( b, sz)
                              , boost::proto::value(boost::proto::child_c<0>(i))
                                .upper( b,sz)
                              );
    }
  };

  //============================================================================
  // Compute indexing size using relative mark-up (begin_,end_) and stride
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::relative_size_, tag::cpu_
                            , (Idx)(Size)(Base)
                            , ((node_ < Idx
                                      , nt2::tag::relative_colon_
                                      , boost::mpl::long_<2>
                                      ,nt2::container::domain>
                              ))
                              (scalar_< unspecified_<Size> >)
                              (scalar_< unspecified_<Base> >)
                            )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE result_type
    operator()(const Idx& i, const Size& sz, const Base& b) const
    {
      return  details::
              colon_size( boost::proto::value(boost::proto::child_c<0>(i))
                          .lower(b,sz)
                        , boost::proto::value(boost::proto::child_c<1>(i))
                        , boost::proto::value(boost::proto::child_c<0>(i))
                          .upper(b,sz)
                        );
    }
  };
} }

#endif
