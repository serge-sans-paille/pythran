//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_MAKE_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_MAKE_SIZE_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/table/details/is_definitely_vector.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/relative_size.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/at.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2 { namespace tag
{
  struct relative_colon_;
} }

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// Build a of_size for size_of
  template< int N
          , class Domain
          , class Shape
          , class Sizes, class Bases
          , class Children
          >
  struct make_size;
                                                                                                   \
  #define M1(z,n,t)                                                                                \
  mpl_value                                                                                        \
  < typename meta::                                                                                \
    call< tag::relative_size_                                                                      \
        ( typename  boost::proto::result_of::child_c<Children, n>::type                            \
        , typename  boost::fusion::result_of::                                                     \
                    at_c<typename meta::strip<Sizes>::type, n>::type                               \
        , typename  boost::fusion::result_of::                                                     \
                    at_c<typename meta::strip<Bases>::type, n>::type                               \
        )                                                                                          \
        >::type                                                                                    \
  >::value                                                                                         \
  /**/

  #define M2(z,n,t)                                                                                \
  that[n] = nt2::relative_size( boost::proto::child_c<n>(children)                                 \
                              , boost::fusion::at_c<n>(sz)                                         \
                              , boost::fusion::at_c<n>(bs)                                         \
                              );                                                                   \
  /**/

  #define M4(t) t
  #define M5(t)

  #define M3(z,n,t)                                                                                \
  template<class Dummy>                                                                            \
  struct impl<n, Dummy>                                                                            \
  {                                                                                                \
    BOOST_FORCEINLINE                                                                              \
    static result_type call(  Sizes    const& BOOST_PP_IF(n,M4,M5)(sz)                             \
                            , Bases    const& BOOST_PP_IF(n,M4,M5)(bs)                             \
                            , Children const& BOOST_PP_IF(n,M4,M5)(children)                       \
                            )                                                                      \
    {                                                                                              \
      result_type that;                                                                            \
      BOOST_PP_REPEAT(n, M2, t)                                                                    \
      return that;                                                                                 \
    }                                                                                              \
  };                                                                                               \
  /**/

  #define M0(z,n,t)                                                                                \
  template< class Domain                                                                           \
          , class Shape, class Sizes, class Bases                                                  \
          , class Children                                                                         \
          >                                                                                        \
  struct make_size<n, Domain, Shape, Sizes, Bases, Children>                                       \
  {                                                                                                \
    typedef of_size_<BOOST_PP_ENUM(n, M1, n)> result_type;                                         \
                                                                                                   \
    template<int N, class Dummy = void>                                                            \
    struct impl {};                                                                                \
                                                                                                   \
    BOOST_PP_REPEAT(BOOST_PP_INC(n), M3, n)                                                        \
                                                                                                   \
    BOOST_FORCEINLINE result_type                                                                  \
    operator()(Shape const&, Sizes const& s, Bases const& b, Children const& children) const       \
    {                                                                                              \
      return impl<result_type::static_size>::call(s, b, children);                                 \
    }                                                                                              \
  };                                                                                               \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2, BOOST_PP_INC(NT2_MAX_DIMENSIONS), M0, ~)
  #undef M0
  #undef M1
  #undef M2
  #undef M3
  #undef M4
  #undef M5

  template< class Domain
          , class Shape, class Sizes, class Bases
          , class Children
          >
  struct make_size<1, Domain, Shape, Sizes, Bases, Children>
  {
    typedef typename boost::proto::result_of::child_c<Children&, 0>::value_type::extent_type idx0_sz;
    static const std::size_t shape_min = Shape::static_size > 2u ? 2u : Shape::static_size;
    static const std::size_t size_max = idx0_sz::static_size > shape_min ? idx0_sz::static_size : shape_min;
    typedef typename nt2::make_size<size_max>::type size_max_type;

    typedef typename boost::mpl::
            if_< boost::mpl::and_ < is_definitely_vector<Shape>
                                  , is_definitely_vector<idx0_sz>
                                  >
               , typename boost::mpl::if_c< Shape::static_size == 1u
                                          , nt2::of_size_<-1>
                                          , nt2::of_size_<1, -1>
                                          >::type
               , typename boost::mpl::
                 if_< boost::mpl::or_ < is_definitely_not_vector<Shape>
                                      , is_definitely_not_vector<idx0_sz>
                                      >
                    , idx0_sz
                    , size_max_type
                    >::type
               >::type                                result_type;

    BOOST_FORCEINLINE result_type
    operator()( Shape const& shp, Sizes const& sz
              , Bases const& bs, Children const& children
              ) const
    {
      std::size_t s = nt2::relative_size( boost::proto::child_c<0>(children)
                                        , boost::fusion::at_c<0>(sz)
                                        , boost::fusion::at_c<0>(bs)
                                        );

      // Select shorter computation if relactive_colon is involved
      typedef boost::is_same< typename Children::proto_child0::proto_tag
                            , nt2::tag::relative_colon_
                            > select_t;

      return eval(shp,children,s,typename select_t::type());
    }

    BOOST_FORCEINLINE result_type
    eval( Shape const& shp, Children const& children, std::size_t s
        , boost::mpl::false_ const&
        ) const
    {
      idx0_sz const& idx0 = boost::proto::child_c<0>(children).extent();
      std::size_t n = nt2::ndims(shp);
      std::size_t m = nt2::ndims(idx0);

      bool idx0_vector  =   (m == 1u)
                        ||  ( m == 2u && boost::fusion::at_c<0>(idx0) == 1u);

      // column vector
      if(idx0_vector && n == 1u) return nt2::of_size(s);

      // row vector
      if(idx0_vector && n == 2u && boost::fusion::at_c<0>(shp) == 1u)
        return nt2::of_size(1u, s);

      // Else return the extent
      return boost::proto::child_c<0>(children).extent();
    }

    BOOST_FORCEINLINE result_type
    eval( Shape const&, Children const&
        , std::size_t s, boost::mpl::true_ const&
        ) const
    {
      return nt2::of_size(1u, s);
    }
  };
} }

#endif
