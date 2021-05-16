from os import walk
import subprocess

subprocess.run(["make", "clean"])

objects = ""
asmObjects = "$(LIBDIR)/loader.o $(LIBDIR)/interruptstubs.o "

subprocess.run(["make", "loader.o"])
subprocess.run(["make", "interruptstubs.o"])

for (dirpath, dirnames, filenames) in walk("src"):
    for file in filenames:
        name = file.split(".")[0]
        prp = file.split(".")[1]
        if (prp == "cpp"):
            print(f"========\n {name} \n========")
            subprocess.run(["make", name + ".o"])
            objects += "$(LIBDIR)/" + name + ".o "

mkFile = ""
with open("makefile", "r") as f:
    for line in f.readlines():
        if (line.startswith("objects")):
            mkFile += "objects = " + asmObjects + objects + "\n"
        else:
            mkFile += line

with open("makefile", "w") as f:
    f.write(mkFile)
"""
make KubOS.bin
make KubOS.iso
make run
"""

subprocess.run(["make", "KubOS.bin"])
subprocess.run(["make", "KubOS.iso"])
subprocess.run(["make", "run"])