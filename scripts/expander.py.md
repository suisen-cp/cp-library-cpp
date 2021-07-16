---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.6/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "#!/usr/bin/env python3\n\nimport re\nimport sys\nimport argparse\nfrom logging\
    \ import Logger, basicConfig, getLogger\nfrom os import getenv, environ\nfrom\
    \ pathlib import Path\nfrom typing import List\n\nlogger = getLogger(__name__)\
    \  # type: Logger\n\nacl_include = re.compile('#include\\s*[\"<](atcoder/.*)[\"\
    >]\\s*')\nlib_include = re.compile('#include\\s*[\"<](library/.*)[\">]\\s*')\n\
    \nacl_include_guard = re.compile('#.*ATCODER_.*')\nlib_include_guard = re.compile('#.*SUISEN_.*')\n\
    \ndefined = set()\n\ndef dfs(f: str, is_acl: bool) -> List[str]:\n    print(f'expanding\
    \ : {f}\\ntype : {\"ACL\" if is_acl else \"LIB\"}')\n    global defined\n    if\
    \ f in defined:\n        logger.info('already included {}, skip'.format(f))\n\
    \        return []\n    defined.add(f)\n\n    logger.info('include {}'.format(f))\n\
    \n    if is_acl:\n        s = open(str(acl_path / f)).read()\n    else:\n    \
    \    s = open(str(lib_path / f)).read()\n\n    result = []\n    for line in s.splitlines():\n\
    \        if acl_include_guard.match(line) or lib_include_guard.match(line):\n\
    \            continue\n\n        acl_matcher = acl_include.match(line)\n     \
    \   if acl_matcher:\n            result.extend(dfs(acl_matcher.group(1), True))\n\
    \            continue\n\n        lib_matcher = lib_include.match(line)\n     \
    \   if lib_matcher:\n            result.extend(dfs(lib_matcher.group(1), False))\n\
    \            continue\n\n        result.append(line)\n    return result\n\n\n\
    if __name__ == \"__main__\":\n    basicConfig(\n        format=\"%(asctime)s [%(levelname)s]\
    \ %(message)s\",\n        datefmt=\"%H:%M:%S\",\n        level=getenv('LOG_LEVEL',\
    \ 'INFO'),\n    )\n    parser = argparse.ArgumentParser(description='Expander')\n\
    \    parser.add_argument('source', help='Source File')\n    parser.add_argument('--acl',\
    \ help='Path to AtCoder Library')\n    parser.add_argument('--lib', help='Path\
    \ to My Library')\n    parser.add_argument('--out', help='Output File')\n    opts\
    \ = parser.parse_args()\n\n    lib_path = Path(opts.lib)\n    acl_path = Path(opts.acl)\n\
    \n    s = open(opts.source).read()\n\n    result = []\n    for line in s.splitlines():\n\
    \        acl_matcher = acl_include.match(line)\n        if acl_matcher:\n    \
    \        result.extend(dfs(acl_matcher.group(1), True))\n            continue\n\
    \        lib_matcher = lib_include.match(line)\n        if lib_matcher:\n    \
    \        result.extend(dfs(lib_matcher.group(1), False))\n            continue\n\
    \        result.append(line)\n\n    output = '\\n'.join(result) + '\\n'\n    with\
    \ open(opts.out, 'w') as f:\n        f.write(output)\n"
  dependsOn: []
  isVerificationFile: false
  path: scripts/expander.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: scripts/expander.py
layout: document
redirect_from:
- /library/scripts/expander.py
- /library/scripts/expander.py.html
title: scripts/expander.py
---
