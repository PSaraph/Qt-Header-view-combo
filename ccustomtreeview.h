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
#ifndef CCUSTOMTREEVIEW_H
#define CCUSTOMTREEVIEW_H

#include <QTreeView>

class CCustomTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CCustomTreeView(QWidget *parent = 0);
    virtual ~CCustomTreeView() {}
    const QModelIndexList GetSelectedIndexes() const; //This is a hack
    void HideColumn(int index);
    
signals:
    
public slots:
protected:
    void scrollContentsBy(int dx, int dy);
    void showEvent(QShowEvent *e);
    
};

#endif // CCUSTOMTREEVIEW_H
