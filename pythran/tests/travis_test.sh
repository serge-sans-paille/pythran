run_tests() {
    if [ -n "$PYTHRAN_DOC" ]
    then
        if [ "$PYTHON_VERSION" = 3 ]
        then
            PYTHONPATH=$PWD:$PYTHONPATH py.test pythran/tests/test_xdoc.py pythran/tests/notebooks docs/examples --nbval
        else
            PYTHONPATH=$PWD:$PYTHONPATH py.test pythran/tests/test_xdoc.py
        fi
        exit
    fi
    printf "[compiler]\nCXX=$CXX\nCC=$CC\ncflags=-std=c++11 $CXXFLAGS -w -O0 -fvisibility=hidden -fno-wrapv\nldflags=$CXXFLAGS -fopenmp -fvisibility=hidden -Wl,-strip-all\n" > ~/.pythranrc
    OMP_NUM_THREADS=3 PYTHONPATH=$PWD:$PYTHONPATH py.test -v $TESTCASE
}

# Test with both clang and gcc
# Only gcc can test openMP, and travis does not support gcc when gcc uses too much memory
# So some tests have been commented out, as it is useless to compile them with clang
run_tests
