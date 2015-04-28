TEMPLATE = subdirs
SUBDIRS = core app \
    db/init-db \
    db/migrate

core.file = src/core.pro
app.file = app.pro
