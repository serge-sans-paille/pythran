#ifndef PYTHONIC_ITERTOOLS_COMBINATIONS_HPP
#define PYTHONIC_ITERTOOLS_COMBINATIONS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"

#include <vector>
#include <iterator>

namespace pythonic {

    namespace itertools {
        template<class T>
            struct combination_iterator : std::iterator< std::forward_iterator_tag,
            types::list<typename T::value_type>,
            ptrdiff_t,
            types::list<typename T::value_type>*,
            types::list<typename T::value_type> /*no ref*/
                                          >
        {
            std::vector<typename T::value_type> iterable;
            std::vector<bool> curr_permut;
            bool end;
            combination_iterator() {}
            combination_iterator(std::vector<typename T::value_type> const& iter, int num_elts, bool end) : iterable(iter), end(end)
            {
                curr_permut.resize(iterable.size());
                std::fill(curr_permut.begin() + num_elts, curr_permut.end(), true);
            }
            types::list<typename T::value_type> operator*() const {
                types::list<typename T::value_type> res(0);
                int i=0;
                for(auto const& iter : iterable)
                {
                    if(!curr_permut[i++])
                        res.push_back(iter);
                }
                return res;
            }
            combination_iterator& operator++()
            {
                end = std::next_permutation(curr_permut.begin(), curr_permut.end());
                return *this;
            }
            bool operator!=(combination_iterator const& other) const
            {
                return !(*this==other);
            }
            bool operator==(combination_iterator const& other) const
            {
                if(other.end != end)
                    return false;
                return std::equal(curr_permut.begin(), curr_permut.end(), other.curr_permut.begin());
            }
            bool operator<(combination_iterator const& other) const
            {
                if(end!=other.end)
                    return end>other.end;
                for(int i=0; i<iterable.size(); i++)
                    if(other.curr_permut[i] < curr_permut[i])
                        return false;
                    else if(other.curr_permut[i] > curr_permut[i])
                        return true;
                return false;
            }
        };

        template<class T>
            struct _combination: combination_iterator<T> {
                typedef T value_type;
                typedef combination_iterator<T> iterator;
                size_t num_elts;
                _combination() {}
                _combination(T iter, int elts): iterator(std::vector<typename T::value_type>(iter.begin(), iter.end()), elts, true), num_elts(elts){}
                iterator const& begin() const {
                    return *this;
                }
                iterator begin() {
                    return *this;
                }
                iterator end() const {
                    return combination_iterator<T>(combination_iterator<T>::iterable, num_elts, false);
                }
            };

        template <typename T0>
            _combination<T0> combinations(T0 iter, int num_elts) {
                return _combination<T0>(iter, num_elts);
            }

        PROXY(pythonic::itertools, combinations);

    }

}

#endif

