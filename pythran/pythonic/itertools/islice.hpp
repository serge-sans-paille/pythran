#ifndef PYTHONIC_ITERTOOLS_ISLICE_HPP
#define PYTHONIC_ITERTOOLS_ISLICE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/itertools/common.hpp"
#include "pythonic/__builtin__/xrange.hpp"
#include <iterator>

namespace pythonic {

    namespace itertools {
        template <typename Iterable>
            struct islice_iterator : std::iterator< typename Iterable::iterator::iterator_category, typename Iterable::iterator::value_type > {
                typename std::remove_reference<typename std::remove_cv<Iterable>::type>::type iterable_ref;
                typename std::remove_reference<typename std::remove_cv<Iterable>::type>::type::iterator iterable;
                __builtin__::xrange xr_ref;
                __builtin__::xrange_iterator state;
                __builtin__::xrange_iterator::value_type prev;

                islice_iterator() {}
                islice_iterator(Iterable const & iterable, __builtin__::xrange const& xr): xr_ref(xr), iterable_ref(iterable), iterable(iterable_ref.begin()), state(xr_ref.begin()), prev(*state) {
                    std::advance(this->iterable, *state);
                }
                islice_iterator(npos const& n, Iterable const & iterable, __builtin__::xrange const& xr): xr_ref(xr), iterable_ref(iterable), iterable(iterable_ref.begin()), state(xr_ref.end()), prev(0) {}

                typename Iterable::value_type operator*() const {
                    return *iterable;
                }

                islice_iterator& operator++() { 
                    ++state;
                    std::advance(this->iterable, *state-prev);
                    prev = *state;
                    return *this; 
                }

                bool operator==(islice_iterator const& other) const { 
                    return (state == other.state);
                }

                bool operator!=(islice_iterator const& other) const { 
                    return state != other.state;
                }

                bool operator<(islice_iterator const& other) const {
                    return state != other.state;                       
                }

                int operator-(islice_iterator const& other) const {
                    return state - other.state;
                }

            };


        template <typename Iterable>
            struct _islice : islice_iterator<Iterable> {

                typedef islice_iterator<Iterable> iterator;
                typedef typename Iterable::value_type value_type;

                iterator end_iter;

                _islice() {}
                _islice(Iterable const& iterable, __builtin__::xrange const& xr) : iterator(iterable, xr), end_iter(npos(), iterable, xr) {
                }

                iterator& begin() { return *this; }
                iterator const& begin() const { return *this; }
                iterator end() const { return end_iter; }

            };

        template <typename Iterable>
            _islice<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type> islice(Iterable&& iterable, long start, long stop, long step=1) {
                return _islice<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>(iterable, __builtin__::xrange(start, stop, step));
            }
        template <typename Iterable>
            _islice<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type> islice(Iterable&& iterable, long stop) {
                return _islice<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>(iterable, __builtin__::xrange(0, stop, 1));
            }

        PROXY(pythonic::itertools, islice);

    }

}

#endif

