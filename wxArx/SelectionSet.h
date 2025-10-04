#pragma once
class SelectionSet
{
private:
    Int32 m_length = 0;
    const ACHAR* m_mode = nullptr;
    const void  *m_point1 = nullptr;
    const void  *m_point2 = nullptr;
    resbuf  *m_filter = nullptr;
    ads_name m_ss = { 0L, 0L };

public:
    SelectionSet(void);
    SelectionSet(const ACHAR* mode, const void *point1, const void *point2, resbuf *filter);
    ~SelectionSet(void);
    AcDbObjectIdArray Select();
    static const auto entSel(const TCHAR* msg);
};