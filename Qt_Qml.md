# Qt and QML programming

* Qt was originally designed to bridge Windows 95 and Unix/Motif now unifies modern desktop systems as diverse as Windows Vista, Mac OS X, and GNU/Linux, as well as small devices such as mobile phones.

*  Qt is a comprehensive C++ application development framework for creating cross-platform GUI applications using a **_"write once, compile anywhere"_** approach.

*  Qt does include a small amount of features that only work on specific platforms. However, these are minimal and often for special use cases, such as **Qt Sensors**, which only work on mobile platforms; Qt Web Engine, which only works on desktops; Qt NFC, only for Android and Linux; and so on. 
    
*  Qt Quick is a very different type of GUI system in terms of technological concept and development approach. Instead of XML format, Qt Quick Designer saves its data in a declarative language similar to JavaScript called QML.
    
*  QML not only allows the designer to customize their GUI in a CSS like (Cascading Style Sheets) fashion, it also allows the programmer to write functional JavaScript within the QML file.
    
*   The Qt libraries and tools are also part of Qt/Embedded Linux, a product that provides its own window system on top of embedded Linux.

*  For every Qt class, there is a header file with the same name (and capitalization) as the class that contains the class's definition.

*  `QApplication` object manages application-wide resources. The `QApplication` constructor requires argc and argv because Qt supports a few command-line arguments of its own.

*  qmake

```bash
  # create a platform-independent project file (hello.pro)
  qmake -project 

  # create a platform-specific makefile from the project file.
  qmake hello.pro 

  # create a Visual Studio project file from hello.pro
  qmake -tp vc hello.pro 
```

*  Trolltech released Qt/Embedded Linux in 2000. It was designed to run on embedded Linux devices and provided its own window system as a lightweight replacement for X11. Both Qt/X11 and Qt/Embedded Linux were now offered under the widely used GNU General Public License (GPL).

*  Qtopia, an application platform for mobile phones and PDAs.

*  Qt 4's feature set is now so broad that it has taken Qt beyond being a GUI toolkit and made it into a full-blown application development framework.

*  Qt's widgets emit signals to indicate that a user action or a change of state has occurred. A signal can be connected to a function (called a slot in that context) so that when the signal is emitted, the slot is automatically executed.

*  use layouts to manage the geometry of widgets in a window
    
*  A layout manager is an object that sets the size and position of the widgets that lie under its responsibility.
    
*   Qt applications look native on every supported platform. Qt achieves this by emulating the platform's look and feel, rather than wrapping a particular platform or toolkit's widget set.
    
*  The **Plastique** style is the default style for **Qt/X11** applications running under KDE, and **Cleanlooks** is the default under **GNOME**. These styles use gradients and anti-aliasing to provide a modern look and feel. Qt application users can override the default style by using the -style command-line option. 

```bash
    ./age -style motif
  ```

*  Qt Assistant is the Qt help browser, which has powerful searching and indexing features that make it quicker and easier to use than a web browser.

*  A forward declaration tells the C++ compiler that a class exists, without giving all the detail that a class definition (usually located in a header file of its own) provides. using forward declarations when it is possible makes compiling somewhat faster.

*  The `Q_OBJECT` macro at the beginning of the class definition is necessary for all classes that define signals or slots.
    
*  The signals and slots keywords are actually macros. The C++ pre-processor converts it into standard C++ before the compiler sees it.

*  The `tr()` function calls around the string literals mark them for translation to other languages. The function is declared in `QObject` and every subclass that contains the `Q_OBJECT` macro.
    
*  A buddy is a widget that accepts the focus when the label's shortcut key is pressed. The default button is the button that is pressed when the user hits Enter.
    
*  The `close()` slot is inherited from `QWidget`, and its default behavior is to hide the widget from view (without deleting it).

*  `spacer item` (or "stretch") uses up the empty space below the Find and Close buttons, ensuring that these buttons occupy the top of their layout. 
    
*  Layout manager classes are derived from `QLayout`, which in turn is derived from `QObject`. In a running application, layouts are invisible. 
    
*  The `QWidget::sizeHint()` function returns a widget's **"ideal"** size.

*  The emit keyword is specific to Qt; like other Qt extensions it is converted into standard C++ by the C++ pre-processor.

*  If the class definition contains the `Q_OBJECT` macro, the makefile generated by qmake will include special rules  to run `moc`, Qt's **meta-object compiler**.
    
*  For moc to work correctly, we must put the class definition in a header file, separate from the implementation file. The code generated by moc includes this header file and adds some C++ boilerplate code of its own.
    
*  Qt's signal and slot enables the application programmer to bind objects together without the objects knowing anything about each other.
    
*  A slot can be connected to a signal, in which case it is automatically called each time the signal is emitted. When the signal is emitted, the slots are called one after the other, in an unspecified order.

*  A signal can be connected to another signal:
```cpp
    connect(lineEdit, SIGNAL(textChanged(const QString &)), 
          this, SIGNAL(updateRecord(const QString &)));

``` 
*  Connections can be removed: 
```cpp
    disconnect(lcd, SIGNAL(overflow()), this, SLOT(handleMathError()));
  ```
This is rarely needed, because Qt automatically removes all connections involving an object when that object is deleted.
    
*  Qt's **Meta-Object System** provides two key services: 
  1) signals/slots and 
  2) introspection.
    
*  The introspection functionality is necessary for implementing signals and slots, and allows application programmers to obtain "meta-information" about QObject subclasses at run-time, including the list of signals and slots supported by the object and its class name, supports properties (used extensively by Qt Designer) and text translation (for internationalization).
    
*  `moc` parses `Q_OBJECT` class definitions and makes the dynamic meta data information available through C++ functions.
    
*  The qmake tool is smart enough to detect the user interface file (.ui) and to generate the appropriate makefile rules to invoke `uic`, **_Qt's user interface compiler_**. The `uic` tool converts `.ui` file into C++ and puts the result in `ui_filename.h` file. The generated class doesn't have any base class. So create a QDialog and pass it to setupUi().
    
*  Adding functionality to *.ui file. The cleanest approach is to create a new class that is derived from both QDialog and Ui::GoToCellDialog and than implements the missing functionality. custom functionality is implemented by subclassing the uic-generated class.
    
*  Qt provides three built-in validator classes:
  1) QIntValidator, 
  1) QDoubleValidator, and 
  1) QRegExpValidator. 
        
*  Setting the `sizeConstraint` property of the form's layout to `QLayout::SetFixedSize`, makes the dialog non-resizable by the user. The layout then takes over the responsibility for resizing, and resizes the dialog automatically when child widgets are shown or hidden, ensuring that the dialog is always displayed at its optimal size.
    
*  Subtle layout idiom. 
   The `QWidget::sizeHint()` function returns a widget's **"ideal"** size, which the layout system tries to honor. This explains why different kinds of widgets, or similar widgets with different contents, may be assigned different sizes by the layout system. To avoid this inconsistency, set a widget's minimum size to the ideal size, like
```cpp
    primaryColumnCombo->setMinimumSize(20, secondaryColumnCombo->sizeHint());
```

