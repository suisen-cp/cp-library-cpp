#!/usr/bin/env python3

import colorlog
import logging
import textwrap
import argparse
from pathlib import Path

def generate(relative_path: Path):
    dir_path = gen_root / relative_path

    if dir_path.exists():
        logger.debug(f'Directory "{dir_path}" already exists.')
        return

    logger.info(f'Generate directory "{dir_path}."')

    dir_path.mkdir(parents=True)
    gitignore = dir_path / ".gitignore"

    gitignore.write_text(
        textwrap.dedent("""\
            /*
            !.gitignore
            !*.cpp
            combined.cpp
            !*.md
        """)
    )

if __name__ == '__main__':
    logger: logging.Logger = logging.getLogger(__name__)
    handler = colorlog.StreamHandler()
    formatter = colorlog.ColoredFormatter(
        "%(log_color)s%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
    )
    handler.setFormatter(formatter)
    logging.basicConfig(
        level=logging.INFO,
        handlers=[handler]
    )

    parser = argparse.ArgumentParser(description='Generate test directories for all libraries.')
    parser.add_argument('src', help='Base directory of source files')
    parser.add_argument('dst', help='Destination directory')
    opts = parser.parse_args()

    src_root = Path(opts.src)
    gen_root = Path(opts.dst)

    for src_path in src_root.glob('**/*.hpp'):
        generate(src_path.relative_to(src_root).with_suffix(''))
