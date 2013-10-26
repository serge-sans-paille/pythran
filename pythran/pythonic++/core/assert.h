#ifndef PYTHONIC_ASSERT_H
#define PYTHONIC_ASSERT_H

#ifdef NDEBUG
#define pythran_assert(...) 
#else

void pythran_assert(bool cond, pythonic::core::string const& what = "")
{
    if (not cond)
        throw pythonic::core::AssertionError(what);
}

#endif // NDEBUG

#endif
