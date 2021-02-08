# Notes Related to Qt and QML programming

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