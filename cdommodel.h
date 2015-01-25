/*=============================================================================
This is a Program to demonstrate a trivial treeview sorting with combobox on.
header
Copyright (C) 2015  Pradyumna Pramod Saraph
Contact: prady.pps@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the Lesser GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
Lesser GNU General Public License for more details.

You should have received a copy of the Lesser GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
=============================================================================*/
#ifndef CDOMMODEL_H
#define CDOMMODEL_H

#include <QAbstractItemModel>
#include <QDomDocument>
#include <QModelIndex>


class CDomItem;

//! [0]
class CDomModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit CDomModel(QDomDocument document, QObject *parent = 0);
    ~CDomModel();
    void Clear();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    CDomItem* getItem(const QModelIndex &index) const;
    const QDomDocument& GetDocument() const {
        return domDocument;
    }

private:
    QDomDocument domDocument;
    CDomItem *rootItem;
};

#endif // CDOMMODEL_H
