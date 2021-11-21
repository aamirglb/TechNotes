#pragma once
#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class IconEditorPlugin : public QObject,
                         public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
    #if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        Q_PLUGIN_METADATA(IID "iconeditorplugin" FILE "iconeditorplugin.json") 
    #endif

public:
    IconEditorPlugin(QObject *parent = nullptr);

    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget *createWidget(QWidget *parent);
};