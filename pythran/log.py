import logging
logger = logging.getLogger("pythran")

# Initialize logging
try:
    # Set a nice colored output
    from colorlog import ColoredFormatter
    formatter = ColoredFormatter(
        "%(log_color)s%(levelname)-8s%(reset)s %(blue)s%(message)s",
        log_colors={
            'DEBUG':    'cyan',
            'INFO':     'green',
            'WARNING':  'yellow',
            'ERROR':    'red',
            'CRITICAL': 'red',
        }
    )
    stream = logging.StreamHandler()
    stream.setFormatter(formatter)
    logger.addHandler(stream)
except ImportError:
    # No color available, use default config
    logging.basicConfig(format='%(levelname)s: %(message)s')
    logger.warn("Disabling color, you really want to install colorlog.")
