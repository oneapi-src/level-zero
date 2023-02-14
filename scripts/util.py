"""
 Copyright (C) 2023 Intel Corporation

 SPDX-License-Identifier: Apache 2.0

"""
import re
import json
from mako.template import Template

makoFileList = []

def makoWrite(inpath, outpath, **args):
    template = Template(filename=inpath)
    rendered = template.render(**args)
    rendered = re.sub(r"\r\n", r"\n", rendered)

    with open(outpath, 'w') as fout:
        fout.write(rendered)

    makoFileList.append(outpath)
    return len(rendered.splitlines())

def makoFileListWrite(outpath):
    with open(outpath, 'w') as fout:
        fout.write(json.dumps(makoFileList, indent=4, sort_keys=True))
