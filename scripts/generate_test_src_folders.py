#!/usr/bin/env python3

import os
import subprocess
import argparse
from pathlib import Path

def generate(path):
    dir_path = (test_gen + path).replace(".hpp", "")
    if not os.path.exists(dir_path):
        print("generate:", dir_path)
        os.makedirs(dir_path)
    gitignore = Path(dir_path) / Path(".gitignore")
    with open(gitignore, mode='w') as f:
        f.write("/*\n")
        f.write("!.gitignore\n")
        f.write("!*.cpp\n")
        f.write("combined.cpp\n")
        f.write("!*.md\n")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate Test Source Folders for All Libraries')
    parser.add_argument('test_source', help='Source Directory')
    parser.add_argument('test_dest', help='Destination Directory')
    opts = parser.parse_args()

    test_src = opts.test_source
    test_gen = opts.test_dest

    for path in map(str, Path(test_src).glob("**/*.hpp")):
        generate(path[len(test_src):-4])