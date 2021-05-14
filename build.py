from os import walk
import subprocess

subprocess.run(["make", "loader.o"])
for (dirpath, dirnames, filenames) in walk("src"):
    for file in filenames:
        name = file.split(".")[0]
        prp = file.split(".")[1]
        if (prp == "cpp"):
            subprocess.run(["make", name + ".o"])
"""
make KubOS.bin
make KubOS.iso
make run
"""

subprocess.run(["make", "KubOS.bin"])
subprocess.run(["make", "KubOS.iso"])
subprocess.run(["make", "run"])