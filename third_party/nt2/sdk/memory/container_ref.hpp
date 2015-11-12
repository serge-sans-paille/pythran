//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_CONTAINER_REF_HPP_INCLUDED
#define NT2_SDK_MEMORY_CONTAINER_REF_HPP_INCLUDED

#include <nt2/sdk/memory/adapted/container_ref.hpp>
#include <nt2/core/settings/specific_data.hpp>
#include <nt2/sdk/memory/forward/container.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /*!
   * container_ref is like container, but instead of wrapping a buffer it wraps
   * a pointer. Copying a container_ref does not copy any data.
   *
   * \tparam Type    Value type to store in the table
   * \tparam Setting Options list describing the behavior of the container
   **/
  //============================================================================
  template<typename Kind, typename T, typename S>
  struct container_ref
  {
    /// INTERNAL ONLY Precomputed semantic type
    typedef Kind                                                 kind_type;
    typedef S                                                    settings_type;
    typedef typename boost::remove_const<T>::type                value_type;
    typedef std::size_t                                          size_type;
    typedef typename meta::option<S, tag::of_size_, Kind>::type        extent_type;
    typedef typename meta::option<S, tag::storage_order_, Kind>::type  order_type;

    typedef typename specific_data< typename boost::dispatch::
                                             default_site<T>::type
                                  , value_type
                                  >::type                        specific_data_type;

    typedef typename boost::mpl::
            if_< boost::is_const<T>
               , container<Kind, value_type, S> const
               , container<Kind, value_type, S>
               >::type base_t;

    typedef typename boost::mpl::
            if_< boost::is_const<T>
               , container_base<value_type> const
               , container_base<value_type>
               >::type cbase_t;

    typedef typename boost::mpl::
            if_< boost::is_const<T>
               , typename base_t::const_reference
               , typename base_t::reference
               >::type                                           reference;
    typedef typename boost::mpl::
            if_< boost::is_const<T>
               , typename base_t::const_pointer
               , typename base_t::pointer
               >::type                                           pointer;
    typedef typename boost::mpl::
            if_< boost::is_const<T>
               , typename base_t::const_iterator
               , typename base_t::iterator
               >::type                                           iterator;
    typedef typename base_t::const_reference                     const_reference;
    typedef typename base_t::const_pointer                       const_pointer;
    typedef typename base_t::const_iterator                      const_iterator;

    container_ref() : ptr(), base_()
    {
    }

    container_ref(T& value) : ptr(&value), sz(_0D()), base_()
    {
    }

    template<typename Kind2, typename U, typename S2>
    container_ref (container_ref<Kind2,U, S2> const& other)
                  : ptr(other.ptr), sz(other.sz), base_(other.base_)
    {
    }

    template<typename Kind2, typename U, typename S2>
    container_ref (container_shared_ref<Kind2, U, S2, false> const& other)
                  : ptr(other.ptr), sz(other.sz), base_(other.base_.get())
    {
    }

    template<typename Kind2, typename U, typename S2>
    container_ref (container_shared_ref<Kind2, U, S2, true> const& other)
                  : ptr(other.raw()), sz(other.extent())
                  , base_(other.base_.get())
    {
    }

    container_ref(pointer p, extent_type const& sz_) : ptr(p), sz(sz_), base_()
    {
    }

    template<typename Kind2, typename U, typename S2>
    container_ref (container<Kind2, U, S2>& c)
                  : ptr(c.raw()), sz(c.extent()), base_(&c)
    {
    }
    template<typename Kind2, typename U, typename S2>
    container_ref (container<Kind2, U, S2> const& c)
                  : ptr(c.raw()), sz(c.extent()), base_(&c)
    {
    }

    template<typename Kind2, typename U, typename S2>
    container_ref (container<Kind2, U, S2>& c, pointer p, extent_type const& sz_)
                  : ptr(p), sz(sz_), base_(&c)
    {
    }
    template<typename Kind2, typename U, typename S2>
    container_ref (container<Kind2, U, S2> const& c
                  , pointer p, extent_type const& sz_
                  )
                  : ptr(p), sz(sz_), base_(&c)
    {
    }

    template<typename Kind2, typename U, typename S2>
    container_ref ( container_ref<Kind2, U, S2> const& c
                  , pointer p, extent_type const& sz_
                  )
                  : ptr(p), sz(sz_), base_(c.base_)
    {
    }

    //==========================================================================
    /**!
     * Swap the contents of two container of same type and settings
     * \param y Second \c container to swap, the first being *this
     **/
    //==========================================================================
    BOOST_FORCEINLINE void swap(container_ref& y)
    {
      boost::swap(*this, y);
    }

    //==========================================================================
    /*!
     * @brief Resize a container using new dimensions set
     */
    //==========================================================================
    template<typename Size>
    void resize( Size const& ) const
    {
      // do nothing
    }

    //==========================================================================
    /*!
     * @brief Add element at end of container, reshape to 1D
     */
    //==========================================================================
    void push_back( value_type const& )
    {
      // do nothing
    }

    //==========================================================================
    /*!
     * @brief Add range of element at end of container's most external dimension
     */
    //==========================================================================
    template<typename Container> void push_back( Container const& )
    {
      // do nothing
    };

    //==========================================================================
    /*!
     * @brief Return the container dimensions set
     * @return A reference to a constant Fusion RandomAccessSequence containing
     * the size of the container over each of its dimensions.
     **/
    //==========================================================================
    BOOST_FORCEINLINE extent_type const& extent() const
    {
      return sz;
    }

    //==========================================================================
    /*!
     * @brief Return the container number of element
     * @return The number of logical element stored in the buffer.
     **/
    //==========================================================================
    BOOST_FORCEINLINE size_type size() const
    {
      return numel(sz);
    }

    //==========================================================================
    /*!
     * @brief Return the container number of element along the main dimension
     *
     * leading_size retrieves the number of element of the leading dimension in
     * a settings independant way.
     *
     * @return The number of elements stored on the main dimension
     */
    //==========================================================================
    BOOST_FORCEINLINE size_type leading_size() const
    {
      typedef typename boost::mpl
                            ::apply < order_type
                                    , boost::mpl::size_t<extent_type::static_size>
                                    , boost::mpl::size_t<0U>
                                    >::type                     dim_t;
      return extent()[dim_t::value];
    }

    //==========================================================================
    /*!
     * @brief Check for container emptyness
     * @return A boolean that evaluates to \c true if the container stores no
     * value, \c false otherwise.
     */
    //==========================================================================
    BOOST_FORCEINLINE bool empty() const { return size() == 0u; }

    //==========================================================================
    /*!
     * Return the begin of the raw memory
     */
    //==========================================================================
    BOOST_FORCEINLINE pointer        raw() const { return ptr; }

    //==========================================================================
    /*!
     * Return the begin of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       begin() const { return iterator(ptr); }

    //==========================================================================
    /*!
     * Return the end of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       end() const   { return begin() + size(); }

    //==========================================================================
    // Linear Random Access
    //==========================================================================
    BOOST_FORCEINLINE reference operator[](size_type i) const
    {
      return begin()[i];
    }

    //==========================================================================
    /*!
     * @brief Access to the architecture specific container data
     * As the inner structure of a container may change with the hardware
     * configuration, a specific data segment is provided to gather informations
     * that may be required for proper operation on said configuration.
     *
     * @return A reference to the specific data of the container.
     **/
    //==========================================================================
    specific_data_type&  specifics() const { return base_->specifics(); }

    //==========================================================================
    // Check if a position is safely R/W in the current container
    //==========================================================================
    BOOST_FORCEINLINE bool is_safe(size_type p) const { return p == 0u || p < size(); }

    cbase_t* base() const { return base_; }

  private:
    template<typename Kind2, typename U, typename S2>
    friend struct container_ref;

    pointer                     ptr;
    extent_type                 sz;
    cbase_t*                    base_;
  };

  //============================================================================
  /**!
   * Swap the contents of two container of same type and settings
   * \param x First \c container to swap
   * \param y Second \c container to swap
   **/
  //============================================================================
  template<typename Kind, typename T, typename S> inline
  void swap(container_ref<Kind, T, S>& x, container_ref<Kind, T, S>& y)
  {
    x.swap(y);
  }

} }

#endif
