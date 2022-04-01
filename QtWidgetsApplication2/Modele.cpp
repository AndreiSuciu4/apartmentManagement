#include "Modele.h"
TableModel::TableModel(QObject* parent, LocatarService& srv) : QAbstractTableModel(parent), srv{ srv }
{
	srv.addObserver(this);
}

int TableModel::rowCount(const QModelIndex& parent) const
{
	return srv.getAllService().size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		Locatar loc = srv.getAllService()[index.row()];
		if (index.column() == 0)
			return QString::number(loc.getApartament());
		if (index.column() == 1)
			return QString::fromStdString(loc.getNume());
		if (index.column() == 2)
			return QString::number(loc.getSuprafata());
		if (index.column() == 3)
			return QString::fromStdString(loc.getTipApartament());
	}

	if (role == Qt::FontRole) {
		QFont f;
		f.setItalic(index.row() >= 0);
		return f;
	}

	if (role == Qt::BackgroundRole) {
		QBrush bg(Qt::lightGray);
		return bg;
	}

	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0)
				return QString("apartament");
			if (section == 1)
				return QString("nume");
			if (section == 2)
				return QString("suprafata");
			if (section == 3)
				return QString("tip apartament");

		}
		else {
			return QString("locatarul %1").arg(section + 1);
		}
	}
	return QVariant();
}


ListModel::ListModel(QObject* parent, LocatarService& srv) : QAbstractListModel(parent), srv{ srv }
{
	srv.addObserver(this);
}

QVariant ListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		Locatar loc = srv.getAllService()[index.row()];
		if (index.column() == 0)
		{
			auto nume = QString::fromStdString(loc.getNume());
			return nume;
		}
	}

	if (role == Qt::UserRole) {
		Locatar loc = srv.getAllService()[index.row()];
		if (index.column() == 0)
			return QString::number(loc.getApartament());
	}

	if (role == Qt::BackgroundRole) {
		if (index.row() == selectedItem) {
			QBrush bg(Qt::darkGreen);
			return bg;
		}
	}

	if (role == Qt::FontRole) {
		QFont f;
		f.setItalic(index.row() % 2 == 1);
		f.setBold(index.row() >= 0);
		return f;
	}

	return QVariant();
}

void ListModel::setSelectedItem(int item)
{
	selectedItem = item;
}


TableModelNotificari::TableModelNotificari(QObject* parent, LocatarService& srv) : QAbstractTableModel(parent), srv{ srv }
{
	srv.addObserver(this);
}



int TableModelNotificari::rowCount(const QModelIndex& parent) const
{
	return srv.getAllLista().size();
}

int TableModelNotificari::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant TableModelNotificari::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		Locatar loc = srv.getAllLista()[index.row()];
		if (index.column() == 0)
			return QString::number(loc.getApartament());
		if (index.column() == 1)
			return QString::fromStdString(loc.getNume());
		if (index.column() == 2)
			return QString::number(loc.getSuprafata());
		if (index.column() == 3)
			return QString::fromStdString(loc.getTipApartament());
	}

	if (role == Qt::FontRole) {
		QFont f;
		f.setItalic(index.row() >= 0);
		return f;
	}

	if (role == Qt::BackgroundRole) {
		QBrush bg(Qt::lightGray);
		return bg;
	}

	return QVariant();
}

QVariant TableModelNotificari::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0)
				return QString("apartament");
			if (section == 1)
				return QString("nume");
			if (section == 2)
				return QString("suprafata");
			if (section == 3)
				return QString("tip apartament");

		}
		else {
			return QString("locatarul %1").arg(section + 1);
		}
	}
	return QVariant();
}


ListModelNotificari::ListModelNotificari(QObject* parent, LocatarService& srv) : QAbstractListModel(parent), srv{ srv }
{
	srv.addObserver(this);
}

QVariant ListModelNotificari::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		Locatar loc = srv.getAllLista()[index.row()];
		if (index.column() == 0)
		{
			auto nume = QString::fromStdString(loc.getNume());
			return nume;
		}
	}

	if (role == Qt::FontRole) {
		QFont f;
		f.setItalic(index.row() % 2 == 1);
		f.setBold(index.row() >= 0);
		return f;
	}

	return QVariant();
}

TableModel1::TableModel1(QObject* parent, const vector<Locatar>& loc) : QAbstractTableModel(parent), locatari{loc}
{
}

int TableModel1::rowCount(const QModelIndex& parent) const
{
	return locatari.size();
}

int TableModel1::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant TableModel1::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		Locatar loc = locatari[index.row()];
		if (index.column() == 0)
			return QString::number(loc.getApartament());
		if (index.column() == 1)
			return QString::fromStdString(loc.getNume());
		if (index.column() == 2)
			return QString::number(loc.getSuprafata());
		if (index.column() == 3)
			return QString::fromStdString(loc.getTipApartament());
	}
	return QVariant();
}

QVariant TableModel1::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0)
				return QString("apartament");
			if (section == 1)
				return QString("nume");
			if (section == 2)
				return QString("suprafata");
			if (section == 3)
				return QString("tip apartament");

		}
		else {
			return QString("locatarul %1").arg(section + 1);
		}
	}
	return QVariant();
}
