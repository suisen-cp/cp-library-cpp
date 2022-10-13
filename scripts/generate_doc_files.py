#!/usr/bin/env python3

import argparse
import colorlog
import logging
from pathlib import Path
import textwrap

def generate(src_file: Path):
    doc_path = (doc_root / src_file).with_suffix(".md")
    
    if doc_path.exists():
        logger.debug(f"File '{doc_path}' already exists.")
        return
    logger.info(f"Generate file '{doc_path}'.")

    doc_path.parent.mkdir(parents=True, exist_ok=True)
    doc_path.touch()

    lib_name = ' '.join(w.capitalize() for w in doc_path.stem.split('_'))

    doc_path.write_text(
        textwrap.dedent(f"""\
            ---
            title: {lib_name}
            documentation_of: //library/{src_file}
            ---
            ## {lib_name}
        """)
    )

    with open(doc_path, mode='w') as f:
        lib_name = ' '.join(w.capitalize() for w in doc_path.stem.split('_'))

        lines = [
            f'---',
            f'title: {lib_name}',
            f'documentation_of: //library/{src_file}',
            f'---',
            f'## {lib_name}',
        ]
        f.write('\n'.join(lines))

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

    parser = argparse.ArgumentParser(description='Generate document files for all libraries.')
    parser.add_argument('src', help='Base directory of source files')
    parser.add_argument('dst', help='Destination directory')
    opts = parser.parse_args()

    src_root = Path(opts.src)
    doc_root = Path(opts.dst)

    for src_file in Path(src_root).glob("**/*.hpp"):
        generate(src_file.relative_to(src_root))
