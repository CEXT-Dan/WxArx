#include "StdAfx.h"
#include "SelectionSet.h"

SelectionSet::SelectionSet(void)
    : m_length(0), m_mode(NULL),
    m_point1(NULL), m_point2(NULL),
    m_filter(NULL), m_ss{ 0L, 0L }
{
}

SelectionSet::SelectionSet(const ACHAR* mode, const void *point1, const void *point2, const resbuf *filter)
    : m_length(0), m_mode(mode),
    m_point1(point1), m_point2(point2),
    m_filter(filter), m_ss{0L, 0L}
{
}

SelectionSet::~SelectionSet(void)
{
    acedSSFree(m_ss);
}

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

const EntselResult SelectionSet::entSel(const TCHAR* msg /*= L"\nSelect Entity: "*/, const AcRxClass* desc /*= AcDbEntity::desc()*/)
{
    AcDbObjectId id;
    AcGePoint3d pnt;
    ads_name name = { 0L };
    int res = acedEntSel(msg, name, asDblArray(pnt));
    if (auto es = acdbGetObjectId(id, name); es != eOk)
        return std::make_tuple(Acad::PromptStatus::eError, id, pnt);
    if (!id.objectClass()->isDerivedFrom(desc))
        return std::make_tuple(Acad::PromptStatus::eRejected, id, pnt);
    return std::make_tuple(Acad::PromptStatus(res), id, pnt);
}
