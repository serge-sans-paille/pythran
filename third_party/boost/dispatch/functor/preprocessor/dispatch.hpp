//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_DISPATCH_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros for registering a functor overload
 */

#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/dispatch/functor/details/dispatch.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// Helpers that strips each element of a sequence
#define BOOST_DISPATCH_TYPE_TPL(z,n,t) BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define BOOST_DISPATCH_TYPE(z,n,t) class BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))
#define BOOST_DISPATCH_ARG(z,n,t) , BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t)) const
#define BOOST_DISPATCH_TAG(z,n,t) BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(n,t))

// Namespace-related helpers
#define BOOST_DISPATCH_NS_(s,data,elem) elem ::
#define BOOST_DISPATCH_NS(seq) :: BOOST_PP_SEQ_FOR_EACH(BOOST_DISPATCH_NS_, ~, seq)

#define BOOST_DISPATCH_CLOSE_(s,data,elem) }
#define BOOST_DISPATCH_CLOSE(seq) BOOST_PP_SEQ_FOR_EACH(BOOST_DISPATCH_CLOSE_, ~, seq)

#define BOOST_DISPATCH_REOPEN_(s,data,elem) namespace elem {
#define BOOST_DISPATCH_REOPEN(seq) BOOST_PP_SEQ_FOR_EACH(BOOST_DISPATCH_REOPEN_, ~, seq)

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq).
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_TO(NS, Tag, Site, Types, Seq, Ret)             \
BOOST_DISPATCH_CLOSE(NS)                                                       \
namespace boost { namespace dispatch { namespace meta                          \
{                                                                              \
  template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                            \
                         , BOOST_DISPATCH_TYPE                                 \
                         , Types                                               \
                         )                                                     \
          >                                                                    \
  BOOST_DISPATCH_FORCE_INLINE                                                  \
  BOOST_DISPATCH_PP_STRIP(Ret)                                                 \
  dispatching( BOOST_DISPATCH_PP_STRIP(Tag), BOOST_DISPATCH_PP_STRIP(Site)     \
               BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                         \
                              , BOOST_DISPATCH_ARG                             \
                              , Seq                                            \
                            )                                                  \
            , adl_helper = adl_helper()                                        \
            )                                                                  \
  {                                                                            \
    return BOOST_DISPATCH_PP_STRIP(Ret)();                                     \
  }                                                                            \
} } }                                                                          \
BOOST_DISPATCH_REOPEN(NS)                                                      \
/**/

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq), where Seq can
 * contain non-type hierarchy template parameters.
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_TPL_TO(NS, Tag, Site, Types, Seq, Ret)         \
BOOST_DISPATCH_CLOSE(NS)                                                       \
namespace boost { namespace dispatch { namespace meta                          \
{                                                                              \
  template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                            \
                         , BOOST_DISPATCH_TYPE_TPL                             \
                         , Types                                               \
                         )                                                     \
          >                                                                    \
  BOOST_DISPATCH_FORCE_INLINE                                                  \
  BOOST_DISPATCH_PP_STRIP(Ret)                                                 \
  dispatching( BOOST_DISPATCH_PP_STRIP(Tag), BOOST_DISPATCH_PP_STRIP(Site)     \
               BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                         \
                              , BOOST_DISPATCH_ARG                             \
                              , Seq                                            \
                              )                                                \
            , adl_helper = adl_helper()                                        \
            )                                                                  \
  {                                                                            \
    return BOOST_DISPATCH_PP_STRIP(Ret)();                                     \
  }                                                                            \
} } }                                                                          \
BOOST_DISPATCH_REOPEN(NS)                                                      \
/**/

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq) and if the compile
 * time condition \c Cond is verified.
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Cond Compile-time predicates to verify
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_TO_IF(NS, Tag, Site, Types, Cond, Seq, Ret)    \
BOOST_DISPATCH_CLOSE(NS)                                                       \
namespace boost { namespace dispatch { namespace meta                          \
{                                                                              \
  template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                            \
                         , BOOST_DISPATCH_TYPE                                 \
                         , Types                                               \
                         )                                                     \
          >                                                                    \
  BOOST_DISPATCH_FORCE_INLINE                                                  \
  typename boost::enable_if< BOOST_DISPATCH_PP_STRIP(Cond)                     \
                           , BOOST_DISPATCH_PP_STRIP(Ret)                      \
                           >::type                                             \
  dispatching( BOOST_DISPATCH_PP_STRIP(Tag), BOOST_DISPATCH_PP_STRIP(Site)     \
               BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                         \
                              , BOOST_DISPATCH_ARG                             \
                              , Seq                                            \
                              )                                                \
            , adl_helper = adl_helper()                                        \
            )                                                                  \
  {                                                                            \
    return BOOST_DISPATCH_PP_STRIP(Ret)();                                     \
  }                                                                            \
} } }                                                                          \
BOOST_DISPATCH_REOPEN(NS)                                                      \
/**/

