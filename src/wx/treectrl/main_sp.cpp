#include "wx/wx.h"
#include "wx/dataview.h"
#include <memory>
#include <vector>

/////////
// Implement a simple model with 2 columns
// FileName FileSize
/////////

// class DataModelNode;
// WX_DEFINE_ARRAY_PTR(DataModelNode *, DataModelNodePtrArray);

class DataModelNode
{
public:
    DataModelNode(
        std::shared_ptr<DataModelNode> parent,
        const wxString &name,
        const wxString &size)
        : m_Parent{parent},
          m_FileName{name},
          m_FileSize{size},
          m_IsContainer{false}
    {
    }

    DataModelNode(
        std::shared_ptr<DataModelNode> parent,
        const wxString &branch)
        : m_Parent{parent},
          m_FileName{branch},
          m_IsContainer{true}
    {
    }

    ~DataModelNode()
    {
        // size_t count = m_Children.GetCount();
        // for (size_t i = 0; i < count; ++i)
        // {
        //     DataModelNode *child = m_Children[i];
        //     std::cout << "Deleting child: " << child->m_FileName << std::endl;
        //     delete child;
        // }
    }

    bool IsContainer() const { return m_IsContainer; }
    std::shared_ptr<DataModelNode> GetParent() { return m_Parent; }
    std::vector<std::shared_ptr<DataModelNode>> &GetChildren() { return m_Children; }
    std::shared_ptr<DataModelNode> GetNthChild(size_t n) { return m_Children.at(n); }
    void Insert(std::shared_ptr<DataModelNode> child, size_t n) { m_Children.insert(m_Children.begin() + n, child); }
    void Append(std::shared_ptr<DataModelNode> child) { m_Children.push_back(child); }
    size_t GetChildCount() const { return m_Children.size(); }
    void Remove(std::shared_ptr<DataModelNode> child)
    {
        m_Children.erase(std::remove_if(m_Children.begin(), m_Children.end(), [&](auto p)
                                        { return p == child; }),
                         m_Children.end());
    }
    // DataModelNodePtrArray &GetChildren() { return m_Children; }
    // DataModelNode *GetNthChild(size_t n) { return m_Children.Item(n); }
    // void Insert(DataModelNode *child, size_t n) { m_Children.Insert(child, n); }
    // void Append(DataModelNode *child)
    // {
    //     std::cout << "Adding child " << child->m_FileName.ToStdString() << " to " << m_FileName << std::endl;
    //     // if (m_Parent != nullptr)
    //     //     std::cout << "Adding child " << child->m_FileName.ToStdString() << " to " << m_FileName << std::endl;
    //     // else
    //     //     std::cout << "Adding child " << child->m_FileName.ToStdString() << " to *** " << std::endl;
    //     m_Children.Add(child);
    // }
    // size_t GetChildCount() const { return m_Children.GetCount(); }

public:
    wxString m_FileName;
    wxString m_FileSize;
    bool m_IsContainer;

private:
    std::shared_ptr<DataModelNode> m_Parent{};
    std::vector<std::shared_ptr<DataModelNode>> m_Children;
    // DataModelNodePtrArray m_Children;
};

class DataModel : public wxDataViewModel
{
public:
    DataModel()
    {
        // m_Root = new DataModelNode(nullptr, "Root");
        // std::cout << "Roots location: " << m_Root << std::endl;
        // // m_DataItems.Add(wxDataViewItem{m_Root});
        // Add child nodes
        AddNewEntry();
    }

    ~DataModel()
    { /*delete m_Root;*/
    }

    // wxDataViewItem GetRootItem() const
    // {
    //     wxDataViewItem rootItem{static_cast<void *>(m_Root)};
    //     return rootItem;
    // }

    const wxDataViewItemArray &GetAllItems() const
    {
        return m_DataItems;
    }

    unsigned int GetColumnCount() const override { return 2; };
    wxString GetColumnType(unsigned int col) const override { return "string"; }

    wxDataViewItem AddNewEntry(int childCount = 1)
    {
        wxDateTime now = wxDateTime::Now();
        std::cout << now.Format("%F %T") << std::endl;
        wxDataViewItemArray items;

        auto parentNode = std::make_shared<DataModelNode>(nullptr, wxString::Format("Directory-%d", ++m_DirCount));
        // m_Root->Append(parentNode);
        for (int i = 0; i < childCount; ++i)
        {
            auto childNode = std::make_shared<DataModelNode>(parentNode,
                                                             wxString::Format("file-%d", i + 1),
                                                             wxString::Format("%d.%d KB", m_DirCount, i + 1));
            parentNode->Append(childNode);
            // items.Add(childNode);

            wxDataViewItem child{static_cast<void *>(childNode.get())};
            wxDataViewItem parent{static_cast<void *>(parentNode.get())};
            ItemAdded(parent, child);
        }
        // Cleared();
        wxDataViewItem parent{static_cast<void *>(parentNode.get())};
        // ItemAdded(GetRootItem(), parent);
        m_DataItems.Add(parent);
        return parent;
    }

