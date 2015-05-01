#ifndef DBHELPER_H
#define DBHELPER_H

#include <QString>

class DbHelper
{
public:
    DbHelper();
    ~DbHelper();

    static DbHelper fromUri(const QString &uri);

    int 	id() const;
    bool 	isValid() const;
    QString tableName() const;

    void setTableName(const QString &tableName);

    template <typename T>
    bool fetchProperty(QByteArray propName, T &ret);
    template <typename T>
    bool writeProperty(QByteArray propName, const T &val);

protected:
    void setId(int id);

private:
    int m_id;
    QString m_tableName;
};

#endif // DBHELPER_H
