#include "StdAfx.h"
#include "SelectionSet.h"

//++--
SelectionSet::SelectionSet(void)
    : m_length(0), m_mode(NULL),
    m_point1(NULL), m_point2(NULL),
    m_filter(NULL), m_ss{ 0L, 0L }
{
}

//++--
SelectionSet::SelectionSet(const ACHAR* mode, const void *point1, const void *point2, resbuf *filter)
    : m_length(0), m_mode(mode),
    m_point1(point1), m_point2(point2),
    m_filter(filter), m_ss{0L, 0L}
{
}

//++--
SelectionSet::~SelectionSet(void)
{
    if (m_filter != NULL) acutRelRb(m_filter);
    acedSSFree(m_ss);
}

//++--
AcDbObjectIdArray SelectionSet::Select()
{
    AcDbObjectIdArray m_ids;
    if (acedSSGet(m_mode, m_point1, m_point2, m_filter, m_ss) == RTNORM)
    {
        if (acedSSLength(m_ss, &m_length) == RTNORM)
        {
            if (auto es = acedGetCurrentSelectionSet(m_ids); es != eOk)
                acutPrintf(_T("\nSelection error  = %ls :"), acadErrorStatusText(es));
        }
    }
    return m_ids;
}

const auto SelectionSet::entSel(const TCHAR* msg)
{
    AcGePoint3d pnt;
    AcDbObjectId id;
    Acad::ErrorStatus es = eOk;
    ads_name name = { 0L, 0L };
    if (acedEntSel(msg, name, asDblArray(pnt)) == RTNORM)
        es = acdbGetObjectId(id, name);
    return std::make_tuple(es, id, pnt);
}
