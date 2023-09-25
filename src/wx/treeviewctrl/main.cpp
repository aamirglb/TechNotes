#include "wx/wx.h"
#include <wx/treectrl.h>
#include <wx/timer.h>
#include <wx/dataview.h>
#include "wx/hashmap.h"
#include "wx/vector.h"

#include <iostream>
#include <memory>

///////////////////// Tree Model /////////////////////////////

/*
Implement this data model
            Type               Time                 Location      File Size
--------------------------------------------------------------------------
   MAN00001
                              2023-04-28 13:43:22Z  24.55N 47.46W 50.8 KB
   SAR 003
                              2023-04-28 13:43:22Z  24.55N 47.46W 50.8 KB
                              2023-04-28 13:43:22Z  24.55N 47.46W 50.8 KB
*/

class TreeModelNode;
WX_DEFINE_ARRAY_PTR(TreeModelNode *, TreeModelNodePtrArray);

class TreeModelNode
{
public:
    TreeModelNode(TreeModelNode *parent,
                  const wxString &type, const wxString &time, const wxString &location,
                  const wxString &fileSize)
    {
        m_parent = parent;
        m_TrackType = type;
        m_Time = time;
        m_Location = location;
        m_FileSize = fileSize;
        m_quality = "good";

        m_container = false;
        // images.push_back(wxBitmapBundle::FromImpl(new FixedSizeImpl(wxSize(16, 16), icons[0])));
        // SetImages(images);
    }

    TreeModelNode(TreeModelNode *parent,
                  const wxString &branch)
    {
        m_parent = parent;
        m_TrackType = branch;
        m_container = true;
    }

    ~TreeModelNode()
    {
        // free all our children nodes
        size_t count = m_children.GetCount();
        for (size_t i = 0; i < count; i++)
        {
            TreeModelNode *child = m_children[i];
            delete child;
        }
    }

    bool IsContainer() const
    {
        return m_container;
    }

    TreeModelNode *GetParent()
    {
        return m_parent;
    }
    TreeModelNodePtrArray &GetChildren()
    {
        return m_children;
    }
    TreeModelNode *GetNthChild(unsigned int n)
    {
        return m_children.Item(n);
    }
    void Insert(TreeModelNode *child, unsigned int n)
    {
        m_children.Insert(child, n);
    }
    void Append(TreeModelNode *child)
    {
        m_children.Add(child);
    }
    unsigned int GetChildCount() const
    {
        return m_children.GetCount();
    }

public: // public to avoid getters/setters
    wxString m_TrackType;
    wxString m_Time;
    wxString m_Location;
    wxString m_FileSize;
    wxString m_quality;

    // TODO/FIXME:
    // the GTK version of wxDVC (in particular wxDataViewCtrlInternal::ItemAdded)
    // needs to know in advance if a node is or _will be_ a container.
    // Thus implementing:
    //   bool IsContainer() const
    //    { return m_children.GetCount()>0; }
    // doesn't work with wxGTK when MyMusicTreeModel::AddToClassical is called
    // AND the classical node was removed (a new node temporary without children
    // would be added to the control)
    bool m_container;

private:
    wxVector<wxBitmapBundle> images;
    wxIcon icons[1];
    TreeModelNode *m_parent;
    TreeModelNodePtrArray m_children;
};

class TreeModel : public wxDataViewModel
{
public:
    TreeModel();
    ~TreeModel()
    {
        delete m_root;
    }

    // helper method for wxLog

    wxString GetTrackType(const wxDataViewItem &item) const;
    wxString GetTime(const wxDataViewItem &item) const;
    wxString GetLocation(const wxDataViewItem &item) const;
    wxString GetFileSize(const wxDataViewItem &item) const;

    // helper methods to change the model

    // void AddToClassical(const wxString &title, const wxString &artist,
    //                     unsigned int year);
    void Delete(const wxDataViewItem &item);
    void Clear();

