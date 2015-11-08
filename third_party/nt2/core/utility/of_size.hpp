//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_HPP_INCLUDED

#include <nt2/core/settings/forward/size.hpp>
#include <nt2/core/settings/forward/storage_duration.hpp>
#include <nt2/core/utility/of_size/fusion.hpp>
#include <nt2/core/utility/fusion.hpp>
#include <nt2/core/functions/scalar/numel.hpp>
#include <nt2/sdk/memory/copy.hpp>
#include <nt2/sdk/meta/is_iterator.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/include/out.hpp>
#include <boost/array.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/assert.hpp>
#include <cstddef>
#include <iterator>
#include <functional>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
#ifdef NT2_OF_SIZE_USE_PROXY
  template<class Sz>
  struct of_size_proxy
  {
    of_size_proxy(Sz& sz_, std::size_t i_)
     : value(sz_.data()+i_), i(i_)
    {
      BOOST_ASSERT_MSG( i < Sz::static_size, "Out of range access in size" );
    }

    operator std::size_t const&() const
    {
      return *value;
    }

    of_size_proxy& operator=(std::size_t value_)
    {
      BOOST_ASSERT_MSG( static_value(i) < 0 || static_value(i) == value_, "Dimension in size different from static value" );
      *value = value_;
      return *this;
    }

    of_size_proxy& operator=(of_size_proxy const& other)
    {
      return *this = static_cast<std::size_t>(other);
    }

  private:
    #define M1(z, n, t) case n: return boost::mpl::at_c<typename Sz::values_type, n>::type::value;
    #define M0(z, n, t)                                                        \
    static std::ptrdiff_t static_value(std::size_t i, boost::mpl::long_<n>)    \
    {                                                                          \
      switch(i)                                                                \
      {                                                                        \
        BOOST_PP_REPEAT(n, M1, ~)                                              \
      }                                                                        \
      return 0;                                                                \
    }                                                                          \
    /**/
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(NT2_MAX_DIMENSIONS), M0, ~)
    #undef M1
    #undef M0

    static std::ptrdiff_t static_value(std::size_t i)
    {
      return static_value(i, boost::mpl::long_<Sz::static_size>());
    }

    std::size_t* value;
    std::size_t i;
  };