    wxDataViewItem AddNewChildItem(const wxDataViewItem &selectedItem)
    {
        wxDataViewItem returnItem{nullptr};
        if (selectedItem.IsOk())
        {
            auto modelItem = static_cast<DataModelNode *>(selectedItem.GetID());

            // Add directory child to root item
            // if (modelItem == m_Root)
            // {
            //     return AddNewEntry(1);
            // }

            auto now = wxDateTime::Now();
            if (modelItem->GetParent() == nullptr)
            {
                // Add a child to selected root
                auto childItem = std::make_shared<DataModelNode>(std::shared_ptr<DataModelNode>(modelItem),
                                                                 wxString::Format("FILE-%d", m_DirCount),
                                                                 wxString::Format("%d.%d KB", m_DirCount, 1));

                modelItem->Append(childItem);

                wxDataViewItem child{static_cast<void *>(childItem.get())};
                ItemAdded(selectedItem, child);
                returnItem = wxDataViewItem{modelItem};
            }
            else
            {
                // Add a sibling item
                auto parentItem{modelItem->GetParent()};
                auto childItem = std::make_shared<DataModelNode>(parentItem, wxString::Format("File-%d", m_DirCount),
                                                                 wxString::Format("%d.%d KB", m_DirCount, 1));
                parentItem->Append(childItem);
                wxDataViewItem child{static_cast<void *>(childItem.get())};
                wxDataViewItem parent{static_cast<void *>(parentItem.get())};
                ItemAdded(parent, child);
                returnItem = parent;
            }
        }
        // Cleared();
        return returnItem;
    }

    wxString GetFileName(const wxDataViewItem &item) const
    {
        DataModelNode *node = static_cast<DataModelNode *>(item.GetID());
        if (node == nullptr)
            return wxEmptyString;
        return node->m_FileName;
    }

    wxString GetFileSize(const wxDataViewItem &item) const
    {
        DataModelNode *node = static_cast<DataModelNode *>(item.GetID());
        if (node == nullptr)
            return wxEmptyString;
        return node->m_FileSize;
    }

    // Delete Selected item
    void Delete(const wxDataViewItem &item)
    {
        DataModelNode *node = static_cast<DataModelNode *>(item.GetID());
        wxDataViewItem nodeItem{node};

        if (node == nullptr)
            return;

        wxDataViewItem parent{node->GetParent().get()};
        auto parentNode = node->GetParent();

        if (!parent.IsOk())
        {
            // assert(node == m_Root);
            std::cout << "Cannot remove root item!!" << std::endl;
            return;
        }

        if (node->GetParent() == nullptr)
        {
            m_DataItems.Remove(nodeItem);
        }

        node->GetParent()->Remove(std::shared_ptr<DataModelNode>(node));
        delete node;
        ItemDeleted(parent, item);

        // if (parentNode->GetChildCount() == 0 /*&& parentNode != m_Root*/)
        // {
        //     m_Root->GetChildren().Remove(parentNode);
        //     delete parentNode;
        //     wxDataViewItem rootItem{static_cast<void *>(m_Root)};
        //     m_DataItems.Remove(parent);
        //     ItemDeleted(rootItem, parent);
        // }
    }

    void Clear()
    {
        // while (!m_Root->GetChildren().IsEmpty())
        // {
        //     DataModelNode *node = m_Root->GetNthChild(0);
        //     m_Root->GetChildren().Remove(node);
        //     delete node;
        // }
        // m_DataItems.Clear();
        // Cleared();
    }

    int Compare(const wxDataViewItem &item1, const wxDataViewItem &item2,
                unsigned int column, bool ascending) const wxOVERRIDE
    {
        assert(item1.IsOk() && item2.IsOk());

        if (IsContainer(item1) && IsContainer(item2))
        {
            wxVariant value1, value2;
            GetValue(value1, item1, 0);
            GetValue(value2, item2, 0);

            wxString str1 = value1.GetString();
            wxString str2 = value2.GetString();
            int result = str1.Cmp(str2);
            if (result > 0)
            {
                return result;
            }

            wxUIntPtr litem1 = (wxUIntPtr)item1.GetID();
            wxUIntPtr litem2 = (wxUIntPtr)item2.GetID();

            return litem1 - litem2;
        }
        return wxDataViewModel::Compare(item1, item2, column, ascending);
    }

