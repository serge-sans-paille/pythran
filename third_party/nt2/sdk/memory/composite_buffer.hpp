//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_COMPOSITE_BUFFER_HPP_INCLUDED
#define NT2_SDK_MEMORY_COMPOSITE_BUFFER_HPP_INCLUDED

#include <boost/mpl/transform.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/copy.hpp>
#include <boost/fusion/include/swap.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/container_traits.hpp>
#include <nt2/sdk/memory/composite_iterator.hpp>
#include <nt2/sdk/memory/composite_reference.hpp>
#include <nt2/sdk/memory/adapted/composite_buffer.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/transform_view.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**
    * \brief Buffer for composite types
    *
    * composite_buffer allow type registered as composite to automatically be
    * promoted to a structure of array instead of an array of structure.
    *
    * \tparam Buffer Buffer to use as an underlying storage
   **/
  //============================================================================
  template<typename Buffer> class composite_buffer
  {
    public:
    //==========================================================================
    // Extract the value type of Buffer and its meta-model, convert the value
    // to its equivalent fusion tuple and apply a transform to turn each types
    // in this tuple into a buffer of proper model.
    //==========================================================================
    typedef typename Buffer::value_type                                 base_t;
    typedef typename boost::dispatch::meta::model_of<Buffer>::type      model_t;
    typedef typename boost::fusion::result_of::as_vector<base_t>::type  types_t;
    typedef typename boost::mpl::transform<types_t,model_t>::type       data_t;

    //==========================================================================
    // Container types
    //==========================================================================
    typedef base_t                                     value_type;

    typedef typename boost::mpl::
            transform < data_t
                      , meta::allocator_type_<boost::mpl::_>
                      >::type                           allocator_type;

    typedef typename boost::mpl::
            transform < data_t
                      , meta::pointer_<boost::mpl::_>
                      >::type                           pointer;

    typedef typename boost::mpl::
            transform < data_t
                      , meta::const_pointer_<boost::mpl::_>
                      >::type                           const_pointer;

    typedef nt2::container::composite_reference<value_type>        reference;
    typedef nt2::container::composite_reference<value_type const>  const_reference;

    typedef composite_iterator< pointer
                              , value_type
                              , reference
                              >                         iterator;

    typedef composite_iterator< const_pointer
                              , value_type
                              , const_reference
                              >                         const_iterator;

    typedef std::reverse_iterator<iterator>             reverse_iterator;
    typedef std::reverse_iterator<const_iterator>       const_reverse_iterator;

    typedef std::size_t                                 size_type;
    typedef std::ptrdiff_t                              difference_type;

    private:
    //==========================================================================
    // Some helper
    //==========================================================================
    struct resizer
    {
      std::size_t n_;
      resizer( std::size_t n ) : n_(n) {}
      template<typename T> BOOST_FORCEINLINE
      void operator()(T& t) const  { t.resize(n_); }
    };

    struct unary_ctor
    {
      template<typename T> BOOST_FORCEINLINE
      void operator()(T const& t) const
      {
        typename  meta::strip < typename  boost::fusion::result_of
                                        ::value_at_c<T,0>::type
                              >::type that(boost::fusion::at_c<1>(t));

        boost::fusion::at_c<0>(t).swap(that);
      }
    };

    typedef boost::fusion::vector2<data_t&,allocator_type&> seq_t;
    typedef boost::fusion::zip_view<seq_t>                  view_t;

    public:
    //==========================================================================
    // Default constructor
    //==========================================================================
    composite_buffer() {}

    //==========================================================================
    // Constructor from allocator
    //==========================================================================
    composite_buffer(allocator_type a)
    {
      boost::fusion::for_each( view_t( seq_t(data_,a) ), unary_ctor() );
    }

    //==========================================================================
    // Size constructor
    //==========================================================================
    composite_buffer( size_type n )
    {
      boost::fusion::for_each(data_, resizer(n) );
    }

    //==========================================================================
    // Size+Allocator constructor
    //==========================================================================
    composite_buffer( size_type n, allocator_type a)
    {
      boost::fusion::for_each( view_t( seq_t(data_,a) ), unary_ctor() );
      boost::fusion::for_each( data_, resizer(n) );
    }

    //==========================================================================
    // Resize
    //==========================================================================
    void resize( size_type sz )
    {
      boost::fusion::for_each(data_, resizer(sz) );
    }

    private:
    //==========================================================================
    // push_back helpers
    //==========================================================================
    struct pusher
    {
      template<typename T> BOOST_FORCEINLINE
      void operator()(T const& t) const
      {
        boost::fusion::at_c<0>(t).push_back(boost::fusion::at_c<1>(t));
      }
    };

    public:
    //==========================================================================
    // Resizes and add one element at the end
    //==========================================================================
    template<typename T> void push_back( T const& t )
    {
      typedef boost::fusion::vector2<data_t&,T const&>  pseq_t;
      typedef boost::fusion::zip_view<pseq_t>           pview_t;

      boost::fusion::for_each( pview_t( pseq_t(data_,t) ), pusher() );
    }

    //==========================================================================
    // Resizes and add a range of elements at the end
    //==========================================================================
    struct range_pusher
    {
      template<typename T> BOOST_FORCEINLINE
      void operator()(T const& t) const
      {
        boost::fusion::at_c<0>(t).push_back ( boost::fusion::at_c<1>(t)
                                            , boost::fusion::at_c<2>(t)
                                            );
      }
    };

    template<typename Iterator>
    void push_back( Iterator const& b, Iterator const& e )
    {
      typedef typename Iterator::sequence_type iseq_t;
      typedef boost::fusion::vector3< data_t&
                                    , iseq_t const&
                                    , iseq_t const&
                                    >               pseq_t;
      typedef boost::fusion::zip_view<pseq_t>       pview_t;

      boost::fusion::for_each( pview_t(pseq_t(data_,b,e)), range_pusher() );
    }

    //==========================================================================
    // Swap
    //==========================================================================
    void swap( composite_buffer& src )
    {
      boost::fusion::swap(data_,src.data_);
    }

    private:
    //==========================================================================
    // Iterators helper
    //==========================================================================
    struct beginer
    {
      template<class Sig> struct result;
      template<class This,class Elem> struct result<This(Elem)> : result<This(Elem&)> {};
      template<class This,class Elem> struct result<This(Elem&)>
      {
        typedef typename Elem::iterator type;
      };
      template<class This,class Elem> struct result<This(Elem const&)>
      {
        typedef typename Elem::const_iterator type;
      };

      template<typename T> BOOST_FORCEINLINE
      typename result<beginer(T&)>::type
      operator()(T& t) const  { return t.begin(); }

      template<typename T> BOOST_FORCEINLINE
      typename result<beginer(T const&)>::type
      operator()(T const& t) const  { return t.begin(); }
    };

    struct ender
    {
      template<class Sig> struct result;
      template<class This,class Elem> struct result<This(Elem)> : result<This(Elem&)> {};
      template<class This,class Elem> struct result<This(Elem&)>
      {
        typedef typename Elem::iterator type;
      };
      template<class This,class Elem> struct result<This(Elem const&)>
      {
        typedef typename Elem::const_iterator type;
      };

      template<typename T> BOOST_FORCEINLINE
      typename result<ender(T&)>::type
      operator()(T& t) const  { return t.end(); }

      template<typename T> BOOST_FORCEINLINE
      typename result<ender(T const&)>::type
      operator()(T const& t) const  { return t.end(); }
    };

    public:
    //==========================================================================
    // Iterators API
    //==========================================================================
    BOOST_FORCEINLINE iterator begin()
    {
      boost::fusion::transform_view<data_t,beginer> that(data_,beginer());
      return iterator(that);
    }

    BOOST_FORCEINLINE const_iterator begin() const
    {
      boost::fusion::transform_view<data_t const,beginer> that(data_,beginer());
      return const_iterator(that);
    }

    BOOST_FORCEINLINE iterator end()
    {
      boost::fusion::transform_view<data_t,ender> that(data_, ender() );
      return iterator(that);
    }

    BOOST_FORCEINLINE const_iterator end() const
    {
      boost::fusion::transform_view<data_t const,ender> that(data_, ender() );
      return const_iterator(that);
    }

    BOOST_FORCEINLINE reverse_iterator rbegin()
    {
      return reverse_iterator(end());
    }

    BOOST_FORCEINLINE const_reverse_iterator rbegin() const
    {
      return const_reverse_iterator(end());
    }

    BOOST_FORCEINLINE reverse_iterator rend()
    {
      return reverse_iterator(begin());
    }

    BOOST_FORCEINLINE const_reverse_iterator rend() const
    {
      return const_reverse_iterator(begin());
    }

    private:
    //==========================================================================
    // Raw values helper
    //==========================================================================
    struct rawer
    {
      template<class Sig> struct result;
      template<class This,class Elem> struct result<This(Elem)> : result<This(Elem&)> {};
      template<class This,class Elem> struct result<This(Elem&)>
      {
        typedef typename Elem::pointer type;
      };
      template<class This,class Elem> struct result<This(Elem const&)>
      {
        typedef typename Elem::const_pointer type;
      };

      template<typename T> BOOST_FORCEINLINE
      typename result<rawer(T&)>::type
      operator()(T& t) const  { return t.raw(); }

      template<typename T> BOOST_FORCEINLINE
      typename result<rawer(T const&)>::type
      operator()(T const& t) const  { return t.raw(); }
    };

    public:
    //==========================================================================
    // Raw values
    //==========================================================================
    BOOST_FORCEINLINE pointer raw()
    {
      boost::fusion::transform_view<data_t,rawer> that(data_, rawer() );
      return that;
    }

    BOOST_FORCEINLINE const_pointer raw() const
    {
      boost::fusion::transform_view<data_t const,rawer> that(data_, rawer() );
      return that;
    }

    //==========================================================================
    // Size related members
    //==========================================================================
    BOOST_FORCEINLINE size_type  size()      const
    {
      return boost::fusion::at_c<0>(data_).size();
    }

    BOOST_FORCEINLINE size_type  capacity()  const
    {
      return boost::fusion::at_c<0>(data_).capacity();
    }

    BOOST_FORCEINLINE bool empty() const
    {
      return boost::fusion::at_c<0>(data_).empty();
    }

    BOOST_FORCEINLINE bool is_safe(size_type p) const
    {
      return boost::fusion::at_c<0>(data_).is_safe(p);
    }

    //==========================================================================
    // Random access helper
    //==========================================================================
    private:
    struct indexer
    {
      template<class Sig> struct result;
      template<class This,class Elem> struct result<This(Elem)> : result<This(Elem&)> {};
      template<class This,class Elem> struct result<This(Elem&)>
      {
        typedef typename Elem::reference type;
      };
      template<class This,class Elem> struct result<This(Elem const&)>
      {
        typedef typename Elem::const_reference type;
      };

      size_type i_;
      indexer(size_type i) : i_(i) {}

      template<typename T> BOOST_FORCEINLINE
      typename result<indexer(T&)>::type
      operator()(T& t) const  { return t[i_]; }

      template<typename T> BOOST_FORCEINLINE
      typename result<indexer(T const&)>::type
      operator()(T const& t) const  { return t[i_]; }
    };

    //==========================================================================
    // Random access
    //==========================================================================
    public:
    BOOST_FORCEINLINE reference operator[](size_type i)
    {
      boost::fusion::transform_view<data_t,indexer> that(data_,indexer(i));
      return that;
    }

    BOOST_FORCEINLINE const_reference operator[](size_type i) const
    {
      boost::fusion::transform_view<data_t const,indexer> that(data_,indexer(i));
      return that;
    }

    private:
    data_t data_;
  };

  //============================================================================
  /**!
   * Swap the contents of two composite_buffer of same type and allocator
   * settings
   * \param x First \c composite_buffer to swap
   * \param y Second \c composite_buffer to swap
   **/
  //============================================================================
  template<class B>
  inline void swap(composite_buffer<B>& x, composite_buffer<B>& y)
  {
    x.swap(y);
  }
} }

#endif
