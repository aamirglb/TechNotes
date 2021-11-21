#include "iconeditorplugin.h"
#include "../iconeditor/iconeditor.h"

IconEditorPlugin::IconEditorPlugin(QObject *parent)
    : QObject(parent)
{
}

QString IconEditorPlugin::name() const {
    return "IconEditor";
}

QString IconEditorPlugin::includeFile() const {
    return "iconeditor.h";
}

QString IconEditorPlugin::group() const {
    return tr("Image Manipulation Widgets");
}

QIcon IconEditorPlugin::icon() const {
    return QIcon(":/images/iconeditor.png");
}

QString IconEditorPlugin::toolTip() const {
    return tr("An icon editor widget");
}

QString IconEditorPlugin::whatsThis() const {
    return tr("Custom Qt Widget.");
}

bool IconEditorPlugin::isContainer() const {
    return false;
}

QWidget *IconEditorPlugin::createWidget(QWidget *parent) {
    return new IconEditor(parent);
}

// Q_EXPORT_PLUGIN2(iconeditorplugin, IconEditorPlugin)
