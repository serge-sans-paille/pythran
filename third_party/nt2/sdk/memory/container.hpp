//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_CONTAINER_HPP_INCLUDED
#define NT2_SDK_MEMORY_CONTAINER_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/interleaving.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/settings/specific_data.hpp>
#include <nt2/core/settings/storage_scheme.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/include/functions/scalar/numel.hpp>
#include <nt2/include/functions/scalar/ndims.hpp>
#include <nt2/sdk/memory/adapted/container.hpp>
#include <nt2/sdk/memory/composite_buffer.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/mpl/at.hpp>
#include <boost/assert.hpp>
#include <algorithm>

#ifdef NT2_LOG_COPIES
#include <iostream>
#endif

namespace nt2 { namespace tag
{
  struct table_;
} }

namespace nt2 { namespace memory
{
  /*!
    @brief Memory handling typename for nt2 Container

    container is the base typename handling a container semantic, layout and
    memory used by nt2 terminals. It is built from a value
    @c Type, a list of @c Settings describing how it should behave both at
    runtime and compile-time and a @c Kind describing which kind of
    high-level behavior the container will have.

    @tparam Kind      Describe the behavior of the container
    @tparam Type      Value type to store in the table
    @tparam Setting   Options list describing the options of the container
  **/
  template<typename Kind, typename Type, typename Settings>
  struct container : public container_base<Type>
  {
    public:

    /// INTERNAL ONLY Precomputed semantic type
    typedef Kind                                          kind_type;

    /// INTERNAL ONLY Precomputed settings type
    typedef Settings                                      settings_type;

    /// INTERNAL ONLY storage_scheme option
    typedef typename meta::option < Settings
                                  , tag::storage_scheme_
                                  , Kind
                                  >::type                 scheme_t;

    /// INTERNAL ONLY Storage Scheme option
    typedef typename scheme_t::template apply<container> scheme_type;

    /// INTERNAL ONLY Check if Type is a Fusion Sequence
    typedef boost::fusion::traits::is_sequence<Type>      composite_t;

    /// INTERNAL ONLY Retrieve interleaving option
    typedef typename meta::option < Settings
                                  , tag::interleaving_
                                  , Kind
                                  >::type::interleaving_type  inter_t;

    /// INTERNAL ONLY Base buffer type
    typedef typename scheme_type::type                        buffer_t;

    /*!
      @brief Container memory buffer type

      This typedef defines the type used by container to store its values.
      This type is computed by using the various settings the container may
      have.
    **/
    typedef typename boost::mpl::if_< boost::mpl::and_<composite_t,inter_t>
                                    , composite_buffer<buffer_t>
                                    , buffer_t
                                    >::type               buffer_type;

    /*!
      @brief Hardware specific data type

      Depending on current architecture, container data block may need to be
      augmented by a hardware specific member that take care of said hardware
      specificities

      @see spec_data
    **/
    typedef typename specific_data< typename  boost::dispatch::
                                              default_site<Type>::type
                                  , Type
                                  >::type               specific_data_type;

    /// @brief Allocator type used by the Container
    typedef typename buffer_type::allocator_type   allocator_type;

    /// @brief Value type stored by the Container
    typedef typename buffer_type::value_type       value_type;

    /// @brief Iterator type exposed by the Container
    typedef typename buffer_type::iterator         iterator;

    /// @brief Constant iterator type exposed by the Container
    typedef typename buffer_type::const_iterator   const_iterator;

    /// @brief Reference type exposed by the Container
    typedef typename buffer_type::reference        reference;

    /// @brief Constant reference type exposed by the Container
    typedef typename buffer_type::const_reference  const_reference;

    /// @brief Size type exposed by the Container
    typedef typename buffer_type::size_type        size_type;

    /// @brief Interval type exposed by the Container
    typedef typename buffer_type::difference_type  difference_type;

    /// @brief Pointer type exposed by the Container
    typedef typename buffer_type::pointer          pointer;

    /// @brief Constant pointer type exposed by the Container
    typedef typename buffer_type::const_pointer    const_pointer;

    /// @brief Type used to store extent of the data
    typedef typename meta::option < Settings
                                  , tag::of_size_
                                  , Kind
                                  >::type       extent_type;

    /// @brief Type used to store base index value of the data
    typedef typename meta::option < Settings
                                  , tag::index_
                                  , Kind
                                  >::type       index_type;

    /// @brief Type used to represent the container storage order
    typedef typename meta::option < Settings
                                  , tag::storage_order_
                                  , Kind
                                  >::type       order_type;

