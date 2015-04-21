#include "filtered-attribute-list.h"

FilteredAttributeList::FilteredAttributeList()
{

}

FilteredAttributeList::~FilteredAttributeList()
{

}

QString FilteredAttributeList::pattern() const
{
    return m_pattern;
}

ProjectContext::AttributeList FilteredAttributeList::attribtues()
{
    return ProjectContext::AttributeList(this, m_attributes);
}

void FilteredAttributeList::setPattern(QString arg)
{
    if (m_pattern == arg)
        return;

    m_pattern = arg;
    emit patternChanged(arg);

    QRegExp regex(m_pattern, Qt::CaseInsensitive, QRegExp::Wildcard);

    auto all = AttributeManager::instance().attributes();
    std::copy_if(all.begin(), all.end(),
                 std::back_inserter(m_attributes),
                 [&](Attribute *a){
        return regex.exactMatch(a->uri());
    });
}