    // wxDataViewItem GetNinthItem() const
    // {
    //     return wxDataViewItem(m_ninth);
    // }

    // override sorting to always sort branches ascendingly

    int Compare(const wxDataViewItem &item1, const wxDataViewItem &item2,
                unsigned int column, bool ascending) const wxOVERRIDE;

    // implementation of base class virtuals to define model

    virtual void GetValue(wxVariant &variant,
                          const wxDataViewItem &item, unsigned int col) const wxOVERRIDE;
    virtual bool SetValue(const wxVariant &variant,
                          const wxDataViewItem &item, unsigned int col) wxOVERRIDE;

    virtual bool IsEnabled(const wxDataViewItem &item,
                           unsigned int col) const wxOVERRIDE;

    virtual wxDataViewItem GetParent(const wxDataViewItem &item) const wxOVERRIDE;
    virtual bool IsContainer(const wxDataViewItem &item) const wxOVERRIDE;
    virtual unsigned int GetChildren(const wxDataViewItem &parent,
                                     wxDataViewItemArray &array) const wxOVERRIDE;

private:
    TreeModelNode *m_root;
    // TreeModel *m_root2;
    // TreeModel *m_tracks;

    // pointers to some "special" nodes of the tree:
    TreeModelNode *m_pop;
    TreeModelNode *m_classical;
    TreeModelNode *m_ninth;

    // ??
    bool m_classicalMusicIsKnownToControl;
    std::vector<TreeModelNode *> m_TrackNodes;
};

TreeModel::TreeModel()
{
    m_root = new TreeModelNode(NULL, "");
    // auto *m_root2 = new TreeModelNode(NULL, "ROOT2");

    m_TrackNodes.emplace_back(new TreeModelNode(nullptr, "MAN00001"));
    m_root->Append(m_TrackNodes.back());

    m_TrackNodes[0]->Append(new TreeModelNode(m_TrackNodes[0], "MAN", "10:34:44.55Z", "43.88N, 47.34W", "55.4 KB"));

    m_TrackNodes.emplace_back(new TreeModelNode(nullptr, "ASI00001"));
    m_root->Append(m_TrackNodes.back());
    m_TrackNodes[1]->Append(new TreeModelNode(m_TrackNodes[1], "ASI", "13:40:00.10Z", "43.87N, 47.31W", "65.4 KB"));
    m_TrackNodes[1]->Append(new TreeModelNode(m_TrackNodes[1], "ASI", "00:00:10.55Z", "43.87N, 47.31W", "65.4 KB"));

    // auto *m_pop = new TreeModelNode(m_root, "MAN00001");
    // m_root->Append(m_pop);

    // m_pop->Append(
    //     new TreeModelNode(m_pop, "MAN00001"));
    // m_pop->Append(
    //     new TreeModelNode(m_pop, "SAR 01"));
    // m_pop->Append(
    //     new TreeModelNode(m_pop, "MAN00002"));
    // m_root->Append(m_pop);

    // // setup classical music
    // m_classical = new TreeModelNode( m_root, "Classical music" );
    // m_ninth = new TreeModelNode( m_classical, "Ninth symphony",
    //                                     "Ludwig van Beethoven", 1824 );
    // m_classical->Append( m_ninth );
    // m_classical->Append( new TreeModelNode( m_classical, "German Requiem",
    //                                                "Johannes Brahms", 1868 ) );
    // m_root->Append( m_classical );

    // m_classicalMusicIsKnownToControl = false;
}
wxString TreeModel::GetTrackType(const wxDataViewItem &item) const
{
    TreeModelNode *node = (TreeModelNode *)item.GetID();
    if (!node) // happens if item.IsOk()==false
        return wxEmptyString;

    return node->m_TrackType;
}

wxString TreeModel::GetTime(const wxDataViewItem &item) const
{
    TreeModelNode *node = (TreeModelNode *)item.GetID();
    if (!node) // happens if item.IsOk()==false
        return wxEmptyString;

    return node->m_Time;
}

