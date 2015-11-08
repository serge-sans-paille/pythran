//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SWAR_FUNCTIONS_EXPR_SORT_HPP_INCLUDED
#define NT2_SWAR_FUNCTIONS_EXPR_SORT_HPP_INCLUDED

#include <boost/simd/swar/functions/sort.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/core/container/table/table.hpp>
#include <algorithm>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/include/functions/indices.hpp>
#include <nt2/include/functions/linesstride.hpp>
#include <nt2/sdk/meta/is_target.hpp>
#include <string>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of sort is called whenever a tie(...) = sort(...) is captured
  // before assign is resolved. As a tieable function, sort retrieves rhs/lhs
  // pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sort_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::sort_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       child0;
    typedef typename meta::strip<child0>::type                        st_child0;
    typedef typename st_child0::value_type                           value_type;
    typedef typename st_child0::index_type                           index_type;
    typedef container::table<value_type,index_type>                       res_t;
    typedef typename st_child0::extent_type                               ext_t;
    typedef typename result_of::as_subscript<ext_t,size_t>::type          sub_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      // Copy data in output first
      //      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      //     std::cout << display_type<ct>() << std::endl;
      size_t dim = 1;
      bool up = true;
      //retrieve options
      choice(a0, up, dim, N0());
      // compute the sorted result
      compute(a0, a1, up,  dim, N0(), N1(), typename meta::is_target<child0>::type() );
    }

  private:
    BOOST_FORCEINLINE void
    choice(A0 const &, bool& up, size_t & dim, boost::mpl::long_<1> const &) const
    {
      up = true;  dim = 1;
    }

    BOOST_FORCEINLINE void
    choice(A0 const & a0, bool& up, size_t & dim, boost::mpl::long_<2> const &) const
    {
      check(boost::proto::value(boost::proto::child_c<1>(a0)), up, dim);
    }

    BOOST_FORCEINLINE void
    choice(A0 const & a0, bool& up, size_t & dim, boost::mpl::long_<3> const &) const
    {
      const char mode = boost::proto::value(boost::proto::child_c<2>(a0));
//     BOOST_ASSERT_MSG( std::strcmp("descend", mode) == 0 || std::strcmp("ascend", mode) == 0,
//                       "sorting direction must be 'ascend' or 'descend'");
      up = mode == 'a';
      dim = boost::proto::value(boost::proto::child_c<1>(a0));
    }

    //==============================================================================================
    // checking ascend or descend or dim
    // according to the type of boost::proto::value(boost::proto::child_c<1>(a0))
    // const char * or size_t
    //==============================================================================================
    BOOST_FORCEINLINE  void
    check(const size_t  mode, bool& up, size_t & dim) const
    {
      if (mode < 65)
      {
        up = true; dim = mode;
      }
      else
      {
        BOOST_ASSERT_MSG( 'd' == mode || 'a' ==  mode,
                          "sorting direction must be 'a' or 'd'");

        up = mode == 'a'; dim = 1;
      }
    }

//  BOOST_FORCEINLINE void
//  check(const char * mode, bool& up, size_t & dim) const
//  {
// // BOOST_ASSERT_MSG( std::strcmp("descend", mode) == 0 || std::strcmp("ascend", mode) == 0,
// //                   "sorting direction must be 'ascend' or 'descend'");
//    std::cout << "check char *" << mode << std::endl;
//    up = mode[0] == 'a';
//    dim = 1;
//  }

