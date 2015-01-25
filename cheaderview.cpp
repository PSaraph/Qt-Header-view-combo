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
#include "cheaderview.h"
CHeader::CHeader(const QString& strLabelText, QWidget *parent)
    : QWidget(parent),
      m_pMemberCombo(NULL),
      m_pMemberLabel(NULL),
      m_pMemberHorzLayout(NULL),
      m_bHasCombo(false) {
    CreateLabel(strLabelText);
    CreateLayOut();
}

CHeader::CHeader(const QStringList& strComboItems, QWidget *parent)
    : QWidget(parent),
      m_pMemberCombo(NULL),
      m_pMemberLabel(NULL),
      m_pMemberHorzLayout(NULL),
      m_bHasCombo(true) {
    CreateCombo();
    PopulateCombo(strComboItems);
    CreateLayOut();
}

CHeader::CHeader(const QString &strLabelText,const QStringList& strComboItems, QWidget *parent)
    : QWidget(parent),
      m_pMemberCombo(NULL),
      m_pMemberLabel(NULL),
      m_pMemberHorzLayout(NULL) {
    CreateLabel(strLabelText);
    CreateCombo();
    PopulateCombo(strComboItems);
    CreateLayOut();
    MakeConnections();
}

void CHeader::PopulateCombo(const QStringList& objItemList) {
    int iIndex = 0;
    foreach (const QString &strItem, objItemList) {
        m_pMemberCombo->insertItem(m_pMemberCombo->count() + 1,strItem);
        ++iIndex;
    }
}

void CHeader::CreateCombo() {
    if(!m_pMemberCombo) {
        m_pMemberCombo = new CHeaderCombo(this);
        m_pMemberCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

void CHeader::SetComboWidth(int iSectionWidth) {
    QFontMetrics objMetric(m_pMemberCombo->font());
    m_pMemberCombo->setMinimumWidth(abs(iSectionWidth -
                                        (m_pMemberLabel->text().length() * objMetric.maxWidth())));
}

const QString CHeader::GetComboCurrentText() const {
    return m_pMemberCombo->itemText(m_pMemberCombo->currentIndex());
}

QMap<QString,int> CHeader::GetComboContentMap() {
    QMap<QString,int> objComboMap;
    int i = 0;
    for (i = 0;i < m_pMemberCombo->count(); i++) {
        objComboMap.insert(m_pMemberCombo->itemText(i),i);
    }
    return objComboMap;
}

void CHeader::ReloadCombo(const QStringList& objItemList) {
    if(m_pMemberCombo) {
        m_pMemberCombo->clear();
        PopulateCombo(objItemList);
        m_pMemberCombo->setCurrentIndex(0);
        m_pMemberCombo->update();
    }
}

void CHeader::CreateLabel(const QString& strLabelText) {
    if(!m_pMemberLabel) {
        m_pMemberLabel  = new QLabel();
    }

    m_pMemberLabel->setText(strLabelText);
    QFontMetrics objMetric(m_pMemberLabel->font());
    m_pMemberLabel->setMinimumWidth((m_pMemberLabel->text().length() - 1) * objMetric.maxWidth());
}

void CHeader::CreateLayOut() {
    if(!m_pMemberHorzLayout) {
        m_pMemberHorzLayout = new QHBoxLayout;
        m_pMemberHorzLayout->setContentsMargins(QMargins(1,2,1,2));
    }

    if(m_pMemberLabel) {
        m_pMemberHorzLayout->addWidget(m_pMemberLabel);
    }

    if(m_pMemberCombo) {
        m_pMemberHorzLayout->addWidget(m_pMemberCombo);
        m_pMemberHorzLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum));
    }
    setLayout(m_pMemberHorzLayout);
}

CHeader::~CHeader() {
}

void CHeader::MakeConnections() {
    connect(m_pMemberCombo,SIGNAL(currentIndexChanged(int)),this,
            SLOT(OnComboSelectionChanged(int)));

}

void CHeader::OnComboSelectionChanged(int iIndex) {
    m_pMemberCombo->setCurrentIndex(iIndex);
    //    QString strSelectedPurpose = m_pMemberCombo->itemData(iIndex,Qt::UserRole).toString();
    //    //We have to notify the TreeView... i.e the proxy to make
    //    //Changes in the filer and invalidate it...
    //    if(!strSelectedPurpose.isEmpty()) {
    //        CSapMyActivityTab* pclsMyActvtyTab =
    //                CSapMyActivityTab::GetMe();
    //        if(pclsMyActvtyTab) {
    //            QMetaObject::invokeMethod(pclsMyActvtyTab,"OnHeaderPurposeChanged",
    //                                      Q_ARG(QString,strSelectedPurpose));
    //        }
    //        pclsMyActvtyTab = NULL;
    //    }
    emit ComboIndexChanged(iIndex);
}

