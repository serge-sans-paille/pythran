#ifndef PYTHONIC_UTILS_SEQ_HPP
#define PYTHONIC_UTILS_SEQ_HPP

namespace pythonic {

    namespace utils {

        template<int ...>
            struct seq { };

        template<int N, int ...S>
            struct gens : gens<N-1, N-1, S...> { };

        template<int ...S>
            struct gens<1, S...> {
                typedef seq<S...> type;
            };

        template<int N, int ...S>
            struct rgens : rgens<N-1, sizeof...(S), S...> { };

        template<int ...S>
            struct rgens<1, S...> {
                typedef seq<S...> type;
            };

    }

}

#endif
