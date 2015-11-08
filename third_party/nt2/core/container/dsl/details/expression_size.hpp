//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_EXPRESSION_SIZE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_EXPRESSION_SIZE_HPP_INCLUDED

#include <nt2/core/container/dsl/size.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>

namespace nt2 { namespace container
{
  template<typename Sizes, typename Enable = void>
  struct expression_size
  {
    BOOST_FORCEINLINE expression_size(Sizes const& size) : size_(size)
    {}

    template<typename Base, typename Expr> BOOST_FORCEINLINE
    expression_size ( Base const&, Expr const& expr )
                    : size_(expr.size_.size_)
    {}

    Sizes size_;

    BOOST_FORCEINLINE Sizes const& data() const { return size_; }
  };

  template<typename Sizes>
  struct expression_size< Sizes
                        , typename boost::
                                   enable_if< boost::is_reference<Sizes> >::type
                        >
  {
    typedef typename boost::remove_reference<Sizes>::type Sizes_;

    BOOST_FORCEINLINE expression_size(Sizes size) : size_(&size)
    {}

    template<typename Base, typename Expr>
    BOOST_FORCEINLINE
    expression_size ( Base const& base, Expr const& )
                    : size_(&size_transform<domain>()(base))
    {}

    Sizes_* size_;

    BOOST_FORCEINLINE Sizes_& data() const { return *size_; }
  };
} }

#endif
