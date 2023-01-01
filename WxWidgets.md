# WxWidget

* `wxWidgets` has bindings for a variety of other languages such as **Python**, **Perl**, a **BASIC** variant, **Lua**, **Eiffel**, **JavaScript**, **Java**, **Ruby**, **Haskell**, and **C#**. Some of these bindings are more advanced than others.

* http://www.wxwidgets.org

```
 taskkill /F /IM wx_hello.exe
```

* We need the GTK development libraries which wxWidgets depend on.

```shell
$ sudo apt-get install libgtk-3-dev build-essential checkinstall
```

* The utility called `checkinstall` would allow us to create an installation package for wxwidgets, so that later on it can un-installed easily using package managers.

* **DialogBlocks** is a sizer-based resource editor that quickly gets you creating professional-looking dialogs, wizards and frames for deployment on Windows, Linux, Mac or any other supported wxWidgets platform.

* wxWidgets is a programmer’s toolkit for writing desktop or mobile applications with graphical user interfaces (GUIs). It’s a _framework_, in the sense that it does a lot of the housekeeping work and provides default application behavior.

* wxWidgets provides classes for
    * files and streams,
    * multiple threads,
    * application settings,
    * interprocess communication,
    * online help,
    * database access, and much more.

* wxWidgets provides a native look and feel. wxWidgets uses the native widgets wherever possible (and its own widget set in other cases) so that not only does the application look native on the major platforms, but it actually is native.

* Initially, wxWidgets targeted XView and MFC 1.0; Borland C++ users complained about the requirement for MFC, so it was rewritten to use pure Win32.
Because XView was giving way to Motif, a Motif port quickly followed.

* Wolfram Gloger suggested that wxWidgets should be ported to GTK+, the up-and-coming widget set being adopted for the GNOME desktop environment.

* Robert Roebling became the lead developer for wxGTK, which is now the main Unix/Linux port of wxWidgets.

* wxUniversal, wxWidgets’s own set of widgets for use on platforms A Brief History of wxWidgets 5 that have no widget set of their own. wxUniversal was first used in SciTech’s port to MGL, their low-level graphics layer.

* In 2002, Julian Smart and Robert Roebling added the wxX11 port using the wxUniversal widgets. Requiring only Unix and X11, wxX11 is suitable for
any Unix environment and can be used in fairly low-spec systems.

* The object-oriented language Smalltalk designed by Alan Kay and others in the 1970s was an important milestone in GUI history, making innovations in user interface technology as well as language design, and although wxWidgets uses a different language and API, the principles employed are broadly the same.

![](images/wx/wx_port.png)

* wxWidgets code base is divided into 6 layers
    1. Common code
    1. Generic code
    1. wxUniversal
    1. Platform-specific code
    1. Contributed code
    1. Third-party code

* Every wxWidgets application defines an application class deriving from `wxApp`.

```cpp
// Declare the application class
class MyApp : public wxApp
{
public:
    // Called on application startup
    virtual bool OnInit();
};
```

* The implementation of OnInit usually creates at least one window, interprets any command-line arguments, sets up data for the application, and performs any other initialization tasks required for the application.

* `wxT()` macro converts string and character literals to the appropriate type to allow the
application to be compiled in Unicode mode.

```cpp
// Give wxWidgets the means to create a MyApp object
IMPLEMENT_APP(MyApp)
```

* When wxWidgets creates a `MyApp` object, it assigns the result to the global variable `wxTheApp`. You can use this in your application, but it would be more convenient if you didn't have to cast the `wxApp` pointer to `MyApp`.

```cpp
// Implements MyApp& wxGetApp()
DECLARE_APP(MyApp)
```

* A frame is a top-level window that contains other windows, and usually has a title bar and menu bar.

```cpp
// Declare our main frame class
class MyFrame : public wxFrame
{
public:
    // Constructor
    MyFrame(const wxString& title);
    // Event handlers
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
private:
    // This class handles events
    DECLARE_EVENT_TABLE()
};
```

* Small bitmaps and icons can be implemented using the `XPM` format on all platforms. XPM files have valid C++ syntax and so can be included as `SetIcon(wxIcon(modrian_xpm));`

* Most GUI applications are not multithreaded so each task is being done in turn.

* wxWidgets uses _event tables_ to expose event handling to the application.

* Every class that derives from `wxEvtHandler`, including `frames`, `buttons`, `menus`, and even `documents`, can contain an event table to tell wxWidgets how events are routed to handler functions.

* All window classes (derived from `wxWindow`), and the application class, are derived from `wxEvtHandler`.

