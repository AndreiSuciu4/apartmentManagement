#include <qwidget.h>
#include <QtWidgets/QApplication>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QItemSelectionModel>
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
#include <QPoint>
using std::vector;
using std::string;

//clasa pentru a afisa un tabel
class tabel :public QDialog {
private:
	vector<Locatar>locatari;
	QHBoxLayout* box;

	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();
public:
	/*constructor
	* date de intrare:-locatar-vector
	* date de iesire:-
	*/
	tabel(vector<Locatar> locatar) :locatari{locatar} {
		init();
	}
};

class tabelDetalii :public QDialog {
private:
	Locatar locatar;
	QLineEdit* apartament;
	QLineEdit* nume;
	QLineEdit* suprafata;
	QLineEdit* tipApartament;
	/*initilizare
	date de intrare:-
	date de iesire:-
	*/
	void init();
public:
	/*constructor
	* date de intrare:-locatar-vector
	* date de iesire:-
	*/
	tabelDetalii(Locatar locatar) :locatar{ locatar } {
		init();
	}
};

//clasa pentru lista de notificari
class listNotificariGUI : public QWidget {
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
	void loadList(vector<Locatar>,int numar);

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
	listNotificariGUI(LocatarService& srv) :srv{srv} {
		init();
		loadList(srv.getAllService(),0);
		connect();
	}
};

class CosCRUDGUI : public QWidget, public Observer {
private:
	LocatarService& srv;
	//box-uri
	QHBoxLayout* principalBox;
	QVBoxLayout* box;
	QHBoxLayout* box1;
	QTableWidget* table;

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
	CosCRUDGUI(LocatarService& srv) :srv{ srv } {
		init();
		loadTable(srv.getAllLista(), srv.nrApartamenteLista());
		connect();
	}

};

class CosV2CRUDGUI : public QWidget, public Observer {
private:
	LocatarService& srv;
	//box-uri
	QHBoxLayout* principalBox;
	QVBoxLayout* box;
	QHBoxLayout* box1;
	QListWidget* list;

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
	CosV2CRUDGUI(LocatarService& srv) :srv{ srv } {
		init();
		loadList(srv.getAllLista(), srv.nrApartamenteLista());
		connect();
	}

};

class CosReadOnlyGUI :public QWidget, public Observer {

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
	CosReadOnlyGUI(LocatarService& srv) :srv{ srv } {
		this->setWindowTitle("Fereastra CosReadOnlyGUI");
		srv.addObserver(this);
	}

	void paintEvent(QPaintEvent* ev) override {
		
		QPainter p{ this };
		vector<string>imagini = { "imagine.jpq", "patrat.jpg", "cerc.jpg", "caprioara.jpg" };
		for(int i = 0; i< srv.nrApartamenteLista(); i++)
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

class GUI:public QWidget
{
private:
	LocatarService& srv;
	//box-uri
	QHBoxLayout* principalBox;
	QVBoxLayout* box;
	QHBoxLayout* box1;
	QHBoxLayout* box2;
	QHBoxLayout* box3;
	QHBoxLayout* box4;
	QHBoxLayout* box5;
	QLabel* mesaj;
	QVBoxLayout* buttAndLines;
	QHBoxLayout* buttons ;

	//butoane
	QPushButton* adauga;
	QPushButton* afisare;
	QPushButton* sterge;
	QPushButton* cauta;
	QPushButton* modifica;
	QPushButton* filtrare;
	QPushButton* filtrareTip;
	QPushButton* filtrareSuprafata;
	QPushButton* sortare;
	QPushButton* sortareSuprafata;
	QPushButton* sortareNume;
	QPushButton* sortareTipSuprafata;
	QPushButton* undo;
	QPushButton* listaNotificari;
	QPushButton* CosCRUD;
	QPushButton* CosV2CRUD;
	QPushButton* CosReadOnly;
	QPushButton* adaugaCos;
	QPushButton* Export;
	QPushButton* genereaza;
	QPushButton* exit;

	//QLineEdit
	QLineEdit* apartament;
	QLineEdit* nume;
	QLineEdit* suprafata;
	QLineEdit* tipApartament;
	QLineEdit* fisier;
	QLineEdit* nrApart;

	//lista
	QListWidget* list;
	QTableWidget* table;
	//functii

	QListWidgetItem* selectedItem = nullptr;

	/*init
	* date de intrare:-
	* date de iesire:-
	*/
	void init();

	/*afisare lista utilizand QListWidget
	* date de intrare:-vector de Locatar
	* date de iesire:
	*/
	void loadList(vector<Locatar>);

	/*
	* conectam butoanele cu functiile
	* date de intrare:
	* date de iesire:
	*/
	void connect();

	/*conectam butonul adauga cu functia de adaugare din service
	* date de intrare:
	* date de iesire:
	*/
	void adaugaLocatar();

	/*conectam butonul afisare cu functia getALL din service
	* date de intrare:
	* date de iesire:
	*/
	void afisareLocatar();

	/*conectam butonul sterge cu functia de stergere din service
	* date de intrare:
	* date de iesire:
	*/
	void stergeLocatar();

	/*conectam butonul cauta cu functia de cautare din service
	* date de intrare:
	* date de iesire:
	*/
	void cautaLocatar();

	/*conectam butonul modifica cu functia de modificare din service
	* date de intrare:
	* date de iesire:
	*/
	void modificaLocatar();

	/*conectam butonul filtrare la butoanele filtreTip si filtrareSuprafata
	* date de intrare:
	* date de iesire:
	*/
	void filtrareButton();

	/*conectam butonul filtrareTip cu functia de filtrare dupa tipul apartamentului din service
	* date de intrare:
	* date de iesire:
	*/
	void filtrareTipApart();

	/*conectam butonul filtrareSuprafata cu functia de filtrare dupa suprafata din service
	* date de intrare:
	* date de iesire:
	*/
	void filtrareSupra();

	/*conectam butonul sortare la butoanele sortareSuprafata, sortareNume si sortareTipSuprafata
	* date de intrare:
	* date de iesire:
	*/
	void sortareButton();

	/*conectam butonul sortareSuprafata cu functia de sortare dupa suprafata din service
	* date de intrare:
	* date de iesire:
	*/
	void sortSuprafata();

	/*conectam butonul sortareNume cu functia de sortare dupa nume din service
	* date de intrare:
	* date de iesire:
	*/
	void sortNume();

	/*conectam butonul sortareTipSuprafata cu functia de sortare dupa tip sisuprafata din service
	* date de intrare:
	* date de iesire:
	*/
	void sortTipSuprafata();

	/*conectam butonul undo cu functia undo din service
	* date de intrare:
	* date de iesire:
	*/
	void Undo();

	//void update()override;

	void tab(vector<Locatar>);

public:
	GUI(LocatarService& srv) :srv{ srv } {
		init();
		loadList(srv.getAllService());
		connect();
		tab(srv.getAllService());
	}
};
