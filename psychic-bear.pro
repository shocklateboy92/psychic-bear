TEMPLATE = subdirs
SUBDIRS = core

core.file = src/core.pro

app.file = app.pro
app.depends = core

db/init-db.depends = core
db/migrate.depends = core

mobile.file = mobile/mobile.pro
mobile.depends = core

android {
    SUBDIRS += mobile
} else {
    SUBDIRS += app db/init-db db/migrate
}
