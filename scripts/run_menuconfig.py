import os

import sys
print(os.getcwd())
# First, get our variables from the environment
pio_env = sys.argv[1]
os.system("cp -f scripts/Kconfig.template ./Kconfig.{0}".format(pio_env))
os.system("KCONFIG_CONFIG=./.config.{0} menuconfig Kconfig.{0}".format(pio_env))