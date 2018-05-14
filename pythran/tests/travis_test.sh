run_tests() {
    if [ "$PYTHON_VERSION" = 2 -a "$TRAVIS_PYTHON_VERSION" = 3.5 ]
    then
        exit
    fi
    if [ -n "$NOTEBOOK" ]
    then
        PYTHONPATH=$PWD:$PYTHONPATH py.test pythran/tests/notebooks --nbval
        exit
    fi
    printf "[compiler]\nCXX=$CXX\nCC=$CC\ncflags=-std=c++11 $CXXFLAGS -w -O0 -fvisibility=hidden -fno-wrapv\nldflags=$CXXFLAGS -fopenmp -fvisibility=hidden -Wl,-strip-all\n" > ~/.pythranrc
    OMP_NUM_THREADS=3 PYTHONPATH=$PWD:$PYTHONPATH py.test -v $TESTCASE
}

# Test with both clang and gcc
# Only gcc can test openMP, and travis does not support gcc when gcc uses too much memory
# So some tests have been commented out, as it is useless to compile them with clang
run_tests