//  BOOST_FORCEINLINE  void
//  check(const size_t d, bool& up, size_t & dim) const
//  {
//    std::cout << "check size_t " << d << std::endl;
//    up = true;
//    dim = d;
//  }

    //==============================================================================================
    // computing the sorted array
    //==============================================================================================
    BOOST_FORCEINLINE
    void compute(A0 const&a0, A1 & a1, bool, size_t, boost::mpl::long_<1> const&, boost::mpl::long_<1> const&, boost::mpl::false_ const &) const
    {
      // no options  -> up =  true,  dim = 1;
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      dosort(boost::proto::child_c<0>(a1));
    }

    BOOST_FORCEINLINE
    void compute(A0 const&a0, A1 & a1, bool up, size_t dim, boost::mpl::long_<2> const&, boost::mpl::long_<1> const&, boost::mpl::false_ const &) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      dosort(boost::proto::child_c<0>(a1), up, dim);
    }

    BOOST_FORCEINLINE
    void compute(A0 const& a0, A1 & a1, bool up, size_t dim, boost::mpl::long_<3> const&, boost::mpl::long_<1> const&, boost::mpl::false_ const &) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      dosort(boost::proto::child_c<0>(a1), up, dim);
    }

    BOOST_FORCEINLINE
    void compute( A0 const& a0, A1 & a1
                , bool, size_t
                , boost::mpl::long_<1> const&, boost::mpl::long_<2> const&
                , boost::mpl::false_ const &
                ) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      // no options  -> up =  true,  dim = 1;
      doindsort(boost::proto::child_c<0>(a1), boost::proto::child_c<1>(a1));
    }

    BOOST_FORCEINLINE
    void compute(A0 const& a0, A1 & a1, bool up, size_t dim, boost::mpl::long_<2> const&, boost::mpl::long_<2> const&, boost::mpl::false_ const &) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      doindsort(boost::proto::child_c<0>(a1), boost::proto::child_c<1>(a1), up, dim);
    }

    BOOST_FORCEINLINE
    void compute(A0 const& a0, A1 & a1, bool up, size_t dim, boost::mpl::long_<3> const&, boost::mpl::long_<2> const&, boost::mpl::false_ const &) const
    {
      boost::proto::child_c<0>(a1) = boost::proto::child_c<0>(a0);
      doindsort(boost::proto::child_c<0>(a1), boost::proto::child_c<1>(a1), up, dim);
    }

    BOOST_FORCEINLINE
    void compute(A0 const& a0, A1 & a1, bool, size_t, boost::mpl::long_<1> const&, boost::mpl::long_<2> const&, boost::mpl::true_ const &) const
    {
      // no options  -> up =  true,  dim = 1;
      doindsort2(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a1));
    }

    BOOST_FORCEINLINE
    void compute(A0 const& a0, A1 & a1, bool up, size_t dim, boost::mpl::long_<2> const&, boost::mpl::long_<2> const&, boost::mpl::true_ const &) const
    {
      doindsort2(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a1), up, dim);
    }

    BOOST_FORCEINLINE
    void compute(A0 const& a0, A1 & a1, bool up, size_t dim, boost::mpl::long_<3> const&, boost::mpl::long_<2> const&, boost::mpl::true_ const &) const
    {
      doindsort2(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a1), up, dim);
    }

    static bool sort_up (value_type i,value_type j) { return (i<j); }
    static bool sort_dn (value_type i,value_type j) { return (i>j); }
    template <class T> BOOST_FORCEINLINE
    void dosort(T & res,  bool up = true, size_t dim = 1) const
    {
      size_t h = nt2::size(res, dim);
      if (h <= 1) return;
      size_t nbslice =  numel(res)/h;
//    if (dim == 1)
//    {
//      value_type* beg = res.raw();
//      value_type* fin = beg+h;
//      for(size_t i=0; i < nbslice; ++i)
//      {
//        std::sort(beg, fin, up?&sort_up:&sort_dn);
//        beg = fin; fin+= h;
//      }
//    }
//    else
//    {
        size_t stride = linesstride(res, dim);
        size_t decal =  stride*(size(res, dim)-1);
        size_t p = 0;
        value_type* beg = res.raw();
        for(size_t i=0; i < nbslice; ++i)
        {
          sub_t pos = as_subscript(res.extent(), p);

          if (pos[dim-1]!= 0)
          {
            p+= decal;
          }
          tri(beg+p, stride, h, up?&sort_up:&sort_dn);
          ++p;
        }
//    }
    }
    template <class T, class iT> BOOST_FORCEINLINE
      void doindsort(T & res,  iT & idx, bool up = true, size_t dim = 1) const
    {
      typedef typename iT::value_type                           i_type;
      typedef typename boost::mpl::at_c< typename T::index_type::index_type, 0>::type  ind_type;
      // here 0 has to be replaced by min(dim-1, size(index_type)),  but dim-1 is run-time
      // and I dont know how to simpy take the ith element of the index_type
      const i_type base = ind_type::value-1;
      idx =  nt2::indices(size(res), nt2::over(dim), meta::as_<i_type>())+base;

      size_t h = nt2::size(res, dim);
      if (h <= 1) return;
      size_t nbslice =  numel(res)/h;
      size_t stride = linesstride(res, dim);
      size_t decal = stride*(size(res, dim)-1);
      size_t p = 0;
      value_type* beg = res.raw();
      i_type* bep = idx.raw();
      for(size_t i=0; i < nbslice; ++i)
      {
        sub_t pos = as_subscript(res.extent(), p);
        if (pos[dim-1]!= 0)
        {
          p+= decal;
        }
        indtri(beg+p, bep+p, stride, h, up?&sort_up:&sort_dn);
        ++p;
      }
    }

    template <class T, class iT> BOOST_FORCEINLINE
    void doindsort2(T & res,  iT & idx, bool up = true, size_t dim = 1) const
    {
      typedef typename iT::value_type                           i_type;
      typedef typename boost::mpl::at_c< typename T::index_type::type, 0>::type  ind_type;
      // here 0 has to be replaced by min(dim-1, size(index_type)),  but dim-1 is run-time
      // and I dont know how to simpy take the ith element of the index_type
      idx =  nt2::indices(size(res), nt2::over(dim), meta::as_<i_type>())-One<i_type>();
      //base 0 here for indexing the raw array

      size_t h = nt2::size(res, dim);
      if (h <= 1) { idx = idx+ind_type::value; return; }
      size_t nbslice =  numel(res)/h;
      size_t stride = linesstride(res, dim);
      size_t decal = stride*(size(res, dim)-1);
      size_t p = 0;
      value_type* beg = res.raw();
      i_type* bep = idx.raw();
      for(size_t i=0; i < nbslice; ++i)
      {
        sub_t pos = as_subscript(res.extent(), p);
        if (pos[dim-1]!= 0)
        {
          p+= decal;
        }
        indtri2(beg+p, bep+p, stride, h, up?&sort_up:&sort_dn);
        ++p;
      }
      idx = idx+ind_type::value;
    }

    // This is a classical heap sort with a constant stride between
    // elements to be sorted
    template < class T, class S> static void
    heap(T * data, const size_t stride, const size_t N, size_t k, const S& comp)
    {
      T v = data[k*stride];
      while (k <= N >> 1)
      {
        size_t j = k << 1;
        if (j < N && comp(data[j*stride], data[(j+1)*stride])) ++j;
        if (!(comp(v, data[j*stride]))) break; /* avoid infinite loop if nan */
        data[k*stride] = data[j*stride];
        k = j;
      }
      data[k*stride] = v;
    }

    template < class T, class S > static void
    tri (T * data, const size_t stride, const size_t n, const S& comp)
    {
      if (n == 0) return;                   /* No data to sort */
      /* We have n_data elements, last element is at 'n_data-1', first at
         '0' Set N to the last element number. */
      size_t N = n - 1;
      size_t k = N >> 1;
      ++k; //Compensate the first use of 'k--'
      do
      {
        --k;
        heap(data, stride, N, k, comp);
      } while (k > 0);

      while (N > 0)
      {
        // first swap the elements
        std::swap( data[0],data[N*stride]);
//      T tmp = data[0 * stride];
//      data[0 * stride] = data[N * stride];
//      data[N * stride] = tmp;
        // then process the heap
        N--;
        heap(data, stride, N, 0, comp);
      }
    }

    template < class T, class iT, class S> static void
    indheap(T * data, iT * idx, const size_t stride, const size_t N, size_t k, const S& comp)
    {
      T v = data[k*stride];
      iT ind = idx[k*stride];
      while (k <= N >> 1)
      {
        size_t j = k << 1;
        if (j < N && comp(data[j*stride], data[(j+1)*stride])) ++j;
        if (!(comp(v, data[j*stride]))) break; /* avoid infinite loop if nan */
        data[k*stride] = data[j*stride];
        idx[k*stride] = idx[j*stride];
        k = j;
      }
      data[k*stride] = v;
      idx[k*stride] = ind;
    }

    template < class T, class iT, class S > static void
    indtri (T * data, iT* idx, const size_t stride, const size_t n, const S& comp)
    {
      if (n == 0) return;                   /* No data to sort */
      /* We have n_data elements, last element is at 'n_data-1', first at
         '0' Set N to the last element number. */
      size_t N = n - 1;
      size_t k = N >> 1;
      ++k; //Compensate the first use of '--k'
      do
      {
        --k;
        indheap(data, idx, stride, N, k, comp);
      } while (k > 0);

      while (N > 0)
      {
        // first swap the elements
        std::swap( data[0],data[N*stride]);
        std::swap( idx[0],  idx[N*stride]);
//      T tmp = data[0 * stride];
//      data[0 * stride] = data[N * stride];
//      data[N * stride] = tmp;
//      iT itmp = idx[0 * stride];
//      idx[0 * stride] = idx[N * stride];
//      idx[N * stride] = itmp;
        // then process the heap
        N--;
        indheap(data, idx, stride, N, 0, comp);
      }
    }

    // This is a classical heap indsort with a constant stride between
    // elements to be indsorted
    template < class T, class iT, class S> static void
    indheap2(const T * data, iT * idx, const size_t stride, const size_t N, size_t k, const S& comp)
    {
      const iT idki = idx[k*stride];
      while (k <= N >> 1)
      {
        size_t j = k << 1;
        if (j < N && comp(data[idx[j*stride]], data[idx[(j+1)*stride]])) ++j;
        if (!(comp(data[idki], data[idx[j*stride]]))) break; /* avoid infinite loop if nan */
        idx[k*stride] = idx[j*stride];
        k = j;
      }
      idx[k*stride] = idki;
    }

    template < class T, class iT, class S > static void
    indtri2 (T * data, iT* idx, const size_t stride, const size_t n, const S& comp)
    {
      if (n == 0) return;                   /* No data to indsort */
      /* We have n_data elements, last element is at 'n_data-1', first at
         '0' Set N to the last element number. */
      size_t N = n - 1;
      size_t k = N >> 1;
      ++k; //Compensate the first use of '--k'
      do
      {
        --k;
        indheap2(data, idx, stride, N, k, comp);
      } while (k > 0);

      while (N > 0)
      {
        // first swap the elements
        std::swap(idx[0],idx[N*stride]);
//      iT itmp = idx[0 * stride];
//      idx[0 * stride] = idx[N * stride];
//      idx[N * stride] = itmp;
        // then process the heap
        N--;
        indheap2(data, idx, stride, N, 0, comp);
      }
    }
  };
} }

#endif
