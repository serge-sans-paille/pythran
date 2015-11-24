#ifndef PYTHONIC_BUILTIN_XRANGE_HPP
#define PYTHONIC_BUILTIN_XRANGE_HPP

#include "pythonic/include/__builtin__/xrange.hpp"

#include <iterator>

namespace pythonic
{

  namespace __builtin__
  {

    xrange_iterator::xrange_iterator()
    {
    }

    xrange_iterator::xrange_iterator(long v, long s)
        : value(v), step(s), sign(s < 0 ? -1 : 1)
    {
    }

    typename xrange_iterator::reference xrange_iterator::operator*() const
    {
      return value;
    }

    xrange_iterator &xrange_iterator::operator++()
    {
      value += step;
      return *this;
    }

    xrange_iterator xrange_iterator::operator++(int)
    {
      xrange_iterator self(*this);
      value += step;
      return self;
    }

    xrange_iterator &xrange_iterator::operator+=(long n)
    {
      value += step * n;
      return *this;
    }

    bool xrange_iterator::operator!=(xrange_iterator const &other) const
    {
      return value != other.value;
    }

    bool xrange_iterator::operator==(xrange_iterator const &other) const
    {
      return value == other.value;
    }

    bool xrange_iterator::operator<(xrange_iterator const &other) const
    {
      return sign * value < sign * other.value;
    }

    long xrange_iterator::operator-(xrange_iterator const &other) const
    {
      return (value - other.value) / step;
    }

    xrange_riterator::xrange_riterator()
    {
    }

    xrange_riterator::xrange_riterator(long v, long s)
        : value(v), step(s), sign(s < 0 ? 1 : -1)
    {
    }

    long xrange_riterator::operator*()
    {
      return value;
    }

    xrange_riterator &xrange_riterator::operator++()
    {
      value += step;
      return *this;
    }

    xrange_riterator xrange_riterator::operator++(int)
    {
      xrange_riterator self(*this);
      value += step;
      return self;
    }

    xrange_riterator &xrange_riterator::operator+=(long n)
    {
      value += step * n;
      return *this;
    }

    bool xrange_riterator::operator!=(xrange_riterator const &other) const
    {
      return value != other.value;
    }

    bool xrange_riterator::operator==(xrange_riterator const &other) const
    {
      return value == other.value;
    }

    bool xrange_riterator::operator<(xrange_riterator const &other) const
    {
      return sign * value > sign * other.value;
    }

    long xrange_riterator::operator-(xrange_riterator const &other) const
    {
      return (value - other.value) / step;
    }

    void xrange::_init_last()
    {
      if (_step > 0)
        _last = _begin +
                std::max(0L, _step * ((_end - _begin + _step - 1) / _step));
      else
        _last = _begin +
                std::min(0L, _step * ((_end - _begin + _step + 1) / _step));
    }

    xrange::xrange()
    {
    }

    xrange::xrange(long b, long e, long s) : _begin(b), _end(e), _step(s)
    {
      _init_last();
    }

    xrange::xrange(long e) : _begin(0), _end(e), _step(1), _last(e)
    {
    }

    xrange_iterator xrange::begin() const
    {
      return xrange_iterator(_begin, _step);
    }

    xrange_iterator xrange::end() const
    {
      return xrange_iterator(_last, _step);
    }

    typename xrange::reverse_iterator xrange::rbegin() const
    {
      return {_last - _step, -_step};
    }

    typename xrange::reverse_iterator xrange::rend() const
    {
      return {_begin - _step, -_step};
    }

    // clang++ is not happy with PROXY
    namespace functor
    {
      template <class... Types>
      pythonic::__builtin__::xrange xrange::operator()(Types &&... args)
      {
        return pythonic::__builtin__::xrange(std::forward<Types>(args)...);
      }
    }
  }
}

#endif
