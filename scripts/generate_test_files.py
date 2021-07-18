#!/usr/bin/env python3

import os
import subprocess
import argparse
from pathlib import Path

def generate(path):
    input_path = test_src + path
    output_path = (test_gen + path).replace(".cpp", ".test.cpp")

    dir_path = os.path.dirname(output_path)
    if not os.path.exists(dir_path):
        os.makedirs(dir_path)

    args = [
        'python3', './scripts/expander.py',
        '--lib', './',
        '--acl', acl_dir,
        '--out', output_path,
        input_path
    ]
    subprocess.call(args)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate Test Files')
    parser.add_argument('test_source', help='Source Directory')
    parser.add_argument('test_dest', help='Destination Directory')
    parser.add_argument('--acl', help='AtCoder Library Directory')
    opts = parser.parse_args()

    test_src = opts.test_source
    test_gen = opts.test_dest
    acl_dir = opts.acl

    for path in map(str, Path(test_src).glob("**/*.cpp")):
        print(f'{path[len(test_src):]}')
        generate(path[len(test_src):])