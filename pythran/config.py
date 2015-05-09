try:
    import configparser
except:
    import ConfigParser as configparser
import logging
import numpy.distutils.system_info as numpy_sys
import os
from sys import platform

logger = logging.getLogger(__name__)


def init_cfg(sys_file, platform_file, user_file):
    sys_config_dir = os.path.dirname(__file__)
    sys_config_path = os.path.join(sys_config_dir, sys_file)

    platform_config_path = os.path.join(sys_config_dir, platform_file)

    user_config_dir = os.environ.get('XDG_CONFIG_HOME', '~')
    user_config_path = os.path.expanduser(
        os.path.join(user_config_dir, user_file))

    cfg = configparser.SafeConfigParser()
    for required in (sys_config_path, platform_config_path):
        cfg.readfp(open(required))
    cfg.read([user_config_path])

    for key in ('CC', 'CXX'):
        value = cfg.get('compiler', key)
        if value:
            os.environ[key] = value

    for obsolete_section in ('user', 'sys'):
        if cfg.has_section(obsolete_section):
            logger.warn("Your pythranrc has an obsolete `{}' section".format(
                obsolete_section))

    return cfg


def make_extension(**extra):
    def parse_define(define):
        index = define.find('=')
        if index < 0:
            return (define, None)
        else:
            return define[:index], define[index + 1:]
    extension = {
        "define_macros": cfg.get('compiler', 'defines').split(),
        "undef_macros": cfg.get('compiler', 'undefs').split(),
        "include_dirs": cfg.get('compiler', 'include_dirs').split(),
        "library_dirs": cfg.get('compiler', 'library_dirs').split(),
        "libraries": cfg.get('compiler', 'libs').split(),
        "extra_compile_args": cfg.get('compiler', 'cflags').split(),
        "extra_link_args": cfg.get('compiler', 'ldflags').split(),
    }

    extension['define_macros'].append('ENABLE_PYTHON_MODULE')

    here = os.path.dirname(os.path.dirname(__file__))
    # using / as separator as advised in the distutils doc
    extension["include_dirs"].append(here + '/pythran')
    for k, w in extra.items():
        extension[k].extend(w)
    extension["define_macros"] = map(parse_define, extension["define_macros"])
    if cfg.getboolean('pythran', 'complex_hook'):
        # the patch is *not* portable
        extension["include_dirs"].append(here + '/pythran/pythonic/patch')

    # blas dependency
    numpy_blas = numpy_sys.get_info("blas")
    extension['libraries'].extend(numpy_blas['libraries'])
    extension['library_dirs'].extend(numpy_blas['library_dirs'])
    return extension


def compiler():
    return os.environ.get('CXX', 'c++')

# load platform specific configuration then user configuration
cfg = init_cfg('pythran.cfg',
               'pythran-{}.cfg'.format(platform),
               '.pythranrc')
