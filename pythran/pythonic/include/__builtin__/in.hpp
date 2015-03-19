#ifndef PYTHONIC_INCLUDE_BUILTIN_IN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_IN_HPP

namespace pythonic {

    template<bool has_contains>
        struct _in
        {
            template<class T, class V>
                bool operator()(T&& t, V const& v) const;
        };

    template <class T, class V>
        bool in(T &&t, V const &v);

}

#endif
