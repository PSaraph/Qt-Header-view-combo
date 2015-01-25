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
#ifndef CDOMITEM_H
#define CDOMITEM_H

//This is the class that holds the basic item of the My actvty treeview
#include <QDomNode>
#include <QHash>

class CDomItem
{
public:
    CDomItem(QDomNode &node, int row, CDomItem *parent = 0);
    ~CDomItem();
    CDomItem *child(int i);
    bool removeChild(int i);
    CDomItem *parent();
    QDomNode node() const;
    int row();

private:
    QDomNode domNode;
    QHash<int,CDomItem*> childItems;
    CDomItem *parentItem;
    static QString m_clsCurrentPurpose;
    int rowNumber;
};
#endif // CCDOMITEM_H