* All event handler functions have the same form—their return type is void, they are not virtual, and they take a single event object argument.

* A list of system events that will not get sent to the parent’s event handler:
    * `wxActivateEvent`,
    * `wxCloseEvent`,
    * `wxEraseEvent`,
    * `wxFocusEvent`,
    * `wxKeyEvent`,
    * `wxIdleEvent`,
    * `wxInitDialogEvent`,
    * `wxJoystickEvent`,
    * `wxMenuEvent`,
    * `wxMouseEvent`,
    * `wxMoveEvent`,
    * `wxPaintEvent`,
    * `wxQueryLayoutInfoEvent`,
    * `wxSizeEvent`,
    * `wxScrollWinEvent`, and
    * `wxSysColourChangedEvent`

* Call `wxEvent::Skip` to indicate that the search for the event handler should continue. Pass the events to the original event handler using `wxEvent::Skip`.

* top-level windows (`wxFrame`, `wxDialog`, `wxPopup`)

* When a window needs to be painted, it receives two events, `wxEVT_ERASE_BACKGROUND` to paint the background, and `wxEVT_PAINT` to paint the foreground.

* When a window is resized, either by the application or by the user, it receives a `wxEVT_SIZE` event.

* Most stock windows have a notion of a default size and position if you pass them `wxDefaultSize` or `wxDefaultPosition` (or -1 as an individual size or position value).

* Each control implements `DoGetBestSize`, which returns a reasonable default size based on the control content, current font, and other factors.

* The `wxEVT_SET_FOCUS` event is sent to a window that is receiving the focus; `wxEVT_KILL_FOCUS` is sent when the focus is moving to a different window.

* All windows are (unless otherwise specified) recipients of _idle_ events (`wxEVT_IDLE`), which are sent when all other events have been processed, specified
with the `EVT_IDLE(func)` macro.

* `wxCAPTION | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxTHICK_FRAME`

### Window Classes

|  Class      |   Description |
|-------------|---------------|
| **Base Window Classes** ||
| `wxWindow`           | The base class for all windows. |
| `wxControl`          | The base class for controls, such as wxButton |
| `wxControlWithItems` | The base class for multi-item controls. |
| **Top-Level Windows** ||
| `wxFrame`            | A resizable window containing other windows. |
| `wxMDIParentFrame`   | A frame that manages other frames. |
| `wxMDIChildFrame`    | A frame managed by a parent frame. |
| `wxDialog`           | A resizable window for presenting choices. |
| `wxPopupWindow`      | A transient window with minimal decoration. |
| **Container Windows** ||
| `wxPanel`            | A window for laying out controls. |
| `wxNotebook`         | A window for switching pages using tabs. |
| `wxScrolledWindow`   | A window that scrolls children and graphics. |
| `wxSplitterWindow`   | A window that manages two child windows. |
| **Non-Static Controls**||
| `wxButton`           | A push-button control with a text label. |
| `wxBitmapButton`     | A push-button control with a bitmap label. |
| `wxChoice`           | A drop-down list of choices. |
| `wxComboBox`         | An editable field with a list of choices. |
| `wxCheckBox`         | A control representing a check box, on or off. |
| `wxListBox`          | A list of selectable string items. |
| `wxRadioBox`         | A grid of radio buttons. |
| `wxRadioButton`      | A control resembling a radio button, on or off. |
| `wxScrollBar`        | A scrollbar control. |
| `wxSpinButton`       | Arrows for incrementing/decrementing values. |
| `wxSpinCtrl`         | A text field and spin button for editing integers. |
| `wxSlider`           | A control for changing a value within a given range. |
| `wxTextCtrl`         | A single- or multiple-line text entry field. |
| `wxToggleButton`     | A button that can be toggled on and off. |
| **Static Controls**  ||
| `wxGauge`            | A control showing a quantity. |
| `wxStaticText`       | A control that shows a text label. |
| `wxStaticBitmap`     | A control that shows a bitmap label. |
| `wxStaticLine`       | A control displaying a line. |
| `wxStaticBox`        | A control displaying a box around other controls. |
| **Menus**            ||
| `wxMenu`             | A menu that can be used as a popup or in a menu bar. |
| **Control Bars**     ||
| `wxMenuBar`          | A menu bar that presents commands in a wxFrame. |
| `wxToolBar`          | A toolbar that provides quick access to commands. |
| `wxStatusBar`        | A status bar that shows information in multiple fields. |

* CMake superbuild pattern (ExternalProject module) as a modern way of managing and downloading dependencies for C++ projects.

