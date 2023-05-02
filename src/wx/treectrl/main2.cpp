#include "wx/wx.h"
#include "wx/dataview.h"

//////////////// Custom Renderer  //////////////////////////////////
class MyCustomRenderer : public wxDataViewCustomRenderer
{
public:
    // This renderer can be either activatable or editable, for demonstration
    // purposes. In real programs, you should select whether the user should be
    // able to activate or edit the cell and it doesn't make sense to switch
    // between the two -- but this is just an example, so it doesn't stop us.
    explicit MyCustomRenderer(wxDataViewCellMode mode)
        : wxDataViewCustomRenderer("string", mode, wxALIGN_CENTER)
    {
    }

    virtual bool Render(wxRect rect, wxDC *dc, int state) wxOVERRIDE
    {
        dc->SetBrush(*wxLIGHT_GREY_BRUSH);
        dc->SetPen(*wxTRANSPARENT_PEN);

        // rect.Deflate(2);
        // rect.Inflate(4, 0);
        // dc->DrawRoundedRectangle(rect, 5);

        RenderText(m_value,
                   0, // no offset
                   wxRect(dc->GetTextExtent(m_value)).CentreIn(rect),
                   dc,
                   state);
        return true;
    }

    virtual bool ActivateCell(const wxRect &WXUNUSED(cell),
                              wxDataViewModel *WXUNUSED(model),
                              const wxDataViewItem &WXUNUSED(item),
                              unsigned int WXUNUSED(col),
                              const wxMouseEvent *mouseEvent) wxOVERRIDE
    {
        wxString position;
        if (mouseEvent)
            position = wxString::Format("via mouse at %d, %d", mouseEvent->m_x, mouseEvent->m_y);
        else
            position = "from keyboard";
        // wxLogMessage("MyCustomRenderer ActivateCell() %s", position);
        std::cout << "MyCustomRenderer activateCell() " << position.ToStdString() << std::endl;
        return false;
    }

    virtual wxSize GetSize() const wxOVERRIDE
    {
        return GetView()->FromDIP(wxSize(60, 20));
    }

    virtual bool SetValue(const wxVariant &value) wxOVERRIDE
    {
        m_value = value.GetString();
        return true;
    }

    virtual bool GetValue(wxVariant &WXUNUSED(value)) const wxOVERRIDE { return true; }

#if wxUSE_ACCESSIBILITY
    virtual wxString GetAccessibleDescription() const wxOVERRIDE
    {
        return m_value;
    }
#endif // wxUSE_ACCESSIBILITY

    virtual bool HasEditorCtrl() const wxOVERRIDE
    {
        return true;
    }

    virtual wxWindow *
    CreateEditorCtrl(wxWindow *parent,
                     wxRect labelRect,
                     const wxVariant &value) wxOVERRIDE
    {
        wxTextCtrl *text = new wxTextCtrl(parent, wxID_ANY, value,
                                          labelRect.GetPosition(),
                                          labelRect.GetSize(),
                                          wxTE_PROCESS_ENTER);
        text->SetInsertionPointEnd();

        return text;
    }

    virtual bool
    GetValueFromEditorCtrl(wxWindow *ctrl, wxVariant &value) wxOVERRIDE
    {
        wxTextCtrl *text = wxDynamicCast(ctrl, wxTextCtrl);
        if (!text)
            return false;

        value = text->GetValue();

        return true;
    }

private:
    wxString m_value;
};

/////////
// Implement a simple model with 2 columns
// FileName FileSize
/////////

class DataModelNode;
WX_DEFINE_ARRAY_PTR(DataModelNode *, DataModelNodePtrArray);

class DataModelNode
{
public:
    DataModelNode(
        DataModelNode *parent,
        const wxString &name,
        const wxString &size) : m_Parent{parent},
                                m_FileName{name},
                                m_FileSize{size},
                                m_IsContainer{false}
    {
    }

    DataModelNode(
        DataModelNode *parent,
        const wxString &branch)
        : m_Parent{parent},
          m_FileName{branch},
          m_IsContainer{true}
    {
    }

    ~DataModelNode()
    {
        size_t count = m_Children.GetCount();
        for (size_t i = 0; i < count; ++i)
        {
            DataModelNode *child = m_Children[i];
            delete child;
        }
    }

    bool IsContainer() const { return m_IsContainer; }
    DataModelNode *GetParent() { return m_Parent; }
    DataModelNodePtrArray &GetChildren() { return m_Children; }
    DataModelNode *GetNthChild(size_t n) { return m_Children.Item(n); }
    void Insert(DataModelNode *child, size_t n) { m_Children.Insert(child, n); }
    void Append(DataModelNode *child) { m_Children.Add(child); }
    size_t GetChildCount() const { return m_Children.GetCount(); }

public:
    wxString m_FileName;
    wxString m_FileSize;
    bool m_IsContainer;

private:
    DataModelNode *m_Parent;
    DataModelNodePtrArray m_Children;
};

class DataModel : public wxDataViewModel
{
public:
    DataModel()
    {
        m_Root = new DataModelNode(nullptr, "");

        // Add child nodes
        AddNewEntry();
    }

    ~DataModel() { delete m_Root; }

    wxDataViewItem GetRootItem() const
    {
        wxDataViewItem rootItem{static_cast<void *>(m_Root)};
        return rootItem;
    }