//==============================================================================
/*!
 * Register an overload for function \c Tag on \c Site when called on types
 * belonging to the hierarchies specified by \c (Types,Seq), where Seq can
 * contain non-type hierarchy template parameters and if the compile
 * time condition \c Cond is verified.
 * This forwards to the PFO specified by \c Ret.
 *
 * \param NS Current namespace as a preprocessor sequence
 * \param Tag Function tag to register
 * \param Site Evaluation context to use in this overload
 * \param Types Preprocessor sequence of template types used in the hierarchy
 * \param Cond Compile-time predicates to verify
 * \param Ret Implementation target to select if \c Cond is verified
 * \param Seq Sequence of hierarchy defining the overload
 */
//==============================================================================
#define BOOST_DISPATCH_REGISTER_TPL_TO_IF(NS, Tag, Site, Types, Cond, Seq, Ret) \
BOOST_DISPATCH_CLOSE(NS)                                                       \
namespace boost { namespace dispatch { namespace meta                          \
{                                                                              \
  template< BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Types)                            \
                         , BOOST_DISPATCH_TYPE_TPL                             \
                         , Types                                               \
                         )                                                     \
          >                                                                    \
  BOOST_DISPATCH_FORCE_INLINE                                                  \
  typename boost::enable_if< BOOST_DISPATCH_PP_STRIP(Cond)                     \
                           , BOOST_DISPATCH_PP_STRIP(Ret)                      \
                           >::type                                             \
  dispatching( BOOST_DISPATCH_PP_STRIP(Tag), BOOST_DISPATCH_PP_STRIP(Site)     \
               BOOST_PP_REPEAT( BOOST_PP_SEQ_SIZE(Seq)                         \
                              , BOOST_DISPATCH_ARG                             \
                              , Seq                                            \
                              )                                                \
            , adl_helper = adl_helper()                                        \
            )                                                                  \
  {                                                                            \
    return BOOST_DISPATCH_PP_STRIP(Ret)();                                     \
  }                                                                            \
} } }                                                                          \
BOOST_DISPATCH_REOPEN(NS)                                                      \
/**/

//==============================================================================
// Variants that dispatch to implement<Sig, Site>
//==============================================================================

#define BOOST_DISPATCH_IMPLEMENT_(Tag, Site, Seq)                              \
implement< BOOST_DISPATCH_PP_STRIP(Tag)                                        \
           ( BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(Seq)                             \
                          , BOOST_DISPATCH_TAG                                 \
                          , Seq                                                \
                          )                                                    \
           )                                                                   \
         , BOOST_DISPATCH_PP_STRIP(Site)                                       \
         >                                                                     \
/**/

#define BOOST_DISPATCH_REGISTER(NS, Tag, Site, Types, Seq)                     \
BOOST_DISPATCH_REGISTER_TO( NS, Tag, Site, Types, Seq                          \
                          , ( BOOST_DISPATCH_NS(NS)                            \
                              BOOST_DISPATCH_IMPLEMENT_(Tag, Site, Seq)        \
                            )                                                  \
                          )                                                    \
/**/

#define BOOST_DISPATCH_REGISTER_TPL(NS, Tag, Site, Types, Seq)                 \
BOOST_DISPATCH_REGISTER_TPL_TO( NS, Tag, Site, Types, Seq                      \
                              , ( BOOST_DISPATCH_NS(NS)                        \
                                  BOOST_DISPATCH_IMPLEMENT_(Tag, Site, Seq)    \
                                )                                              \
                              )                                                \
/**/

#define BOOST_DISPATCH_REGISTER_IF(NS, Tag, Site, Types, Cond, Seq)            \
BOOST_DISPATCH_REGISTER_TO_IF( NS, Tag, Site, Types, Cond, Seq                 \
                             , ( BOOST_DISPATCH_NS(NS)                         \
                                 BOOST_DISPATCH_IMPLEMENT_(Tag, Site, Seq)     \
                               )                                               \
                             )                                                 \
/**/

#define BOOST_DISPATCH_REGISTER_TPL_IF(NS, Tag, Site, Types, Cond, Seq)        \
BOOST_DISPATCH_REGISTER_TPL_TO_IF( NS, Tag, Site, Types, Cond, Seq             \
                                 , ( BOOST_DISPATCH_NS(NS)                     \
                                     BOOST_DISPATCH_IMPLEMENT_(Tag, Site, Seq) \
                                   )                                           \
                                 )                                             \
/**/

#endif
