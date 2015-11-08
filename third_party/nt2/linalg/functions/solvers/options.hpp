//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SOLVERS_OPTIONS_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SOLVERS_OPTIONS_HPP_INCLUDED

#include <nt2/linalg/details/utility/options.hpp>

namespace nt2 { namespace solvers {
  class options
  {
  public:
    options(bool t =  false):
      lt_(false),
      ut_(false),
      uhess_(false),
      sym_(false),
      posdef_(false),
      rect_(true),
      transa_(t),
      unidiag_(false),
      general_(true)
    {}

    void lt(bool b){
      lt_ = b;
      if (lt_){
        general_ = posdef_ = sym_ = uhess_ = ut_ = false;
      }
    }
    void ut(bool b){
      ut_ = b;
      if (ut_){
        general_ = posdef_ = sym_ = uhess_ = lt_ = false;
      }
    }
    void uhess(bool b){
      uhess_ = b;
      if (ut_){
        general_ = rect_ = posdef_ = sym_ = lt_= ut_ = false;
      }
    }
    void sym(bool b){
      sym_ = b;
      if (sym_){
        general_ = uhess_ = lt_ = ut_ = false;
      }
    }
    void rect(bool b){
      rect_ = b;
      if (rect_){
        sym_ = posdef_ = uhess_ = lt_ = ut_ = false;
        general_ =  true;
      }
    }

    void posdef(bool b){
      posdef_ = b;
      if (posdef_){
        general_ = uhess_ = lt_ = ut_ = rect_ = false;
      }
    }

    void unidiag(bool b){
      unidiag_ = b;
    }

    void transa(bool b){
      transa_ = b;
    }
    bool ut()const{return ut_; }
    bool lt()const{return lt_; }
    bool uhess()const{return uhess_; }
    bool sym()const{return sym_; }
    bool posdef()const{return posdef_; }
    bool transa()const{return transa_; }
    bool unidiag()const{return unidiag_; }
    bool rect()const{return rect_; }

    const char& uplo()const{return *details::lapack_option(ut_?'u':'l'); }

    template < class t >
    const char& trans(const t & a = 1)const{
      return *details::lapack_option(transa_ ? (!is_real(a)? 'c':'t') :'n');
    }

    const char& uni()const{return *details::lapack_option(unidiag_?'u':'n'); }

    ~options(){};

  private:
    bool lt_;
    bool ut_;
    bool uhess_;
    bool sym_;
    bool posdef_;
    bool rect_;
    bool transa_;
    bool unidiag_;
    bool general_;
  };
} }

#endif
