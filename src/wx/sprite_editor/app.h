#pragma once

#include <wx/wx.h>
#include "frame.h"

class App : public wxApp
{
public:
    virtual bool OnInit();

private:
    Frame *m_Frame = nullptr;
};