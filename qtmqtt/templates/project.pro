TEMPLATE = subdirs

SUBDIRS += apps
SUBDIRS += servers
SUBDIRS += plugins
SUBDIRS += libs

apps.depends += plugins
apps.depends += servers
servers.depends += libs
plugins.depends += libs

OTHER_FILES += .qmake.conf

