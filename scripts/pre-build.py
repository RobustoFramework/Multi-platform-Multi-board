import os

Import("env")

# First, get our variables from the environment
pio_env = env.subst('$PIOENV')
build_dir = os.path.join(env.subst('$BUILD_DIR'), "config")
project_dir = env.subst('$PROJECT_DIR')
script_dir = os.path.join(project_dir, "scripts")
framework = env.subst('$PIOFRAMEWORK')


# Create the build folder
print("mkdir -p {0}".format(build_dir))
os.system("mkdir -p {0}".format(build_dir))

# Copy the include to there
print("cp {0}/robconfig.h {1} ".format(script_dir, build_dir))
os.system("cp {0}/robconfig.h {1} ".format(script_dir, build_dir))

print("Build dir: ", build_dir)
print("Script dir: ", script_dir)
print("environment: ", pio_env)

# Add files to path
env.Append(CPPPATH=[build_dir])
env.BuildSources(build_dir, build_dir)


# If its not ESP-IDF, we add the settings header anyway so that the framework and applications don't have to care.
if framework != "espidf":
    # Check if there is anything for us to do here. TODO: Create the file if it is missing? Default configs?
    kconfig_filename = os.path.join(project_dir, "Kconfig." + pio_env)
    if os.path.isfile(kconfig_filename):
        # Generate the config
        print("KCONFIG_CONFIG=.config.{0} genconfig Kconfig.{0} --header-path {1}/robconfig_.h".format(pio_env, build_dir))
        os.system("KCONFIG_CONFIG=.config.{0} genconfig Kconfig.{0} --header-path {1}/robconfig_.h".format(pio_env, build_dir))
    else: 
        print("Won't do any config, no", kconfig_filename, " file.")  
else: 
    print("Skipping ESP-IDF framework, it has its own Kconfig handling.")  
