#ifndef PYTHONIC_INCLUDE_UTILS_SEQ_HPP
#define PYTHONIC_INCLUDE_UTILS_SEQ_HPP

namespace pythonic {

    namespace utils {

        // gens<N>::type = seq<0, ..., N-1>
        //
        // This is a backport for std::make_index_sequence in C++14

        template<int ...>
            struct seq
            {};

        template<int N, int ...S>
            struct gens : gens<N-1, N-1, S...>
            {};

        template<int ...S>
            struct gens<0, S...>
            {
                using type = seq<S...>;
            };

        template<>
            struct gens<0>
            {
                using type = seq<>;
            };

        // rgens<N>::type = seq<N-1, ..., 0>

        template<int N, int ...S>
            struct rgens : rgens<N-1, sizeof...(S), S...>
            {};

        template<int ...S>
            struct rgens<0, S...>
            {
                using type = seq<S...>;
            };

    }

}

#endif
