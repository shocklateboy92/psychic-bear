#include "spell-list.h"

SpellList::SpellList(QQuickItem *parent)
    : Resource(QStringLiteral("SpellLists"), parent)
{

}

QString SpellList::className() const
{
    return m_className;
}

//SpellList::Model SpellList::model() const
//{
//    return m_model;
//}

void SpellList::setClassName(QString className)
{
    if (m_className == className)
        return;

    m_className = className;
    emit classNameChanged(className);
}



//int SpellList::Model::rowCount(const QModelIndex &parent) const
//{
//}

//QVariant SpellList::Model::data(const QModelIndex &index, int role) const
//{
//}

//QVariant SpellList::Model::headerData(int section, Qt::Orientation orientation, int role) const
//{
//}

//SpellList::Model::Model(SpellList *parent)
//    : m_parent(parent)
//{

//}