    /// INTERNAL ONLY detects if default initialization is required
    typedef typename meta::option < Settings
                                  , tag::storage_duration_
                                  , Kind
                                  >::type                     duration_t;

    /// INTERNAL ONLY Check if static initialization is required
    /// This is true for non-automatic, non-empty container
    typedef boost::mpl::
            bool_ <   ! ( boost::mpl::at_c<typename extent_type::values_type,0>
                                    ::type::value <= 0
                        )
                  &&  !boost::is_same<duration_t,automatic_>::value
                  >                                         require_static_init;

    /// INTERNAL ONLY detects if container size is known at compile time
    typedef boost::mpl::
            bool_ <   extent_type::static_status
                  ||  boost::is_same<duration_t,automatic_>::value
                  >                                         has_static_size;

    /*!
      @brief Default constructor

      A default-constructed container is initialized to be:
       - empty if its size is dynamic
       - preallocated if its size is static or its storage is automatic
    **/
    container() : data_()
    {
      init(sizes_, require_static_init());
    }

#ifdef NT2_LOG_COPIES
    container(container const& other) : data_(other.data_), sizes_(other.sizes_)
    {
      std::cout << "copying container" << std::endl;
    }

    container& operator=(container const& other)
    {
      data_ = other.data_;
      sizes_ = other.sizes_;
      std::cout << "assigning container" << std::endl;
      return *this;
    }
#endif

    /*!
      @brief Constructor from an allocator

      Construct a container from an allocator instance. Such container is
      initialized to be:
       - empty if its size is dynamic
       - pre-allocated if its size is static or its storage is automatic

      container is aware of stateful allocator and will handle
      them properly.

      @param a Allocator used for container construction
    **/
    container ( allocator_type const& a ) : data_(a)
    {
      init(sizes_, require_static_init());
    }

    /*!
      @brief Construct a container from a dimension set

      Construct a container from a Fusion RandomAccessSequence of integral
      values representing the logical number of element in each dimensions.

      Passing a dimension set to container with automatic storage or set up
      to use a static dimension set will result in a assert being raised if
      said dimension set is not compatible with its static size.

      container is aware of stateful allocator and will handle them properly.

      @param sz Fusion Sequence to use as dimensions
      @param a  Allocator used for container construction
    **/
    template<typename Size>
    container ( Size const& sz, allocator_type const& a = allocator_type() )
              : data_(a), sizes_(sz)
    {
      BOOST_ASSERT_MSG( !has_static_size::value || sz == extent_type()
                      , "Invalid constructor for statically sized container"
                      );

      init(sizes_);
    }

    /*!
      @brief container swapping

      Swap the contents of current container with another container

      @param y container to swap @c *this with
    **/
    template<typename S2, typename Kind2>
    BOOST_FORCEINLINE void swap(container<Kind2,Type,S2>& y)
    {
      data_.swap(y.data_);
      sizes_.swap(y.sizes_);
      this->specifics().swap(y.specifics());
    }

    BOOST_FORCEINLINE void swap(Type& y)
    {
      BOOST_ASSERT_MSG( sizes_ == _0D(), "swapping non-singleton container with scalar" );
      boost::swap(y, data_[0]);
    }

    //==========================================================================
    /*!
     * @brief Resize a container using new dimensions set
     */
    //==========================================================================
    template<typename Size> void resize( Size const& szs )
    {
      resize(szs,boost::mpl::bool_<!extent_type::static_status>());
    }

    //==========================================================================
    /*!
     * @brief Add element at end of container, reshape to 1D
     */
    //==========================================================================
    void push_back( value_type const& t )
    {
      data_.push_back(t);
      sizes_ = extent_type(numel(sizes_) + 1);
    }

    //==========================================================================
    /*!
     * @brief Add range of element at end of container's most external dimension
     */
    //==========================================================================
    template<typename Container> void push_back(Container const& c, std::size_t d)
    {
      BOOST_ASSERT_MSG( d >= (nt2::ndims(sizes_)-1u)
                      , "Dimension for push_back isn't outer dimension"
                      );
      BOOST_ASSERT_MSG( d < extent_type::static_size && (empty() || std::equal(c.extent().begin(), c.extent().begin()+std::min(d,c.extent().size()), sizes_.begin()))
                      , "Incompatible size in range push_back"
                      );

      if(empty())
        sizes_ = c.extent();
      else
        sizes_[d] += (d < c.extent().size()) ? c.extent()[d] : 1u;

      data_.push_back(c.begin(), c.end());
    };

    template<typename Container> void push_back(Container const& c)
    {
      return push_back(c, nt2::ndims(c.extent()));
    }

