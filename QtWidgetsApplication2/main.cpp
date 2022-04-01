#include "QtWidgetsApplication2.h"
#include <QtWidgets/QApplication>
#include "LocatarRepository.h"
#include "ValidareLocatar.h"
#include "ListaNotificari.h"
#include "LocatarService.h"
#include "LocatarRepositoryFile.h"
#include "ExceptionRepo.h"
#include <iostream>
#include <string>
#include "Teste.h"
#include "UI.h"
#include "Exceptii.h"
#include "GUI.h"
#include "MyGUIModel.h"
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LocatarRepository repo;
    ValidareLocatar val;
    ListaNotificari lista;
    LocatarService srv{ repo, val, lista };
    UI app(srv);
    app.UIadauga(); 
    /*GUI myGUI(srv);
    QPalette pal = myGUI.palette();
    pal.setColor(QPalette:: Window, Qt::lightGray);
    pal.setColor(QPalette::Base, Qt::gray);
    pal.setColor(QPalette::Shadow, Qt::lightGray);
    myGUI.setAutoFillBackground(true);
    myGUI.setPalette(pal);
    myGUI.show();*/

    MyGUIModel myGUI(srv);
    QPalette pal = myGUI.palette();
    pal.setColor(QPalette::Window, Qt::lightGray);
    pal.setColor(QPalette::Base, Qt::gray);
    pal.setColor(QPalette::Shadow, Qt::lightGray);
    myGUI.setAutoFillBackground(true);
    myGUI.setPalette(pal);
    myGUI.show();
    return a.exec();
}
