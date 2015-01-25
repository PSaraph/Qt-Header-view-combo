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
#ifndef CTREEFILTERPROXYMODEL_H
#define CTREEFILTERPROXYMODEL_H

//This is the Filter model from the MVC model
//We need to filter view based on various criteria

#include <QSortFilterProxyModel>

class CTreeFilterProxy : public QSortFilterProxyModel {
    Q_OBJECT
public:
    CTreeFilterProxy(QObject* parent = 0) : QSortFilterProxyModel(parent),
        m_strFilterValue("ALL"),m_bIsModelReset(false)
    {

    }
    void SetFilterValue(const QString& strValue);
    const QString& GetFilterValue() const {
        return m_strFilterValue;
    }

    void SetModelToReset(bool bReset) {
        m_bIsModelReset = bReset;
    }

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    QString m_strFilterValue;
    bool m_bIsModelReset;
};
#endif // CTREEFILTERPROXYMODEL_H
