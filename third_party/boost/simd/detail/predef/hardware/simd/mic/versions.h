/*
Copyright 2016 NumScale SAS
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_HARDWARE_SIMD_MIC_VERSIONS_H
#define BOOST_PREDEF_HARDWARE_SIMD_MIC_VERSIONS_H

#include <boost/predef/version_number.h>

/*`
 Those defines represent MIC SIMD extensions versions.

 [note You *MUST* compare them with the predef `BOOST_HW_SIMD_MIC`.]
 */

// ---------------------------------

/*`
 [heading `BOOST_HW_SIMD_MIC_IMCI_VERSION`]

 The [@https://en.wikipedia.org/wiki/Xeon_Phi MIC] (Xeon Phi) x86 extension
 version number.

 Version number is: *9.0.0*.
 */
#define BOOST_HW_SIMD_MIC_IMCI_VERSION BOOST_VERSION_NUMBER(9, 0, 0)

#endif
