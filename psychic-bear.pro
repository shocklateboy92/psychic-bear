TEMPLATE = subdirs
SUBDIRS = core app \
    db/init-db \
    db/migrate

core.file = src/core.pro

app.file = app.pro
app.depends = core

db/init-db.depends = core
db/migrate.depends = core
