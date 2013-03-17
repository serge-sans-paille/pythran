#ifndef PYTHONIC_MODULE_OPERATOR_H
#define PYTHONIC_MODULE_OPERATOR_H

#define WRAPPER2ARGS(fname, lname) \
        template <class A, class B> auto fname(A a, B b) -> decltype(lname(a, b)) { return lname(a, b); } 


#define WRAPPER1ARG(fname, lname) \
        template <class A> auto fname(A a) -> decltype(lname(a)) { return lname(a); } 

namespace pythonic {
    namespace operator_ {
        template <class A, class B>
            bool lt(A const& a, B const& b) {
                return a<b;
            }

        WRAPPER2ARGS(__lt__, lt)

        template <class A, class B>
            bool le(A const& a, B const& b) {
                return a<=b;
            }

        WRAPPER2ARGS(__le__, le)

        template <class A, class B>
            bool eq(A const& a, B const& b) {
                return a==b;
            }

        WRAPPER2ARGS(__eq__, eq)

        template <class A, class B>
            bool ne(A const& a, B const& b) {
        	return 	a!=b;
            }

        WRAPPER2ARGS(__ne__, ne)

        template <class A, class B>
            bool ge(A const& a, B const& b) {
        	return a>=b;
            }

        WRAPPER2ARGS(__ge__, ge)

        template <class A, class B>
            bool gt(A const& a, B const& b) {
        	return a>b;
            }

        WRAPPER2ARGS(__gt__, gt)

        bool not_(bool const& a) {
            return !a;
        }

        WRAPPER1ARG(__not__, not_)

        bool truth(bool const& a) {
            return a;
        }

        template <class A, class B>
            bool is_(A const& a, B const& b) {
        	return a==b;
            }

        template <class A, class B>
            bool is_not(A const& a, B const& b) {
        	return a != b;
            }

        WRAPPER1ARG(__abs__, abs)

        template <class A, class B>
            auto add(A const& a, B const& b) -> decltype(a+b) {
        	return a+b;
            }

        WRAPPER2ARGS(__add__, add)

        template <class A, class B>
            auto and_(A const& a, B const& b) -> decltype(a&b){
        	return a&b;
            }

        WRAPPER2ARGS(__and__, and_)

        template <class A, class B>
            auto div(A const& a, B const& b) -> decltype(a/b){
        	if (b==0)
        	{
                    throw __builtin__::ZeroDivisionError("Division by zero !");
        	}
        	return a/b;
            }

        WRAPPER2ARGS(__div__, div)

        template <class A, class B>
            auto floordiv(A const& a, B const& b) -> decltype(a/b){
        	if (b==0)
        	{
                    throw __builtin__::ZeroDivisionError("Division by zero !");
        	}
        	return (a-(a % b))/b;
            }

        WRAPPER2ARGS(__floordiv__, floordiv)

//        template <class A>
//            int index(A const& a) {
//        	
//            }
//
//        template <class A>
//            int __index__(A const& a) {
//            }

        template <class A>
            A inv(A const& a) {
        	return ~a;
            }

        WRAPPER1ARG(__inv__, inv)

        template <class A>
            A invert(A const& a) {
        	return ~a;
            }

        WRAPPER1ARG(__invert__, invert)

        template <class A>
            A lshift(A const& a, int const& b) {
        	return a<<b;
            }

        WRAPPER2ARGS(__lshift__, lshift)

         int mod(int const& a, int const& b) {
        	return a%b;
            }

        WRAPPER2ARGS(__mod__, mod)

        template <class A, class B>
            auto mul(A const& a, B const& b) -> decltype(a*b) {
        	return a*b;
            }

        WRAPPER2ARGS(__mul__, mul)

        template <class A>
            A neg(A const& a) {
        	return -a;
            }

        WRAPPER1ARG(__neg__, neg)

        template <class A, class B>
            auto or_(A const& a, B const& b) -> decltype(a|b) {
        	return a|b;
            }

        WRAPPER2ARGS(__or__, or_)

