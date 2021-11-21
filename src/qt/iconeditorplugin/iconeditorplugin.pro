TEMPLATE   = lib
CONFIG    += plugin release
QT        += designer 
HEADERS    = ../iconeditor/iconeditor.h iconeditorplugin.h
SOURCES    = ../iconeditor/iconeditor.cpp iconeditorplugin.cpp
RESOURCES  = iconeditorplugin.qrc
#DESTDIR    = $$[QT_INSTALL_PLUGIN]/designer
#message($$QT_INSTALL_PLUGIN)
#message(qmake file in value = $$[QTDIR])

#for(var, $$list($$enumerate_vars())) {
#    message($$var)
#    #message($$eval($$var))
#}