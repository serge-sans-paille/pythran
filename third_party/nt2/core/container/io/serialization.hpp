//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_IO_SERIALIZATION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_IO_SERIALIZATION_HPP_INCLUDED

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/fusion.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl/expression.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/sdk/parameters.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/numel.hpp>

namespace boost { namespace serialization
{
  //==========================================================================
  // First entry point of the serialization in table<T,S>
  //==========================================================================
  template<class Archive, class T, class S, class D>
  void save( Archive & ar, const nt2::container::table<T,S,D>& t
           , unsigned int const& version
           )
  {
    typedef typename nt2::container::table<T,S,D>::parent expression_type;
    ar << boost::serialization::base_object< const expression_type >(t);
  }

  template<class Archive, class T, class S, class D>
  void load( Archive & ar, nt2::container::table<T,S,D>& t
           , unsigned int const& version)
  {
    typedef typename nt2::container::table<T,S,D>::parent expression_type;
    ar >> boost::serialization::base_object< expression_type >(t);
  }

  template<class Archive, class T, class S, class D>
  inline void serialize( Archive & ar, nt2::container::table<T,S,D>& t
                       , unsigned int const& file_version)
  {
    split_free(ar, t, file_version);
  }

  //==========================================================================
  // Down in expression, serialized its extent member
  //==========================================================================
  template<class Archive, class E, class R, class D>
  void save( Archive& ar, const nt2::container::expression<E,R,D>& e
           , unsigned int const& version
           , typename boost::enable_if< typename boost::mpl::equal_to<
               typename boost::proto::arity_of<E>
             , boost::mpl::int_<0> >
             >::type* dummy = 0
           )
  {
    BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<E>::value == 0)
                        , NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL
                        , (E)
                        );
    typedef typename nt2::container::expression<E,R,D>::extent_type e_t;
    typedef typename nt2::meta::strip<e_t>::type size_type;
    size_type size_ = e.extent();
    ar << size_;
    ar << make_array(e.raw(), nt2::numel(e));
  }

  template<class Archive, class E, class R, class D>
  void load( Archive& ar, nt2::container::expression<E,R,D>& e
           , unsigned int const& version
           , typename boost::enable_if< typename boost::mpl::equal_to<
                 typename boost::proto::arity_of<E>
               , boost::mpl::int_<0> >
             >::type* dummy = 0
           )
  {
    BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<E>::value == 0)
                        , NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL
                        , (E)
                        );
    typedef typename nt2::container::expression<E,R,D>::extent_type e_t;
    typedef typename nt2::meta::strip<e_t>::type size_type;
    size_type size_;
    ar >> size_;
    e.resize(size_);
    ar >> make_array(e.raw(), nt2::numel(e));
  }

  template<class Archive, class E, class R, class D>
  inline void serialize( Archive& ar
                       , nt2::container::expression<E,R,D>& e
                       , unsigned int const& file_version
                       )
  {
    split_free(ar, e, file_version);
  }

  //==========================================================================
  // Serialization of proto expression:
  //==========================================================================
  template<class Archive>
  struct saver_
  {
    typedef Archive archive_type;
    explicit saver_(archive_type& a) : ar(a) {}
    template<class Terminal>
    void operator()(Terminal const& t) const
    { ar << t; }
    archive_type& ar;
  };

  template<class Archive, class E, class R, class D>
  void save( Archive& ar, const nt2::container::expression<E,R,D>& e
           , unsigned int const& version
           , typename boost::enable_if< typename boost::mpl::not_equal_to<
               typename boost::proto::arity_of<E>
             , boost::mpl::int_<0> >
             >::type* dummy = 0
           )
  {
   BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<E>::value != 0)
                        ,  NT2_INVALID_ACCESS_TO_EXPRESSION_NODES_ON_NON_EXPRESSION
                        , (E)
                        );

    typedef typename proto::result_of::
    flatten< const nt2::container::expression<E,R,D> >::type sequence_type;
    saver_<Archive> save_terminals_(ar);
    sequence_type terminals = boost::proto::flatten(e);
    boost::fusion::for_each(terminals,save_terminals_);
  }

  template<class Archive>
  struct loader_
  {
    typedef Archive archive_type;
    explicit loader_(archive_type& a) : ar(a) {}
    template<class Terminal>
    void operator()(Terminal& t) const
    { ar >> t; }
    archive_type& ar;
  };

  template<class Archive, class E, class R, class D>
  void load( Archive& ar, nt2::container::expression<E,R,D>& e
           , unsigned int const& version
           , typename boost::enable_if< typename boost::mpl::not_equal_to<
               typename boost::proto::arity_of<E>
             , boost::mpl::int_<0> >
             >::type* dummy = 0
           )
  {
    BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<E>::value != 0)
                        , NT2_INVALID_ACCESS_TO_EXPRESSION_NODES_ON_NON_EXPRESSION
                        , (E)
                        );

    typedef typename proto::result_of::
    flatten< nt2::container::expression<E,R,D>& >::type sequence_type;
    sequence_type terminals = boost::proto::flatten(e);
    loader_<Archive> load_terminals_(ar);
    boost::fusion::for_each(terminals,load_terminals_);
  }

  //==========================================================================
  // Down in extent, serialization of struct of_size_
  //==========================================================================
  template<class Archive, BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  void save( Archive& ar
           , const nt2::of_size_< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D) >& of
           , unsigned int const& version)
  {
    ar << of.data_;
  }

  template<class Archive, BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  void load( Archive& ar
           , nt2::of_size_< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D) >& of
           , unsigned int const& version)
  {
    ar >> of.data_;
  }

  template<class Archive, BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  inline void serialize( Archive& ar
                       , nt2::of_size_< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D) >& of
                       , unsigned int const& file_version)
  {
    split_free(ar, of, file_version);
  }
} }

#endif
