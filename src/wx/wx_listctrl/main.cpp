#include "wx/wx.h"
#include <wx/listctrl.h>

#include <memory>
#include <unordered_set>
#include <iostream>

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

private:
    wxListView *basicListView;
    void populateListView();
    void addItem(int id, const std::string &name, const std::string &description);

    // sorting methods
    void sortByColumn(int column);
    int sortDirection{1};

    struct ItemData
    {
        int id;
        std::string name;
        std::string description;
    };
    std::unordered_set<std::unique_ptr<ItemData>> itemDataBag;

    static int compareInts(int i1, int i2, int direction);
    static int compareString(const std::string &s1, const std::string &s2, int direction);

    static int idSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
    static int nameSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);
    static int descriptionSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction);

    void sortById(wxCommandEvent &);
    // int sortDirection{1};
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("List Control", wxDefaultPosition, wxDefaultSize);
    frame->Show();
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxPanel *panel = new wxPanel(this);
    basicListView = new wxListView(panel);
    basicListView->AppendColumn("ID");
    basicListView->AppendColumn("Name");
    basicListView->AppendColumn("Desription");

    basicListView->SetColumnWidth(0, 80);
    basicListView->SetColumnWidth(1, 120);
    basicListView->SetColumnWidth(2, 600);

    basicListView->Bind(wxEVT_LIST_COL_CLICK, [this](wxListEvent &event)
                        { this->sortByColumn(event.GetColumn()); });

    // add button for sorting the values
    // auto button = new wxButton(panel, wxID_ANY, "Sort By ID");
    // button->Bind(wxEVT_BUTTON, &MyFrame::sortById, this);

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(basicListView, 1, wxALL | wxEXPAND, 0);
    // sizer->Add(button, 0, wxALIGN_RIGHT | wxTOP | wxBOTTOM | wxRIGHT, 5);

    panel->SetSizerAndFit(sizer);
    populateListView();
}

void MyFrame::populateListView()
{
    std::cout << "Adding items to list..." << std::endl;
    addItem(100, "Aamir", "Aamir's Item");
    addItem(99, "Mohammad", "Mohammad's Item");
    // addItem(101, "Ali", "Ali's Item");

    // basicListView->InsertItem(0, "100");
    // basicListView->SetItem(0, 1, "Aamir");
    // basicListView->SetItem(0, 2, "Aamir's Item");

    // basicListView->InsertItem(1, "101");
    // basicListView->SetItem(1, 1, "Mohammad");
    // basicListView->SetItem(1, 2, "Mohammad's Item");

    // basicListView->InsertItem(2, "102");
    // basicListView->SetItem(2, 1, "Ali");
    // basicListView->SetItem(2, 2, "Ali's Item");
}

void MyFrame::addItem(int id, const std::string &name, const std::string &description)
{
    int index = basicListView->GetItemCount();

    basicListView->InsertItem(index, std::to_string(id));
    basicListView->SetItem(index, 1, name);
    basicListView->SetItem(index, 2, description);

    ItemData data{id, name, description};
    auto dataPtr = std::make_unique<ItemData>(data);
    basicListView->SetItemData(index, reinterpret_cast<wxIntPtr>(dataPtr.get()));
    std::cout << "Address of data ptr: " << dataPtr.get() << std::endl;
    itemDataBag.insert(std::move(dataPtr));

    // pass meta data to listview
    // basicListView->SetItemData(index, id);
}

void MyFrame::sortById(wxCommandEvent &)
{

    //     basicListView->SortItems(
    //         [](wxIntPtr item1, wxIntPtr item2, wxIntPtr dir) -> int
    //         {
    //             if (item1 == item2)
    //             {
    //                 return 0;
    //             }
    //             else if (item1 < item2)
    //             {
    //                 return static_cast<int>(dir) * -1;
    //             }
    //             else
    //             {
    //                 return static_cast<int>(dir);
    //             }
    //         },
    //         this->sortDirection);

    sortByColumn(0);
    // basicListView->Refresh();
    // this->sortDirection = -this->sortDirection;
}

void MyFrame::sortByColumn(int column)
{
    std::cout << "column - " << column << " clicked." << std::endl;
    switch (column)
    {
    case 0:
        basicListView->SortItems(idSortCallback, this->sortDirection);
        break;
    case 1:
        basicListView->SortItems(nameSortCallback, this->sortDirection);
        break;
    case 2:
        basicListView->SortItems(descriptionSortCallback, this->sortDirection);
        break;
    default:
        return;
    }
    basicListView->Refresh();
    this->sortDirection = -this->sortDirection;
}

int MyFrame::compareInts(int i1, int i2, int direction)
{
    if (i1 == i2)
        return 0;
    else if (i1 < i2)
        return -direction;
    else
        return direction;
}

int MyFrame::compareString(const std::string &s1, const std::string &s2, int direction)
{
    return s1.compare(s2) * direction;
}

int MyFrame::idSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
    std::cout << "Item1 address: " << reinterpret_cast<ItemData *>(item1) << std::endl;
    ItemData *i1 = reinterpret_cast<ItemData *>(item1);
    ItemData *i2 = reinterpret_cast<ItemData *>(item2);

    return compareInts(
        i1->id,
        i2->id,
        static_cast<int>(direction));

    // return compareInts(
    //     reinterpret_cast<ItemData *>(item1)->id,
    //     reinterpret_cast<ItemData *>(item2)->id,
    //     static_cast<int>(direction));
}

int MyFrame::nameSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
    return compareString(
        reinterpret_cast<ItemData *>(item1)->name,
        reinterpret_cast<ItemData *>(item2)->name,
        static_cast<int>(direction));
}

int MyFrame::descriptionSortCallback(wxIntPtr item1, wxIntPtr item2, wxIntPtr direction)
{
    return compareString(
        reinterpret_cast<ItemData *>(item1)->description,
        reinterpret_cast<ItemData *>(item2)->description,
        static_cast<int>(direction));
}
