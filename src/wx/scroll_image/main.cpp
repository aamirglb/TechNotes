#include <wx/wx.h>
#include <wx/scrolwin.h>

class MyFrame : public wxFrame
{
public:
    MyFrame()
        : wxFrame(NULL, wxID_ANY, _("Scrolling controls"), wxDefaultPosition, wxSize(500, 300))
    {
        wxScrolledWindow* sw = new wxScrolledWindow(this);                

        // Add a vertical box sizer with a bunch of buttons
        const size_t vSizerRows = 6;
        wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);
        
        for ( size_t i = 0; i < vSizerRows; i++ )
            vSizer->Add(new wxButton(sw, wxID_ANY, wxString::Format("Button %zu", i)));
                    
        // add a grid sizer with a bunch of static texts and edit controls
        const size_t gSizerRows = 15;
        const size_t gSizerCols = 6;
        wxGridSizer* gSizer = new wxGridSizer(gSizerRows, gSizerCols, 5, 5);

        for ( size_t i = 0; i < gSizerRows; i++ )
        {
            for ( size_t i1 = 0; i1 < gSizerCols; i1 += 2 )
            {
                gSizer->Add(new wxStaticText(sw, wxID_ANY, wxString::Format("Label  (gs row %zu, col %zu)", i, i1)));
                gSizer->Add(new wxTextCtrl(sw, wxID_ANY, wxString::Format("TextCtrl (gs row %zu, col %zu)", i, i1+1)));
            }
        }

        // create a sizer for wxScrolledWindow
        wxBoxSizer* swSizer = new wxBoxSizer(wxVERTICAL);
                
        swSizer->Add(vSizer);
        swSizer->Add(gSizer);
        
        sw->SetSizer(swSizer);
        sw->SetScrollRate(5, 5);        
    }	
};

class MyApp : public wxApp
{
public:     
    virtual bool OnInit()
    {        
        (new MyFrame())->Show();
        return true;
    }
};
wxIMPLEMENT_APP(MyApp);

// #include "wx/wx.h"
// #include <iostream>

// class ScrolledImageComponent : public wxScrolledWindow
// {
//     wxBitmap *bitmap;
//     int w, h;

// public:
//     ScrolledImageComponent(wxWindow *parent, wxWindowID id, wxString image_path) : wxScrolledWindow(parent, id)
//     {
//         wxImage image(image_path);
//         if (!image.IsOk())
//         {
//             wxMessageBox(wxT("there was an error loading the image"));
//             return;
//         }

//         w = image.GetWidth();
//         h = image.GetHeight();

//         /* init scrolled area size, scrolling speed, etc. */
//         SetScrollbars(1, 1, w, h, 0, 0);

//         bitmap = new wxBitmap(image);
//     }
//     ~ScrolledImageComponent()
//     {
//         delete bitmap;
//     }
//     void OnDraw(wxDC &dc)
//     {
//         /* render the image - in a real app, if your scrolled area
//            is somewhat big, you will want to draw only visible parts,
//            not everything like below */
//         dc.DrawBitmap(*bitmap, 0, 0, false);

//         // also check wxScrolledWindow::PrepareDC
//     }
// };

// class MyApp : public wxApp
// {
//     wxFrame *frame;

// public:
//     bool OnInit()
//     {
//         wxInitAllImageHandlers();
//         wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
//         frame = new wxFrame((wxFrame *)NULL, -1, wxT("Scrolling an Image"), wxPoint(50, 50), wxSize(650, 650));

//         ScrolledImageComponent *my_image = new ScrolledImageComponent(frame, wxID_ANY, wxT("C:/Users/aamir.ali/Pictures/demo-lib/DSLR-0002.jpg"));
//         sizer->Add(my_image, 1, wxALL | wxEXPAND, 120);
//         frame->SetSizer(sizer);

//         frame->Show();
//         return true;
//     }
// };

// IMPLEMENT_APP(MyApp)