    virtual void GetValue(wxVariant &variant,
                          const wxDataViewItem &item, unsigned int col) const wxOVERRIDE
    {
        assert(item.IsOk());

        DataModelNode *node = static_cast<DataModelNode *>(item.GetID());
        switch (col)
        {
        case 0:
            variant = node->m_FileName;
            break;
        case 1:
            variant = node->m_FileSize;
            break;
        default:
            std::cout << "GetValue: wrong column " << col << std::endl;
        }
    }

    virtual bool SetValue(const wxVariant &variant,
                          const wxDataViewItem &item, unsigned int col) wxOVERRIDE
    {
        assert(item.IsOk());
        DataModelNode *node = static_cast<DataModelNode *>(item.GetID());
        switch (col)
        {
        case 0:
            node->m_FileName = variant.GetString();
            break;
        case 1:
            node->m_FileSize = variant.GetString();
            break;
        default:
            std::cout << "SetValue: wrong column " << col << std::endl;
        }
        return false;
    }

    virtual bool IsEnabled(const wxDataViewItem &item,
                           unsigned int col) const wxOVERRIDE
    {
        assert(item.IsOk());
        DataModelNode *node = static_cast<DataModelNode *>(item.GetID());
        return true;
    }

    virtual wxDataViewItem GetParent(const wxDataViewItem &item) const wxOVERRIDE
    {
        if (!item.IsOk())
            return wxDataViewItem(0);

        DataModelNode *node = static_cast<DataModelNode *>(item.GetID());
        // if (node == m_Root)
        //     return wxDataViewItem(0);
        return wxDataViewItem(static_cast<void *>(node->GetParent().get()));
    }

    virtual bool IsContainer(const wxDataViewItem &item) const wxOVERRIDE
    {
        if (!item.IsOk())
            return true;
        DataModelNode *node = static_cast<DataModelNode *>(item.GetID());
        return node->IsContainer();
    }

    virtual unsigned int GetChildren(const wxDataViewItem &parent,
                                     wxDataViewItemArray &array) const wxOVERRIDE
    {
        DataModelNode *node = static_cast<DataModelNode *>(parent.GetID());

        if (node == nullptr)
        {
            // size_t count = m_Root->GetChildren().GetCount();
            // for (size_t i = 0; i < count; ++i)
            // {
            //     DataModelNode *child = m_Root->GetChildren().Item(i);
            //     array.Add(wxDataViewItem(static_cast<void *>(child)));
            // }
            // return count;
            // return GetChildren(wxDataViewItem(m_Root), array);
            array.Add(wxDataViewItem(static_cast<void *>(m_DataItems[0])));
            return 1;
        }

        if (node->GetChildCount() == 0)
        {
            return 0;
        }

        size_t count = node->GetChildren().size();
        for (size_t i = 0; i < count; ++i)
        {
            auto child = node->GetChildren()[i];
            array.Add(wxDataViewItem(static_cast<void *>(child.get())));
        }
        return count;
    }

private:
    int m_DirCount{};
    // DataModelNode *m_Root{};
    wxDataViewItemArray m_DataItems;
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size)
    {
        m_MainSizer = new wxBoxSizer(wxVERTICAL);
        SetSizer(m_MainSizer);

        SetBackgroundColour(wxColour(*wxWHITE));

        auto *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
        m_AddButton = new wxButton(this, wxID_ANY, "Add", wxDefaultPosition, wxSize(100, 24));
        m_AddToSelectedButton = new wxButton(this, wxID_ANY, "Add To Selected", wxDefaultPosition, wxSize(120, 24));
        m_DeleteButton = new wxButton(this, wxID_ANY, "Delete", wxDefaultPosition, wxSize(100, 24));
        m_ClearButton = new wxButton(this, wxID_ANY, "Clear", wxDefaultPosition, wxSize(100, 24));
        m_ExpandAllButton = new wxButton(this, wxID_ANY, "Expand All", wxDefaultPosition, wxSize(100, 24));
        m_CollapseAllButton = new wxButton(this, wxID_ANY, "Collapse All", wxDefaultPosition, wxSize(100, 24));

        buttonSizer->Add(m_AddButton, 0, wxEXPAND | wxALL, 4);
        buttonSizer->Add(m_AddToSelectedButton, 0, wxEXPAND | wxALL, 4);
        buttonSizer->Add(m_DeleteButton, 0, wxEXPAND | wxALL, 4);
        buttonSizer->Add(m_ClearButton, 0, wxEXPAND | wxALL, 4);
        buttonSizer->Add(m_ExpandAllButton, 0, wxEXPAND | wxALL, 4);
        buttonSizer->Add(m_CollapseAllButton, 0, wxEXPAND | wxALL, 4);

        m_AddButton->Bind(wxEVT_BUTTON, &MyFrame::OnAddNewEntry, this);
        m_AddToSelectedButton->Bind(wxEVT_BUTTON, &MyFrame::OnAddToSelected, this);
        m_DeleteButton->Bind(wxEVT_BUTTON, &MyFrame::OnDeleteSelected, this);
        m_ClearButton->Bind(wxEVT_BUTTON, &MyFrame::OnClearDataModel, this);
        m_ExpandAllButton->Bind(wxEVT_BUTTON, &MyFrame::OnExpandAll, this);
        m_CollapseAllButton->Bind(wxEVT_BUTTON, &MyFrame::OnCollapseAll, this);

        m_DataModel = new DataModel;
        m_DataViewCtrl = new wxDataViewCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
        m_DataViewCtrl->AssociateModel(m_DataModel.get());
        // m_DataViewCtrl->Expand(m_DataModel->GetRootItem());

        m_MainSizer->Add(m_DataViewCtrl, 1, wxEXPAND | wxALL, 5);
        m_MainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5);
        Layout();

        AddColumns();
    }

    void AddColumns()
    {
        wxDataViewTextRenderer *tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
        wxDataViewColumn *column0 =
            new wxDataViewColumn("File Name", tr, 0, FromDIP(150), wxALIGN_LEFT,
                                 wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
        m_DataViewCtrl->AppendColumn(column0);

        tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_EDITABLE);
        wxDataViewColumn *column1 =
            new wxDataViewColumn("File Size", tr, 1, FromDIP(150), wxALIGN_LEFT,
                                 wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE | wxDATAVIEW_COL_RESIZABLE);
        column1->SetMinWidth(FromDIP(120));
        m_DataViewCtrl->AppendColumn(column1);
    }

