try:
    import configparser
except:
    import ConfigParser as configparser
import os
from sys import platform


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

    return cfg

# load platform specific configuration then user configuration
cfg = init_cfg('pythran.cfg',
               'pythran-{}.cfg'.format(platform),
               '.pythranrc')
