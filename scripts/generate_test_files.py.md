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
  code: "#!/usr/bin/env python3\n\nimport os\nimport subprocess\nimport argparse\n\
    from pathlib import Path\n\ndef generate(path):\n    input_path = test_src + path\n\
    \    output_path = (test_gen + path).replace(\".cpp\", \".test.cpp\")\n\n    dir_path\
    \ = os.path.dirname(output_path)\n    if not os.path.exists(dir_path):\n     \
    \   os.makedirs(dir_path)\n\n    args = [\n        'python3', './scripts/expander.py',\n\
    \        '--lib', './',\n        '--acl', acl_dir,\n        '--out', output_path,\n\
    \        input_path\n    ]\n    subprocess.call(args)\n\nif __name__ == '__main__':\n\
    \    parser = argparse.ArgumentParser(description='Expander')\n    parser.add_argument('test_source',\
    \ help='Source Directory')\n    parser.add_argument('test_dest', help='Destination\
    \ Directory')\n    parser.add_argument('--acl', help='AtCoder Library Directory')\n\
    \    opts = parser.parse_args()\n\n    test_src = opts.test_source\n    test_gen\
    \ = opts.test_dest\n    acl_dir = opts.acl\n\n    for path in map(str, Path(test_src).glob(\"\
    **/*.cpp\")):\n        print(f'{path[len(test_src):]}')\n        generate(path[len(test_src):])"
  dependsOn: []
  isVerificationFile: false
  path: scripts/generate_test_files.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: scripts/generate_test_files.py
layout: document
redirect_from:
- /library/scripts/generate_test_files.py
- /library/scripts/generate_test_files.py.html
title: scripts/generate_test_files.py
---
