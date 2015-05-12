#ifndef PYTHONIC_INCLUDE_BUILTIN_GETATTR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_GETATTR_HPP

namespace pythonic
{

  namespace __builtin__
  {

    template <class T, size_t AttributeID>
    void getattr(T const &self);
  }
}
#endif
