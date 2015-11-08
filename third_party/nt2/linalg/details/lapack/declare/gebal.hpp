//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_LAPACK_DECLARE_GEBAL_HPP_INCLUDED
#define NT2_LINALG_DETAILS_LAPACK_DECLARE_GEBAL_HPP_INCLUDED
#include <nt2/linalg/details/utility/f77_wrapper.hpp>


/* ! \file gebal_itf.hh

    *
    **  purpose
    **  =======
    **
    **  xgebal balances a general DATA TYPE matrix a.  this involves, first,
    **  permuting a by a similarity transformation to isolate eigenvalues
    **  in the first 1 to ilo-1 and last ihi+1 to n elements on the
    **  diagonal; and second, applying a diagonal similarity transformation
    **  to rows and columns ilo to ihi to make the rows and columns as
    **  close in norm as possible.  both steps are optional.
    **
    **  balancing may reduce the 1-norm of the matrix, and improve the
    **  accuracy of the computed eigenvalues and/or eigenvectors.
    **
    **  arguments
    **  =========
    **
    **  job     (input) char
    **          specifies the operations to be performed on a:
    **          = 'n':  none:  simply set ilo = 1, ihi = n, scale(i) = 1.0
    **                  for i = 1,...,n;
    **          = 'p':  permute only;
    **          = 's':  scale only;
    **          = 'b':  both permute and scale.
    **
    **  n       (input) long int
    **          the order of the matrix a.  n >= 0.
    **
    **  a       (input/output) DATA TYPE array, dimension (lda,n)
    **          on entry, the input matrix a.
    **          on exit,  a is overwritten by the balanced matrix.
    **          if job = 'n', a is not referenced.
    **          see further details.
    **
    **  lda     (input) long int
    **          the leading dimension of the array a.  lda >= max(1,n).
    **
    **  ilo     (output) long int
    **  ihi     (output) long int
    **          ilo and ihi are set to integers such that on exit
    **          a(i,j) = 0 if i > j and j = 1,...,ilo-1 or i = ihi+1,...,n.
    **          if job = 'n' or 's', ilo = 1 and ihi = n.
    **
    **  scale   (output) BASE DATA TYPE array, dimension (n)
    **          details of the permutations and scaling factors applied to
    **          a.  if p(j) is the index of the row and column interchanged
    **          with row and column j and d(j) is the scaling factor
    **          applied to row and column j, then
    **          scale(j) = p(j)    for j = 1,...,ilo-1
    **                   = d(j)    for j = ilo,...,ihi
    **                   = p(j)    for j = ihi+1,...,n.
    **          the order in which the interchanges are made is n to ihi+1,
    **          then 1 to ilo-1.
    **
    **  info    (output) long int
    **          = 0:  successful exit.
    **          < 0:  if info = -i, the i-th argument had an illegal value.
    **
    **  further details
    **  ===============
    **
    **  the permutations consist of row and column interchanges which put
    **  the matrix in the form
    **
    **             ( t1   x   y  )
    **     p a p = (  0   b   z  )
    **             (  0   0   t2 )
    **
    **  where t1 and t2 are upper triangular matrices whose eigenvalues lie
    **  along the diagonal.  the column indices ilo and ihi mark the starting
    **  and ending columns of the submatrix b. balancing consists of applying
    **  a diagonal similarity transformation inv(z) * b * d to make the
    **  1-norms of each row of b and its corresponding column nearly equal.
    **  the output matrix is
    **
    **     ( t1     x*d          y    )
    **     (  0  inv(d)*b*d  inv(d)*z ).
    **     (  0      0           t2   )
    **
    **  information about the permutations p and the diagonal matrix d is
    **  returned in the vector scale.
    **
    **  this subroutine is based on the eispack routine cbal.
    **
    **  modified by tzu-yi chen, computer science division, university of
    **    california at berkeley, usa
    **
**/

extern "C"
{
  void NT2_F77NAME(cgebal)(const char* job      , const nt2_la_int* n
                          , nt2_la_complex* a   , const nt2_la_int* lda
                          ,  nt2_la_int* ilo    , nt2_la_int* ihi,
                           float* scale         , nt2_la_int* info);
  void NT2_F77NAME(dgebal)(const char* job      , const nt2_la_int* n
                          , double* a           , const nt2_la_int* lda
                          ,  nt2_la_int* ilo    , nt2_la_int* ihi
                          , double* scale       , nt2_la_int* info);
  void NT2_F77NAME(sgebal)(const char* job      , const nt2_la_int* n
                          , float* a            , const nt2_la_int* lda
                          ,  nt2_la_int* ilo    , nt2_la_int* ihi
                          , float* scale        , nt2_la_int* info);
  void NT2_F77NAME(zgebal)(const char* job      , const nt2_la_int* n
                          , nt2_la_complex* a   , const nt2_la_int* lda
                          , nt2_la_int* ilo     , nt2_la_int* ihi
                          , double* scale       , nt2_la_int* info);
}

#endif