wxString TreeModel::GetLocation(const wxDataViewItem &item) const
{
    TreeModelNode *node = (TreeModelNode *)item.GetID();
    if (!node) // happens if item.IsOk()==false
        return wxEmptyString;

    return node->m_Location;
}

wxString TreeModel::GetFileSize(const wxDataViewItem &item) const
{
    TreeModelNode *node = (TreeModelNode *)item.GetID();
    if (!node) // happens if item.IsOk()==false
        return wxEmptyString;

    return node->m_FileSize;
}

void TreeModel::Delete(const wxDataViewItem &item)
{
    TreeModelNode *node = (TreeModelNode *)item.GetID();
    if (!node) // happens if item.IsOk()==false
        return;

    wxDataViewItem parent(node->GetParent());
    if (!parent.IsOk())
    {
        wxASSERT(node == m_root);

        // don't make the control completely empty:
        wxLogError("Cannot remove the root item!");
        return;
    }

    // is the node one of those we keep stored in special pointers?
    if (node == m_pop)
        m_pop = NULL;
    else if (node == m_classical)
        m_classical = NULL;
    else if (node == m_ninth)
        m_ninth = NULL;

    // first remove the node from the parent's array of children;
    // NOTE: MyMusicTreeModelNodePtrArray is only an array of _pointers_
    //       thus removing the node from it doesn't result in freeing it
    node->GetParent()->GetChildren().Remove(node);

    // free the node
    delete node;

    // notify control
    ItemDeleted(parent, item);
}

void TreeModel::Clear()
{
    m_pop = NULL;
    m_classical = NULL;
    m_ninth = NULL;

    while (!m_root->GetChildren().IsEmpty())
    {
        TreeModelNode *node = m_root->GetNthChild(0);
        m_root->GetChildren().Remove(node);
        delete node;
    }

    Cleared();
}

int TreeModel::Compare(const wxDataViewItem &item1, const wxDataViewItem &item2,
                       unsigned int column, bool ascending) const
{
    wxASSERT(item1.IsOk() && item2.IsOk());
    // should never happen

    if (IsContainer(item1) && IsContainer(item2))
    {
        wxVariant value1, value2;
        GetValue(value1, item1, 0);
        GetValue(value2, item2, 0);

        wxString str1 = value1.GetString();
        wxString str2 = value2.GetString();
        int res = str1.Cmp(str2);
        if (res)
            return res;

        // items must be different
        wxUIntPtr litem1 = (wxUIntPtr)item1.GetID();
        wxUIntPtr litem2 = (wxUIntPtr)item2.GetID();

        return litem1 - litem2;
    }

    return wxDataViewModel::Compare(item1, item2, column, ascending);
}

void TreeModel::GetValue(wxVariant &variant,
                         const wxDataViewItem &item, unsigned int col) const
{
    wxASSERT(item.IsOk());

    TreeModelNode *node = (TreeModelNode *)item.GetID();
    switch (col)
    {
    case 0:
        variant = node->m_TrackType;
        break;
    case 1:
        variant = node->m_Time;
        break;
    case 2:
        variant = node->m_Location;
        // if (node->m_year != -1)
        //     variant = (long)node->m_year;
        break;
    case 3:
        variant = node->m_FileSize;
        break;
    default:
        wxLogError("MyMusicTreeModel::GetValue: wrong column %d", col);
    }
}

bool TreeModel::SetValue(const wxVariant &variant,
                         const wxDataViewItem &item, unsigned int col)
{
    wxASSERT(item.IsOk());

    TreeModelNode *node = (TreeModelNode *)item.GetID();
    switch (col)
    {
    case 0:
        node->m_TrackType = variant.GetString();
        return true;
    case 1:
        node->m_Time = variant.GetString();
        return true;
    case 2:
        node->m_Location = variant.GetString();
        return true;
    case 3:
        node->m_FileSize = variant.GetString();
        return true;

    default:
        wxLogError("MyMusicTreeModel::SetValue: wrong column");
    }
    return false;
}

