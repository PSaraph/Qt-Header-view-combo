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

#include <QtXml>

QString CDomItem::m_clsCurrentPurpose;

CDomItem::CDomItem(QDomNode &node, int row, CDomItem *parent) {
    domNode = node;
    // Record the item's location within its parent.
    rowNumber = row;
    parentItem = parent;
}

CDomItem::~CDomItem() {
    QHash<int,CDomItem*>::iterator it;
    for (it = childItems.begin(); it != childItems.end(); ++it)
        delete it.value();
}

QDomNode CDomItem::node() const {
    return domNode;
}

CDomItem *CDomItem::parent() {
    return parentItem;
}

CDomItem *CDomItem::child(int i) {
    if (childItems.contains(i))
        return childItems[i];

    if (i >= 0 && i < domNode.childNodes().count()) {
        QDomNode childNode = domNode.childNodes().item(i);
        CDomItem *childItem = new CDomItem(childNode, i, this);
        childItems[i] = childItem;
        return childItem;
    }
    return 0;
}

bool CDomItem::removeChild(int i) {
    if (childItems.contains(i)) {
        delete childItems[i];
        childItems.remove(i);
        return true;
    }
    return false;
}

int CDomItem::row() {
    return rowNumber;
}