#endif

  namespace tag { struct of_size_; }

  //============================================================================
  /*!
   * \c of_size_ is a thin buffer containing values of a dimensions set in an
   * hybrid static/dynamic way.
   **/
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  struct of_size_
  {
    typedef of_size_                            of_size_type;

    typedef tag::of_size_                       fusion_tag;
    typedef boost::fusion::fusion_sequence_tag  tag;

    typedef std::size_t                           value_type;
#ifdef NT2_OF_SIZE_USE_PROXY
    typedef of_size_proxy<of_size_>               reference;
#else
    typedef std::size_t&                          reference;
#endif
    typedef std::size_t const&                    const_reference;
    typedef std::size_t*                          iterator;
    typedef std::size_t const*                    const_iterator;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    //==========================================================================
    // Count non-trivial size values
    //==========================================================================
    #define M0(z,n,t)                                                          \
    : BOOST_PP_CAT(D, BOOST_PP_DEC(BOOST_PP_SUB(NT2_MAX_DIMENSIONS, n))) != 1  \
    ? BOOST_PP_SUB(NT2_MAX_DIMENSIONS, n)

    static const std::size_t
      static_size = 0 ? 0 BOOST_PP_REPEAT(NT2_MAX_DIMENSIONS,M0,~) : 0
    ;
    #undef M0

    //==========================================================================
    // Check if size is entirely known at compile-time
    //==========================================================================
    #define M0(z,n,t) && (BOOST_PP_CAT(D,n) >= 0)
    static const std::size_t
      static_status = (D0 >= 0)
                      BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_DIMENSIONS,M0,~)
    ;
    #undef M0

    //==========================================================================
    // Compute its potential compile-time numel
    //==========================================================================
    #define M0(z,n,t) * (BOOST_PP_CAT(D,n) >= 0 ? BOOST_PP_CAT(D,n) : 1)
    static const std::size_t
      static_numel = (D0 >= 0 ? D0 : 1)
                      BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_DIMENSIONS,M0,~)
    ;
    #undef M0

    //==========================================================================
    // Static size values used internally by MPL/Fusion
    //==========================================================================
    typedef boost::mpl::
            vector_c< std::ptrdiff_t
                    , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)
                    >                                               values_type;

    //==========================================================================
    // Storage Size informations
    //==========================================================================
    typedef boost::mpl::integral_c< std::size_t
                                  , (static_status ? static_numel : 0ULL)
                                  >                           storage_size_type;

    typedef typename boost::mpl::if_c < static_status
                                      , automatic_
                                      , dynamic_
                                      >::type             storage_duration_type;

    //==========================================================================
    // Size values storage
    //==========================================================================
    boost::array<std::size_t,static_size> data_;

    //==========================================================================
    // Default constructor either generate [0 1 .. 1] or [D0 ... Dn]
    //==========================================================================
    of_size_()
    {
      data_[0] = (D0 < 0) ? 0u : D0;
      default_(boost::mpl::size_t<static_size-1>(), boost::mpl::size_t<((D0 < 0) ? 1u : 0u)>());
    }

    #define M2(z,n,t)                                     \
    BOOST_ASSERT_MSG( valid_size_parameter(D##n,t(n),n)   \
                    , "of_size_ constructor parameter "   \
                      BOOST_PP_STRINGIZE(BOOST_PP_INC(n)) \
                      " is invalid."                      \
                    );                                    \
    /**/

    #define M2D(n)    d##n
    #define M2DATA(n) ((static_size > std::size_t(n)) ? data_[n]: D##n)

    //==========================================================================
    // Constructor from a Fusion sequence:
    // - smaller sequence are padded with 1
    // - larger sequence are compacted
    //==========================================================================
    template<class Sz>
    of_size_( Sz const& other
            , typename  boost::enable_if
                        < boost::fusion::traits::is_sequence<Sz> >::type* = 0
            )
    {
      static const std::size_t osz = boost::fusion::result_of::size<Sz>::type::value;
      static const std::size_t msz = (osz < static_size) ? osz : static_size;
      details::copy(details::pop_back_c<osz - msz>(other),&data_[0]);

      for(std::size_t i = msz; i != size(); ++i) data_[i] = 1u;
      data_[size()-1] *= value_type(numel(details::pop_front_c<msz>(other)));

      BOOST_PP_REPEAT(NT2_MAX_DIMENSIONS,M2,M2DATA)
    }

    //==========================================================================
    // Constructor from a Iterator range
    // - smaller range are padded with 1
    // - larger range are valid as long as said values don't violate
    //   static properties. No compression occurs
    //==========================================================================
    template<class Iterator>
    of_size_( Iterator b, Iterator e
            , typename  boost::enable_if
                        < meta::is_iterator<Iterator> >::type*   = 0
            )
    {
      const std::size_t osz = e - b;
      const std::size_t msz = (osz < size()) ? osz : size();

      BOOST_ASSERT_MSG( full_of_one(b,msz,e)
                      , "Construction of of_size from a Range failed because "
                        "of Range size mismatch."
                      );

      nt2::memory::cast_copy(b, b+msz, &data_[0]);
      for(std::size_t i = msz; i != size(); ++i) data_[i] = 1u;
    }

    //==========================================================================
    // Constructors from [D0 .. Dn]
    // - smaller constructions are padded with 1
    // - larger constructions are valid as long as said values don't violate
    //   static properties. No compression occurs
    //==========================================================================
    #define M1(z,n,t) fill(   (D##n < 0)                                       \
                            ? std::size_t(d##n)                                \
                            : std::size_t(D##n)                                \
                          , boost::mpl::size_t<std::size_t(n)>()               \
                          , boost::mpl::bool_<(std::size_t(n)<static_size)>()  \
                          );                                                   \
    /**/

    #define M3(z,n,t) fill(   (D##n < 0)                                       \
                            ? std::size_t(1u)                                  \
                            : std::size_t(D##n)                                \
                          , boost::mpl::size_t<std::size_t(n)>()               \
                          , boost::mpl::bool_<(std::size_t(n)<static_size)>()  \
                          );                                                   \
    /**/

    #define M0(z,n,t)                                                          \
    template<BOOST_PP_ENUM_PARAMS(n, class I)>                                 \
    of_size_( BOOST_PP_ENUM_BINARY_PARAMS(n,I, const& d)                       \
            , typename  boost::disable_if                                      \
                        < boost::fusion::traits::is_sequence<I0> >::type* = 0) \
    {                                                                          \
      BOOST_PP_REPEAT(n,M2,M2D)                                                \
      BOOST_PP_REPEAT(n,M1,~)                                                  \
      BOOST_PP_REPEAT_FROM_TO(n,NT2_MAX_DIMENSIONS,M3,~)                       \
    }                                                                          \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

    #undef M0
    #undef M1
    #undef M2
    #undef M2D
    #undef M2DATA
    #undef M3

    //==========================================================================
    // Swap
    //==========================================================================
    template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t DI) >
    void swap ( of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,DI)>& src )
    {
      std::size_t i=0;
      for(; i<std::min(size(), src.size()); ++i)
        boost::swap(data_[i], src.data_[i]);
      for(std::size_t j=i; j<size(); ++j)
        data_[i] = 1;
      for(std::size_t j=i; j<src.size(); ++j)
        src.data_[i] = 1;
    }

    //==========================================================================
    // RandomAccessSequence interface
    //==========================================================================
    iterator        begin()       { return &data_[0];               }
    const_iterator  begin() const { return &data_[0];               }
    iterator        end()         { return &data_[0] + static_size; }
    const_iterator  end()   const { return &data_[0] + static_size; }

    reverse_iterator        rbegin()       { return reverse_iterator(end());          }
    const_reverse_iterator  rbegin() const { return const_reverse_iterator(end());    }
    reverse_iterator        rend()         { return reverse_iterator(begin());        }
    const_reverse_iterator  rend()   const { return const_reverse_iterator(begin());  }

    static std::size_t size() { return static_size; }
    static bool empty()       { return false; }

