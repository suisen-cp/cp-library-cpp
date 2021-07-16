#!/usr/bin/env python3

import re
import sys
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ
from pathlib import Path
from typing import List

logger = getLogger(__name__)  # type: Logger

problem_def = re.compile('#define\s*PROBLEM\s.*')

acl_include = re.compile('#include\s*["<](atcoder/.*)[">]\s*')
lib_include = re.compile('#include\s*["<](library/.*)[">]\s*')

acl_include_guard = re.compile('#.*ATCODER_.*')
lib_include_guard = re.compile('#.*SUISEN_.*')

defined = set()

def dfs(f: str, is_acl: bool) -> List[str]:
    print(f'expanding : {f}\ntype : {"ACL" if is_acl else "LIB"}')
    global defined
    if f in defined:
        logger.info('already included {}, skip'.format(f))
        return []
    defined.add(f)

    logger.info('include {}'.format(f))

    if is_acl:
        s = open(str(acl_path / f)).read()
    else:
        s = open(str(lib_path / f)).read()

    result = []
    for line in s.splitlines():
        if acl_include_guard.match(line) or lib_include_guard.match(line):
            continue
        
        if not acl_enabled:
            acl_matcher = acl_include.match(line)
            if acl_matcher:
                result.extend(dfs(acl_matcher.group(1), True))
                continue

        # lib_matcher = lib_include.match(line)
        # if lib_matcher:
        #     result.extend(dfs(lib_matcher.group(1), False))
        #     continue

        result.append(line)
    return result


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Expander')
    parser.add_argument('source', help='Source File')
    parser.add_argument('--acl', help='Path to AtCoder Library')
    parser.add_argument('--lib', help='Path to My Library')
    parser.add_argument('--out', help='Output File')
    opts = parser.parse_args()

    lib_path = Path(opts.lib)
    acl_path = Path(opts.acl)

    acl_enabled = False

    s = open(opts.source).read()

    result = []
    for line in s.splitlines():
        problem_matcher = problem_def.match(line)
        if problem_matcher:
            acl_enabled |= "atcoder" in line or "yosupo" in line

        if not acl_enabled:
            acl_matcher = acl_include.match(line)
            if acl_matcher:
                result.extend(dfs(acl_matcher.group(1), True))
                continue
        # lib_matcher = lib_include.match(line)
        # if lib_matcher:
        #     result.extend(dfs(lib_matcher.group(1), False))
        #     continue
        result.append(line)

    output = '\n'.join(result) + '\n'
    with open(opts.out, 'w') as f:
        f.write(output)
