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
using std::vector;
using std::string;

class ListModel : public QAbstractListModel, public Observer {
private:
	LocatarService& srv;
	int selectedItem{ -1 };
public:
	ListModel(QObject* parent, LocatarService& srv);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return srv.getAllService().size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 1;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void update() override {
		emit layoutChanged();
	}

	//modificam selectdeItem-ul
	//date de intrare:-item-int
	//date de iesire:-
	void setSelectedItem(int item);
};

class TableModel :public QAbstractTableModel, public Observer {
private:
	LocatarService& srv;
public:

	/*constructor
	* date de intrare:parent-pointer la QObject
	*				  srv-referinta la LocatarService
	* date de iesire:-
	*/
	TableModel(QObject* parent, LocatarService& srv);
	/**
	* number of rows
	*/
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* number of columns
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* Value at a given position
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	
	//update table
	void update() override {
		emit layoutChanged();
	}

	//initializam capul de tabel
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

class TableModel1 :public QAbstractTableModel{
private:
	vector<Locatar> locatari;
public:
	/*constructor
	* date de intrare:parent-pointer la QObject
	*				  lov-referinta la vector
	* date de iesire:-
	*/
	TableModel1(QObject* parent, const vector<Locatar>& loc);
	/**
	* number of rows
	*/
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* number of columns
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* Value at a given position
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	//initializam capul de tabel
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

class ListModelNotificari : public QAbstractListModel, public Observer {
private:
	LocatarService& srv;
public:

	/*constructor
	* date de intrare:parent-pointer la QObject
	*				  srv-referinta la LocatarService
	* date de iesire:-
	*/
	ListModelNotificari(QObject* parent, LocatarService& srv);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return srv.getAllLista().size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 1;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	//update lista
	void update() override {
		emit layoutChanged();
	}
};

class TableModelNotificari :public QAbstractTableModel, public Observer {
private:
	LocatarService& srv;
public:

	/*constructor
	* date de intrare:parent-pointer la QObject
	*				  srv-referinta la LocatarService
	* date de iesire:-
	*/
	TableModelNotificari(QObject* parent, LocatarService& srv);
	/**
	* number of rows
	*/
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* number of columns
	*/
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	/**
	* Value at a given position
	*/
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	//update tabel
	void update() override {
		emit layoutChanged();
	}

	//initializam capul tabelului
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};


