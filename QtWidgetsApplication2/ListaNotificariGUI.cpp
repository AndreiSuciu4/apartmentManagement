#include "ListaNotificariGUI.h"
#include "MyGUIModel.h"

void CosCRUDGUI1::update()
{
	loadTable(srv.getAllLista(), srv.nrApartamenteLista());
}

//initializare
//date de intrare:-
//date de isire:-

//afiseaza lista de locatari din lista de notificari
//date de intrare:-locatari:-vector
//                -numar:-int
//date de iesire:-
void listNotificariGUI1::loadList(vector<Locatar>, int numar)
{
	list->clear();
	for (const auto& l : srv.getAllLista())
		list->addItem(QString::fromStdString(l.getNume()));
	list->addItem(QString::fromStdString("numar apartamente: " + std::to_string(numar)));
}


/*initilizare
date de intrare:-
date de iesire:-
*/
void listNotificariGUI1::init()
{
	this->setWindowTitle("Lista Notificari");
	principalBox = new QHBoxLayout;
	box = new QVBoxLayout;
	box1 = new QHBoxLayout;
	box2 = new QHBoxLayout;
	box3 = new QHBoxLayout;
	list = new QListWidget;

	//butoane
	adauga = new QPushButton("&adauga");
	sterge = new QPushButton("&goleste lista");
	genereaza = new QPushButton("&genereaza lista");
	Export = new QPushButton("&export");
	afisare = new QPushButton("&afisare");
	exit = new QPushButton("&exit");

	//QLineEdit
	apartament = new QLineEdit;
	numarApartamente = new QLineEdit;
	numeFisier = new QLineEdit;

	QFormLayout* form = new QFormLayout;
	form->addRow("Apartament", apartament);
	form->addRow("Numar apartamente", numarApartamente);
	form->addRow("Nume fisier", numeFisier);


	principalBox->addWidget(list);
	principalBox->addLayout(form);
	box->addWidget(adauga);
	box->addWidget(sterge);
	box->addWidget(genereaza);
	box->addWidget(Export);
	box->addWidget(afisare);
	box->addWidget(exit);
	principalBox->addLayout(box);
	setLayout(principalBox);

	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::lightGray);
	pal.setColor(QPalette::Base, Qt::gray);
	pal.setColor(QPalette::Shadow, Qt::lightGray);
	setAutoFillBackground(true);
	setPalette(pal);
}

/*
* conectam butoanele
* date de intrare:
* date de iesire:
*/
void listNotificariGUI1::connect()
{
	//srv.addObserver(this);
	QWidget::connect(adauga, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(apartament->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.adaugaLista(apartament1);
			loadList(srv.getAllLista(), srv.nrApartamenteLista());
		}
		catch (const RepoException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		}
	);

	QWidget::connect(sterge, &QPushButton::clicked, [&]() {
		srv.golesteLista();
		loadList(srv.getAllLista(), srv.nrApartamenteLista());
		});

	QWidget::connect(genereaza, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(numarApartamente->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.genereazaLista(apartament1);
			loadList(srv.getAllLista(), srv.nrApartamenteLista());
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});

	QWidget::connect(afisare, &QPushButton::clicked, [&]() {
		auto tab = new tabel1{ srv.getAllLista() };
		tab->setModal(false);
		tab->show();

		});

	QWidget::connect(Export, &QPushButton::clicked, [&]() {
		try {
			srv.writeToFile(numeFisier->text().toStdString());
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});

	QWidget::connect(exit, &QPushButton::clicked, [&]() {
		close();
		});
}

void CosCRUDGUI1::init()
{
	this->setWindowTitle("Fereastra CosCRUDGUI");
	srv.addObserver(this);

	principalBox = new QHBoxLayout;
	box = new QVBoxLayout;
	box1 = new QHBoxLayout;

	tabel = new QTableView();
	model = new TableModelNotificari(tabel, srv);
	tabel->setModel(model);

	//butoane

	sterge = new QPushButton("&goleste lista");
	genereaza = new QPushButton("&genereaza lista");

	exit = new QPushButton("&exit");

	//QLineEdit
	numarApartamente = new QLineEdit;
	apart = new QLineEdit;
	apart->setReadOnly(true);
	QFormLayout* form = new QFormLayout;
	form->addRow("Numarul de apartamente de generat", numarApartamente);
	form->addRow("Numarul de apartamente din lista", apart);

	principalBox->addWidget(tabel);
	principalBox->addLayout(form);
	box->addWidget(sterge);
	box->addWidget(genereaza);
	box->addWidget(exit);
	principalBox->addLayout(box);
	setLayout(principalBox);

	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::lightGray);
	pal.setColor(QPalette::Base, Qt::gray);
	pal.setColor(QPalette::Shadow, Qt::lightGray);
	setAutoFillBackground(true);
	setPalette(pal);
}

