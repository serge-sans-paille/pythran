//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_VIEW_SHARED_VIEW_HPP_INCLUDED
#define NT2_CORE_CONTAINER_VIEW_SHARED_VIEW_HPP_INCLUDED

#include <nt2/sdk/memory/container_ref.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>
#include <nt2/core/container/view/adapted/shared_view.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>

namespace nt2 { namespace container
{
  template<class Expression, class ResultType> struct expression;

  /* shared_view; an expression of a container_shared_ref terminal.
   * allows construction from an expression of a container_shared_ref terminal */
  template<typename Kind, typename T, typename S>
  struct shared_view
       :  expression< boost::proto
          ::basic_expr< boost::proto::tag::terminal
                      , boost::proto::term< memory
                             ::container_shared_ref<Kind,T,S,false>
                                          >
                      , 0l
                      >
                    , memory::container<Kind,T,S>&
                    >
  {
    typedef memory::container_shared_ref< Kind, T, S, false >   container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal
                                    , boost::proto::term<container_ref>
                                    , 0l
                                    >                     basic_expr;
    typedef memory::container<Kind,T,S>&                  container_type;
    typedef expression<basic_expr, container_type>        nt2_expression;

    typedef typename container_ref::iterator              iterator;
    typedef typename container_ref::const_iterator        const_iterator;

    iterator begin()  const { return boost::proto::value(*this).begin(); }
    iterator end()    const { return boost::proto::value(*this).end();   }

    BOOST_FORCEINLINE
    shared_view()
    {
    }

    BOOST_FORCEINLINE
    shared_view( nt2_expression const& expr )
                     : nt2_expression(expr)
    {
    }

    template<class Xpr>
    BOOST_FORCEINLINE
    shared_view( Xpr const& expr )
                     : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    template<class Xpr>
    void reset(Xpr const& other)
    {
      shared_view tmp(other);
      boost::proto::value(*this) = boost::proto::value(tmp);
      this->size_ = tmp.size_;
    }


    //==========================================================================
    // Enable base expression handling of assignment
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<nt2_expression, Xpr>
                              , shared_view&
                              >::type
    operator=(Xpr const& xpr)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE
    shared_view& operator=(shared_view const& xpr)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<nt2_expression, Xpr>
                              , shared_view const&
                              >::type
    operator=(Xpr const& xpr) const
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE
    shared_view const& operator=(shared_view const& xpr) const
    {
      nt2_expression::operator=(xpr);
      return *this;
    }
  };

  template<typename Kind, typename T, typename S>
  struct shared_view<Kind, T const, S>
       : expression <  boost::proto::basic_expr
                      < boost::proto::tag::terminal
                      , boost::proto::term
                        <memory::container_shared_ref<Kind, T const, S, false>
                      >
                    , 0l
                    >
                   , memory::container<Kind,T,S> const&
                   >
  {
    typedef memory::container_shared_ref<Kind, T const, S, false >   container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal
                                    , boost::proto::term<container_ref>
                                    , 0l
                                    >                           basic_expr;
    typedef memory::container<Kind,T,S> const&                      container_type;
    typedef expression<basic_expr, container_type>              nt2_expression;

    typedef typename container_ref::iterator                    iterator;
    typedef typename container_ref::const_iterator              const_iterator;

    iterator begin()  const { return boost::proto::value(*this).begin(); }
    iterator end()    const { return boost::proto::value(*this).end();   }

    BOOST_FORCEINLINE
    shared_view()
    {
    }

    BOOST_FORCEINLINE
    shared_view( nt2_expression const& expr )
                     : nt2_expression(expr)
    {
    }

    template<class Xpr>
    shared_view( Xpr const& expr )
                     : nt2_expression(basic_expr::make(boost::proto::value(expr)))
    {
    }

    template<class Xpr>
    BOOST_FORCEINLINE
    void reset(Xpr const& other)
    {
      shared_view tmp(other);
      boost::proto::value(*this) = boost::proto::value(tmp);
      this->size_ = tmp.size_;
    }

    //==========================================================================
    // Enable base expression handling of assignment
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<nt2_expression, Xpr>
                              , shared_view&
                              >::type
    operator=(Xpr const& xpr)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE
    shared_view& operator=(shared_view const& xpr)
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<nt2_expression, Xpr>
                              , shared_view const&
                              >::type
    operator=(Xpr const& xpr) const
    {
      nt2_expression::operator=(xpr);
      return *this;
    }

    BOOST_FORCEINLINE
    shared_view const& operator=(shared_view const& xpr) const
    {
      nt2_expression::operator=(xpr);
      return *this;
    }
  };
} }

namespace nt2
{
  using nt2::container::shared_view;
}

#endif
