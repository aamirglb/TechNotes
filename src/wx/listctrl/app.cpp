#include "wx/wx.h"
#include "wx/listctrl.h"
#include "wx/log.h"

#include <vector>
#include <string>


// class MyFrame : public wxFrame
// {
//     wxListCtrl* m_item_list;

// public:
//     MyFrame()
//         : wxFrame(nullptr, wxID_ANY, wxT("Hello wxWidgets"), wxPoint(50, 50), wxSize(800, 600))
//     {
//         wxPanel *mainPane = new wxPanel(this);
//         wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
//     }    
// };

class Item
{
public:
    Item() = default;
    Item(std::string name, std::string description) :
        m_name{name},
        m_description{description}
    { }

    bool isFoo() const {
        if(m_name == "Qt") return true;
        else return false;
    }

    std::string getName() const { return m_name; }
    std::string getDescription() const { return m_description; }
private:
    std::string m_name;
    std::string m_description;
};

class ItemContainer
{
public:
    int getItemAmount() const {
        return m_items.size();
    }

    void insert(const Item& item) {
        m_items.push_back(item);
    }

    Item* getItem(int n) {
        if(n < m_items.size()) {
            return &m_items[n];
        } else {
            return nullptr;
        }
    }
private:
    std::vector<Item> m_items;
};

ItemContainer ic;
void populate_test_data() 
{
    ic.insert(Item("wxWidget", "GUI toolkit"));
    ic.insert(Item("Qt", "Another GUI framework"));
}

class MyFrame : public wxFrame
{
public:
    MyFrame() :
        wxFrame(nullptr, wxID_ANY, wxT("Hello wxWidgets"), wxPoint(50, 50), wxSize(800, 600))
    {
        wxPanel *mainPane = new wxPanel(this);
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

        m_item_list = new wxListCtrl(mainPane, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

        wxListItem col0;
        col0.SetId(0);
        col0.SetText( _("Foo") );
        col0.SetWidth(50);
        m_item_list->InsertColumn(0, col0);

        wxListItem col1;
        col1.SetId(1);
        col1.SetText( _("Name") );
        // col1.SetWidth(50);
        m_item_list->InsertColumn(1, col1);

        wxListItem col2;
        col2.SetId(2);
        col2.SetText( _("Comments") );
        col2.SetWidth(150);
        m_item_list->InsertColumn(2, col2);

        populate_test_data();
        const int item_amount = ic.getItemAmount();
        for(int n = 0; n < item_amount; ++n) {
            Item *currItem = ic.getItem(n);

            wxString msg;
            msg.Printf("%s - %s", currItem->getName(), currItem->getDescription());
            wxMessageBox(msg);

            wxListItem item;
            item.SetId(n);
            item.SetText( currItem->getName() );

            m_item_list->InsertItem( item );

            if( !currItem->isFoo() ) {
                m_item_list->SetItem(n, 0, wxT("Foo") );
            } else {
                m_item_list->SetItem(n, 0, wxT("Bar") );
            }

            m_item_list->SetItem( n, 1, currItem->getName() );
            m_item_list->SetItem( n, 2, currItem->getDescription() );
        }

        // m_logger = new wxLogWindow(nullptr, "Log Window", true);

        sizer->Add(m_item_list, 1, wxEXPAND | wxALL, 10);
        // sizer->Add(m_logger, 1, wxEXPAND | wxALL, 10);
        mainPane->SetSizer(sizer);

        Bind(wxEVT_SIZE, &MyFrame::OnWindowResize, this);
        
    }

    void OnWindowResize(wxSizeEvent& event)
    {
        auto title = wxString::Format("%d, %d", 
                event.GetSize().GetWidth(),
                event.GetSize().GetHeight());

        wxStatusBar* sb = this->GetStatusBar();

        if(sb) {
            sb->SetStatusText(title, sb->GetFieldsCount() - 1);
        } else {
            // wxMessageBox(wxT("No Status Bar!!"));
            wxTopLevelWindow::SetTitle(wxString::Format("Hello wxWidgets - (%s)", title));
        }
        event.Skip();
    }

private:
    wxListCtrl* m_item_list;
    wxLogWindow* m_logger;
};

class MyApp : public wxApp
{
public:
    bool OnInit()
    {
        m_frame = new MyFrame();
        m_frame->Show();

        // connect resize event
        return true;
    }
private:
    wxFrame* m_frame;
};

IMPLEMENT_APP(MyApp)