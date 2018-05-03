#!/usr/bin/env python3
# Copyright (c) Pelagicore AB 2016

import sys
import click
import logging
import logging.config
import yaml
from path import Path

from qface.generator import FileSystem, RuleGenerator
from qface.helper.qtcpp import Filters
from qface.helper.doc import parse_doc
from qface.watch import monitor
from qface.shell import sh
import qface.filters

from jinja2 import environmentfilter

here = Path(__file__).dirname()

logging.basicConfig()

log_config = Path('log.yaml')

if log_config.exists():
    logging.config.dictConfig(yaml.load(log_config.open('r')))
log = logging.getLogger(__name__)


features = set()


def run(src, dst, force=False):
    log.debug('run {0} {1}'.format(src, dst))
    project = Path(dst).name
    classPrefix = ''
    system = FileSystem.parse(src)

    context = {
        'dst': dst,
        'system': system,
        'classPrefix': classPrefix,
        'project': project,
        'features': features,
    }

    generator = RuleGenerator(search_path=here / 'templates', destination=dst, context=context, features=features, force=force)

    Filters.classPrefix = classPrefix
    generator.filters.update(Filters.get_filters())
    generator.filters.update({
        'parse_doc': parse_doc,
        'hash': qface.filters.hash,
        'jsonify': qface.filters.jsonify,
    })

    generator.process_rules(here / 'qtmqtt.yml', system)


@click.command()
@click.option('--reload/--no-reload', default=False, help="Auto reload script on changes")
@click.option('--scaffold/--no-scaffold', default=True, help="Generates scaffolding app")
@click.option('--apps/--no-apps', default=True, help="Generates apps stubs")
@click.option('--servers/--no-servers', default=True, help="Generates server code")
@click.option('--force/--no-force', default=True, help="Force writing of target files, ignores preserve")
@click.option('cmd', '--exec', type=click.Path(exists=True), multiple=True, help="Executes script after code generation")
@click.argument('src', nargs=-1, type=click.Path(exists=True))
@click.argument('dst', nargs=1, type=click.Path(exists=False, file_okay=False))
def app(src, dst, reload, cmd, scaffold, apps, servers, force):
    """Takes several files or directories as src and generates the code
    in the given dst directory."""
    global features
    if scaffold:
        features.add('scaffold')
    if apps:
        features.add('apps')
    if servers:
        features.add('servers')
    if reload:
        argv = sys.argv.copy()
        argv.remove('--reload')
        monitor(here, src, dst, argv)
    else:
        run(src, dst, force)
        sh(cmd)


if __name__ == '__main__':
    app()
