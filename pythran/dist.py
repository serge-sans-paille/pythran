'''
This modules contains a distutils extension mechanism for Pythran
    * PythranExtension: is used as distutils's Extension
'''

import pythran.config as cfg

import os.path
import os

from numpy.distutils.extension import Extension

from numpy.distutils.command import build_ext as build_ext0
from distutils.command import build_ext as build_ext1

for build_ext in (build_ext0, build_ext1):

    LegacyBuildExt = build_ext.build_ext

    class PythranBuildExt(LegacyBuildExt):

        # workaround mismatch between distutils and numpy
        # implementation
        def swig_sources(self, sources, *args):
            return sources

        def build_extension(self, ext):
            prev = {'preprocessor': None,
                    'compiler_cxx': None,
                    'compiler_so': None,
                    'compiler': None,
                    'linker_exe': None,
                    'linker_so': None}
            if getattr(ext, 'cxx', None) and 'CXX' not in os.environ:
                for attr in prev.keys():
                    prev[attr] = getattr(self.compiler, attr)[0]
                    getattr(self.compiler, attr)[0] = ext.cxx

                try:
                    return LegacyBuildExt.build_extension(self, ext)
                finally:
                    for attr in prev.keys():
                        getattr(self.compiler, attr)[0] = prev[attr]
            else:
                return LegacyBuildExt.build_extension(self, ext)

    build_ext.build_ext = PythranBuildExt


class PythranExtension(Extension):
    '''
    Description of a Pythran extension

    Similar to distutils.core.Extension except that the sources are .py files
    They must be processable by pythran, of course.

    The compilation process ends up in a native Python module.

    Unlike distutils.core.Extension it also accepts a cxx keyword argument to
    force the compiler executable.
    '''
    def __init__(self, name, sources, *args, **kwargs):
        # the goal is to rely on original Extension
        # to do so we convert the .py to .cpp with pythran
        # and register the .cpp in place of the .py
        # That's stage 0, and it's enough if you get the source
        # from github and `python setup.py install it`
        #
        # *But* if you want to distribute the source through
        # `python setup.py sdist` then the .py no longer exists
        # and only the .cpp is distributed. That's stage 1

        import pythran.toolchain as tc

        cxx_sources = []
        for source in sources:
            base, ext = os.path.splitext(source)
            if ext == ".cpp":
                output_file = source
                stage = 1
            else:
                output_file = base + '.cpp'  # target name
                # stage 0 when we have the .py
                if os.path.exists(source):
                    stage = 0
                # stage 1 otherwise. `.cpp' should already be there
                # as generated upon stage 0
                else:
                    assert os.path.exists(output_file)
                    stage = 1
                    source = output_file

            # stage-dependant processing
            if stage == 0:
                # get the last name in the path
                if '.' in name:
                    module_name = os.path.splitext(name)[-1][1:]
                else:
                    module_name = name
                tc.compile_pythranfile(source, output_file,
                                       module_name, cpponly=True)
            cxx_sources.append(output_file)

        cfg_ext = cfg.make_extension(**kwargs)

        self.cc = cfg_ext.pop('cc', None)
        self.cxx = cfg_ext.pop('cxx', None)
        Extension.__init__(self, name, cxx_sources, *args, **cfg_ext)