//The header view
void CCustomHeader::handleSectionResized(int i)
{
    for (int j = visualIndex(i); j<count();j++) {
        int logical = logicalIndex(j);
        headerSections[logical]->setGeometry(sectionViewportPosition(logical)+2, 0,
                                             sectionSize(logical)-2, height());
    }
    ResizeCombo();
}

void CCustomHeader::handleSectionMoved(int logical, int oldVisualIndex, int newVisualIndex)
{
    int ilogicalIndex = logical;
    for (int i=qMin(oldVisualIndex, newVisualIndex);i<count();i++){
        ilogicalIndex = logicalIndex(i);
        headerSections[ilogicalIndex]->setGeometry(sectionViewportPosition(ilogicalIndex)+2, 0,
                                                   sectionSize(ilogicalIndex)-2, height());
    }
    ResizeCombo();
}

CCustomHeader::CCustomHeader(const QStringList& strLabels,
                             const QStringList &objList,QWidget *parent)
    :QHeaderView(Qt::Horizontal, parent) {

    CreatHeaderObjects(strLabels,objList);
    setMinimumSectionSize(headerSections[0]->minimumSizeHint().width());
    setDefaultSectionSize(headerSections[0]->minimumSizeHint().width());
    setMovable(true);
    connect(this, SIGNAL(sectionResized(int,int,int)), this,
            SLOT(handleSectionResized(int)));

}

CCustomHeader::~CCustomHeader() {
    QVector< QPointer <CHeader> >::Iterator iter = headerSections.begin();
    while(iter != headerSections.end()) {
        delete (*iter);
        (*iter) = NULL;
        ++iter;
    }
    headerSections.clear();
}


void CCustomHeader::Reload(const QStringList objList) {
    QVector< QPointer <CHeader> >::Iterator iter = headerSections.begin();
    while(iter != headerSections.end()) {
        QPointer<CHeader> pObjHeaderObj = (*iter);
        if(!pObjHeaderObj.isNull()) {
            pObjHeaderObj->ReloadCombo(objList);
        }
        ++iter;
    }
    this->update();
}

void CCustomHeader::fixHeaderPositions()
{
    for (int i=0;i<count();i++)
        headerSections[i]->setGeometry(sectionViewportPosition(i) + 2 , 0,
                                       sectionSize(i) - 2 , height());
}

void CCustomHeader::CreatHeaderObjects(const QStringList& strHeaderList,
                                       const QStringList& objComboList) {
    for(int i = 0; i<strHeaderList.count(); i++){
        if(i != strHeaderList.count()-1) {
            headerSections.insert(i,new CHeader(strHeaderList.at(i),this));
        } else {
            headerSections.insert(i,new CHeader(strHeaderList.at(i),objComboList,this));
            connect(headerSections[i],SIGNAL(ComboIndexChanged(int)),this,
                    SLOT(OnHeaderComboChanged(int)));
        }
        QCursor objCursor(Qt::ArrowCursor);
        headerSections[i]->setCursor(objCursor); // We need to set this explicitly for smooth scrolling
        headerSections[i]->hide();
    }
}

void CCustomHeader::ShowSections() {
    for (int i=0;i<count();i++) {
        headerSections[i]->show();
    }
}

void CCustomHeader::showEvent(QShowEvent *e)
{
    fixHeaderPositions();
    ShowSections();
    QHeaderView::showEvent(e);
}

QSize CCustomHeader::sizeHint() const {
    QSize s = size();
    s.setHeight(headerSections[0]->minimumSizeHint().height() + 15);
    return s;
}

int CCustomHeader::count() const {
    return headerSections.size();
}

void CCustomHeader::ResizeCombo() {
    for(int i=0; i < headerSections.size(); i++) {
        if(headerSections[i]->HasCombo()) {
            headerSections[i]->SetComboWidth(sectionSize(logicalIndex(i)) - m_iVerticalScrollWidth);
            break;
        }
    }
}

void CCustomHeader::RefreshSections() {
    handleSectionResized(1);
}

void CCustomHeader::OnHeaderComboChanged(int iIndex) {
    emit ComboIndexChanged(iIndex);
}
