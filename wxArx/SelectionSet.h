#pragma once

using EntselResult = std::tuple<Acad::PromptStatus, AcDbObjectId, AcGePoint3d>;

class SelectionSet
{
private:
    Int32 m_length = 0;
    const ACHAR* m_mode = nullptr;
    const void  *m_point1 = nullptr;
    const void  *m_point2 = nullptr;
    const resbuf  *m_filter = nullptr;
    ads_name m_ss = { 0L, 0L };

public:
    SelectionSet(void);
    SelectionSet(const ACHAR* mode, const void *point1, const void *point2, const resbuf *filter);
    ~SelectionSet(void);
    AcDbObjectIdArray Select();
    const EntselResult entSel(const TCHAR* msg = L"\nSelect Entity: ", const AcRxClass* desc = AcDbEntity::desc());
};