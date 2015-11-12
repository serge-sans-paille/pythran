//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_0D_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_0D_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/mpl/vector_c.hpp>
#include <nt2/core/settings/size.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/core/utility/of_size/fusion.hpp>

namespace nt2
{
  //============================================================================
  // Specialisation for _0D case
  //============================================================================
  template<> struct of_size_<>
  {
    typedef of_size_                                of_size_type;
    typedef boost::mpl::integral_c<std::size_t,1U>  storage_size_type;
    typedef automatic_                              storage_duration_type;
    typedef tag::of_size_                           fusion_tag;
    typedef boost::fusion::fusion_sequence_tag      tag;
    typedef boost::mpl::vector_c< std::ptrdiff_t >  values_type;
    typedef std::size_t                             value_type;
    typedef std::size_t&                            reference;
    typedef std::size_t const&                      const_reference;
    typedef std::size_t*                            iterator;
    typedef std::size_t const*                      const_iterator;
    typedef std::reverse_iterator<iterator>         reverse_iterator;
    typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

    static const std::size_t  static_size   = 0;
    static const bool         static_status = true;
    static const std::size_t  static_numel  = 1;

    static std::size_t size() { return 0;     }
    static bool empty()       { return true;  }

    reference        operator[](std::size_t)       { return *data(); }
    const_reference  operator[](std::size_t) const { return *data(); }

    std::size_t* data()             { return 0; }
    std::size_t const* data() const { return 0; }

    iterator        begin()       { return iterator(0);       }
    const_iterator  begin() const { return const_iterator(0); }
    iterator        end()         { return iterator(0);       }
    const_iterator  end()   const { return const_iterator(0); }

    reverse_iterator        rbegin()       { return reverse_iterator(0);        }
    const_reverse_iterator  rbegin() const { return const_reverse_iterator(0);  }
    reverse_iterator        rend()         { return reverse_iterator(0);        }
    const_reverse_iterator  rend()   const { return const_reverse_iterator(0);  }

    //==========================================================================
    // Default constructor
    //==========================================================================
    of_size_() {}

    //==========================================================================
    // Constructor from Fusion Sequence - Everything should be 1
    //==========================================================================
    template<class S>
    of_size_( S const& other
            , typename boost::enable_if
              < boost::fusion::traits::is_sequence<S> >::type* = 0
            )
    {
      details::check_all_equal(other, 1);
    }

    //==========================================================================
    // Constructor from Range - Everything should be 1
    //==========================================================================
    template<class Iterator>
    of_size_( Iterator b, Iterator e
            , typename  boost::enable_if
                        < meta::is_iterator<Iterator> >::type*   = 0
            )
    {
      BOOST_ASSERT_MSG( full_of_one(b,e)
                      , "Size mismatch at of_size construction"
                      );
    }

    //==========================================================================
    // Constructor from a list of values - Everything should be 1
    //==========================================================================
    #define M1(z,n,t)                                       \
    BOOST_ASSERT_MSG( (d##n==1)                             \
                    , "_0D constructor parameter "          \
                      BOOST_PP_STRINGIZE(BOOST_PP_INC(n))   \
                      " invalid with respect to of_size_ "  \
                      "numbers of dimensions."              \
                    );                                      \
    /**/

    #define M0(z,n,t)                                                           \
    template<BOOST_PP_ENUM_PARAMS(n, class I)>                                  \
    of_size_( BOOST_PP_ENUM_BINARY_PARAMS(n,I, const& d)                        \
            , typename  boost::disable_if                                       \
                        < boost::fusion::traits::is_sequence<I0> >::type* = 0)  \
    {                                                                           \
      BOOST_PP_REPEAT(n,M1,~)                                                   \
    }                                                                           \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

    #undef M0
    #undef M1
    #undef M2
    #undef M3

    private:
    template<class Iterator>
    static inline bool full_of_one(Iterator b, Iterator e)
    {
      while(b != e) { if(*b != 1) return false; b++; }
      return true;
    }
  };
}

#endif
