//==================================================================================================
/*!
  @file

  Defines the abstraction for SIMD registers

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_PACK_HPP_INCLUDED
#define BOOST_SIMD_PACK_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch/detail/declval.hpp>
#include <boost/simd/detail/pack_traits.hpp>
#include <boost/simd/detail/pack_proxy_base.hpp>
#include <boost/simd/detail/storage_of.hpp>
#include <boost/simd/meta/is_power_of_2.hpp>
#include <boost/simd/meta/is_iterator.hpp>
#include <boost/simd/function/aligned_load.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/insert.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/memory/aligned_object.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/config.hpp>
#include <boost/predef/compiler.h>
#include <array>
#include <iterator>
#include <iostream>
#include <cstddef>

#if BOOST_COMP_GNUC
#pragma GCC diagnostic push
// Remove noise due to line 205 return value
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
// Remove noise from attribute from as_simd
#if BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(6,0,0)
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif
#endif


namespace boost { namespace simd
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;

  /*!
    @ingroup  group-api
    @brief    High-level interface for manipulating SIMD data

    For a given pair @c T and @c N, provides an interface to manipulate SIMD
    data with the best storage possible depending on your hardware.

    @pre @c N must be a power of two.
    @pre @c T models Vectorizable

    @tparam T   Type of the stored elements
    @tparam N   Number of element stored
    @tparam ABI Binary flag to prevent ABI issue
   **/
  template< typename T
          , std::size_t N
          , typename ABI
          >
  class pack {

    static_assert( boost::simd::is_power_of_2_<N>::value
                 , "Cardinal must be a power of 2"
                 );

    public:
    using traits          = detail::pack_traits<T, N, typename detail::storage_of<T, N, ABI>::type>;
    using storage_type    = typename traits::storage_type;
    using substorage_type = typename traits::substorage_type;
    using storage_kind    = typename traits::storage_kind;
    using value_type      = typename traits::value_type;
    using size_type       = typename traits::size_type;

    using reference       = typename detail::pack_references<traits, pack>::reference;
    using const_reference = typename detail::pack_references<traits, pack>::const_reference;

    using iterator               = detail::pack_iterator<pack>;
    using const_iterator         = detail::pack_iterator<pack const>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    enum { static_size = N };

    enum { alignment = traits::alignment };

    /// @brief pack type rebinding alias
    template<typename U> using rebind = pack<U,N>;

    /// @brief pack type resizing alias
    template<std::size_t M> using resize = pack<T,M>;

    /// @brief pack type retyping alias
    template<typename U,std::size_t M> using retype = pack<U,M>;

    public:

    /*!
      @brief Default constructor

      Constructs a pack without initializing any of its elements.
    **/
    BOOST_FORCEINLINE pack() BOOST_NOEXCEPT {}

    /// @brief Copy constructor
    BOOST_FORCEINLINE pack(pack const& rhs) BOOST_NOEXCEPT : data_(rhs.data_) {}

    /*!
      @brief Construct a pack from aligned, contiguous memory

      Construct a pack by loading @c N value from the pointer @c ptr which references
      an block of contiguous, aligned memory.

      @pre @c ptr is aligned and reference at least @c N contiguous elements.

      @param ptr Pointer to load from
    **/
    BOOST_FORCEINLINE explicit pack(T const* ptr) BOOST_NOEXCEPT
                              : data_( boost::simd::aligned_load<pack>(ptr).storage() )
    {}

    /*!
      @brief Construct a pack from a standard array of element

      Construct a pack by loading, every element contained inside the standard array
      @c a .

      @param a Array to load from
    **/
    template<typename U
            , typename = typename std::enable_if< !std::is_same < storage_type
                                                                , std::array<U,N>
                                                                >::value
                                                >::type
            >
    BOOST_FORCEINLINE pack( std::array<U,N> const& a )
                    : data_( boost::simd::load<pack>(&a[0]).storage() )
    {}

    /*!
      @brief Construct a pack from a range of element

      Construct a pack by loading, in a piecewise way, every element contained inside the range
      @c [b,e[ . Contrary to the constructor using aligned contiguous memory, this range can
      be unaligned and non-contiguous.

      @pre <tt>std::distance(e,b) >= N</tt>

      @param b Beginning of the range to load from
      @param e End of the range to load from
    **/
    template < typename Iterator
             , typename = typename std::enable_if<is_iterator<Iterator>::value>::type
             >
    BOOST_FORCEINLINE pack(Iterator b, Iterator e)
                    : data_( boost::simd::load<pack>(b,e).storage() )
    {}

    /*!
      @brief Construct a pack from a set of scalar values

      Construct a pack by inserting, in a piecewise way, the exactly @c N scalar values passed
      as parameters.

      @note The number of scalar values must be equal to the cardinal @c N of the pack.

      @param v0 First scalar value to insert
      @param v1 Second scalar value to insert
      @param vn Remaining scalar values to insert
    **/
    template<typename T0, typename T1, typename... Ts>
    BOOST_FORCEINLINE pack(T0 const& v0, T1 const& v1, Ts const&... vn)
    {
      static_assert( 2 + sizeof...(vn) == static_size
                   , "pack<T,N>(T v...) must take exactly N arguments"
                   );

      data_ = boost::simd::make(as_<pack>{},v0,v1,vn...).storage();
    }

    /*!
      @brief Construct a pack by replicating a scalar value

      @param value The value to replicate
    **/
    template< typename U
            , typename = typename std::enable_if< !std::is_pointer<U>::value >::type
            , typename = typename std::enable_if<std::is_convertible<U, value_type>::value>::type
            >
    BOOST_FORCEINLINE explicit pack(U const& value) BOOST_NOEXCEPT
                      : data_( boost::simd::splat<pack>(value).storage() )
    {}

    /// @brief Scalar assignment operator
    template < typename U
             , typename = typename std::enable_if<std::is_convertible<U, value_type>::value>::type
             >
    BOOST_FORCEINLINE pack& operator=(U const& value) BOOST_NOEXCEPT
    {
      data_ = boost::simd::splat<pack>(value_type(value)).storage();
      return *this;
    }

    /// @brief Pack assignment operator
    BOOST_FORCEINLINE pack& operator=(pack const& rhs) BOOST_NOEXCEPT
    {
      data_ = rhs.data_;
      return *this;
    }

    /// @brief Conversion from underlying storage data
    BOOST_FORCEINLINE pack(storage_type const& reg) BOOST_NOEXCEPT : data_(reg) {}

    /// @brief Assignment from underlying storage data
    BOOST_FORCEINLINE pack& operator=( storage_type const& reg ) BOOST_NOEXCEPT
    {
      data_ = reg;
      return *this;
    }

    /// @brief Conversion to underlying storage data
    BOOST_FORCEINLINE operator storage_type() const BOOST_NOEXCEPT
    {
      return data_;
    }

    /// @brief Get reference to internal storage
    BOOST_FORCEINLINE storage_type& storage() BOOST_NOEXCEPT { return data_; }

    /*!
      @overload
    */
    BOOST_FORCEINLINE storage_type const& storage() const BOOST_NOEXCEPT { return data_; }

    /*!
      @brief Random-access to the pack elements

      Return a reference to the @c i th element of the current pack.

      @note This operation may involves proxy reference and is, in general, costly.

      @param i Index to the element to retrieved
    **/
    BOOST_FORCEINLINE reference operator[](std::size_t i)
    {
      return traits::at(*this, i);
    }

    /*!
      @overload
    */
    BOOST_FORCEINLINE const_reference operator[](std::size_t i) const
    {
      return traits::at(*this, i);
    }

    /*!
      @overload
    */
    template<std::uint64_t Index>
    BOOST_FORCEINLINE value_type operator[](tt::integral_constant<std::uint64_t,Index> const&)
    {
      return ::boost::simd::extract<Index>(*this);
    }

    /*!
      @overload
    */
    template<std::uint64_t Index>
    BOOST_FORCEINLINE value_type operator[](tt::integral_constant<std::uint64_t,Index> const&) const
    {
      return ::boost::simd::extract<Index>(*this);
    }

    BOOST_FORCEINLINE value_type get(std::size_t i) const
    {
      return ::boost::simd::extract(*this, i);
    }

    BOOST_FORCEINLINE void set(std::size_t i, T const& v)
    {
      ::boost::simd::insert(*this, i, v);
    }

    public:

    /// @brief Returns an iterator to the beginning of the pack
    BOOST_FORCEINLINE iterator begin() BOOST_NOEXCEPT
    {
      return iterator(this);
    }

    /*!
      @overload
    */
    BOOST_FORCEINLINE const_iterator begin() const BOOST_NOEXCEPT
    {
      return const_iterator(this);
    }

    /// @brief  Returns an iterator to the end of the pack
    BOOST_FORCEINLINE iterator end() BOOST_NOEXCEPT
    {
      return iterator(this, size());
    }

    /*!
       @overload
    */
    BOOST_FORCEINLINE const_iterator end() const BOOST_NOEXCEPT
    {
      return const_iterator(this, size());
    }

    /// @brief  Returns a constant iterator to the beginning of the pack
    BOOST_FORCEINLINE const_iterator cbegin() const BOOST_NOEXCEPT
    {
      return const_iterator(this);
    }

    /// @brief  Returns a constant iterator to the end of the pack
    BOOST_FORCEINLINE const_iterator cend() const BOOST_NOEXCEPT
    {
      return const_iterator(this, size());
    }

    /// @brief Returns a reverse iterator to the beginning of the pack
    BOOST_FORCEINLINE reverse_iterator rbegin() BOOST_NOEXCEPT
    {
      return reverse_iterator(end());
    }

    /*!
      @overload
    */
    BOOST_FORCEINLINE const_reverse_iterator rbegin() const BOOST_NOEXCEPT
    {
      return reverse_iterator(end());
    }

    /// @brief Returns a reverse iterator to the end of the pack
    BOOST_FORCEINLINE reverse_iterator rend() BOOST_NOEXCEPT
    {
      return reverse_iterator(begin());
    }

    /*!
      @overload
    */
    BOOST_FORCEINLINE const_reverse_iterator rend() const BOOST_NOEXCEPT
    {
      return reverse_iterator(begin());
    }

    /// @brief Returns a constant reverse iterator to the beginning of the pack
    BOOST_FORCEINLINE const_reverse_iterator crbegin() const BOOST_NOEXCEPT
    {
      return const_reverse_iterator(cend());
    }

    /// @brief Returns a constant reverse iterator to the end of the pack
    BOOST_FORCEINLINE const_reverse_iterator crend() const BOOST_NOEXCEPT
    {
      return const_reverse_iterator(cbegin());
    }

    reference       back()        { return traits::at(*this, static_size-1); }
    const_reference back() const  { return traits::at(*this, static_size-1); }

    reference       front()        { return traits::at(*this, 0); }
    const_reference front() const  { return traits::at(*this, 0); }

    // Make operator new/delete  correct
    BOOST_SIMD_ALIGNED_OBJECT(pack)

    public:
    BOOST_FORCEINLINE pack& operator++() BOOST_NOEXCEPT_IF_EXPR(inc(bd::detail::declval<pack>()))
    {
      return (*this = inc(*this));
    }

    BOOST_FORCEINLINE pack& operator--() BOOST_NOEXCEPT_IF_EXPR(dec(bd::detail::declval<pack>()))
    {
      return (*this = dec(*this));
    }

    BOOST_FORCEINLINE pack operator++(int) BOOST_NOEXCEPT_IF_EXPR(++bd::detail::declval<pack>())
    {
      pack that = *this;
      ++(*this);
      return that;
    }

    BOOST_FORCEINLINE pack operator--(int)  BOOST_NOEXCEPT_IF_EXPR(--bd::detail::declval<pack>())
    {
      pack that = *this;
      --(*this);
      return that;
    }

    template <typename Other>
    BOOST_FORCEINLINE pack& operator+=(Other const& other) BOOST_NOEXCEPT
    {
      *this = *this + other;
      return *this;
    }

    template <typename Other>
    BOOST_FORCEINLINE pack& operator-=(Other const& other) BOOST_NOEXCEPT
    {
      *this = *this - other;
      return *this;
    }

    template <typename Other>
    BOOST_FORCEINLINE pack& operator*=(Other const& other) BOOST_NOEXCEPT
    {
      *this = *this * other;
      return *this;
    }

    template <typename Other>
    BOOST_FORCEINLINE pack& operator/=(Other const& other) BOOST_NOEXCEPT
    {
      *this = *this / other;
      return *this;
    }

    template <typename Other>
    BOOST_FORCEINLINE pack& operator%=(Other const& other) BOOST_NOEXCEPT
    {
      *this = *this % other;
      return *this;
    }

    template <typename Other>
    BOOST_FORCEINLINE pack& operator&=(Other const& other) BOOST_NOEXCEPT
    {
      *this = *this & other;
      return *this;
    }

    template <typename Other>
    BOOST_FORCEINLINE pack& operator|=(Other const& other) BOOST_NOEXCEPT
    {
      *this = *this | other;
      return *this;
    }

    template <typename Other>
    BOOST_FORCEINLINE pack& operator^=(Other const& other) BOOST_NOEXCEPT
    {
      *this = *this ^ other;
      return *this;
    }

    public:
    /// @brief Retrieve the pack's cardinal, i.e the number of element in the pack.
    static BOOST_FORCEINLINE size_type size()     BOOST_NOEXCEPT { return static_size; }

    /// @brief Retrieve the pack's maximum size, i.e the number of element in the pack.
    static BOOST_FORCEINLINE size_type max_size() BOOST_NOEXCEPT { return static_size; }

    /// @brief Empty status for pack
    BOOST_FORCEINLINE bool empty() const BOOST_NOEXCEPT { return false; }

    /// @brief Swap data between two packs
    BOOST_FORCEINLINE void swap(pack& rhs) BOOST_NOEXCEPT
    {
      using std::swap;
      swap(data_, rhs.data_);
    }

    private:
    storage_type data_;
  };

  /// @brief Swap two packs of same type and cardinal
  template <typename T, std::size_t N>
  void swap(pack<T, N>& lhs, pack<T, N>& rhs) BOOST_NOEXCEPT
  {
    lhs.swap(rhs);
  }

  /// @brief Stream insertion for pack
  template <typename T, std::size_t N>
  std::ostream& operator<<(std::ostream& os, pack<T, N> const& p)
  {
    os << '(' << +p[0];

    for (std::size_t i=1; i != N; ++i)
      os << ", " << +p[i];

    return os << ')';
  }
} }

#if BOOST_COMP_GNUC
#pragma GCC diagnostic pop
#endif

#include <boost/simd/detail/pack_info.hpp>
#include <boost/simd/detail/pack_operators.hpp>

#endif
