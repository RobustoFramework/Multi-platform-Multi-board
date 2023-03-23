import os

Import("env")

framework = env.subst('$PIOFRAMEWORK')
if framework.lower() != "espidf":
    project_dir = env.subst('$PROJECT_DIR')
    pio_env = env.subst('$PIOENV')
    env.AddTarget(
        name="menuconfig",
        dependencies=None,
        group="General",
        actions=[
            "python {0}/scripts/run_menuconfig.py {1}".format(project_dir, pio_env)
        ],
        title="Run menuconfig",
        description="Menuconfig is a tool for configuring an environment"
    )