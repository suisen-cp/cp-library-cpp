#!/usr/bin/env python3

import os
import argparse
from pathlib import Path

def generate(path):
    doc_path = str(Path(doc_folder) / Path(path)).replace(".hpp", ".md")
    if os.path.exists(doc_path):
        return
    if not os.path.exists(os.path.dirname(doc_path)):
        os.makedirs(os.path.dirname(doc_path))
    print("generate:", doc_path)
    with open(doc_path, mode='w') as f:
        lib_name = ' '.join(w.capitalize() for w in Path(doc_path).stem.split('_'))

        lines = [
            f'---',
            f'title: {lib_name}',
            f'documentation_of: //library/{path}',
            f'---',
            f'## {lib_name}',
        ]
        f.write('\n'.join(lines))

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate Document Files for All Libraries')
    parser.add_argument('test_source', help='Source Directory')
    parser.add_argument('doc_folder', help='Documents Floder')
    opts = parser.parse_args()

    src_folder = opts.test_source
    doc_folder = opts.doc_folder

    for path in map(str, Path(src_folder).glob("**/*.hpp")):
        generate(path[len(src_folder):])