        template <class A>
            A pos(A const& a) {
        	return +a;
            }

        WRAPPER1ARG(__pos__, pos)

        template <class A, class B>
            auto rshift(A const& a, B const& b) -> decltype(a>>b) {
        	return a>>b;
            }

        WRAPPER2ARGS(__rshift__, rshift)

        template <class A, class B>
            auto sub(A const& a, B const& b) -> decltype(a-b) {
        	return a-b;
            }

      WRAPPER2ARGS(__sub__, sub)

        template <class A, class B>
            auto truediv(A const& a, B const& b) -> decltype(a/(double)b) {
        	return a/((double)b);
            }

      WRAPPER2ARGS(__truediv__, truediv)

//        template <class A, class B>
//            auto xor(A const& a, B const& b) -> decltype(a^b) {
//        	return a^b;
//            }

        template <class A, class B>
            auto __xor__(A const& a, B const& b) -> decltype(a^b) {
        	return a^b;
            }

        template <class A, class B>
            auto concat(A const& a, B const& b) -> decltype(a+b) {
        	return a+b;
            }

      WRAPPER2ARGS(__concat__, concat)


        PROXY(pythonic::operator_, lt);
        PROXY(pythonic::operator_, le);
        PROXY(pythonic::operator_, eq);
        PROXY(pythonic::operator_, ne);
        PROXY(pythonic::operator_, ge);
        PROXY(pythonic::operator_, gt);
        PROXY(pythonic::operator_, __lt__);
        PROXY(pythonic::operator_, __le__);
        PROXY(pythonic::operator_, __eq__);
        PROXY(pythonic::operator_, __ne__);
        PROXY(pythonic::operator_, __ge__);
        PROXY(pythonic::operator_, __gt__);
        PROXY(pythonic::operator_, not_);
        PROXY(pythonic::operator_, __not__);
        PROXY(pythonic::operator_, truth);
        PROXY(pythonic::operator_, is_);
        PROXY(pythonic::operator_, is_not);
//        PROXY(pythonic::operator_, abs);
        PROXY(pythonic::operator_, __abs__);
        PROXY(pythonic::operator_, add);
        PROXY(pythonic::operator_, __add__);
        PROXY(pythonic::operator_, and_);
        PROXY(pythonic::operator_, __and__);
        PROXY(pythonic::operator_, div);
        PROXY(pythonic::operator_, __div__);
        PROXY(pythonic::operator_, floordiv);
        PROXY(pythonic::operator_, __floordiv__);
//        PROXY(pythonic::operator_, index);
//        PROXY(pythonic::operator_, __index__);
        PROXY(pythonic::operator_, inv);
        PROXY(pythonic::operator_, invert);
        PROXY(pythonic::operator_, __inv__);
        PROXY(pythonic::operator_, __invert__);
        PROXY(pythonic::operator_, lshift);
        PROXY(pythonic::operator_, __lshift__);
        PROXY(pythonic::operator_, mod);
        PROXY(pythonic::operator_, __mod__);
        PROXY(pythonic::operator_, mul);
        PROXY(pythonic::operator_, __mul__);
        PROXY(pythonic::operator_, neg);
        PROXY(pythonic::operator_, __neg__);
        PROXY(pythonic::operator_, or_);
        PROXY(pythonic::operator_, __or__);
        PROXY(pythonic::operator_, pos);
        PROXY(pythonic::operator_, __pos__);
//        PROXY(pythonic::operator_, pow);
//       PROXY(pythonic::operator_, __pow__);
        PROXY(pythonic::operator_, rshift);
        PROXY(pythonic::operator_, __rshift__);
        PROXY(pythonic::operator_, sub);
        PROXY(pythonic::operator_, __sub__);
        PROXY(pythonic::operator_, truediv);
        PROXY(pythonic::operator_, __truediv__);
//        PROXY(pythonic::operator_, xor);
        PROXY(pythonic::operator_, __xor__);
        PROXY(pythonic::operator_, concat);
        PROXY(pythonic::operator_, __concat__);
    }

}

#endif
