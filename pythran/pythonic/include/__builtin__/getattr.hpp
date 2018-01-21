#ifndef PYTHONIC_INCLUDE_BUILTIN_GETATTR_HPP
#define PYTHONIC_INCLUDE_BUILTIN_GETATTR_HPP

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  template <class T, size_t AttributeID>
  void getattr(T const &self);
}
PYTHONIC_NS_END
#endif
