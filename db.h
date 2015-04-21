#ifndef DB_H
#define DB_H

#include <QString>

namespace db
{

const QString DB_FILE = QStringLiteral("psychic_bear.db");

void initialize();
}

#endif // DB_H
