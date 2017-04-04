//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_BOOLEAN_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_HPP_INCLUDED

namespace boost { namespace simd
{
  /*!
    @ingroup group-functions
    @defgroup group-boolean Boolean functions

      These functions provide SIMD algorithms for logical operations and branching
      in SIMD mode, their use is possible but not encouraged on scalars entries.

      All these functions can be included individually or all of them just by including <boost/simd/boolean.hpp>

      - **Logical operators**

        These functions return boost::simd::logical values, do not support short-circuiting
        and act in an elementwise way on SIMD vectors.

       <center>
         |                     |                     |                   |
         |:-------------------:|:-------------------:|:-----------------:|
         | @ref logical_and    | @ref logical_andnot | @ref logical_not  |
         | @ref logical_notand | @ref logical_notor  | @ref logical_or   |
         | @ref logical_ornot  | @ref logical_xor    | @ref mask2logical |
        </center>

        Masks are pattern of bits all zeros or all ones that can allow masking
        using bitwise operations. @ref mask2logical provides a way to transform a mask vector
        into a logical vector.

        Logical types are architecture dependant,  for instance on intel sse or avx
        logical types are mask valued simd vectors.

      - **Branching utilities**

        Be aware that using SIMD and branching are quite antagonist.

        For instance if a SIMD vector contains more than one element (!) a test on the
        elements will simultaneouly return true for some and false
        for others: so branching in simd may be described as 'compute all branches and select the
        pertinent results...'

        The functors listed above are of interest when one of the branches is much cheaper
        than the other.

        All branching utilities begin by if_ or ifnot_. The first parameter is a SIMD test
        pack which may be of any available type. This test pack is used to determine which branch
        will be selected for each element of the result vector. Non-zero elements are considered as true
        and zero elements as false. The result of each branch is given in the following parameters
        either implicitly or explicitly.

        These functors will generally compute all possible outcomes and then select the
        correct one. If each branch has the same cost (notwithstanding the cost of the test
        and the inner pipelining of the processor) the cost of the branching operation may
        be twice as expensive as the cost of evaluating one of the branches.
        It is for this reason that these functions are of greatest interest when the cardinal of
        the simd vector is greater than 2.

       <center>
         |                             |                           |                          |                       |
         |:---------------------------:|:-------------------------:|:------------------------:| :--------------------:|
         | @ref if_allbits_else        | @ref if_allbits_else_zero | @ref if_dec              | @ref if_else_allbits  |
         | @ref if_else                | @ref if_else_nan          | @ref if_else_zero        | @ref if_inc           |
         | @ref if_minus               | @ref if_nan_else          | @ref if_neg              | @ref if_one_else_zero |
         | @ref if_plus                | @ref if_zero_else_allbits | @ref if_zero_else        | @ref if_zero_else_one |
         | @ref ifnot_dec              | @ref ifnot_inc            | @ref ifnot_minus         | @ref ifnot_neg        |
         | @ref ifnot_plus             |                           |                          |                       |
       </center>

  **/

} }

#include <boost/simd/function/if_allbits_else.hpp>
#include <boost/simd/function/if_allbits_else_zero.hpp>
#include <boost/simd/function/if_else_allbits.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_else_nan.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/ifnot_plus.hpp>
#include <boost/simd/function/ifnot_dec.hpp>
#include <boost/simd/function/ifnot_inc.hpp>
#include <boost/simd/function/ifnot_minus.hpp>
#include <boost/simd/function/if_one_else_zero.hpp>
#include <boost/simd/function/if_zero_else_allbits.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/if_zero_else_one.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/logical_andnot.hpp>
#include <boost/simd/function/logical_notand.hpp>
#include <boost/simd/function/logical_notor.hpp>
#include <boost/simd/function/logical_ornot.hpp>
#include <boost/simd/function/logical_xor.hpp>
#include <boost/simd/function/mask2logical.hpp>
#include <boost/simd/function/if_neg.hpp>
#include <boost/simd/function/ifnot_neg.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/if_dec.hpp>
#include <boost/simd/function/if_inc.hpp>
#include <boost/simd/function/if_minus.hpp>

#endif
