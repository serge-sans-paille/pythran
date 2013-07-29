#ifndef PYTHONIC_ITERTOOLS_PERMUTATIONS_HPP
#define PYTHONIC_ITERTOOLS_PERMUTATIONS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/__builtin__/range.hpp"

#include <iterator>
#include <vector>
#include <algorithm>

namespace pythonic {

    namespace itertools {
        /** Permutation iterator
         *
         *  It wraps a vector and provide an iteration over every possible
         *  permutation of the vector. The permutations are represented as lists
         *  of elements.
         *
         *  The following iterator:
         *
         *  permutations_iterator([0, 1, 2])
         *
         *  yelds the following suite:
         *
         *  [(0, 1, 2), (0, 2, 1), (1, 0, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)]
         *
         */
        template<class T>
            struct permutations_iterator :
                std::iterator< std::forward_iterator_tag,
                types::list<typename T::value_type>,
                ptrdiff_t,
                types::list<typename T::value_type>*,
                types::list<typename T::value_type> /* no ref*/
                > {
                    // Vector of inputs, contains elements to permute
                    std::vector<typename T::value_type> pool;

                    // The current permutation as a list of index in the pool
                    // Internally it always has the same size as the pool, even if the
                    // external view is limited
                    types::list<int> curr_permut;

                    // Size of the "visible" permutation
                    size_t _size;
                    bool end; // sentinel marker

                    permutations_iterator() {}
                    permutations_iterator(std::vector<typename T::value_type> const& iter,
                            int num_elts,
                            bool end) :
                        pool(iter), curr_permut(__builtin__::range(pool.size())), _size(num_elts), end(end)
                    {
                        if(num_elts > iter.size()) {
                            end = true;
                        }
                    }

                    /** Build the permutation visible from the "outside" */
                    types::list<typename T::value_type> operator*() const {
                        types::list<typename T::value_type> res(_size);
                        for(int i =0; i<_size; i++)
                        {
                            res[i] = pool[curr_permut[i]]; // Ok because types::list is indeed a vector
                        }
                        return res;
                    }
                    /*  Generate next permutation
                     *
                     *  If the size of the permutation is smaller than the size of the
                     *  pool, we may have to iterate multiple times
                     */
                    permutations_iterator& operator++()
                    {
                        if(_size!=pool.size()) {
                            // Slow path, the iterator is a "view" of a prefix smaller
                            // than the the pool size
                            // FIXME a better implementation would be to avoid
                            // std::next_permutation, but only in the slow path
                            types::list<int> prev_permut(curr_permut.begin(),
                                    curr_permut.begin()+_size);
                            types::list<int> new_permut;
                            while((end = std::next_permutation(curr_permut.begin(),
                                            curr_permut.end()))) {
                                // Check if the prefix of the new permutation is
                                // different of the previous one
                                types::list<int> new_permut(curr_permut.begin(),
                                        curr_permut.begin()+_size);
                                if(!(prev_permut==new_permut)) break;
                            }
                        } else {
                            end = std::next_permutation(curr_permut.begin(),
                                    curr_permut.end());
                        }
                        return *this;
                    }
                    bool operator!=(permutations_iterator const& other) const
                    {
                        return !(*this==other);
                    }
                    bool operator==(permutations_iterator const& other) const
                    {
                        if(other.end != end)
                            return false;
                        return std::equal(curr_permut.begin(), curr_permut.end(), other.curr_permut.begin());
                    }
                    bool operator<(permutations_iterator const& other) const
                    {
                        if(end!=other.end)
                            return end>other.end;
                        for(int i=0; i<pool.size(); i++)
                            if(other.curr_permut[i] < curr_permut[i])
                                return false;
                            else if(other.curr_permut[i] > curr_permut[i])
                                return true;
                        return false;
                    }
                };

        template<class T>
            // FIXME document why this inheritance???
            struct _permutations: permutations_iterator<T> {
                typedef T value_type;
                typedef permutations_iterator<T> iterator;
                _permutations() {}
                _permutations(T iter, int elts) :
                    iterator(std::vector<typename T::value_type>(iter.begin(),
                                iter.end()),
                            elts,
                            true) {}

                iterator const& begin() const {
                    return *this;
                }
                iterator begin() {
                    return *this;
                }
                iterator end() const {
                    return iterator(iterator::pool, iterator::_size, false);
                }
            };

        template <typename T0>
            _permutations<T0> permutations(T0 iter, int num_elts) {
                return _permutations<T0>(iter, num_elts);
            }

        template <typename T0>
            _permutations<T0> permutations(T0 iter) {
                return _permutations<T0>(iter, std::distance(iter.begin(), iter.end()));
            }

        PROXY(pythonic::itertools, permutations);

    }

}

#endif

