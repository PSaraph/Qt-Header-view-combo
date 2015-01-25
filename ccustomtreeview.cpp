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
#include "ccustomtreeview.h"
#include "cheaderview.h"

CCustomTreeView::CCustomTreeView(QWidget* parent) :
    QTreeView(parent)
{
    this->setStyleSheet("QTreeView, QTableView{"\
                        "show-decoration-selected: 1;"\
                        " selection-color: white;"\
                        "alternate-background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #EFEFEF, stop: 1 #DFDFDF);"\
                        "}"\

                        "QTreeView::item {"\
                        "border: transparent;"\
                        "}"\

                        "QTreeView::item:!selected:hover {"\
                        " background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #D0D0D0, stop: 1 #CFCFCF);"\
                        "}"\

                        "QTreeView::item:selected:!hover{"\
                        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #8F9CBF, stop: 1 #838FAF);"\
                        "}"\

                        "QTreeView::item:selected:hover{"\
                        " background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #7888AF, stop: 1 #6D7C9F);"\
                        "}");
}

void CCustomTreeView::scrollContentsBy(int dx, int dy)
{
    QTreeView::scrollContentsBy(dx, dy);
    if (dx != 0) {
        CCustomHeader* pHeader = static_cast<CCustomHeader*> (header());
        pHeader->fixHeaderPositions();
    }
}

const QModelIndexList CCustomTreeView::GetSelectedIndexes() const {
    return selectedIndexes();
}

void CCustomTreeView::HideColumn(int index) {
    if(index >=0) {
        this->hideColumn(index);
    }
}

void CCustomTreeView::showEvent(QShowEvent *e) {
    QTreeView::showEvent(e);
    int iColCount = this->model()->columnCount(), iLoop = 0;
    for(;iLoop < iColCount; iLoop++) {
        resizeColumnToContents(iLoop);
    }
}
