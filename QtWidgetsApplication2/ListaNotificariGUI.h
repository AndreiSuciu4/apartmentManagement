#pragma once
#include <qwidget.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qobject.h>
#include <qtablewidget.h>
#include <qmessagebox.h>
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
#include <vector>
#include <qpainter.h>
#include "Observer.h"
#include <string>
#include <QPoint>
#include <qobject.h>
#include <QTableView>
#include <qcombobox.h>
#include "Modele.h"
using std::vector;
using std::string;

//clasa pentru lista de notificari
class listNotificariGUI1 : public QWidget {
private:
	LocatarService& srv;
	//box-uri
	QHBoxLayout* principalBox;
	QVBoxLayout* box;
	QHBoxLayout* box1;
	QHBoxLayout* box2;
	QHBoxLayout* box3;
	QListWidget* list;

	//butoane
	QPushButton* adauga;
	QPushButton* sterge;
	QPushButton* genereaza;
	QPushButton* Export;
	QPushButton* afisare;
	QPushButton* exit;

	//QLineEdit
	QLineEdit* apartament;
	QLineEdit* numarApartamente;
	QLineEdit* numeFisier;

	//afiseaza lista de locatari din lista de notificari
	//date de intrare:-locatari:-vector
	//                -numar:-int
	//date de iesire:-
	void loadList(vector<Locatar>, int numar);

	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();

	/*
* conectam butoanele
* date de intrare:
* date de iesire:
*/
	void connect();

public:
	//constructor
	//date de intrare:-srv-referinta la LocatarService
	//date de iesire:-
	listNotificariGUI1(LocatarService& srv) :srv{ srv } {
		init();
		loadList(srv.getAllService(), 0);
		connect();
	}
};

class CosCRUDGUI1 : public QWidget, public Observer {
private:
	LocatarService& srv;
	//box-uri
	QHBoxLayout* principalBox;
	QVBoxLayout* box;
	QHBoxLayout* box1;

	TableModelNotificari* model;
	QTableView* tabel;

	//butoane
	QPushButton* sterge;
	QPushButton* genereaza;
	QPushButton* exit;

	//QLineEdit
	QLineEdit* numarApartamente;
	QLineEdit* apart;

	//afisare tabel din lista de notificari
	//date de intrare:-locatari:-vector
	//                -numar:-int
	//date de iesire:-
	void loadTable(vector<Locatar>, int numar);

	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();

	//functie de update
	//date de intrare:-
	//date de isire:-
	void update() override;

	/*
* conectam butoanele
* date de intrare:
* date de iesire:
*/
	void connect();

public:
	//constructor
	//date de intrare:-srv-referinta la LocatarService
	//date de iesire:-
	CosCRUDGUI1(LocatarService& srv) :srv{ srv } {
		init();
		loadTable(srv.getAllLista(), srv.nrApartamenteLista());
		connect();
	}

};

class CosV2CRUDGUI1 : public QWidget, public Observer {
private:
	LocatarService& srv;
	//box-uri
	QHBoxLayout* principalBox;
	QVBoxLayout* box;
	QHBoxLayout* box1;

	QListView* lista;
	ListModelNotificari* modelLista;

	//butoane
	QPushButton* sterge;
	QPushButton* genereaza;
	QPushButton* exit;

	//QLineEdit
	QLineEdit* numarApartamente;
	QLineEdit* apart;

	//afisare tabel din lista de notificari
	//date de intrare:-locatari:-vector
	//                -numar:-int
	//date de iesire:-
	void loadList(vector<Locatar>, int numar);

	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();

	//functie de update
	//date de intrare:-
	//date de isire:-
	void update() override;

	/*
* conectam butoanele
* date de intrare:
* date de iesire:
*/
	void connect();

public:
	//constructor
	//date de intrare:-srv-referinta la LocatarService
	//date de iesire:-
	CosV2CRUDGUI1(LocatarService& srv) :srv{ srv } {
		init();
		loadList(srv.getAllLista(), srv.nrApartamenteLista());
		connect();
	}

};

class CosReadOnlyGUI1 :public QWidget, public Observer {

private:
	LocatarService& srv;

	//functie de update
	//date de intrare:-
	//date de isire:-
	void update() override {
		repaint();
	}

public:

	/*constructor
	* date de intrare:-srv-referinta la LocatarService
	* date de iesire :-
	*/
	CosReadOnlyGUI1(LocatarService& srv) :srv{ srv } {
		this->setWindowTitle("Fereastra CosReadOnlyGUI");
		this->setWindowIcon(QIcon("listaNotificari.jpg"));
		srv.addObserver(this);
	}

	void paintEvent(QPaintEvent* ev) override {

		QPainter p{ this };
		vector<string>imagini = { "imagine.jpq", "patrat.jpg", "cerc.jpg", "caprioara.jpg" };
		for (int i = 0; i < srv.nrApartamenteLista(); i++)
		{
			float x = (float)rand() / RAND_MAX;
			float y = (float)rand() / RAND_MAX;
			int numar = rand() % imagini.size();
			//p.drawImage(numar*500, 0, QImage(QString::fromStdString ("cerc.jpg")));


			//int numar = rand() % 4;
			if (numar == 3) {
				p.setBrush(Qt::yellow);
				p.drawEllipse(500 * x, 500 * y, 400 * x, 500 * y);

			}
			if (numar == 2) {
				p.setBrush(Qt::green);
				p.drawRect(500 * x, 500 * y, 500 * x, 500 * y);
			}
			if (numar == 1) {
				p.setBrush(Qt::red);
				QPointF* points = new QPointF[3];
				points[0] = QPointF(500 * x, 500 * y);
				x = (float)rand() / RAND_MAX;
				y = (float)rand() / RAND_MAX;
				points[1] = QPointF(500 * x, 500 * y);
				x = (float)rand() / RAND_MAX;
				y = (float)rand() / RAND_MAX;
				points[2] = QPointF(500 * x, 500 * y);
				p.drawPolygon(points, 3);
			}
			if (numar == 0) {
				p.setBrush(Qt::magenta);
				QPointF* points = new QPointF[4];
				points[0] = QPointF(500 * x, 500 * y);
				x = (float)rand() / RAND_MAX;
				y = (float)rand() / RAND_MAX;
				points[1] = QPointF(500 * x, 500 * y);
				x = (float)rand() / RAND_MAX;
				y = (float)rand() / RAND_MAX;
				points[2] = QPointF(500 * x, 500 * y);
				x = (float)rand() / RAND_MAX;
				y = (float)rand() / RAND_MAX;
				points[3] = QPointF(500 * x, 500 * y);
				p.drawPolygon(points, 3);
			}
		}

	}

};

