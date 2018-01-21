#ifndef PYTHONIC_INCLUDE_TYPES_ATTR_HPP
#define PYTHONIC_INCLUDE_TYPES_ATTR_HPP

PYTHONIC_NS_BEGIN

namespace types
{

  struct attr {
    enum {
      /* exception attributes */
      ARGS,
      ERRNO,
      STRERROR,
      FILENAME,
      /* complex attributes */
      REAL,
      IMAG,
      /* file attributes */
      CLOSED,
      MODE,
      NAME,
      NEWLINES,
      /* fileinfo attributes */
      EPS,
      /* ndarray attributes */
      SHAPE,
      NDIM,
      STRIDES,
      SIZE,
      ITEMSIZE,
      NBYTES,
      FLAT,
      DTYPE,
      T,
      /* */
      SUPERCALIGRAFILISTICEXPIDELILICIOUS
    };
  };
}
PYTHONIC_NS_END

#endif
