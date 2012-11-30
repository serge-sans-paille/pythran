#ifndef PYTHONIC_DISPATCH_H
#define PYTHONIC_DISPATCH_H

namespace pythonic {
    namespace __dispatch__ {
        template<class Any>
            auto pop(Any&& any) -> decltype(any.pop()) { return any.pop(); }
        template<class Any, class Arg0>
            auto pop(Any&& any, Arg0 const & arg0) -> decltype(any.pop(arg0)) { return any.pop(arg0); }
        template<class Any, class Arg0, class Arg1>
            auto pop(Any&& any, Arg0 const & arg0, Arg1 const& arg1) -> decltype(any.pop(arg0,arg1)) { return any.pop(arg0,arg1); }

        PROXY(pythonic::__dispatch__, pop);

        template<class Any>
            auto clear(Any&& any) -> decltype(any.clear()) {return any.clear();}

        PROXY(pythonic::__dispatch__, clear);

        template<class Any>
            auto copy(Any const& any) -> decltype(any.copy()) {return any.copy();}

        PROXY(pythonic::__dispatch__, copy);

        template<class Any, class Arg0>
            auto remove(Any& any, Arg0 const & arg0) -> decltype(any.remove(arg0)) { return any.remove(arg0); }

        PROXY(pythonic::__dispatch__, remove);

        template<class Any, class Arg0>
            auto update(Any&& any, Arg0 && arg0) -> decltype(any.update(std::forward<Arg0>(arg0))) {
                return any.update(std::forward<Arg0>(arg0));
            }
        template<class Any, class Arg0, class Arg1>
            auto update(Any&& any, Arg0 && arg0, Arg1 && arg1) -> decltype(any.update(std::forward<Arg0>(arg0), std::forward<Arg1>(arg1))) {
                return any.update(std::forward<Arg0>(arg0), std::forward<Arg1>(arg1));
            }

        PROXY(pythonic::__dispatch__, update);

    }
}
#endif

