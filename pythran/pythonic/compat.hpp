#ifndef PYTHONIC_COMPAT_HPP

#ifdef _MSC_VER
#define PYTHONIC_VISUAL_STUDIO
#endif

/* and | or | not... support
 */
#if defined(PYTHONIC_VISUAL_STUDIO)
#include <ciso646>
#endif

/* noexcept support
 */
#if defined(PYTHONIC_VISUAL_STUDIO)
#define PYTHONIC_NOEXCEPT throw()
#else
#define PYTHONIC_NOEXCEPT noexcept
#endif

/* constexpr support
 */
#if defined(PYTHONIC_VISUAL_STUDIO)
#define PYTHONIC_CONSTEXPR const
#else
#define PYTHONIC_CONSTEXPR constexpr
#endif

#endif
