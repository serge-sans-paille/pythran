//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_DETAILS_UTILITY_WORKSPACE_HPP_INCLUDED
#define NT2_LINALG_DETAILS_UTILITY_WORKSPACE_HPP_INCLUDED

/*!
  @file
 @brief Wrapper for LAPACK memory workspaces
**/

#include <cstddef>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/linalg/details/utility/options.hpp>

namespace nt2 { namespace details
{
  /**
    @brief LAPACK memory block wrapper

    Every LAPACK routine is able to use a preallocated workspace to optimize
    its own memory allocation within the routine itself. This class is a wrapper
    for these memory buffers and can be used either as a learning process by
    passing an empty workspace to a routine and check how much memory is
    required or as the regular memory block for internal LAPACK usage.
  **/
  template<typename T> class workspace
  {
    public :
    typedef T                                          value_type;
    typedef typename meta::as_real<T>::type       base_value_type;

    typedef memory::buffer<value_type>           main_workspace_t;
    typedef memory::buffer<base_value_type> main_base_workspace_t;
    typedef memory::buffer<nt2_la_int >      main_int_workspace_t;

    typedef typename main_workspace_t::pointer      main_pointer;
    typedef typename main_base_workspace_t::pointer reals_pointer;
    typedef typename main_int_workspace_t::pointer  integers_pointer;
    typedef typename main_int_workspace_t::pointer  logicals_pointer;

    /*!
      @brief Default constructor

      Setup all the workspaces in QUERY mode. Next time such a workspace will
      be passed to a LAPACK routine, workspaces first elements will be set to
      their required size by the routine itself.
    **/
    workspace() : main_(1), reals_(1), integers_(1), logicals_(1) {}

    /*!
      @brief Constructor from specific size

      Initialize a workspace with a given set of size.

      @param w   Number of elements of the main workspace
      @param rw  Number of elements of the real part workspace
      @param iw  Number of elements of the integer workspace
      @param bw  Number of elements of the boolean workspace
    **/
    workspace (std::size_t w, std::size_t rw, std::size_t iw, std::size_t bw = 0)
              : main_     ( std::max(w  , std::size_t(1)) )
              , reals_    ( std::max(rw , std::size_t(1)) )
              , integers_ ( std::max(iw , std::size_t(1)) )
              , logicals_ ( std::max(bw , std::size_t(1)) )
    {}

    /*!
      @brief Resize the workspaces

      Resize all internal workspace to a new number of elements if necessary.

      @param w   New number of elements of the main workspace
      @param rw  New number of elements of the real part workspace
      @param iw  New number of elements of the integer workspace
      @param bw  New number of elements of the boolean workspace
    **/
    void resize ( std::size_t w       , std::size_t rw = 0u
                , std::size_t iw = 0u , std::size_t bw = 0u
                )
    {
      resize_main(w);
      resize_reals(rw);
      resize_integers(iw);
      resize_logicals(bw);
    }

    void prepare_main()
    {
      resize_main(static_cast<nt2_la_int>(nt2::real(main_[0])));
    }

    void prepare_reals()
    {
      resize_reals(static_cast<nt2_la_int>(nt2::real(reals_[0])));
    }

    void prepare_integers()
    {
      resize_integers(static_cast<nt2_la_int>(integers_[0]));
    }

    void prepare_logicals()
    {
      resize_logicals(static_cast<nt2_la_int>(logicals_[0]));
    }

    void resize_main(nt2_la_int s)
    {
      main_size_ = s;
      if(s > nt2_la_int(main_.size()))   main_.resize(s);
    }

    void resize_reals(std::size_t s)
    {
      reals_size_ = s;
      if(s > size_t(reals_.size()))  reals_.resize(s);
    }

    void resize_integers(std::size_t s)
    {
      integers_size_ = s;
      if(s > size_t(integers_.size())) integers_.resize(s);
    }

    void resize_logicals(std::size_t s)
    {
      logicals_size_ = s;
      if(s > size_t(logicals_.size())) logicals_.resize(s);
    }

    bool is_ok(std::size_t w, std::size_t rw, std::size_t iw, std::size_t bw) const
    {
      return    (w >= main_.size())       && (rw >= reals_.size())
            &&  (iw >= integers_.size())  && (bw >= logicals_.size());
    }

    nt2_la_int main_need(nt2_la_int s = 0)
    {
      main_need_ = (s ? s : static_cast<nt2_la_int>(nt2::real(main_[0])));
      return main_need_;
    }

    nt2_la_int reals_need(nt2_la_int s = 0)
    {
      return reals_need_ = (s ? s : static_cast<nt2_la_int>(reals_[0]));
    }

    nt2_la_int integers_need(nt2_la_int s = 0)
    {
      return integers_need_ = (s ? s : integers_[0]);
    }

    nt2_la_int logicals_need(nt2_la_int s = 0)
    {
      return logicals_need_ = (s ? s : logicals_[0]);
    }
    main_pointer     main()      { return &main_[0];     }
    reals_pointer    reals()     { return &reals_[0];    }
    integers_pointer integers()  { return &integers_[0]; }
    logicals_pointer logicals()  { return &logicals_[0]; }

    nt2_la_int main_size()      const { return main_size_;      }
    nt2_la_int reals_size()     const { return reals_size_;     }
    nt2_la_int integers_size()  const { return integers_size_;  }
    nt2_la_int logicals_size()  const { return logicals_size_;  }

    private :
    main_workspace_t      main_;
    main_base_workspace_t reals_;
    main_int_workspace_t  integers_, logicals_;
    nt2_la_int            main_size_,reals_size_,integers_size_,logicals_size_;
    nt2_la_int            main_need_, reals_need_;
    nt2_la_int            integers_need_, logicals_need_;
  };
} }

#endif
