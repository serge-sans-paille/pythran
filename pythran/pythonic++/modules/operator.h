#ifndef PYTHONIC_MODULE_OPERATOR_H
#define PYTHONIC_MODULE_OPERATOR_H

namespace pythonic {
    namespace operator_ {
	template <class A, class B>
            bool lt(A const& a, B const& b) {
                return a<b;
            }

	template <class A, class B>
            bool le(A const& a, B const& b) {
                return a<=b;
            }

	template <class A, class B>
            bool eq(A const& a, B const& b) {
                return a==b;
            }

        template <class A, class B>
            bool ne(A const& a, B const& b) {
		return 	a!=b;
            }

        template <class A, class B>
            bool ge(A const& a, B const& b) {
		return a>=b;
            }

        template <class A, class B>
            bool gt(A const& a, B const& b) {
		return a>b;
            }

        template <class A, class B>
            bool __lt__(A const& a, B const& b) {
		return a<b;
            }

        template <class A, class B>
            bool __le__(A const& a, B const& b) {
		return a<=b;
            }

        template <class A, class B>
            bool __eq__(A const& a, B const& b) {
		return a==b;
            }

        template <class A, class B>
            bool __ne__(A const& a, B const& b) {
		return a!=b;
            }

        template <class A, class B>
            bool __ge__(A const& a, B const& b) {
		return a>=b;
            }

        template <class A, class B>
            bool __gt__(A const& a, B const& b) {
		return a>b;
            }

        bool not_(bool const& a) {
	    return !a;
        }

        bool __not__(bool const& a) {
	    return !a;
        }

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

//	using std::abs;

        template <class A>
            A __abs__(A const& a) {
		return abs(a);
            }

        template <class A, class B>
            auto __add__(A const& a, B const& b) -> decltype(a+b) {
		return a+b;
            }

        template <class A, class B>
            auto add(A const& a, B const& b) -> decltype(a+b) {
		return __add__(a+b);
            }


        template <class A, class B>
            auto and_(A const& a, B const& b) -> decltype(a&b){
		return a&b;
            }

        template <class A, class B>
            auto __and__(A const& a, B const& b) -> decltype(a&b){
		return a&b;
            }

        template <class A, class B>
            auto div(A const& a, B const& b) -> decltype(a/b){
		if (b==0)
		{
                    throw ZeroDivisionError("Division by zero impossible !");
		}
		return a/b;
            }

        template <class A, class B>
            auto __div__(A const& a, B const& b) -> decltype(a/b){
		if (b==0)
		{
                    throw ZeroDivisionError("Division by zero impossible !");
		}
		return a/b;
            }

        template <class A, class B>
            auto floordiv(A const& a, B const& b) -> decltype(a/b){
		if (b==0)
		{
                    throw ZeroDivisionError("Division by zero impossible !");
		}
		return (a-(a % b))/b;
            }

        template <class A, class B>
            auto __floordiv__(A const& a, B const& b) -> decltype(a/b) { 
		if (b==0)
		{
                    throw ZeroDivisionError("Division by zero impossible !");
		}
		return (a-(a % b))/b;
            }

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

        template <class A>
            A invert(A const& a) {
		return ~a;
            }

        template <class A>
            A __inv__(A const& a) {
		return ~a;
            }

        template <class A>
            A __invert__(A const& a) {
		return ~a;
            }

        template <class A>
            A lshift(A const& a, int const& b) {
		return a<<b;
            }

        template <class A>
            A __lshift__(A const& a, int const& b) {
		return a<<b;
            }

         int mod(int const& a, int const& b) {
		return a%b;
            }

         int __mod__(int const& a, int const& b) {
		return a%b;
            }

        template <class A, class B>
            auto mul(A const& a, B const& b) -> decltype(a*b) {
		return a*b;
            }

        template <class A, class B>
            auto __mul__(A const& a, B const& b) -> decltype(a*b) {
		return a*b;
            }

        template <class A>
            A neg(A const& a) {
		return -a;
            }

        template <class A>
            A __neg__(A const& a) {
		return -a;
            }

        template <class A, class B>
            auto or_(A const& a, B const& b) -> decltype(a|b) {
		return a|b;
            }

        template <class A, class B>
            auto __or__(A const& a, B const& b) -> decltype(a|b) {
		return a|b;
            }

        template <class A>
            A pos(A const& a) {
		return +a;
            }

        template <class A>
            A __pos__(A const& a) {
		return +a;
            }

//        template <class A, class B>
//            auto pow(A const& a, B const& b) -> decltype(a**b) {
//		return a**b;
//            }
//
//        template <class A, class B>
//            auto __pow__(A const& a, B const& b) -> decltype(a**b) {
//		return a**b;
//            }

        template <class A, class B>
            auto rshift(A const& a, B const& b) -> decltype(a>>b) {
		return a>>b;
            }

        template <class A, class B>
            auto __rshift__(A const& a, B const& b) -> decltype(a>>b) {
		return a>>b;
            }

        template <class A, class B>
            auto sub(A const& a, B const& b) -> decltype(a-b) {
		return a-b;
            }

        template <class A, class B>
            auto __sub__(A const& a, B const& b) -> decltype(a-b) {
		return a-b;
            }

        template <class A, class B>
            auto truediv(A const& a, B const& b) -> decltype(a/b) {
		return a/b;
            }

        template <class A, class B>
            auto __truediv__(A const& a, B const& b) -> decltype(a/b) {
		return a/b;
            }

//        template <class A, class B>
//            auto xor(A const& a, B const& b) -> decltype(a^b) {
//		return a^b;
//            }

        template <class A, class B>
            auto __xor__(A const& a, B const& b) -> decltype(a^b) {
		return a^b;
            }

        template <class A, class B>
            auto concat(A const& a, B const& b) -> decltype(a+b) {
		return a+b;
            }

        template <class A, class B>
            auto __concat__(A const& a, B const& b) -> decltype(a+b) {
		return a+b;
            }



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