bool TreeModel::IsEnabled(const wxDataViewItem &item,
                          unsigned int col) const
{
    wxASSERT(item.IsOk());

    TreeModelNode *node = (TreeModelNode *)item.GetID();

    // // disable Beethoven's ratings, his pieces can only be good
    // if (col == 3 && node->m_artist.EndsWith("Beethoven"))
    //     return false;

    // // also disable editing the year when it's not specified, this doesn't work
    // // because the editor needs some initial value
    // if (col == 2 && node->m_year == -1)
    //     return false;

    // otherwise allow editing
    return true;
}

wxDataViewItem TreeModel::GetParent(const wxDataViewItem &item) const
{
    // the invisible root node has no parent
    if (!item.IsOk())
        return wxDataViewItem(0);

    TreeModelNode *node = (TreeModelNode *)item.GetID();

    // "MyMusic" also has no parent
    if (node == m_root)
        return wxDataViewItem(0);

    return wxDataViewItem((void *)node->GetParent());
}

bool TreeModel::IsContainer(const wxDataViewItem &item) const
{
    // the invisible root node can have children
    // (in our model always "MyMusic")
    if (!item.IsOk())
        return true;

    TreeModelNode *node = (TreeModelNode *)item.GetID();
    return node->IsContainer();
}

unsigned int TreeModel::GetChildren(const wxDataViewItem &parent,
                                    wxDataViewItemArray &array) const
{
    TreeModelNode *node = (TreeModelNode *)parent.GetID();
    if (!node)
    {
        return GetChildren(wxDataViewItem(m_root), array);
        // array.Add(wxDataViewItem((void *)m_root));
        return 1;
    }

    if (node == m_classical)
    {
        TreeModel *model = const_cast<TreeModel *>(this);
        model->m_classicalMusicIsKnownToControl = true;
    }

    if (node->GetChildCount() == 0)
    {
        return 0;
    }

    unsigned int count = node->GetChildren().GetCount();
    for (unsigned int pos = 0; pos < count; pos++)
    {
        TreeModelNode *child = node->GetChildren().Item(pos);
        array.Add(wxDataViewItem((void *)child));
    }

    return count;
}

