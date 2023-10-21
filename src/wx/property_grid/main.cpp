#include "wx/wx.h"
#include <wx/propgrid/propgrid.h>
#include <wx/timer.h>

#include <iostream>
#include <memory>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    void OnTimeout(wxTimerEvent &event){
        // static int counter{};
        // std::cout << "Speed = " << pg->GetPropertyValue("Car.Speeds.Max. Speed (mph)").GetLong() << std::endl;
        // ++counter;
        // if (counter % 15 == 0)
        // {
        //     // wxPropertyGridIterator it;
        //     // for (it = pg->GetIterator(); !it.AtEnd(); ++it)
        //     // {
        //     //     wxPGProperty *p = *it;
        //     //     std::cout << p->GetName() << ", " << p->GetValueAsString() << std::endl;
        //     // }

        //     // wxPropertyGridIterator it;
        //     // for (it = pg->GetIterator(wxPG_ITERATE_VISIBLE, wxBOTTOM); !it.AtEnd(); --it)
        //     // {
        //     //     wxPGProperty *p = *it;
        //     //     std::cout << p->GetName() << ", " << p->GetValueAsString() << std::endl;
        //     // }
        // }
    };

    void OnPropertyGridChanged(wxPropertyGridEvent &event)
    {
        wxPGProperty *property = event.GetProperty();
        if (property == nullptr)
            return;
        wxAny value = property->GetValue();

        if (value.IsNull())
            return;

        std::cout << property->GetName() << ", " << value.As<wxString>() << std::endl;
    }

private:
    wxPropertyGrid *m_PropertyGrid = nullptr;
    wxPropertyGrid *pg;
    std::unique_ptr<wxTimer> timer;
    long int speed;
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Property Grid", wxDefaultPosition, wxDefaultSize);
    frame->Show();
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    timer = std::make_unique<wxTimer>(this, 5'002);
    Bind(wxEVT_TIMER, wxTimerEventHandler(MyFrame::OnTimeout), this, 5'002);
    m_PropertyGrid = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxSize(300, 0), wxPG_LIMITED_EDITING);

    m_PropertyGrid->SetEmptySpaceColour(this->GetBackgroundColour());
    m_PropertyGrid->SetCellBackgroundColour(this->GetBackgroundColour());

    wxPGProperty *generalCategory = m_PropertyGrid->Append(new wxPropertyCategory(_("General Information")));
    m_PropertyGrid->AppendIn(generalCategory, new wxStringProperty(_("Location"), wxPG_LABEL, wxString::Format("43.45N, 47.85W")));
    // pg = new wxPropertyGrid(
    //     this,
    //     -1,
    //     wxDefaultPosition,
    //     wxDefaultSize,
    //     wxPG_SPLITTER_AUTO_CENTER | wxPG_DEFAULT_STYLE, "");

    // pg->SetColumnCount(4);
    // Bind(wxEVT_PG_CHANGED, &MyFrame::OnPropertyGridChanged, this);

    // pg->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS | wxPG_NO_INTERNAL_BORDER | wxPG_LIMITED_EDITING);
    // pg->Append(new wxLongStringProperty(wxT("A Label For Values"),
    //                                     wxPG_LABEL,
    //                                     wxT("Value itself")
    //                                         wxT("...")));
    // pg->Append(new wxStringProperty("Label", "Name", "Initial Value"));
    // pg->Append(new wxIntProperty("IntProperty", wxPG_LABEL, 335456));
    // pg->Append(new wxFloatProperty("FloatProperty", wxPG_LABEL, 32.123));
    // pg->Append(new wxLongStringProperty("LongStringProperty",
    //                                     wxPG_LABEL, "This is much longer string than the first one. Edit it by clicking the button."));
    // pg->Append(new wxDirProperty("DirProperty", wxPG_LABEL, ::wxGetUserHome()));
    // pg->Append(new wxArrayStringProperty("Label of ArrayStringProperty", "NameOfArrayStringProp"));
    // pg->Append(new wxFileProperty("FileProperty", wxPG_LABEL, wxEmptyString));
    // pg->SetPropertyAttribute("FileProperty", wxPG_FILE_WILDCARD, "All Files (*.*)|*.*");

    // wxArrayString arrDiet;
    // arrDiet.Add("Hello");
    // arrDiet.Add("World");
    // arrDiet.Add("wxWidgets");

    // wxArrayInt arrIds;
    // arrIds.Add(10);
    // arrIds.Add(20);
    // arrIds.Add(30);

    // pg->Append(new wxEnumProperty("String", wxPG_LABEL, arrDiet, arrIds, 30));

    // pg->Append(new wxPropertyCategory("Main"));
    // pg->Append(new wxStringProperty("Name"));
    // pg->Append(new wxIntProperty("Age", wxPG_LABEL, 40));

    // pg->Append(new wxPropertyCategory("Attributes"));
    // pg->Append(new wxIntProperty("Intelligence"));
    // pg->Append(new wxIntProperty("Agility"));

    // // tree-like property structure
    // wxPGProperty *carProp = pg->Append(new wxStringProperty("Car", wxPG_LABEL, "<composed>"));
    // pg->SetPropertyTextColour(carProp, *wxBLUE);
    // pg->AppendIn(carProp, new wxStringProperty("Model", wxPG_LABEL, "Lamborghini Diablo SV"));
    // pg->AppendIn(carProp, new wxIntProperty("Engine Size (cc)", wxPG_LABEL, 5707));

    // wxPGProperty *speedProp = pg->AppendIn(carProp, new wxStringProperty("Speeds", wxPG_LABEL, "<composed>"));
    // pg->SetPropertyTextColour(speedProp, *wxBLACK);
    // pg->AppendIn(speedProp, new wxIntProperty("Max. Speed (mph)", wxPG_LABEL, 290));
    // pg->AppendIn(speedProp, new wxFloatProperty("0-100 mph (sec)", wxPG_LABEL, 3.9));
    // pg->AppendIn(speedProp, new wxFloatProperty("1/4 mile (sec)", wxPG_LABEL, 8.6));
    timer->Start(1000);
}

/*
//add property grid
            wxPropertyGrid* regProp = new wxPropertyGrid(
                panel_right, // parent
                wxID_ANY, // id
                wxDefaultPosition, // position
                wxSize(400, 200), // size
                wxPG_SPLITTER_AUTO_CENTER | // Automatically center splitter until user manually adjusts it
                // Default style
                wxPG_DEFAULT_STYLE);
            regProp->SetColumnCount(4);
            regProp->SetExtraStyle(wxPG_EX_HELP_AS_TOOLTIPS);

            //label
            regProp->Append(new wxLongStringProperty(wxT("A Label For Values"),
                wxPG_LABEL,
                wxT("Value itself")
                wxT("...")));
            regProp->SetPropertyAttribute(wxT("A Label For Values"), wxPG_ATTR_UNITS, wxT("Permissions"));
            regProp->SetPropertyCell(wxT("A Label For Values"), 3, wxString("Permissions"), wxBitmap(wxNullBitmap), wxColour(100, 100, 100));
            regProp->SetPropertyCell(wxT("A Label For Values"), 4, wxString("Bit-Field"), wxBitmap(wxNullBitmap), wxColour(100, 200, 100));
*/