*  A QTabWidget provides a tab bar that controls a built-in QStackedWidget. For QTabWidgets, both the shape and the position of the tabs can be set.
    
    *  \textbf{Dynamic Dialogs}: 
    Dynamic dialogs are dialogs that are created from Qt Designer .ui files at run-time. Instead of converting the .ui file to C++ code using uic, we can load the file at run-time using the QUiLoader class:
    
    \begin{lstlisting}[language=C++]
    QUiLoader uiLoader;
    QFile file("sortdialog.ui");
    QWidget *sortDialog = uiLoader.load(&file);
    if (sortDialog) {
        ...
    }
    \end{lstlisting}
    
    *  The QUiLoader class is located in a separate library.
    CONFIG += uitools
    
    *  Advantage of Dynamic Dialog
    1) change the layout of a form without recompiling the application
    2) create thin-client applications, where the executable merely has a front-end form built-in and all other forms are created as required.
    
    *  \textbf{Built-in Widget and Dialog Classes}
        \begin{itemize}
            *  Qt's Button Widgets
            \begin{enumerate}
                *  QPushButton
                *  QToolButton
                *  QCheckBox
                *  QRadioButton
            \end{enumerate}
                
            *  Qt's single-page container widgets
            \begin{enumerate}
                *  QGroupBox
                *  QFrame
            \end{enumerate}
            
            *  Qt's multi-page container widgets
            \begin{enumerate}
                *  QTabWidget
                *  QToolBox
            \end{enumerate}
            
            *  Qt's item view widgets
            \begin{enumerate}
                *  QListVoew (as list/ as Icon)
                *  QTreeView
                *  QTableView
            \end{enumerate}
            
            *  Qt's display widgets
            \begin{enumerate}
                *  QLabel (text/image)
                *  QLCDNumber
                *  QProgressBar
                *  QTextBrowser
            \end{enumerate}
            
            *  Qt's input widgets
            \begin{enumerate}
                *  QSpinBox
                *  QDoubleSpinBox
                *  QComboBox
                *  QDateEdit
                *  QTimeEdit
                *  QDateTimeEdit
                *  QScrollBar
                *  QSlider
                *  QTextEdit
                *  QLineEdit
                *  QDial
            \end{enumerate}
            
            *  Qt's feedback dialogs
            \begin{enumerate}
                *  QInputDialog
                *  QProgressBarDialog
                *  QMessageBox
                *  QErrorMessage
            \end{enumerate}
            
            *  Qt's color and font dialogs
            \begin{enumerate}
                *  QColorDialog
                *  QFontDialog
            \end{enumerate}
            
            *  Qt's file and print dialogs
            \begin{enumerate}
                *  QPageSetupDialog
                *  QFileDialog
                *  QPrintDialog
            \end{enumerate}
            
            *  Qt's  QWizard dialog
        \end{itemize}
        
    *  The Qt library includes a rich text engine that can be used for displaying and editing formatted text.
    
    *  QTextBrowser is a read-only QTextEdit subclass that can display formatted text. Both QLineEdit and QTextEdit are fully integrated with the clipboard.
    
    *  On Windows and Mac OS X, Qt uses the native dialogs rather than its own common dialogs when possible.
    
    *  The return value of a slot is ignored when a slot is executed in response to a signal.
    
    *   There is no platform-independent way of setting the application icon that appears on the desktop.
    
    *  X PixMap (XPM) is an image file format used by the X Window System,  it is a plain text file in the XPM2 format or of a C programming language syntax, which can be included in a C program file.
    
    *  Resource files are compiled into the application's executable, so they can't get lost. Resources can be any kind of file (not just images), and we can use them in most places where Qt expects a file name.
    
    *  An action (QAciton) is an item that can be added to any number of menus and toolbars.
    
    *  Using the appropriate QKeySequence::StandardKey enum value, we ensure that Qt will provide the correct shortcuts for the platform on which the application is running.
    newAction->setShortcut(QKeySequence::New);
    
    *  Checkable actions are rendered with a check-mark in the menu and implemented as toggle buttons in the toolbar.
    showGridAction->setCheckable(true);
    
    *  Qt also supports mutually exclusive actions through the QActionGroup class.
    
    *  In addition to warning(), QMessageBox also provides information(), question(), and critical().
    
    *  The parent-child relationship doesn't mean the same thing for dialogs as for other widgets. A dialog is always a window in its own right, but if it has a parent, it is centered on top of the parent by default. A child dialog also shares its parent's taskbar entry.
    
    *  By reimplementing QWidget::closeEvent(), we can intercept attempts to close the main window and decide whether we want the window to actually close or not.
    
    *  When the last window is closed, the application terminates. If needed, we can disable this behavior by setting QApplication's quitOnLastWindowClosed property to false, in which case the application keeps running until we call QApplication::quit().
    
    *  Every QWidget has a windowModified property that should be set to true if the window's document has unsaved changes, and to false otherwise. Qt handles this behavior automatically platform independently, as long to appear when it is required.
    
    *  Every action can have an associated "data" item of type QVariant.
        recentFileActions[j]->setData(recentFiles[j]);
        
    *  The QVariant type can hold values of many C++ and Qt types.
    
    *  \begin{lstlisting}[language=C++]
        QAction *action = qobject_cast<QAction *>(sender());
        if (action)
            loadFile(action->data().toString());
    \end{lstlisting}    
    The \lstinline{qobject_cast<T>()} function performs a dynamic cast based on the meta-information generated by moc. It returns a pointer of  requested QObject subclass, or 0 if the object cannot be cast to that type. Unlike the Standard C++ \lstinline{dynamic_cast<T>()}, Qt's \lstinline{qobject_cast<T>()} works correctly across dynamic library boundaries.

    *  A \textbf{modeless} window is one that runs independently of any other windows in the application. A \textbf{modal} window is a window that pops up when invoked and blocks the application, preventing any other processing or interactions from taking place until the window is closed.
    
    *  A dialog is modeless if it's invoked using show() (unless we call setModal() beforehand to make it modal); it is modal if it's invoked using exec().
    
    *  \begin{lstlisting}[language=C++]
            findDialog->show();  // Make visible
            findDialog->raise();  // on top of other
            findDialog->activateWindow();  // active
          \end{lstlisting}
          
    *  By default, QSettings stores the application's settings in platform-specific locations. On Windows, it uses the system registry; on Unix, it stores the data in text files; on Mac OS X, it uses the Core Foundation Preferences API.
    
    * 
        \begin{lstlisting}[language=C++]
        MainWindow::MainWindow()
        {
        ...
        setAttribute(Qt::WA_DeleteOnClose);
        ...
        }
        \end{lstlisting}
        \listing{Qt::WA_DeleteOnClose} attribute tells Qt to delete the window when it is closed. The \listing{Qt::WA_DeleteOnClose} attribute is one of many flags that can be set on a QWidget to influence its behavior.
        
    * 
        \begin{lstlisting}[language=C++]
            foreach (QWidget *win, QApplication::topLevelWidgets()) {
                if (MainWindow *mainWin = qobject_cast<MainWindow *>(win))
                    mainWin->updateRecentFileActions();
            }
        \end{lstlisting}
        
    *  Applications that provide one document per main window are said to be SDI (single document interface) applications. A common alternative on Windows is MDI (multiple document interface), where the application has a single main window that manages multiple document windows within its central area.
    
    *  The QSplitter arranges its child widgets horizontally or vertically, with splitter handles to give some sizing control to the user. Splitters can contain all kinds of widgets, including other splitters.
    
    *  
        \begin{figure}[h]
        \centering
        \includegraphics[width=0.75\textwidth]{Qt/TableWidget}
        \caption{Table Widget}
        \label{fig:TableWidget}
        \end{figure}
        
    *   QFile and QDataStream together provide platform-independent binary I/O.  A QIODevice represents an input/output medium one can read data from and write data to. The QFile class is an example of an I/O device.
    
    * 
        \begin{lstlisting}[language=C++]
        QApplication::setOverrideCursor(Qt::WaitCursor);
        // Processing here...
        QApplication::restoreOverrideCursor();
        \end{lstlisting}
        
    *  QDataStream is very versatile. It can be used on a QFile, and also on a QBuffer, a QProcess, a QTcpSocket, a QUdpSocket, or a QSslSocket. Qt also offers a QTextStream class that can be used instead of QDataStream for reading and writing text files.
    
    *  The system clipboard is available in Qt through the \listing{QApplication::clipboard()} static function. By calling \listing{QClipboard::setText()}, we make the text available on the clipboard, both to this application and to other applications that support plain text.
    
    *  Variables declared with the C++ mutable keyword can be modified in const functions.
    
    *  Qt's item classes like QTableWidgetItem are not derived from QObject to keep their overhead to the barest minimum.
    
    *  Every QTableWidgetItem can hold some data, up to one QVariant for each data "role". The most commonly used roles are Qt::EditRole and Qt::DisplayRole. 
    
    *  A QVariant can store values of different types, such as double and QString, and provides functions to convert the variant to other types.
    
    *  For performance and portability reasons, Qt never uses C++ exceptions to report failure. This doesn't prevent you from using them in Qt programs if your compiler supports them.
    
    *  If behavior beyond what can be achieved through signals and slots is required, write the necessary code in a class that is derived from both QWidget and the uic-generated class.
    
    *  the \listing{Q_PROPERTY()} macro declare custom properties. Each property has a data type, a "read" function, and an optional "write" function.Properties may be of any type supported by QVariant. The \listing{Q_OBJECT} macro is necessary for classes that define properties.
    
    *  The zoom factor is set to 8, meaning that each pixel in the icon will be rendered as an 8 x 8 square.
    
    *  32-bit ARGB format supports semi-transparency. Qt provides two types for storing colors: QRgb and QColor.
    
    *  The QImage class stores an image in a hardware-independent fashion. It can be set to use a 1-bit, 8-bit, or 32-bit depth. An image with 32-bit depth uses 8 bits for each of the red, green, and blue components of a pixel. The remaining 8 bits store the pixel's alpha component (opacity).
    
    *  QRgb is simply a typedef for unsigned int, and qRgb() and qRgba() are inline functions that combine their arguments into one 32-bit ARGB integer value.
        \begin{lstlisting}[language=C++]
        QRgb red = qRgba(255, 0, 0, 255);
        QRgb red = 0xFFFF0000;
        \end{lstlisting}
    
    *  A widget's size hint is mostly useful in conjunction with layouts. Qt's layout managers try as much as possible to respect a widget's size hint when they lay out a form's child widgets.
    
    *  size policy tells the layout system whether they like to be stretched and shrunk.
    
    *  We can force a paint event by calling QWidget::update() or QWidget::repaint(). The difference between these two functions is that repaint() forces an immediate repaint, whereas update() simply schedules a paint event for when Qt next processes events. 
    
    *  Every widget is equipped with a \textbf{palette} that specifies which colors should be used for what. For example, there is a palette entry for the background color of widgets (usually light gray) and one for the color of text on that background (usually black). By default, a widget's palette adopts the window system's color scheme. By using colors from the palette, we ensure that software respects user's preferences.
    
    *  A widget's palette consists of three color groups: active, inactive, and disabled.
    
    *  The call to IconEditor::pixelRect() returns a QRect that defines the region to repaint.
    
    *  \listing{Qt::WA_StaticContents} attribute tells Qt that the widget's content doesn't change when the widget is resized and that the content stays rooted to the widget's top-left corner
    
    *  The plugin approach for Integrating Custom Widgets with Qt Designer requires the creation of a plugin library that Qt Designer can load at run-time and use to create instances of the widget. subclass \listing{QDesignerCustomWidgetInterface} and reimplement some virtual functions. 
    
    *  The qmake build tool has some predefined variables built into it. One of them is \listing{QT_INSTALL_PLUGINS]}, which holds the path to the plugins directory inside the directory where Qt is installed. 
    
    *  \textbf{Double buffering} is a GUI programming technique that consists of rendering a widget to an off-screen pixmap and copying the pixmap onto the display.
    
    *  Qt provides the QRubberBand class for drawing rubber bands.
    
    *  The QWidget::style() function returns the style that should be used to draw the widget. In Qt, a widget style is a subclass of QStyle. The built-in styles include QWindowsStyle, QWindowsXPStyle, QWindowsVistaStyle, QMotifStyle, QCDEStyle, QMacStyle, QPlastiqueStyle, and QCleanlooksStyle.
    
    *  Qt's built-in widgets rely almost exclusively on QStyle to paint themselves.
    
    *  An advantage of Qt's layout classes is that they ensure that forms adapt automatically to different fonts, languages, and platforms.
    
    *  Qt provides several classes that lay out widgets on a form: QHBoxLayout, QVBoxLayout, QGridLayout, and QStackedLayout. Other classes that perform layout management include QSplitter, QScrollArea, QMainWindow, and QMdiArea.
    
    *  The margin around the dialog and the spacing between the child widgets are set to default values based on the current widget style; they can be changed using QLayout::setContentsMargins() and QLayout::setSpacing().
    
    *  Layout managers automatically set a minimum size for the form as a whole, based on the form's child widgets' minimum sizes and size hints.
    
    *  If the layout manager's default layout is not sufficient we can adjust the layout by changing the size policies and size hints of the widgets being laid out.
    
    *  A widget's size policy tells the layout system how it should stretch or shrink.
    
    *  A QSizePolicy has both a horizontal and a vertical component. Here are the most useful values:
    Fixed means the widget always stays at the size of its size hint. 
    Minimum means that the widget's size hint is its minimum size. 
    Maximum means that the widget's size hint is its maximum size. 
    Preferred means that the widget's size hint is its preferred size, but that the widget can still shrink or grow if necessary.
    Expanding means that the widget can shrink or grow and that it is especially willing to grow.
    
    *  When a form that contains both Preferred and Expanding widgets is resized, extra space is given to the Expanding widgets, while the Preferred widgets stay at their size hint. 
    
    *  The stretch factors can be used to indicate that different child widgets should grow at different rates when the form expands. 
    
    *  Another way of influencing a layout is to set a minimum size, a maximum size, or a fixed size on the child widgets. The layout manager will respect these constraints when laying out the widgets. And if this isn't sufficient, we can always derive from the child widget's class and reimplement sizeHint() to obtain the size hint we need.
    
    *  The QStackedLayout class lays out a set of child widgets, or "pages", and shows only one at a time, hiding the others from the user. For convenience, Qt also includes QStackedWidget, which provides a QWidget with a built-in QStackedLayout. 
    
    *  For cases where the number of pages is small and likely to remain small, a simpler alternative to using a QStackedWidget and QListWidget is to use a QTabWidget.
    
    *  Unlike layout managers, which simply lay out a form's child widgets and have no visual representation, QSplitter is derived from QWidget and can be used like any other widget.
    
    *  Splitter handles can be moved programmatically by calling QSplitter::setSizes(). The QSplitter class also provides a means of saving and restoring its state the next time the application is run.
    \listing{
    settings.setValue("mainSplitter", mainSplitter->saveState());
    mainSplitter->restoreState(settings.value("mainSplitter").toByteArray()); // Restore settings
    }
        
    *  Dock windows are windows that can be docked inside a QMainWindow or floated as independent windows.  In Qt, dock windows are instances of QDockWidget.
    
    *  
        \begin{figure}[h]
        \centering
        \includegraphics[width=0.75\textwidth]{Qt/DockArea}
        \caption{Dock Area}
        \label{fig:DockArea}
        \end{figure}
        
    *  The corners indicated with dotted lines can belong to either of their two adjoining dock areas.
        \begin{lstlisting}[language=C++]
        QMainWindow::setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea)
        \end{lstlisting}
        
    *  Every QObject can be given an "object name".
    
    *  Use QMainWindow::saveState() and QMainWindow::restoreState() to save and restore the dock window and toolbar geometries and states.
    
    *  QMainWindow provides a context menu that lists all the dock windows and toolbars.
    
    *  \listing{QTimer::singleShot(0, this, SLOT(loadFiles()));} 
    Such timers time out as soon as the event loop is idle. 
    
    *  Qt-specific command-line options, such as -style and -font, are automatically removed from the argument list by the QApplication constructor. 
    
    *  Events are generated by the window system or by Qt itself in response to various occurrences. Most events are generated in response to user actions, but some, such as timer events, are generated independently by the system.
    
    *  When we program with Qt, we seldom need to think about events, because Qt widgets emit signals when something significant occurs.
    
    *  Events should not be confused with signals. As a rule, signals are useful when using a widget, whereas events are useful when implementing a widget.
    
    *  In Qt, an event is an instance of a QEvent subclass. Qt handles more than a hundred types of events, each identified by an enum value. For example, QEvent::type() returns QEvent::MouseButtonPress for mouse press events.
    
    *  Events are notified to objects through their event() function, inherited from QObject. 
    
    *  The Tab and Backtab (Shift+Tab) keys are special cases. QWidget::event() handles them before it calls keyPressEvent(), with the semantic of passing the focus to the next or previous widget in the focus chain.
    
    *   If the commands don't appear in the user interface, the QAction objects could be replaced with a QShortcut object, the class used internally by QAction to support key bindings.
    
    *  QWidget::fontMetrics() returns a QFontMetrics object that can be queried to obtain information relating to the widget's font.
    
    *  QObject supports multiple independent timers, each with its own time interval. After the call to startTimer(), Qt will generate a timer event approximately every 30 milliseconds; the accuracy depends on the underlying operating system.
    
    *  One really powerful feature of Qt's event model is that a QObject instance can be set to monitor the events of another QObject instance before the latter object even sees them.
    
    *  Setting up an event filter involves two steps:
        1. Register the monitoring object with the target object by calling installEventFilter() on the target.
        2. Handle the target object's events in the monitor's eventFilter() function.
        
    *  By reimplementing the event() function, we can process events before they reach the specific event handlers.
    
    *  Qt's 2D graphics engine is based on the QPainter class. QPainter can draw geometric shapes (points, lines, rectangles, ellipses, arcs, chords, pie segments, polygons, and Bézier curves), as well as pixmaps, images, and text. Furthermore, QPainter supports advanced features such as antialiasing (for text and shape edges), alpha blending, gradient filling, and vector paths. QPainter also supports linear transformations, such as translation, rotation, shearing, and scaling.
    
    *  Qt 4.2 introduced a completely new "graphics view" architecture centered on the QGraphicsView, QGraphicsScene, and QGraphicsItem classes. This architecture offers a high-level interface for doing item-based graphics, and supports standard user actions on items, including moving, selecting, and grouping.
    
    *  An alternative to QPainter is to use OpenGL commands. OpenGL is a standard library for drawing 3D graphics.
    
    *  The setRenderHint() call enables antialiasing, telling QPainter to use different color intensities on the edges to reduce the visual distortion that normally occurs when the edges of a shape are converted into pixels. The result is smoother edges on platforms and devices that support this feature.
    
    *  Painter paths are the ultimate drawing primitive in the sense that any shape or combination of shapes can be expressed as a painter path.
    
    *  In modern applications, gradient fills are a popular alternative to monochrome fill patterns. Gradients rely on color interpolation to obtain smooth transitions between two or more colors.
    
    *  Qt supports three types of gradients: linear, conical, and radial.
    
    *  save the current state of a painter on an internal stack by calling save() and restore it later on by calling restore(). 
    
    *  QPainter's viewport, window, and world transform: The viewport and the window are tightly bound. The viewport is an arbitrary rectangle specified in physical coordinates. The window specifies the same rectangle, but in logical coordinates. 
    
    *  The window &viewport mechanism is useful to make the drawing code independent of the size or resolution of the paint device. 
    
    *  The world transform is a transformation matrix that is applied in addition to the window viewport conversion. It allows us to translate, scale, rotate, or shear the items we are drawing.
    
    *  On X11 and Mac OS X, drawing on a QWidget or QPixmap relies on the platform's native paint engine.
    
    *  On X11, features such as antialiasing and support for fractional coordinates are available only if the X Render extension is present on the X server.
    
    *  On Mac OS X, the native aliased graphics engine uses different algorithms for drawing polygons than X11 and Windows, with slightly different results.
    
    *  When accuracy is more important than efficiency, we can draw to a QImage and copy the result onto the screen. This always uses Qt's own internal paint engine, giving identical results on all platforms. 
    
    *  The initFrom() call initializes the painter's pen, background, and font based on the widget.  
    
    *  
        \begin{lstlisting}[language=C++]
        QImage image(size(), QImage::Format_ARGB32_Premultiplied);
        QPainter imagePainter(&image);
        imagePainter.initFrom(this);
        \end{lstlisting}
        
    *  A QGraphicsScene has three layers: a background layer, an item layer, and a foreground layer. The background and foreground are normally specified by QBrushes, but it is possible to reimplement drawBackground() or drawForeground() for complete control.
    
    *  The scene can tell us which items have collided, which are selected, and which are at a particular point or in a particular region.
    
    *  A QGraphicsView is a widget that presents a scene, providing scroll bars if necessary and capable of applying transformations that affect how the scene is rendered. This is useful to support zooming and rotating as aids for viewing the scene.
    
    *  By default, QGraphicsView renders using Qt's built-in 2D paint engine, but it can be changed to use an OpenGL widget with a single setViewport() call after it has been constructed.
    
    *  The GraphicsView architecture uses three different coordinate systems 1) viewport coordinates, 2) scene coordinates, and 3) item coordinates with functions for mapping from one coordinate system to another. 
    
    *  QGraphicsItem is not a QObject subclass, but if we wanted to add signals and slots to Link, there is nothing to stop us from using multiple inheritance with QObject.
    class Link : public QGraphicsLineItem, public QObject
    
    *  Every graphics item has an (x, y) position, and a z value that specifies how far forward or back it is in the scene. A negative z value means it will always be drawn underneath other items which has default z value of 0.
    
    *  The QGraphicsItem::pos() function returns the position of its graphics item relative to the scene (for top-level items) or to the parent item (for child items).
    
    *  The \listing{Q_DECLARE_TR_FUNCTIONS()} macro is used to add a tr() function to this class, even though it is not a QObject subclass instead of using static QObject::tr() or QCoreApplication::translate(). 
    
    * 
        \begin{lstlisting}[language=C++]
        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *painter,
                    const QStyleOptionGraphicsItem *option, QWidget *widget);
        \end{lstlisting}
        
        reimplemented shape() to return a more accurate shape otherwise it will fall back on the boundingRect().
        
    *  The graphics view architecture uses the bounding rectangle to determine whether an item needs to be drawn. The shape is used for determining whether a point is inside an item, or whether two items collide.
    
    *  The shape() function is called by QGraphicsView for fine-grained collision detection.
    
    *  The option parameter of type QStyleOptionGraphicsItem is an unusual class for Qt because it provides several public member variables. These include the current layout direction, font metrics, palette, rectangle, state (selected, "has focus", and many others), the transformation matrix, and the level of detail.
    
    *  
        QApplication::clipboard()->setText(str);
        QString str = QApplication::clipboard()->text();
        
    *  The levelOfDetail member of the QStyleOptionGraphicsItem class stores a floating-point value that tells us what the zoom factor is. A value of 1.0 means that the scene is being viewed at its natural size, a value of 0.5 means that the scene has been zoomed out to half its natural size, and a value of 2.5 means that the scene has been zoomed in to two and a half times its natural size. 
    
    *  On Windows and Mac OS X, QPrinter uses the system's printer drivers. On Unix, it generates PostScript and sends it to lp or lpr (or to the program set using QPrinter::setPrintProgram()).
    
    *  QTextDocument is Qt's rich text engine.
    
    *  Drag and drop and clipboard support, both mechanisms are based on QMimeData, a class that can provide data in several formats.
    
    *  The MIME type text/uri-list is used to store a list of uniform resource identifiers (URIs), which can be file names, URLs (such as HTTP or FTP paths), or other global resource identifiers. Standard MIME types are defined by the Internet Assigned Numbers Authority (IANA). They consist of a type and a subtype separated by a slash.
    
    *  The clipboard and the drag and drop system use MIME types to identify different types of data.
    
    *  QString Qt::escape(const QString &plain) is obsolete. Use QString::toHtmlEscaped() instead.
    
    *  The Smalltalk language popularized a flexible approach to visualizing large data sets: modela view controller (MVC).
    
    *  The model represents the data set and is responsible for both fetching the data that is needed for viewing and saving back any changes. Each type of data set has its own model, but the API that the models provide to the views is uniform regardless of the underlying data set.
    
    *  The controller mediates between the user and the view, converting user actions into requests to navigate or edit data, which the view then transmits to the model as necessary.
    
    *  In Qt, the model behaves the same as it does for classic MVC. But instead of a controller, Qt uses a slightly different abstraction: the delegate. The delegate is used to provide fine control over how items are rendered and edited.
    
    *   Use Qt's convenience item view classes (QListWidget, QTableWidget, and QTreeWidget) for relatively small numbers of items.
    
    *  For large data sets use Qt's views (QListView, QTableView, and QTreeView) in conjunction with a data model, which can be a custom model or one of Qt's predefined models. For example, if the data set is held in a database, we can combine a QTableView with a QSqlTableModel.
    
    *  To access an application's settings, a QSettings object must be created with the organization's name and the application's name as parameters. A group is the QSettings equivalent of a file system directory.
    
    *  Every data item in a model has a corresponding "model index", which is represented by a QModelIndex object. A QModelIndex has three main components: a row, a column, and a pointer to the model to which it belongs.
    
    *  QDirModel class encapsulates the computer's file system and is capable of showing (and hiding) various file attributes. This model can apply a filter to restrict the kinds of file system entries that are shown and can order the entries in various ways.
    
    *  The main advantages of the Qt containers is they are implicitly shared "copy on write", optimized.
    
    *  They can be streamed using QDataStream, and they usually result in less code in the executable than the corresponding STL containers. 

    *  \textif{QString} is a 16-bit Unicode string used throughout Qt's API. \textif{QByteArray} is an array of 8-bit chars useful for storing raw binary data. \textif{QVariant} is a type that can store most C++ and Qt value types.
 
    *  Qt classes that are derived from \textif{QObject} lack a copy constructor and an assignment operator.
    
    *  Qt provides two categories of iterators for traversing the items stored in a container: Java-style iterators and STL-style iterators.
    
    *  Qt's features are developed for each platform by using native technology available on that platform. This means that, for example, creating a audio playback app using MediaPlayer QML element will use Media Foundation on Windows while using GStreamer on Linux (see Qt Multimedia Backends).
    
    *  Qt supports two main ways of writing GUI applications. One is using a \textbf{Widget} module, and the other is using a \textbf{Quick} module. Widgets provide and older way of writing GUI applications using C++ while the Quick module is a newer way using QML language.
    
    
    \subsection*{Qt Quick and QML}
    
    *  Qt Quick is script-based, just like Python or Perl.  A script needs to be interpreted and executed by an engine. This engine in Qt Quick is called Qt Declarative UI Runtime. 
    
    *  Qt Quick's purpose is to serve as a script-based programming environment for application UI. Complex application logic and heavy processing should stay on the C++ side and expose its APIs to Qt Quick.
    
    *  Qt Quick (Qt User Interface Creation Kit) 

    *  Most use cases for Qt Quick are in areas where users expect non-widget based UIs with rich animations, effects and graphical resources.
    
    *  Most of Qt Quick elements are rectangles or something similar to it.  
    
    *   Anchoring allows positioning of elements relatively to each other.
    
     *  QML is a declarative language that is part of Qt framework and Quick module and it enables building fluid and performant user interfaces.
    
    *  \textbf{Flutter} is Google’s UI toolkit for building beautiful, natively compiled applications for mobile, web, and desktop from a single codebase. 
    
    *   Qt WebEngine integrates chromium engine in the same way while still giving you the whole Qt platform underneath that you can use to extend functionality.
    
    *  Gone are the days when you actually write some plain HTML with Javascript and CSS. You are probably using some abstractions like Angular with TypeScript and Sass, which also includes Node.js. There are also alternative approaches like translating QML to HTML with projects like PureQML and QMLWeb.
    
    *  QML provides a JavaScript host environment tailored to writing QML applications. This environment is different from the host environment provided by a browser or a server-side JavaScript environment such as Node.js. For example, QML does not provide a window object or DOM API as commonly found in a browser environment.
    
    *  The \textit{alias} keyword allows us to forward a property of an object or an object itself from within the type to an outer scope.
    
    *  For every property, you can provide a signal handler. This handler is called after the property changes.
    
    *  Using the Qt Quick Controls 2 module, it is possible to create user interfaces built from standard platform components such as buttons, labels and sliders.
    
    *  Valid colors values are colors from the SVG color names (see http://www.w3.org/TR/css3-color/#svg-color)
    
    *  To further enhance the text rendering you can use the style and styleColor property, which allows you render the text in outline, raised and sunken mode.
    
    *  For more complex interaction, Qt Quick Input Handlers where introduced with Qt 5.12. They are intended to be used instead of elements such as MouseArea and Flickable and offer greater control and flexibility.
    
    *  A component is a reusable element and QML provides different ways to create components. A simple component is a file based component.
    
    *  Only the root level properties can be accessed from outside the file by other components.
    
    *  A transformation manipulates the geometry of an object. QML Items can, in general, be translated, rotated and scaled. There is a simple form of these operations and a more advanced way.
    
    *  Elements which appear earlier in the code have a lower stacking order (called z-order). The z-order can also be manipulated by the z-property of an Item.
    
    *  There are a number of QML elements used to position items (called positioners) 
    \begin{enumerate}
        *  Row
        *  Column
        *  Grid
        *  Flow
    \end{enumerate}
    
    *  OpenSSL is a robust, commercial-grade, and full-featured toolkit for the Transport Layer Security (TLS) and Secure Sockets Layer (SSL) protocols. It is also a general-purpose cryptography library.
    
    \subsection*{Qt Maps}
    
    *  The Qt Location module provides developer access to geocoding and navigation information.
    
    *  At the moment (Qt 5.13/2019), Qt's \textit{map view} does not support C++, only QML. 
    
    *  \textbf{QML (Qt Modeling Language)} is a user interface markup language for Qt Quick applications. Since QML is powered by the JavaScript framework, its coding syntax is almost similar to the JavaScript.
    
    *   Qt can be used for  navigation, nearby point-of-interest lookup, location-based services (such as calling for a taxi), and so on, but you will require an advanced database system, if you're going for something more complex.
    
    *  QT += core gui \textbf{location qml quickwidgets}
    
    *  Qt include a small amount of features that only work on specific platforms. For example:
        \begin{enumerate}
            *  \textbf{Qt Sensors:} Mobile platforms
            *  \textbf{Qt Web Engine:} Desktops only
            *  \textbf{Qt NFC:} Only for Android and Linux
        \end{enumerate}
        
    *  
        \begin{lstlisting}[language=C++]
        \end{lstlisting}
        
    *  GUI designer comes with two different types of editors: 
    one for widget-based applications, called Qt Designer, and another for Qt Quick Application, called Qt Quick Designer.
    
    *  Instead of XML format, Qt Quick Designer saves its data in a declarative language similar to JavaScript called QML. QML not only allows the designer to customize their GUI in a CSS-like (Cascading Style Sheets) fashion, it also allows the programmer to write functional JavaScript within the QML file.
    
    *  Qt supports different types of version control systems, such as Git, SVN, Mercurial, Perforce, and so on.
    
    *  Qt's Widgets Application uses a styling system called Qt Style Sheets, which is similar to the web technology's styling system—CSS (Cascading Style Sheet). All you need to do is write the style description of the widget and Qt will render it accordingly.
    
    *  Qt Style Sheet and CSS contain a declaration block and a selector. Each declaration consists of a property and value, which are separated by a colon.
    
    *  The Qt resource system is a platform-independent mechanism for storing binary files in the application's executable. You can basically store all of those important files here, such as icon images or language files, directly into your executable by using the Qt resource file. 
    
    *  Qt supports multiple different types of database systems:
    \begin{itemize}
        *  MySQL (or MariaDB)
        *  SQLite (version 2 and 3)
        *  IBM DB2
        *  Oracle
        *  ODBC
        *  PostgreSQL
        *  Sybase Adaptive Server
    \end{itemize}

    *  The SQLite database is usually used offline and it doesn't require any setup as it uses an on-disk file format for storing data.
    
    *  MySQL is an open source database management system based on the relational model, which is the most common method used by modern database systems to store information for various purposes. 
    
    *  MySQL is an open-source database management system, commonly installed as part of the popular \textbf{LAMP} (Linux, Apache, MySQL, PHP/Python/Perl) stack. It uses a relational database and SQL (Structured Query Language) to manage its data.
    
    *  Software package called \textbf{XAMPP}, which is a web server stack package developed by a group called Apache Friends. This package comes with Apache, MariaDB, PHP, and other optional services that you can add on during the installation process.
    
    *  similar software packages such as AppServ, AMPPS, LAMP (Linux only), WAMP (Windows only), ZendServer, and so on.
    
    *  Since Qt 5.7, several modules that were only available for commercial users before have become free for all the open source package users, which includes the Qt Charts module.
    
    *  Polar charts present data in a circular graph, where the placement of the data is based on both the angle and the distance from the center of the graph, which means the higher the value of the data, the further away the point is from the center of the chart.
    
    \chapter{Qt 5 Projects}
    
    *  Qt has a concise syntax with the QML and JavaScript languages, and its horsepower and expressiveness with the C++ language, as well as its language bindings for Python, Go, and more.
    
    *  Behavior-Driven Development (BDD) is a way of developing software that encourages starting from user stories (or features) and then moving on from those to system implementation. According to Dan North, one of BDD's initiators, a feature is a description of a requirement and its business benefit (https://dannorth.net/)
    
    *  Gherkin (https://github.com/cucumber/cucumber/wiki/Gherkin) is such a standard for BDD: a human-readable language, which can also be used by a software system to link usage expectations to system instructions by means of acceptance tests, which strictly follow the structure of scenarios.
    
    *  QMake is a build and project organization system. Qt support other build and project organization systems beyond QMake. The most widespread are Qbs (pronounced as cubes, which is part of the Qt Project and CMake.
    
    *  Qt Creator provides several kinds of project templates. These templates create most or some of the project's boilerplate code for you.
    
    *  Many Qt modules are offered with two different APIs; one for QML and one for C++.
    
    *  QML is a declarative language, which, on one hand, supports JavaScript expressions and features (such as garbage collection), and, on the other hand, allows us to use Qt objects defined in C++ in both a declarative and an imperative way by taking care of most data conversions between C++ and JavaScript. [ https://doc.qt.io/qt-5/qtqml-index.html ]
    
    \begin{figure}[h]
    \centering
    \includegraphics[width=0.75\textwidth]{images/Qt/Cpp_QML.PNG}
    \caption{C++ & QML}
    \label{fig:CppAndQml}
    \end{figure}
    
    *  Currently there is no public C++ API for most Qt Quick UI components, and, conversely, there is no QML API for most Qt Widgets UI components.
    
    *  QML has some more constraints, as it requires you to instantiate a QQmlEngine C++ object in order to be used, and thread-based programming is supported in QML code in a limited way. 
    
    *  The QtTest framework is a collection of C++ classes and QML types that provides many tools for writing effective test cases for Qt applications.
    
    *  The practice of starting with tests before moving to implementations is called \textbf{test-driven-development (TDD)}. TDD is a common way to translate BDD features into working code.
    
    *  QML is a declarative language with support for imperative JavaScript expressions.
    
    *  Property bindings are a core feature of QML that lets developers specify relationships between different object properties. When a property's dependencies change in value, the property is automatically updated according to the specified relationship. 
    
    *  Component.onCompleted: This is a built-in signal handler that is called as soon as the QML object is complet, useful to perform post-creation initialization operations.
    
    *  GUI technologies in Qt
        \begin{itemize}
            *  QWidgets 
            *  QPainter 
            *  QGraphicsView
            *  Qt Quick 1 
            *  Qt Quick 2 
            *  Qt Quick Controls 1 and 2
            *  QWindow 
            *  OpenGL 
            *  Vulkan 
            *  Direct3D
            *  Qt3D 
            *  Qt Canvas 3D
            *  QtQuick Canvas
        \end{itemize}
        
    *  Qt 3D is probably a better choice than Qt Canvas 3D. It is newer, it's got almost feature-pare QML and C++ APIs, and it is much more powerful. Also, Qt 3D is soon going to support virtual reality systems, and it has many more features beyond UI. 

    *  Qt Canvas 3D, on the other hand, supports a port of the three.js 3D JavaScript framework.
    
    *  \textit{Qt Widgets} and \textit{Qt Quick Controls 2} provide classic UI controls out of the box, while QPainter, QGraphicsView, and Qt Quick 2 are choices which give more freedom, each one with its own limitations and benefits.
    
    *  Because of QML and OpenGL, Qt Quick 2 provides a very powerful animation framework. 
    
    *  \textit{Qt Widgets} were born in the desktop era, and still serve the desktop context primarily. They provide a rich set of controls and layouts, with a C++ API. However, they are not particularly suited for devices with touch input.
    
    *  Qt Quick 2 is more suitable, as it was developed with touch devices in mind. It also provides a rich set of controls via the Qt Quick Controls 2 module: a recent module which was designed for devices having limited resources (for example, embedded) in mind. Qt Quick Controls 2 are also well supported on desktop. They do not provide, however, native look and feel on all platforms out of the box, and lack (at the time of writing) some widely used controls like tables and treeviews.
    
    *  Third parties providing additional control libraries, both for Qt Quick and Qt Widgets
    \begin{itemize}
        *  https://qwt.sourceforge.io/
        *  https://felgo.com/apps
    \end{itemize}
    
    *  Both Qt Widgets and Qt Quick are supported by dedicated visual editors that ship with Qt Creator: \textbf{Designer} and \textbf{Qt Quick Designer}. These fully fledged visual editors output clean markup files, also known as forms (XML for the Qt Widgets - .ui file extension, QML for the Qt Quick - .ui.qml file extension) without requiring any coding.
    
    *  The current public Qt Quick API is QML only.
    
    *  A \textbf{kit} consists of a set of values that define one environment, such as a device, compiler, and the Qt version.   
    
    *    A kit consists of a set of values that define one environment, such as a device, compiler, and the Qt version.
    
    *  QMake's .pri files are just convenience files that can be included in .pro files to keep sources and resources modular and organized, and to separate the source files from other resources. They can contain most of what goes into a .pro file.
    
    *  Adding Q\_OBJECT macro is required to make Qt work its magic. Signals and slots, properties, and, in general, all introspection capabilities of QObject derived classes are activated by adding this macro to the private section of the QObject-derived class. 
    
    *  Q\_OBJECT macro ensures that the copy constructor and assignment operator are made private, and disables them. This is because each QObject has an identity (for example, it might be referred to by an objectName, and it appears within a specific parent-child relationship, which also affects its lifetime). [ http://doc.qt.io/qt-5.9/object.html#identity-vs-value ]
    
    *  Slots can also be marked private, in which case they can be invoked by client code in a signal/slot connection, but not directly as methods. [http://doc.qt.io/qt-5.9/object.html]
    
    *  Signals and slots is one of the two main communication models that Qt implements. The other model being that of events, which is mostly used to handle user input.
    
    *  QString is Qt's string type. Among other things, it provides out-of-the-box support for UTF-8, many useful methods for string manipulation, and the implicit sharing mechanism, common across Qt value types, which performs a deep copy of a string only when it is written to, thus providing efficient memory usage.
    
    *  QObject's connection method, which is used to connect signals to slots, is available both as static and nonstatic, depending on the usage scenario
    
    *  The \textif{emit} macro keyword is optional; it is just used for clarity to show that the method we are invoking is a signal.
    
    *  Besides QObject, another type which makes Qt code so powerful is QVariant, a type which \textit{acts like a union for the most common Qt data types}. QVariant's represents an abstraction over several Qt and C++ built-in data types, and allows conversion between them.
    
    *  The QT -= gui directive excludes the Qt Gui module from the resulting application.
    
    *  CONFIG -= app\_bundle is macOS-specific, and avoids generating an app bundle, outputting a simple executable instead.
    
    *  Two special methods provided by the QtTest framework, init() and cleanup(), which are automatically run on each test execution.
    
    *  There are two main paths to expose C++ code to QML: 
    \begin{enumerate}
        *  Expose already instantiated C++ objects to a QML engine's context
        *  Register C++ classes as QML types, and then create object instances on the QML side.
    \end{enumerate}
    
    *  Any QML component requires an environment where it should be instantiated. Such an environment is the sum of a \textbf{QQmlContext}, which is responsible for exposing data to the QML component, and a \textbf{QQmlEngine}, which is responsible for instantiating the component and managing a hierarchy of QQmlContexts. 
    
    *  The QQmlContext manages property bindings and contextual properties like the C++ object instances we want to expose to the QML UI. 
    
    *  The \textbf{QQmlApplicationEngine} is a specialization of QQmlEngine which offers a few additional features commonly used in Qt QML applications such as multi-language support.
    
    *  A QML engine automatically provides a root context, which can be accessed by calling the engine's rootContext() method.
    
    *  It is not enough to expose a C++ object via a context property for its methods to be invoked from QML; we also need to mark all methods that we intend to invoke with the Q\_INVOKABLE macro This macro registers the method with Qt's Meta-Object system.
    
    *  A property alias is a reference to an object, or an object's property.
    
    *  For more information about supported host and target platforms, and related requirements, take a look at https://doc.qt.io/qt-5/supported-platforms.html.
    
    *  Depending on the Qt for Windows version you have chosen (Universal Windows Platform/WinRT versus Windows), two main output types are possible: a Windows Runtime sandbox (MSVC environment only or an installation tree for Windows desktop applications.
    
    *  A QML module is a bundle of QML documents that share a namespace. It exposes a list of QML and JS files as types and resources, with specific version numbers. [https://doc.qt.io/qt-5/qtqml-modules-topic.html ]
    
    *  Defining a QML module requires the presence of a qmldir file in the folder containing the types to be exposed.
    
    *  Qt Resource Collection file (.qrc), is an XML file that indexes a group of application resources and makes them accessible through the powerful Qt resource system. [https://doc.qt.io/qt-5/resources.html] 
    
    *  To know more about Qt's resolution independence capabilities and other scalability-related issues, take a look at https://doc.qt.io/qt-5/scalability.html
    
    *  A QML file whose name begins with an upper case letter is automatically recognized by Qt as a new QML type, and will be available for import in other files as such. 
    
    *  Item is the base type in Qt Quick's type hierarchy. It is a visual (it has a geometry, a position, and so on) but not a visible type.
    
    *  Qt Quick Layouts system provides four container types: ColumnLayout, GridLayout, RowLayout, and StackLayout.
    
    *  One of the most important things to remember regarding layouts is that the sizing behavior of their children should be defined via the children's Layout.preferredWidth and Layout.preferredHeight attached properties (or other compatible options), rather than width and height.
    
    *  QML provides a much simpler non-visual type, Repeater, which exposes model and delegate properties (pretty much as ListView does), and creates replicas of the QML component specified as a delegate, based on the model's characteristics.
    
    *  Qt Multimedia is a cross-platform solution for interfacing with media sources (both video and audio) and exposes both a QML and a (currently richer) C++ API. It is a vast collection of QML types and C++ classes, which provides common recipes for different multimedia needs.
    * 
    *  

----------------------------------------------------------------------------------
* One is the core Qt functionality that is implemented in a standard C++ language, which is essentially platform-independent. The other is a set of small plugins that implement a so-called **_Qt Platform Abstraction (QPA)_** that contains all the platform-specific code related to creating windows, drawing on surfaces, using fonts, and so on. Therefore, porting Qt to a new platform in practice boils down to implementing the QPA plugin for it, provided the platform uses one of the supported standard C++ compilers.

* **_XCB (X protocol C-language Binding)_** is a library implementing the client-side of the X11 display server protocol. XCB is written in the C programming language and distributed under the MIT License. 

* Bringing Qt to new platforms and less powerful hardware required a new approach to create user interfaces and to make them more lightweight, fluid, and eye candy. Nokia engineers working on Qt came up with a new declarative language to develop such interfaces the **_Qt Modeling Language (QML)_** and a Qt runtime for it called **_Qt Quick_**.

* In Qt 5 the whole framework was refactored into a different set of modules

* An object-oriented 2D graphics canvas called Graphics View

* In Qt 4, the Qt Quick framework was implemented on top of _Graphics View_. This proved to be too slow when used with low-end hardware even with OpenGL ES acceleration enabled. This new version of Qt Quick instead uses a _scene-graph_ approach.

* When using Microsoft compilers, you can choose whether to use native OpenGL drivers (the versions with the OpenGL suffix) or to emulate OpenGL ES using DirectX calls.

* A complete build configuration is called a **_kit_**. It consists of a Qt installation and a compiler that will be executed to perform the build.

* **_shadow building_** (that is, building your project outside the source code directory tree).

* Instead of nmake, you can use a tool called **_jom_** that is bundled with Qt. It will reduce the compilation time on multicore machines, which is what the default nmake tool can't do. For make and mingw32-make, you can pass the -j N parameter, where N stands for the number of cores in your machine.

* QApplication is a singleton class that manages the whole application. In particular, it is responsible for processing events that come from within the application or from external sources.

* Layouts allow us to arrange the content of a widget, making sure that its space is used efficiently. QLayout class  
  * QHBoxLayout
  * QVBoxLayout
  * QGridLayout
  * QFormLayout
  * QStackedLayout

* This is because each widget has an attribute called a size policy, which decides how a widget is to be resized by a layout. default size is returned by the sizeHint virtual method.

* with every QObject subclass, there is a special object associated that contains information about that class. It allows us to make runtime queries to learn useful things about the class—the class name, superclass, constructors, methods, fields, enumerations, and so on.

* Code of the class is preprocessed by a special **_Meta-Object Compiler (moc)_** tool

* To trigger functionality as a response to something that happens in an application, Qt uses a mechanism of **_signals and slots_**. This is based on connecting a notification (which we call a signal) about a change of state in some object with a function or method (called a slot) that is executed when such a notification arises.

* Since Qt 5, there are a couple of different connect syntax available that don't require a metaobject for the class implementing the **_slot_**. The QObject legacy is still a requirement though, and the meta-object is still required for the class that emits the signal.

  1. Macro based signal/slot mechanism: SIGNAL/SLOT -> arguments should match exactly

  2. Pointer based signal/slot mechanism: (&QPushButton::Cliced), the slot can be any member function of any QObject subclass that has argument types that match the signal or such that can be converted to match the signal.

  3. Signal connected to a standalone function: useful if you want to invoke a slot with a fixed argument value that can't be carried by a signal because it has less arguments  

* When a slot is invoked, a pointer to the object that caused the signal to be sent is accessible through a special method in QObject called sender().

* Qt meta-objects also give programmers an ability to use the so-called **_properties_** that are essentially named attributes that can be assigned values of a particular type.

* To create a property, we first need to declare it in a private section of a class that inherits QObject using a special **_Q_PROPERTY_** macro

    Q_PROPERTY(double height READ height)  
    Q_PROPERTY(double height READ height WRITE setHeight)

* QVariant, which behaves a lot like a C union in the way that it can store values of different types.

* **_Widget Accelerators_**: keyboard shortcuts that, when activated, cause particular widgets to gain keyboard focus or perform a predetermined action.

* QT forms are XML files. As part of the build process, Qt calls a special tool called **_User Interface Compiler (uic)_** that reads the file and generates a C++ class that contains a setupUi() method.

* **_QAction_** represents a functionality that can be invoked by a user. The QAction class provides an abstract user interface action that can be inserted into widgets.

* Qt allows us to embed arbitrary files (such as images for icons) directly in the application executable. This is done by preparing resource files that are later compiled in the binary.

* Image file is transformed into a C data array code and integrated with the application binary.

* The **qApp** special macro represents a pointer to the application object instance

* In Qt5, '*QSignalMapper::QSignalMapper(QObject*)*' is deprecated. The same functionality can be achieved using lambda functions.

* Text in Qt is internally encoded using Unicode, which allows to represent characters in almost all languages

* Contrary to the QString class, the C++ language does not use Unicode by default. Thus, each string literal ( each bare text wrap in quotation marks) needs to be converted to Unicode first before it can be stored in any of Qt's string handling classes.

* **International Components for Unicode (ICU)** is an open source project of mature C/C++ and Java libraries for Unicode support, software internationalization, and software globalization. ICU is widely portable to many operating systems and environments. 

* ```toInt()```, ```toDouble()```, or ```toLongLong()``` extract numerical values from strings. static method ```number()``` convert numerical value to textual representation.  

  ```QString txt = QString::number(255, 16); // txt = "0xFF"```

* ```QString``` to/from ```std::string```: ```toStdString()``` and
```fromStdString()```

* Qt allows to specify positional parameters in strings and then replace them with real values. Positions in the string are marked with the % sign (for example, %1, %2, and so on) and they are replaced by making a call to arg()

  ```cpp
  QString str = QStringLiteral("Copying file %1 of %2").arg(current).arg(total);
  ```

* Even though there are many flavors of the regular expression's syntax, the one that Perl uses has become the de facto standard. According to QRegularExpression, Qt offers Perl compatible regular expressions.

* **QRegularExpression** was first introduced with Qt 5. In the previous versions, older **QRegExp** class is used. Since QRegularExpression is closer to the Perl standard and its execution speed is much faster compared to QRegExp.

* ````QRegularExpression regex("[1-9][0-9]{0,2}[ ]? (mg|g|kg)");regex.setPatternOptions(QRegularExpression:: CaseInsensitiveOption);````

* Named groups inside the pattern, for example, if you have written (?<number> 1-9][0-9]{0,2}), then you can get the digits by calling match.captured("number").

* Regular Expression related methods in Qt
  * QRegularExpression
  * QRegularExpressionMatch
  * QRegularExpressionMatchIterator

* QFile map() and unmap() calls add and remove mappings of the parts of a file to a memory address that you can then use like a regular array of bytes.

* **QIODevice** is a Qt interface that is used to abstract entities related to reading and writing. (sequential (like socket) and random access (like file) devices.)

* **QBuffer** class that implements the QIODevice API and acts as an adapter for QByteArray or QString

* The `QTextStream` class operates on any `QIODevice` API in a stream-oriented way. You can send tokens to the stream using the << operator, where they get converted into strings, separated by spaces, encoded using a codec of your choice, and written to the underlying device.

* `QTextStream` can operate on standard C file structures, write to stdout or read from stdin

  ```cpp
  QTextStream qout(stdout);
  qout << "This text goes to process standard output." << endl;
  ```

* **Data serialization**
 Storing object data in a device-independent way so that it can be restored later, possibly on a different machine with a different data layout and so on. In computer science, this is called serialization.

* `QTextStream` serialize and deserialize data to a text format.

* `QDataStream` class handles serialization and deserialization of arbitrary data to a binary format. It uses a custom data format to store and retrieve data from QIODevice in a platform-independent way.

* **XML** has become one of the most popular standards that is used to store hierarchical data. Difficul to read by human eye but very easy to read by machines.

* Qt provides support for reading and writing XML documents in two modules. **QtXml**  and **QtCore** modules. QtXml provides access using the **Document Object Model  (DOM)** standard.

* One of the downsides of `QDomDocument` is that it requires us to load the whole XML tree into the memory before parsing it.

* `QXmlStreamReader` and `QXmlStreamWriter`

* `QStringRef` represents a string reference â€” a substring in an existing stringâ€”and is implemented in a way that avoids expensive string construction; therefore, it is very fast.

* **JSON** stands for **JavaScript Object Notation**, which is a popular lightweight textual format that is used to store object-oriented data in a human-readable form.

* JSON can express two kinds of entities: objects (enclosed in braces) and arrays (enclosed in square brackets) where an object is defined as a set of key-value pairs, where a value can be a simple string, an object, or array.

* Qt can create and read JSON descriptions using the `QJsonDocument` class.

* `QSettings` class uses different backends on different platforms, such as system registry on Windows or INI files on Linux. correlated settings can be put into named groups. To operate on a group, you can use the `beginGroup()` and `endGroup()`.

* Qt splits graphics domain into two separate parts. **raster graphics** (used by widgets, for example). This part focuses on using high-level operations (such as drawing lines or filling rectangles) to manipulate colors of a grid of points that can be visualized on different devices, such as images or the display of your computer device. The other is **vector graphics**, which involves manipulating vertices, triangles, and textures. This is tailored for maximum speed of processing and display using hardware acceleration provided by modern graphics cards.

* Qt abstracts graphics by using the concept of a surface that it draws on. The surface (represented by the `QSurface` class) can be of one of two types `RasterSurface` or `OpenGLSurface`.

* Qt's drawing architecture consists of three parts
  * `QPaintDevice`: the device the drawing takes place on. Qt provides a number of paint device subclasses such as `QWidget` or `QImage` and `QPrinter` or `QPdfWriter`.
  * `QPaintEngine`: The paint engine responsible for performing the actual paint operations on a particular paint device.
  * `QPainter`: An adapter for the whole painting framework. It contains a set of high-level operations that can be invoked on the paint device.

* `QPainter` class API
  * painter attributes: font, pen, and brush.
  * draw and fill methods
  * manipulating the coordinate system

* font size (either in points or device-dependent pixels)

* `QFontDatabase` class provides information about available fonts (such as whether a particular font is scalable or bitmap or what writing systems it supports) and allows adding new fonts into the registry by loading their definitions directly from files.

* `QFontMetrics` class allows calculating how much space is needed to paint particular text using a font or calculates text eliding.

  ````cpp
  QFontMetrics fm = painter.fontMetrics();
  QRect rect = fm.boundingRect("Game Programming using Qt");
  ````

* pen defines the outline, and the brush fills the shapes drawn using the painter. Any brush can be used as a pen.

* color is made up of four attributes—three color components (red, green, and blue) and an optional alpha channel value that determines transparency of the color (the larger the value, the more opaque the color).

* `QBrush` has two additional ways of expressing the fill of a shape.

  `QBrush::setTexture()` to set a pixmap that will be used as a stamp or
  `QBrush::setGradient()` to make the brush use a gradient to do the filling.

* 

Calling QML function from C++
```c++
QQmlEngine engine;
QQmlComponent component(&engine, "MyItem.qml");
QObject *object = component.create();

QVariant returnedValue;
QVariant msg = "Hello from C++";
QMetaObject::invokeMethod(object, "myQmlFunction",
    Q_RETURN_ARG(QVariant, returnedValue),
    Q_ARG(QVariant, msg));

qDebug() << "QML function returned:" << returnedValue.toString();
delete object;
```
[Invoking QML Methods](https://doc.qt.io/qt-5/qtqml-cppintegration-interactqmlfromcpp.html#invoking-qml-methods)

Animation types will interpolate property values to create smooth transitions.

These *property animations* apply smooth movements by interpolating values between property value changes. Property animations provide timing controls and allows different interpolations through *easing curves*.

**Qt Quick States** are property configurations where a property may have different values to reflect different states. State changes introduce abrupt property changes; animations smooth transitions to produce visually appealing state changes. The **Transition** type can contain animation types to interpolate property changes caused by state changes.

```cpp
QVariant variant = QVariant::fromValue<QColor>(QColor(Qt::red));
QColor color = variant.value<QColor>(); // read back
qDebug() << variant.typeName(); // QColor
```

Any QObject-derived class can be registered as a qml type or injected into the QML context.

Injection of a c++ object into the qml context, making it a global object accessible to the qml engine.

Registering your c++ object as a type in QML
`qmlRegisterType()`
`qmlRegisterInterface()`
`qmlRegisterUncreatableType()`
`qmlRegisterSingletonType()`