private:
    void OnClearDataModel(wxCommandEvent &WXUNUSED(event))
    {
        m_DataModel->Clear();
    }

    void OnAddNewEntry(wxCommandEvent &WXUNUSED(event))
    {
        auto item = m_DataModel->AddNewEntry(2);
        // m_DataViewCtrl->Expand(m_DataModel->GetRootItem());
        m_DataViewCtrl->Expand(item);
    }

    void DeleteSelectedItems()
    {
        wxDataViewItemArray items;
        int count = m_DataViewCtrl->GetSelections(items);
        for (int i = 0; i < count; ++i)
        {
            if (items[i].IsOk())
            {
                m_DataModel->Delete(items[i]);
            }
        }
    }

    void OnDeleteSelected(wxCommandEvent &WXUNUSED(event))
    {
        DeleteSelectedItems();
    }

    void OnAddToSelected(wxCommandEvent &event)
    {
        auto item{m_DataViewCtrl->GetSelection()};
        auto newItem = m_DataModel->AddNewChildItem(item);

        m_DataViewCtrl->Expand(newItem);
        // m_DataViewCtrl->Select( newItem );
    }
    void OnCollapseAll(wxCommandEvent &WXUNUSED(event))
    {
        wxDataViewItemArray items = m_DataModel->GetAllItems();
        for (int i = 0; i < items.GetCount(); ++i)
        {
            if (items[i].IsOk())
            {
                m_DataViewCtrl->Collapse(items[i]);
            }
        }
    }

    void OnExpandAll(wxCommandEvent &WXUNUSED(event))
    {
        wxDataViewItemArray items = m_DataModel->GetAllItems();
        for (int i = 0; i < items.GetCount(); ++i)
        {
            if (items[i].IsOk())
            {
                m_DataViewCtrl->Expand(items[i]);
            }
        }
    }

private:
    wxObjectDataPtr<DataModel> m_DataModel;
    wxDataViewCtrl *m_DataViewCtrl;
    wxButton *m_AddButton;
    wxButton *m_AddToSelectedButton;
    wxButton *m_DeleteButton;
    wxButton *m_ClearButton;
    wxButton *m_ExpandAllButton;
    wxButton *m_CollapseAllButton;
    wxBoxSizer *m_MainSizer;
};

class MyApp : public wxApp
{
public:
    bool OnInit() override
    {
        MyFrame *frame = new MyFrame("wxDataViewCtrl-SharedPointer Model", wxDefaultPosition, wxSize(640, 480));
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
