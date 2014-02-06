import ConfigParser as configparser
import sys
import os


def init_cfg(sys_file, user_file):
    sys_config_dir = os.path.dirname(__file__)
    sys_config_path = os.path.join(sys_config_dir, sys_file)

    user_config_dir = os.environ.get('XDG_CONFIG_HOME', '~')
    user_config_path = os.path.expanduser(
        os.path.join(user_config_dir, user_file))

    cfg = configparser.SafeConfigParser()
    cfg.read([sys_config_path, user_config_path])

    return cfg

cfg = init_cfg('pythran.cfg', '.pythranrc')
