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
#include "ctreefilterproxymodel.h"
#include "ccommondefines.h"
#include <QDebug>

bool CTreeFilterProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    bool bRetVal = true;
    QModelIndex iIndexYear = sourceModel()->index(source_row, Year, source_parent);
    qDebug() << sourceModel()->data(iIndexYear).toString() << endl;
    if(!m_strFilterValue.compare("ALL",Qt::CaseInsensitive)) {
        return bRetVal;
    }

    QString strYear = sourceModel()->data(iIndexYear).toString();
    if(!strYear.isEmpty()) {
        if(strYear.compare(m_strFilterValue)) {
            bRetVal = false;
        }
    }
    return bRetVal;
}

void CTreeFilterProxy::SetFilterValue(const QString& strValue) {
    m_strFilterValue = strValue;
    invalidateFilter();
}
