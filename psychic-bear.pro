TEMPLATE = subdirs
SUBDIRS = core \
    mobile

core.file = src/core.pro

app.file = app.pro
app.depends = core

db/init-db.depends = core
db/migrate.depends = core

android {
    SUBDIRS += mobile/mobile.pro
} else {
    SUBDIRS += app db/init-db db/migrate
}