//////////////////////////////////////////////////
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
    wxObjectDataPtr<TreeModel> m_music_model;
    wxDataViewCtrl *m_ctrl[1];
    wxDataViewTreeCtrl *m_TreeCtrl;

    wxButton *b1;
    wxButton *b2;
    wxBoxSizer *m_main_sizer;
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("wxTreeCtrl Example", wxDefaultPosition, wxDefaultSize);
    frame->Show();
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    m_main_sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_main_sizer);
    this->SetBackgroundColour(wxColour(*wxWHITE));
    auto *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    b1 = new wxButton(this, wxID_ANY, "OK", wxDefaultPosition, wxSize(100, 24));
    b2 = new wxButton(this, wxID_ANY, "Cancel", wxDefaultPosition, wxSize(100, 24));
    buttonSizer->Add(b1, 0, wxEXPAND | wxALL, 4);
    buttonSizer->Add(b2, 0, wxEXPAND | wxALL, 4);

    m_music_model = new TreeModel();
    m_TreeCtrl = new wxDataViewTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    m_TreeCtrl->AppendTextColumn("Track Type", 0);
    m_TreeCtrl->AppendTextColumn("Time", 1);
    m_TreeCtrl->AppendTextColumn("Position", 2);
    m_TreeCtrl->AppendTextColumn("File Size", 3);

    // m_TreeCtrl->AssociateModel(m_music_model.get());

    // m_ctrl[0] =
    //     new wxDataViewCtrl(this, wxID_ANY, wxDefaultPosition,
    //                        wxDefaultSize, wxDV_HORIZ_RULES);
    // m_ctrl[0]->AssociateModel(m_music_model.get());

    // m_main_sizer->Add(m_ctrl[0], 1, wxEXPAND | wxALL, 5);
    m_main_sizer->Add(m_TreeCtrl, 1, wxEXPAND | wxALL, 4);
    m_main_sizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 1);
    Layout();

    /////////////////
    // m_ctrl[0]->AppendBitmapColumn("Image", 1, wxDATAVIEW_CELL_INERT, -1,
    //                               wxALIGN_CENTER, wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_REORDERABLE);

    // Create the bitmap.
    // wxImage *image = new wxImage(icon3_xpm); // IsOk() returns true
    // wxBitmap *bitmap = new wxBitmap(*image); // IsOk() returns true

    // // Add an item.
    // wxVector<wxVariant> images;
    // images.push_back("Apples");
    // images.push_back(wxVariant(*bitmap));
    // m_ctrl[0]->AppendItem(images);
    //////////////////

    // m_ctrl[0]->AppendIconTextColumn("Track", 0, wxDATAVIEW_CELL_INERT, FromDIP(120));
    // m_ctrl[0]->AppendIconTextColumn(_("Date"), DATE, wxDATAVIEW_CELL_INERT, DEFAULT_SIZE, wxALIGN_NOT, wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
    // wxDataViewTextRenderer *tr =
    //     new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    // wxDataViewColumn *column0 =
    //     new wxDataViewColumn("Track", tr, 0, FromDIP(100), wxALIGN_LEFT,
    //                          wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_RESIZABLE);
    // m_ctrl[0]->AppendColumn(column0);

    // m_ctrl[0]->AppendBitmapColumn("Track", 1, wxDATAVIEW_CELL_INERT, -1,
    //                               wxALIGN_CENTER, wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_REORDERABLE);

    // tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_EDITABLE);
    // wxDataViewColumn *column1 =
    //     new wxDataViewColumn("Time", tr, 1, FromDIP(100), wxALIGN_LEFT,
    //                          wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
    //                              wxDATAVIEW_COL_RESIZABLE);
    // column1->SetMinWidth(FromDIP(150)); // this column can't be resized to be smaller
    // m_ctrl[0]->AppendColumn(column1);

    // tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_EDITABLE);
    // wxDataViewColumn *column2 =
    //     new wxDataViewColumn("Location", tr, 2, FromDIP(100), wxALIGN_LEFT,
    //                          wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
    //                              wxDATAVIEW_COL_RESIZABLE);
    // column1->SetMinWidth(FromDIP(150)); // this column can't be resized to be smaller
    // m_ctrl[0]->AppendColumn(column2);

    // tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_EDITABLE);
    // wxDataViewColumn *column3 =
    //     new wxDataViewColumn("File Size", tr, 3, FromDIP(100), wxALIGN_LEFT,
    //                          wxDATAVIEW_COL_SORTABLE | wxDATAVIEW_COL_REORDERABLE |
    //                              wxDATAVIEW_COL_RESIZABLE);
    // column1->SetMinWidth(FromDIP(150)); // this column can't be resized to be smaller
    // m_ctrl[0]->AppendColumn(column3);

    // m_Tree = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
    //                         wxTR_DEFAULT_STYLE | wxTR_HIDE_ROOT | wxTR_NO_LINES);

    // wxTreeItemId rootId = m_Tree->AddRoot("Root");
    // wxTreeItemId id = m_Tree->AppendItem(rootId, "First");
    // m_Tree->AppendItem(id, "1.1");
    // m_Tree->AppendItem(id, "1.2");
    // m_Tree->AppendItem(id, "1.3");

    // wxTreeItemId id2 = m_Tree->AppendItem(rootId, "Second");
    // m_Tree->AppendItem(id2, "2.1");
    // m_Tree->AppendItem(id2, "2.2");
    // m_Tree->AppendItem(id2, "2.3");
}
