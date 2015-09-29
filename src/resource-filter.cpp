#include "resource-filter.h"

ResourceFilter::ResourceFilter(QObject *parent)
    : QObject(parent)
{

}

ResourceFilter::~ResourceFilter()
{

}

QString ResourceFilter::pattern() const
{
    return m_pattern;
}

ProjectContext::ResourceList ResourceFilter::matches()
{
    return ProjectContext::ResourceList(this, m_matches);
}

void ResourceFilter::setPattern(QString arg)
{
    if (m_pattern == arg)
        return;

    m_pattern = arg;
    emit patternChanged(arg);
}

void ResourceFilter::updateResources(Resource::List availableResources)
{
    QRegExp regex(m_pattern, Qt::CaseInsensitive, QRegExp::Wildcard);

    m_matches.clear();
    auto all = availableResources;

    std::copy_if(all.begin(), all.end(),
                 std::back_inserter(m_matches),
                 [&](Resource *a){
        return regex.exactMatch(a->uri());
    });

    emit matchesChanged(matches());
}

