#ifndef PYTHONIC_DISPATCH_H
#define PYTHONIC_DISPATCH_H

namespace pythonic {
    namespace __dispatch__ {
        template<class Any>
            auto pop(Any& any) -> decltype(any.pop()) { return any.pop(); }
        template<class Any, class Arg0>
            auto pop(Any& any, Arg0 const & arg0) -> decltype(any.pop(arg0)) { return any.pop(arg0); }
        template<class Any, class Arg0, class Arg1>
            auto pop(Any& any, Arg0 const & arg0, Arg1 const& arg1) -> decltype(any.pop(arg0,arg1)) { return any.pop(arg0,arg1); }

        VPROXY(pythonic::__dispatch__, pop)
    }
}
#endif

