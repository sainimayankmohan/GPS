TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = DcMapLib DcMapApp
DcMapApp.depends = DcMapLib