#ifdef NT2_OF_SIZE_USE_PROXY
    reference       operator[](std::size_t i)       { return reference(*this, i); }
#else
    reference       operator[](std::size_t i)       { return data_[i];            }
#endif
    const_reference operator[](std::size_t i) const { return data_[i];            }

    std::size_t*        data()       { return &data_[0]; }
    std::size_t const*  data() const { return &data_[0]; }

    private:

    static
    bool valid_size_parameter(std::ptrdiff_t Dn, std::size_t tn, std::size_t n)
    {
      return  ( Dn >= 0
              ? std::equal_to<std::size_t>()(tn, Dn)
              : ( static_size <= n
                ? (std::size_t(tn)==1u) : true
                )
              );
    }

    template<class Iterator, class Offset>
    static inline bool full_of_one(Iterator b, Offset o, Iterator e)
    {
      std::advance(b,o);
      while(b != e) { if(*b != 1) return false; b++; }
      return true;
    }

    template<class T, class N>
    inline void fill(T value, N const&, boost::mpl::true_ const&)
    {
      data_[N::value] = value;
    }

    template<class T, class N>
    inline void fill(T, N const&, boost::mpl::false_ const&) {}

    template<std::size_t N, std::size_t D>
    inline void default_(boost::mpl::size_t<N> const&, boost::mpl::size_t<D> const&)
    {
      typedef typename boost::mpl::at_c<values_type,N>::type value;
      data_[N] = (value::value < 0) ? D : value::value;
      default_(boost::mpl::size_t<N-1u>(), boost::mpl::size_t<((value::value < 0) ? 1u : D)>());
    }

    template<std::size_t D>
    inline void default_(boost::mpl::size_t<0> const&, boost::mpl::size_t<D> const&) {}
  };

  //============================================================================
  // of_size_ swap
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D)
          , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t DI)
          >
  void swap ( of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)>& a
            , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,DI)>& b
            )
  {
    a.swap(b);
  }

  //============================================================================
  // of_size_ display
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  inline std::ostream&
  operator<<( std::ostream& os
            , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS,D)> const& seq
            )
  {
    return boost::fusion::out(os, seq);
  }
}

#include <nt2/core/utility/of_size/0d.hpp>
#include <nt2/core/utility/of_size/max.hpp>
#include <nt2/core/utility/of_size/predef.hpp>
#include <nt2/core/utility/of_size/comparison.hpp>
#include <nt2/core/utility/of_size/mpl_value.hpp>

#endif
