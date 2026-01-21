import os
import sys

Import("env")

project_dir = env["PROJECT_DIR"]
project_name = os.path.basename(project_dir.rstrip(os.sep))
home_dir = os.path.expanduser("~")

if sys.platform.startswith("win"):
    base_dir = os.path.join(home_dir, "AppData", "Local", "PlatformIO", project_name)
elif sys.platform == "darwin":
    base_dir = os.path.join(home_dir, "Library", "Caches", "PlatformIO", project_name)
else:
    base_dir = os.path.join(home_dir, ".cache", "platformio", project_name)

build_dir = os.path.join(base_dir, "build")
libdeps_dir = os.path.join(base_dir, "libdeps")

env.Replace(PROJECT_BUILD_DIR=build_dir)
env.Replace(PROJECTBUILD_DIR=build_dir)
env.Replace(LIBDEPS_DIR=libdeps_dir)