/*
* conectam butoanele
* date de intrare:
* date de iesire:
*/
void CosCRUDGUI1::connect()
{
	this->setWindowTitle("Fereastra CosCRUDGUI");
	this->setWindowIcon(QIcon("listaNotificari.jpg"));

	QWidget::connect(sterge, &QPushButton::clicked, [&]() {
		srv.golesteLista();
		loadTable(srv.getAllLista(), srv.nrApartamenteLista());
		});

	QWidget::connect(genereaza, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(numarApartamente->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.genereazaLista(apartament1);
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});
	QWidget::connect(exit, &QPushButton::clicked, [&]() {
		srv.removeObserver(this);
		close();
		});
}

void CosCRUDGUI1::loadTable(vector<Locatar>locatari, int numar) {

	apart->setText(QString::number(numar));
}


void CosV2CRUDGUI1::update()
{
	loadList(srv.getAllLista(), srv.nrApartamenteLista());
}

//initializare
//date de intrare:-
//date de isire:-
void CosV2CRUDGUI1::init()
{
	this->setWindowTitle("Fereastra CosV2CRUDGUI");
	this->setWindowIcon(QIcon("listaNotificari.jpg"));

	principalBox = new QHBoxLayout;
	box = new QVBoxLayout;
	box1 = new QHBoxLayout;

	//butoane

	sterge = new QPushButton("&goleste lista");
	genereaza = new QPushButton("&genereaza lista");

	exit = new QPushButton("&exit");

	//QLineEdit
	numarApartamente = new QLineEdit;
	apart = new QLineEdit;
	apart->setReadOnly(true);
	QFormLayout* form = new QFormLayout;
	form->addRow("Numarul de apartamente de generat", numarApartamente);
	form->addRow("Numarul de apartamente din lista", apart);

	lista = new QListView();
	modelLista = new ListModelNotificari(lista, srv);
	lista->setModel(modelLista);
	lista->setUniformItemSizes(true);

	principalBox->addWidget(lista);
	principalBox->addLayout(form);
	box->addWidget(sterge);
	box->addWidget(genereaza);
	box->addWidget(exit);
	principalBox->addLayout(box);
	setLayout(principalBox);

	QPalette pal = palette();
	pal.setColor(QPalette::Window, Qt::lightGray);
	pal.setColor(QPalette::Base, Qt::gray);
	pal.setColor(QPalette::Shadow, Qt::lightGray);
	setAutoFillBackground(true);
	setPalette(pal);
}


void CosV2CRUDGUI1::connect()
{
	srv.addObserver(this);
	QWidget::connect(sterge, &QPushButton::clicked, [&]() {
		srv.golesteLista();
		});

	QWidget::connect(genereaza, &QPushButton::clicked, [&]() {
		int apartament1{ 0 };
		try {
			try {
				apartament1 = std::stoi(numarApartamente->text().toStdString());
			}
			catch (const std::invalid_argument) {
				QMessageBox::warning(this, "warning", "valoare invalida");
				return;
			}
			srv.genereazaLista(apartament1);
		}
		catch (const listaException& msg) {
			QMessageBox::warning(this, "warning", QString::fromStdString(msg.getMesaj()));
		}
		});
	QWidget::connect(exit, &QPushButton::clicked, [&]() {
		srv.removeObserver(this);
		close();
		});
}

void CosV2CRUDGUI1::loadList(vector<Locatar>locatari, int numar) {

	apart->setText(QString::number(numar));
}