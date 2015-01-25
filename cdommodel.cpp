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
#include "cdomItem.h"
#include "cdommodel.h"
#include "ccommondefines.h"

#include <QtXml>
#include <QDateTime>
#include <QFont>
#include <QColor>

CDomModel::CDomModel(QDomDocument document, QObject *parent)
    : QAbstractItemModel(parent), domDocument(document) {
    rootItem = new CDomItem(domDocument, 0);
}

CDomModel::~CDomModel() {
    if(rootItem) {
        delete rootItem;
        rootItem = NULL;
    }
}

int CDomModel::columnCount(const QModelIndex &/*parent*/) const {
    return ColumnCount;
}

QVariant CDomModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::ToolTipRole) {
        CDomItem *item = static_cast<CDomItem*>(index.internalPointer());
        QDomNode node = item->node();
        QDomNamedNodeMap attributeMap = node.attributes();
        QString strTextToDisplay;
        switch (index.column()) {
        case Name: {
            if(index.parent().isValid() && !node.hasChildNodes()) {
                QDomNode objParent = node.parentNode();
                QDomNamedNodeMap objParentattributeMap = objParent.attributes();
                if(!objParentattributeMap.namedItem(NAME_ATTRIB).nodeValue().
                        compare(attributeMap.namedItem(NAME_ATTRIB).nodeValue())) {
                    return strTextToDisplay;
                }
            }
            strTextToDisplay = attributeMap.namedItem(NAME_ATTRIB).nodeValue();
            return strTextToDisplay;
        }

        case Author: {
            strTextToDisplay =  attributeMap.namedItem(AUTHOR_ATTRIB).nodeValue();
            return strTextToDisplay;
        }

        case Publisher:
            strTextToDisplay =  attributeMap.namedItem(PUBLISHER_ATTRIB).nodeValue();
            return strTextToDisplay;

        case Pages: {
            strTextToDisplay =  attributeMap.namedItem(PAGES_ATTRIB).nodeValue();
            return strTextToDisplay;
        }
        case Year: {
            strTextToDisplay =  attributeMap.namedItem(YEAR_ATTRIB).nodeValue();
            return strTextToDisplay;
        }
        default:
            return QVariant();
        }

    }
    return QVariant();
}

Qt::ItemFlags CDomModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;
    Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        theFlags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled;
    }
    return theFlags;
}

QVariant CDomModel::headerData(int section, Qt::Orientation orientation,
                               int role) const {
    //We have our own header Widget
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);
    return QVariant();
}

QModelIndex CDomModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CDomItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CDomItem*>(parent.internalPointer());

    CDomItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CDomModel::parent(const QModelIndex &child) const {
    if (!child.isValid())
        return QModelIndex();

    CDomItem *childItem = static_cast<CDomItem*>(child.internalPointer());
    CDomItem *parentItem = childItem->parent();

    if (!parentItem || parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int CDomModel::rowCount(const QModelIndex &parent) const {
    if (parent.column() > 0)
        return 0;

    CDomItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<CDomItem*>(parent.internalPointer());

    return parentItem->node().childNodes().count();
}

CDomItem *CDomModel::getItem(const QModelIndex &index) const {
    if (index.isValid()) {
        CDomItem *item = static_cast<CDomItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

void CDomModel::Clear() {
    reset();
}
