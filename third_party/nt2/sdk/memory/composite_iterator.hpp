//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_COMPOSITE_ITERATOR_HPP_INCLUDED
#define NT2_SDK_MEMORY_COMPOSITE_ITERATOR_HPP_INCLUDED

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/comparison.hpp>
#include <boost/fusion/include/transform_view.hpp>

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::composite_iterator class
  **/
//==============================================================================

namespace nt2 { namespace memory
{
  template<class P, class V, class R>
  class composite_iterator
        : public boost::
          iterator_facade < composite_iterator<P,V,R>
                          , V, std::random_access_iterator_tag
                            // boost::random_access_traversal_tag
                          , R
                          >
  {
    private:
    struct enabler {};

    public:
    typedef P sequence_type;

    //==========================================================================
    // Default constructor
    //==========================================================================
    composite_iterator() {}

    //==========================================================================
    // Construct from a fusion sequence of pointer
    //==========================================================================
    explicit composite_iterator(P const& p) : composites_(p) {}

    //==========================================================================
    // Construct from a compatible composite_iterator
    //==========================================================================
    template <class P2,class V2, class R2>
    composite_iterator( composite_iterator<P2,V2,R2> const& other
                      , typename  boost::
                                  enable_if < boost::is_convertible<P,P2>
                                            , enabler
                                            >::type = enabler()
                      )
                      : composites_(other.composites_)
    {}

    void display(std::ostream& os) const
    {
      os << boost::fusion::as_vector(composites_);
    }

    //XXXMathias: needed for iterator-to-pointer conversion in container_ref constructor
    //TODO: find a better way to deal with this?
    operator P const&() const
    {
      return composites_;
    }

  private:
    friend class boost::iterator_core_access;
    template<class,class,class> friend class composite_iterator;

    //==========================================================================
    // Various Fusion for_each helpers
    //==========================================================================
    struct inc
    {
      template<class T> BOOST_FORCEINLINE void operator()(T& t) const { t++; }
    };

    struct dec
    {
      template<class T> BOOST_FORCEINLINE void operator()(T& t) const { t--; }
    };

    struct adv
    {
      std::ptrdiff_t n_;
      adv(std::ptrdiff_t n) : n_(n) {}
      template<class T>
      BOOST_FORCEINLINE void operator()(T& t) const { t += n_; }
    };

    struct derefer
    {
      template<class Sig> struct result;
      template<class This,class Elem> struct result<This(Elem const&)>
      {
        typedef typename boost::iterator_reference<Elem>::type type;
      };

      template<typename T> BOOST_FORCEINLINE
      typename result<derefer(T const&)>::type
      operator()(T const& t) const  { return *t; }
    };

    //==========================================================================
    // Implement ++ for RandomAccessIterator interface
    //==========================================================================
    void increment() { boost::fusion::for_each(composites_,inc()); }

    //==========================================================================
    // Implement -- for RandomAccessIterator interface
    //==========================================================================
    void decrement() { boost::fusion::for_each(composites_,dec()); }

    //==========================================================================
    // Implement it + n for RandomAccessIterator interface
    //==========================================================================
    void advance(std::ptrdiff_t n)
    {
      boost::fusion::for_each(composites_,adv(n));
    }

    //==========================================================================
    // Implement distance for RandomAccessIterator interface
    //==========================================================================
    std::ptrdiff_t distance_to(composite_iterator const& z) const
    {
      return std::distance( boost::fusion::at_c<0>(composites_)
                          , boost::fusion::at_c<0>(z.composites_)
                          );
    }

    //==========================================================================
    // Implement equality comparison for RandomAccessIterator interface
    //==========================================================================
    bool equal(composite_iterator const& other) const
    {
      return composites_ == other.composites_;
    }

    //==========================================================================
    // Implement oeprator* for RandomAccessIterator interface
    //==========================================================================
    R dereference() const
    {
      boost::fusion::transform_view<P const,derefer> that(composites_,derefer());
      return that;
    }

    P composites_;
  };

  template<class P, class V, class R>
  std::ostream& operator<<(std::ostream& os,composite_iterator<P,V,R> const& i)
  {
    i.display(os);
    return os;
  }
} }

#endif
