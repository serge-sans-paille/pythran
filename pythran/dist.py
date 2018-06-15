'''
This modules contains a distutils extension mechanism for Pythran
    * PythranExtension: is used as distutils's Extension
'''

import pythran.config as cfg
import pythran.toolchain as tc

from distutils.command.build_ext import build_ext as _build_ext
from distutils.sysconfig import customize_compiler
from numpy.distutils.extension import Extension

import os.path
import os



class build_ext(_build_ext):
    '''
    Build PythranExtension within a contextmanager for handling the environment
    variables. Subclasses `distutils.command.build_ext.build_ext`.
    '''
    def build_extension(self, ext):
        if isinstance(ext, PythranExtension):
            with cfg.compiler_cfg():
                # Use configured environment variables CC and CXX
                customize_compiler(self.compiler)
                super(build_ext, self).build_extension(ext)

            # Restore environment variables CC and CXX
            customize_compiler(self.compiler)
        else:
            super(build_ext, self).build_extension(ext)


class PythranExtension(Extension):
    '''
    Description of a Pythran extension

    Similar to distutils.core.Extension except that the sources are .py files
    They must be processable by pythran, of course.

    The compilation process ends up in a native Python module.
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

        cxx_sources = []
        for source in sources:
            base, _ = os.path.splitext(source)
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
        Extension.__init__(self, name, cxx_sources, *args, **cfg_ext)
