#ifndef PYTHONIC_TYPES_SLICE_HPP
#define PYTHONIC_TYPES_SLICE_HPP

#include "pythonic/__builtin__/None.hpp"

#include <cassert>
#include <iostream>


namespace pythonic {

    namespace types {

        struct normalized_slice {
            long lower, upper, step;
            normalized_slice() {}
            normalized_slice(long lower, long upper, long step = 1)
                : lower(lower), upper(upper), step(step) {}

            template<class S>
            normalized_slice operator*(S const& other) const {
                return S(lower + step * other.lower, lower + step * other.upper, step * other.step);
            }

            long size() const
            {
                return std::max(0L, long(ceil(double(upper - lower)/double(step))));
            }

            inline long get(long i) const
            {
                return lower + i * step;
            }
        };

        struct slice {
            typedef normalized_slice normalized_type;
            none<long> lower, upper;
            long step;
            slice(none<long> lower, none<long> upper, none<long> step = 1)
                : lower(lower),
                  upper(upper),
                  step(step.is_none?1:(long)step)
            {}
            slice(){}

            template<class S>
            slice operator*(S const& other) const {
              none<long> new_lower;
              if(lower.is_none and other.lower.is_none)
                new_lower = none_type{};
              else if(lower.is_none)
                new_lower = other.lower;
              else if(other.lower.is_none)
                new_lower = lower;
              else
                new_lower = (long)lower + step * (long)other.lower;

              long new_step = step * other.step;
              if(upper < 0L and other.upper < 0L) {
                return {new_lower, upper * step + other.upper * step, new_step};
              }
              else if(upper.is_none or other.upper.is_none) {
                if(upper.is_none and other.upper.is_none)
                  return {new_lower, upper, new_step};
                else if(upper.is_none)
                  return {new_lower, other.upper, new_step};
                else
                  return {new_lower, upper, new_step};
              }
              else {
                return {new_lower, lower * step + other.upper, new_step};
              }
            }

            /*
               Normalize change a[:-1] to a[:len(a)-1] to have positif index.
               It also check for value bigger than len(a) to fit the size of the container
               */
            normalized_slice normalize(long max_size) const
            {
                long normalized_upper;
                if (upper.is_none) {
                  if (step > 0L)
                    normalized_upper = max_size;
                  else
                    normalized_upper = -1L;
                }
                else {
                  if(upper<0L) normalized_upper = std::max(-1L, max_size + upper);
                  else if(upper> max_size) normalized_upper = max_size;
                  else normalized_upper = (long)upper;
                }

                long normalized_lower;
                if(lower.is_none and step>0L) normalized_lower = 0L;
                else if(lower.is_none and step<0L) normalized_lower = max_size - 1L;
                else if(lower <0L) normalized_lower = std::max(0L, max_size + lower);
                else if(lower > max_size) normalized_lower = max_size - 1L;
                else normalized_lower = (long)lower;

                return {normalized_lower, normalized_upper, step};
            }

            long size() const
            {
                assert(not upper.is_none and not lower.is_none);
                return std::max(0L, long(ceil(double(upper - lower)/double(step))));
            }

            long get(long i) const
            {
                assert(not upper.is_none and not lower.is_none);
                return (long)lower + i * (long)step;
            }
        };

        struct contiguous_normalized_slice {
            long lower, upper;
            static constexpr long step = 1;
            contiguous_normalized_slice() {}
            contiguous_normalized_slice(long lower, long upper)
                : lower(lower), upper(upper) {
                }

            contiguous_normalized_slice operator*(contiguous_normalized_slice const& other) const {
                return contiguous_normalized_slice(lower + other.lower, upper + other.upper);
            }
            normalized_slice operator*(normalized_slice const& other) const {
                return normalized_slice(lower + step * other.lower, lower + step * other.upper, step * other.step);
            }

            long size() const
            {
                return std::max(0L, long(ceil(double(upper - lower))));
            }

            inline long get(long i) const
            {
                return lower + i;
            }
        };

        struct contiguous_slice {
            typedef contiguous_normalized_slice normalized_type;
            none<long> lower, upper;
            static const long step;
            contiguous_slice(none<long> lower, none<long> upper)
                : lower(lower.is_none?0:(long)lower), upper(upper) {}
            contiguous_slice(){}

            contiguous_slice operator*(contiguous_slice const& other) const {
              if(upper < 0L and other.upper < 0L)
                return contiguous_slice(lower + other.lower, upper + other.upper);
              else if(upper.is_none or other.upper.is_none)
                return contiguous_slice(lower + other.lower, upper + other.upper);
              else
                return contiguous_slice(lower + other.lower, lower + other.upper);
            }
            slice operator*(slice const& other) const {
              long new_lower = lower + other.lower;
              long new_step = other.step;
              if(upper.is_none and other.upper.is_none)
                return {new_lower, upper, new_step};
              else
                return {new_lower, (upper < 0L and other.upper < 0L) ? (long)upper : (long)lower, new_step};
            }


            /*
               Normalize change a[:-1] to a[:len(a)-1] to have positif index.
               It also check for value bigger than len(a) to fit the size of the container
               */
            contiguous_normalized_slice normalize(long max_size) const
            {
                long normalized_upper;
                if(upper.is_none) normalized_upper = max_size;
                else if(upper<0L) normalized_upper = std::max(-1L, max_size + upper);
                else if(upper> max_size) normalized_upper = max_size;
                else normalized_upper = (long)upper;

                long normalized_lower = (long)lower;
                if(lower <0L) normalized_lower = std::max(0L, max_size + lower);
                else if(lower > max_size) normalized_lower = max_size - 1L;
                else normalized_lower = (long)lower;

                return contiguous_normalized_slice(normalized_lower, normalized_upper);
            }

            long size() const
            {
                assert(not upper.is_none);
                return std::max(0L, long(ceil(double(upper - lower))));
            }

            inline long get(long i) const
            {
                return int(lower) + i;
            }
        };

        const long contiguous_slice::step = 1;
    }
}

#endif