    const wxDataViewItemArray &GetAllItems() const
    {
        return m_DataItems;
    }

    wxDataViewItem AddNewEntry(int childCount = 3)
    {
        wxDataViewItemArray items;
        auto *parentNode = new DataModelNode(m_Root, wxString::Format("Directory-%d", ++m_DirCount));
        m_Root->Append(parentNode);
        for (int i = 0; i < childCount; ++i)
        {
            auto *childNode = new DataModelNode(parentNode,
                                                wxString::Format("File-%d", i + 1),
                                                wxString::Format("%d.%d", m_DirCount, i + 1));
            parentNode->Append(childNode);
            // items.Add(childNode);

            wxDataViewItem child{static_cast<void *>(childNode)};
            wxDataViewItem parent{static_cast<void *>(parentNode)};
        }
        Cleared();
        wxDataViewItem parent{static_cast<void *>(parentNode)};
        m_DataItems.Add(parent);
        return parent;
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
        if (node == nullptr)
            return;

        wxDataViewItem parent{node->GetParent()};
        DataModelNode *parentNode = node->GetParent();

        if (!parent.IsOk())
        {
            assert(node == m_Root);
            std::cout << "Cannot remove root item!!" << std::endl;
            return;
        }

        node->GetParent()->GetChildren().Remove(node);
        delete node;
        ItemDeleted(parent, item);

        if (parentNode->GetChildCount() == 0 && parentNode != m_Root)
        {
            m_Root->GetChildren().Remove(parentNode);
            delete parentNode;
            wxDataViewItem rootItem{static_cast<void *>(m_Root)};
            m_DataItems.Remove(parent);
            ItemDeleted(rootItem, parent);
        }
    }

    void Clear()
    {
        while (!m_Root->GetChildren().IsEmpty())
        {
            DataModelNode *node = m_Root->GetNthChild(0);
            m_Root->GetChildren().Remove(node);
            delete node;
        }
        m_DataItems.Clear();
        Cleared();
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
        if (node == m_Root)
            return wxDataViewItem(0);
        return wxDataViewItem(static_cast<void *>(node->GetParent()));
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
            // return GetChildren(wxDataViewItem(m_Root), array);
            array.Add(wxDataViewItem((void *)m_Root));
            return 1;
        }

        if (node->GetChildCount() == 0)
        {
            return 0;
        }

        size_t count = node->GetChildren().GetCount();
        for (size_t i = 0; i < count; ++i)
        {
            DataModelNode *child = node->GetChildren().Item(i);
            array.Add(wxDataViewItem(static_cast<void *>(child)));
        }

        return count;
    }

private:
    int m_DirCount{};
    DataModelNode *m_Root{};
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
        m_DeleteButton = new wxButton(this, wxID_ANY, "Delete", wxDefaultPosition, wxSize(100, 24));
        m_ClearButton = new wxButton(this, wxID_ANY, "Clear", wxDefaultPosition, wxSize(100, 24));
        m_ExpandAllButton = new wxButton(this, wxID_ANY, "Expand All", wxDefaultPosition, wxSize(100, 24));
        m_CollapseAllButton = new wxButton(this, wxID_ANY, "Collapse All", wxDefaultPosition, wxSize(100, 24));

        buttonSizer->Add(m_AddButton, 0, wxEXPAND | wxALL, 4);
        buttonSizer->Add(m_DeleteButton, 0, wxEXPAND | wxALL, 4);
        buttonSizer->Add(m_ClearButton, 0, wxEXPAND | wxALL, 4);
        buttonSizer->Add(m_ExpandAllButton, 0, wxEXPAND | wxALL, 4);
        buttonSizer->Add(m_CollapseAllButton, 0, wxEXPAND | wxALL, 4);

        m_AddButton->Bind(wxEVT_BUTTON, &MyFrame::OnAddNewEntry, this);
        m_DeleteButton->Bind(wxEVT_BUTTON, &MyFrame::OnDeleteSelected, this);
        m_ClearButton->Bind(wxEVT_BUTTON, &MyFrame::OnClearDataModel, this);
        m_ExpandAllButton->Bind(wxEVT_BUTTON, &MyFrame::OnExpandAll, this);
        m_CollapseAllButton->Bind(wxEVT_BUTTON, &MyFrame::OnCollapseAll, this);

        m_DataModel = new DataModel;
        m_DataViewCtrl = new wxDataViewCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
        m_DataViewCtrl->AssociateModel(m_DataModel.get());
        m_DataViewCtrl->Expand(m_DataModel->GetRootItem());

        m_MainSizer->Add(m_DataViewCtrl, 1, wxEXPAND | wxALL, 5);
        m_MainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 5);
        Layout();

        AddColumns();
    }

    void AddColumns()
    {
        MyCustomRenderer *cr = new MyCustomRenderer(wxDATAVIEW_CELL_ACTIVATABLE);
        // wxDataViewTextRenderer *tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
        wxDataViewColumn *column0 =
            new wxDataViewColumn("File Name", cr, 0, FromDIP(150), wxALIGN_LEFT,
                                 wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
        m_DataViewCtrl->AppendColumn(column0);

        wxDataViewTextRenderer *tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_EDITABLE);
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
        m_DataViewCtrl->Expand(m_DataModel->GetRootItem());
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
        MyFrame *frame = new MyFrame("wxDataViewCtrl Test", wxDefaultPosition, wxSize(640, 480));
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
