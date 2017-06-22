//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DIAGNOSTIC_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DIAGNOSTIC_HPP_INCLUDED

#include <ostream>
#include <iostream>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch/detail/declval.hpp>

#if defined(BOOST_SIMD_ENABLE_DIAG)

namespace boost { namespace simd { namespace detail
{
  namespace bd = boost::dispatch;

// Use template so that we don't need static instantiation in a .cpp, this prevents
// linkage from failing..
template <typename Stream = std::ostream>
class diagnostic
{
  using stream_type = Stream;

  template <typename T>
  struct is_streamable
  {
    template <typename U>
    static auto test( int ) -> decltype( std::cout << bd::detail::declval<U>()
                                       , tt::true_type()
                                       );

    template<typename>
    static auto test( ... ) -> tt::false_type;

    using type = typename std::is_same<decltype(test<T>(0)), tt::true_type>::type;
  };

  template <typename T, typename R>
  using if_streamable = typename std::enable_if<is_streamable<T>::type::value, R>::type;

  template <typename T, typename R>
  using if_not_streamable = typename std::enable_if<!is_streamable<T>::type::value, R>::type;

  // Automatically add a '\n' at the end
  class stream_flusher
  {
    public:
    stream_flusher(stream_type& pos) : os_(pos) {}

    ~stream_flusher()
    {
      os_ << "\n";
      os_.flush();
    }

    stream_type& os() { return os_; }

    private:
    stream_type& os_;
  };

  // Print a pretty type_id whenever the argument is not streamable
  class stream_proxy
  {
    public:
    stream_proxy(stream_proxy&&) = default;
    stream_proxy(stream_proxy const&) = default;
    stream_proxy(stream_type& os) : stream_(new stream_flusher(os)) {}

    template <typename T>
    if_streamable<T, stream_proxy>& operator<<(T const& something)
    {
      stream_->os() << something;
      return *this;
    }

    template <typename T>
    if_not_streamable<T, stream_proxy>& operator<<(T const&)
    {
      stream_->os() << boost::core::demangle(typeid(T).name());
      return *this;
    }

    private:
    std::shared_ptr<stream_flusher> stream_;
  };

  private:
  diagnostic(stream_type* os = &std::cout) : os_(os) {}

  public:
  ~diagnostic() { delete instance_; }

  public:
  static diagnostic& instance()
  {
    if (instance_ == nullptr) {
      instance_ = new diagnostic();
    }
    return *instance_;
  }

  stream_proxy stream()
  {
    return stream_proxy(*os_) << "boost::simd(diagnostic): ";
  }

  private:
  static diagnostic* instance_;

  private:
  stream_type* os_;
};

template <typename T>
diagnostic<T>* diagnostic<T>::instance_ = nullptr;

} } }

#define BOOST_SIMD_DIAG(expr)                                                                      \
  ::boost::simd::detail::diagnostic<>::instance().stream() << expr                                 \
  /**/

#else

#define BOOST_SIMD_DIAG(expr)

#endif


#endif