    /*!
      @brief Return the container dimensions set
      @return A reference to a constant Fusion RandomAccessSequence containing
              the size of the container over each of its dimensions.
    **/
    BOOST_FORCEINLINE extent_type const& extent() const { return sizes_;  }

    /*!
      @brief Return the container number of element
      @return The number of logical element stored in the buffer.
    **/
    BOOST_FORCEINLINE size_type size() const { return data_.size();  }

    /*!
      @brief Return the container number of element along the main dimension
      @return The number of elements stored on the main dimension
    **/
    BOOST_FORCEINLINE size_type leading_size() const
    {
      typedef typename boost::mpl
                            ::apply < order_type
                                    , boost::mpl::size_t<extent_type::static_size>
                                    , boost::mpl::size_t<0U>
                                    >::type                     dim_t;
      return sizes_[dim_t::value];
    }

    /*!
      @brief Check for if container is empty
      @return A boolean that evaluates to @c true if the container
              number of elements is 0.
    **/
    BOOST_FORCEINLINE bool empty() const { return data_.empty(); }

    /*!
      @brief Raw memory accessor
      @return Pointer to the raw memory of the container
    **/
    BOOST_FORCEINLINE pointer       raw()       { return data_.raw(); }

    /// @overload
    BOOST_FORCEINLINE const_pointer raw() const { return data_.raw(); }

    /*!
      @brief Container's beginning of data
      @return Pointer to the beginning of the container underlying sequence
    **/
    BOOST_FORCEINLINE iterator       begin()       { return data_.begin(); }

    /// @overload
    BOOST_FORCEINLINE const_iterator begin() const { return data_.begin(); }

    /*!
      @brief Container's end of data
      @return Pointer to the end of the container underlying sequence
    **/
    BOOST_FORCEINLINE iterator       end()       { return data_.end(); }

    /// @overload
    BOOST_FORCEINLINE const_iterator end() const { return data_.end(); }

    /*!
      @brief Random access to container's data
      @param i Index of the element to access
      @return Reference to the ith element of the container
    **/
    BOOST_FORCEINLINE reference operator[](size_type i)
    {
      this->specifics().synchronize();
      return data_[i];
    }

    /// @overload
    BOOST_FORCEINLINE const_reference operator[](size_type i) const
    {
      this->specifics().synchronize();
      return data_[i];
    }

    // Check if a position is safely R/W in the current container
    BOOST_FORCEINLINE bool is_safe(size_type p) const { return data_.is_safe(p); }

    protected:

    /// INTERNAL ONLY
    /// Initialization of inner data_ and sizes_
    /// Note that the number of non-trivial (nnz) is delegated to storage scheme
    template<typename Size> BOOST_FORCEINLINE void init( Size const& )
    {
      data_.resize( scheme_type::nnz( sizes_ ) );
    }

    /// INTERNAL ONLY
    /// Handle the default initialization of statically-sized dynamic container
    template<typename Size> BOOST_FORCEINLINE
    void init(Size const& sz, boost::mpl::true_ const&  ) { init(sz); }

    template<typename Size> BOOST_FORCEINLINE
    void init(Size const&, boost::mpl::false_ const& ) {}

    /// INTERNAL ONLY
    /// Handle the resize of statically sized container
    template<typename Size> BOOST_FORCEINLINE
    void resize( Size const& szs, boost::mpl::true_ const& )
    {
      if( szs != sizes_ )
      {
        sizes_ = extent_type(szs);
        init(sizes_);
      }
    }

    template<typename Size> BOOST_FORCEINLINE
    void resize( Size const& szs, boost::mpl::false_ const& )
    {
      BOOST_ASSERT_MSG( szs == extent_type()
                      , "Statically sized container can't be resized dynamically"
                      );
    }

    private:
    buffer_type                 data_;
    extent_type                 sizes_;

    template<typename Kind2, typename T2, typename S2>
    friend struct container;
  };

  /*!
    @brief Container generalized swap

    Swap the contents of two containers

    @param x First @c container to swap
    @param y Second @c container to swap
  **/
  template< typename Kind1, typename Kind2
          , typename T
          , typename S1, typename S2
          >
  BOOST_FORCEINLINE
  void swap(container<Kind1,T,S1>& x, container<Kind2,T,S2>& y)  { x.swap(y); }

  /// @overload
  template<typename Kind, typename T, typename S>
  BOOST_FORCEINLINE
  void swap(T& x, container<Kind, T, S>& y) { y.swap(x); }

  /// @overload
  template<typename Kind, typename T, typename S>
  BOOST_FORCEINLINE
  void swap(container<Kind, T, S>& x, T& y) { x.swap(y); }

} }

#endif
