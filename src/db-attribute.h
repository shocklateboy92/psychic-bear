#ifndef DBATTRIBUTE_H
#define DBATTRIBUTE_H

class QString;

class DBAttribute
{
public:
    DBAttribute();
    ~DBAttribute();

    bool fetchId(const QString &uri);

    bool error() const;

private:
    int m_id;
    bool m_error;
};

#endif // DBATTRIBUTE_H
