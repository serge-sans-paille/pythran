try:
    # python3 vs. python2
    import configparser
except ImportError:
    import ConfigParser as configparser
import logging
import numpy.distutils.system_info as numpy_sys
import numpy
import os
import sys

logger = logging.getLogger('pythran')


def init_cfg(sys_file, platform_file, user_file):
    sys_config_dir = os.path.dirname(__file__)
    sys_config_path = os.path.join(sys_config_dir, sys_file)

    platform_config_path = os.path.join(sys_config_dir, platform_file)

    user_config_dir = os.environ.get('XDG_CONFIG_HOME', '~')
    user_config_path = os.path.expanduser(
        os.path.join(user_config_dir, user_file))

    cfgp = configparser.SafeConfigParser()
    for required in (sys_config_path, platform_config_path):
        cfgp.readfp(open(required))
    cfgp.read([user_config_path])

    for obsolete_section in ('user', 'sys'):
        if cfgp.has_section(obsolete_section):
            logger.warn("Your pythranrc has an obsolete `%s' section",
                        obsolete_section)

    return cfgp


def make_extension(generic, **extra):

    def parse_define(define):
        index = define.find('=')
        if index < 0:
            return (define, None)
        else:
            return define[:index], define[index + 1:]

    extension = {
        "language": "c++",
        # forcing str conversion to handle Unicode case (the default on MS)
        "define_macros": [str(x) for x in
                          cfg.get('compiler', 'defines').split()],
        "undef_macros": [str(x) for x in
                         cfg.get('compiler', 'undefs').split()],
        "include_dirs": [str(x) for x in
                         cfg.get('compiler', 'include_dirs').split()],
        "library_dirs": [str(x) for x in
                         cfg.get('compiler', 'library_dirs').split()],
        "libraries": [str(x) for x in
                      cfg.get('compiler', 'libs').split()],
        "extra_compile_args": [str(x) for x in
                               cfg.get('compiler', 'cflags').split()],
        "extra_link_args": [str(x) for x in
                            cfg.get('compiler', 'ldflags').split()],
    }

    if not generic:
        extension['define_macros'].append('ENABLE_PYTHON_MODULE')
    extension['define_macros'].append(
        '__PYTHRAN__={}'.format(sys.version_info.major))

    here = os.path.dirname(os.path.dirname(__file__)) or '.'
    # using / as separator as advised in the distutils doc
    extension["include_dirs"].append(here + '/pythran')

    extra.pop('language', None)  # forced to c++ anyway
    cxx = extra.pop('cxx', None)
    if cxx is not None:
        extension['cxx'] = cxx
    else:
        extension['cxx'] = compiler()

    for k, w in extra.items():
        extension[k].extend(w)
    if cfg.getboolean('pythran', 'complex_hook'):
        # the patch is *not* portable
        extension["include_dirs"].append(here + '/pythran/pythonic/patch')

    # Numpy can pollute stdout with warning message which should be on stderr
    old_stdout = sys.stdout
    try:
        sys.stdout = sys.stderr

        # numpy specific
        if not generic:
            extension['include_dirs'].append(numpy.get_include())

        # blas dependency
        user_blas = cfg.get('compiler', 'blas')
        numpy_blas = numpy_sys.get_info(user_blas)
        # required to cope with atlas missing ectern "C"
        extension['define_macros'].append('PYTHRAN_BLAS_{}'
                                          .format(user_blas.upper()))
        extension['libraries'].extend(numpy_blas.get('libraries', []))
        extension['library_dirs'].extend(numpy_blas.get('library_dirs', []))
        extension['include_dirs'].extend(numpy_blas.get('include_dirs', []))
    finally:
        sys.stdout = old_stdout

    # final macro normalization
    extension["define_macros"] = [
        dm if isinstance(dm, tuple) else parse_define(dm)
        for dm in extension["define_macros"]]
    return extension


def compiler():
    """Get compiler to use for C++ to binary process. The precedence for
    choosing the compiler is as follows::

      1. `CXX` environment variable
      2. User configuration (~/.pythranrc)
      3. Default to `c++`

    """
    cfg_cxx = str(cfg.get('compiler', 'CXX'))
    if not cfg_cxx:
        cfg_cxx = 'c++'
    return os.environ.get('CXX', cfg_cxx)


def have_gmp_support(**extra):
    """Check if the USE_GMP macro is defined."""
    return (sys.version_info.major != 3 and
            any("USE_GMP" == name
                for name, _ in make_extension(False, **extra)["define_macros"]))


# load platform specific configuration then user configuration
cfg = init_cfg('pythran.cfg',
               'pythran-{}.cfg'.format(sys.platform),
               '.pythranrc')


def run():
    '''
    Dump on stdout the config flags required to compile pythran-generated code.
    '''
    import argparse
    import distutils.sysconfig
    import pythran
    import numpy

    parser = argparse.ArgumentParser(
        prog='pythran-config',
        description='output build options for pythran-generated code',
        epilog="It's a megablast!"
        )

    parser.add_argument('--compiler', action='store_true',
                        help='print default compiler')

    parser.add_argument('--cflags', action='store_true',
                        help='print compilation flags')

    parser.add_argument('--libs', action='store_true',
                        help='print linker flags')

    parser.add_argument('--generic', action='store_true',
                        help='don\t include python stuff')

    args = parser.parse_args(sys.argv[1:])

    output = []

    extension = pythran.config.make_extension(args.generic)

    if args.compiler:
        output.append(compiler())

    if args.cflags:
        def fmt_define(define):
            name, value = define
            if value is None:
                return '-D' + name
            else:
                return '-D' + name + '=' + value
        output.extend(fmt_define(define)
                      for define in extension['define_macros'])
        output.extend(('-I' + include)
                      for include in extension['include_dirs'])
        if not args.generic:
            output.append('-I' + numpy.get_include())
            output.append('-I' + distutils.sysconfig.get_python_inc())

    if args.libs:
        output.extend(('-L' + include)
                      for include in extension['library_dirs'])
        if not args.generic:
            output.append('-L' + distutils.sysconfig.get_config_var('LIBPL'))
        output.extend(('-l' + include)
                      for include in extension['libraries'])
        if not args.generic:
            output.extend(distutils.sysconfig.get_config_var('LIBS').split())
            output.append('-lpython' +
                          distutils.sysconfig.get_config_var('VERSION'))

    if output:
        print(' '.join(output))


if __name__ == '__main__':
    run()
