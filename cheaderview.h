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
#ifndef CHEADERVIEW_H
#define CHEADERVIEW_H
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPointer>
#include <QToolTip>
class CHeaderCombo : public QComboBox {
    Q_OBJECT
public:
    CHeaderCombo(QWidget* parent = 0) : QComboBox(parent) {
    }

    virtual ~CHeaderCombo(){}

protected:
    virtual void enterEvent(QEvent* ev) {
        QToolTip::showText(this->mapToGlobal(this->mapFromParent(this->geometry().center())),
                           currentText(),this);
        QComboBox::enterEvent(ev);
    }

    virtual void leaveEvent(QEvent* ev) {
        QToolTip::hideText();
        QComboBox::leaveEvent(ev);
    }
};

class CHeader : public QWidget{
    Q_OBJECT
public:
    CHeader(const QString& strLabelText, QWidget *parent = 0);
    CHeader(const QStringList& strComboItems, QWidget *parent = 0);

    CHeader(const QString &strLabelText,
            const QStringList& strComboItems, QWidget *parent = 0);
    virtual ~CHeader();
    void PopulateCombo(const QStringList& objItemList);
    void CreateCombo();
    void SetComboWidth(int iSectionWidth);
    void CreateLabel(const QString& strLabelText);
    void CreateLayOut();
    const QString GetComboCurrentText() const;
    const QComboBox* GetHeaderCombo() const {
        return m_pMemberCombo;
    }
    void ChangeHeaderLabel(const QString& strText) {
        if(m_pMemberLabel) {
            m_pMemberLabel->setText(strText);
            m_pMemberLabel->update();
        }
    }

    QMap<QString,int> GetComboContentMap();
    void ReloadCombo(const QStringList& objItemList);
    void Clear() {
        m_pMemberCombo->clear();
    }
    
    bool HasCombo() const {
        return m_bHasCombo;
    }

private:
    void MakeConnections();
public Q_SLOTS:
    void OnComboSelectionChanged(int iIndex);

signals:
    void ComboIndexChanged(int);
private:
    CHeaderCombo *m_pMemberCombo;
    QLabel* m_pMemberLabel;
    QHBoxLayout *m_pMemberHorzLayout;
    bool m_bHasCombo;
};


//The actual header view
class CCustomHeader : public QHeaderView{
    Q_OBJECT
public Q_SLOTS:
    void handleSectionResized(int i);
    void handleSectionMoved(int logical, int oldVisualIndex, int newVisualIndex);

public:
    CCustomHeader(const QStringList &strLabels,const QStringList& objList, QWidget *parent = NULL);
    virtual ~CCustomHeader();
    void RefreshSections();
    int count() const;
    void fixHeaderPositions();
    void ShowSections();
    void Reload(const QStringList objList);
    CHeader* GetHeaderObjectOfCombo() {
        int iCount = headerSections.count(),i=0;
        for(; i < iCount; i++) {
            if(headerSections[i]->HasCombo()) {
                return headerSections[i];
            }
        }
        return NULL;
    }

    void SetHeaderTextAt(int iHeaderIndex,const QString& strText) {
        if(iHeaderIndex >=0 && iHeaderIndex < headerSections.size()) {
            headerSections.at(iHeaderIndex)->ChangeHeaderLabel(strText);
            this->repaint();
        }
    }
    void SetVerticalScrollWidth(int iWidth) {
        m_iVerticalScrollWidth = iWidth;
    }

private Q_SLOTS:
    void OnHeaderComboChanged(int iIndex);
signals:
    void ComboIndexChanged(int);
protected:
    void CreatHeaderObjects(const QStringList &strHeaderList, const QStringList &objComboList);
    void showEvent(QShowEvent *e);
    QSize sizeHint() const;
    void ResizeCombo();
private:
    mutable QVector< QPointer <CHeader> > headerSections;
    int m_iVerticalScrollWidth;
};
#endif // CHEADERVIEW_H
