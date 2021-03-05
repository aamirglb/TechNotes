# Qt and QML programming

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

