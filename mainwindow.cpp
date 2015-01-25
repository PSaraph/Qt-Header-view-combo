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
#include <QDomDocument>
#include <QFile>
#include <QtGui>

#include "cdommodel.h"
#include "mainwindow.h"
#include"cheaderview.h"
#include "ccommondefines.h"

#include <QDebug>

MainWindow::MainWindow() : QMainWindow(), model(0)
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()),
                        QKeySequence::Open);
    fileMenu->addAction(tr("E&xit"), this, SLOT(close()),
                        QKeySequence::Quit);

    model = new CDomModel(QDomDocument(), this);
    pProxyModel = new CTreeFilterProxy(this);
    view = new CCustomTreeView(this);
    pProxyModel->setSourceModel(model);
    view->setModel(pProxyModel);
    QStringList strLabels,objComboList;
    strLabels<<QString(NAME)
            <<QString(AUTHOR)
           <<QString(PUBLISHER)
          <<QString(PAGES)
         <<QString(YEAR);
    objComboList <<"ALL"
                << "2000"
                << "2001"
                << "2002"
                << "2003"
                << "2004"
                << "2005"
                << "2006"
                << "2007"
                << "2008"
                << "2009"
                << "2010"
                << "2011"
                << "2012"
                << "2013"
                << "2014"
                << "2015";
    CCustomHeader * pCustomHeader = new CCustomHeader(strLabels,objComboList,this);
    connect(pCustomHeader,SIGNAL(ComboIndexChanged(int)), this, SLOT(OnHeaderComboIndexChanged(int)));
    view->setHeader(pCustomHeader);
    view->header()->setStretchLastSection(true);
    setCentralWidget(view);
    setWindowTitle(tr("Simple DOM Model"));
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    xmlPath, tr("XML files (*.xml);;HTML files (*.html);;"
                                                                "SVG files (*.svg);;User Interface files (*.ui)"));

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            QDomDocument document;
            if (document.setContent(&file)) {
                CDomModel *newModel = new CDomModel(document, this);
                //view->setModel(newModel);
                int ColCount = newModel->columnCount();
                for(int i=0 ; i < ColCount; i++) {
                    view->resizeColumnToContents(i);
                }
                delete model;
                model = newModel;
                pProxyModel->setSourceModel(model);
                view->setModel(pProxyModel);
                xmlPath = filePath;
            }
            file.close();
        }
    }
}

void MainWindow::OnHeaderComboIndexChanged(int iIndex) {
    Q_UNUSED(iIndex);
    qDebug() << static_cast<CCustomHeader*>(view->header())->GetHeaderObjectOfCombo()->GetComboCurrentText();
    pProxyModel->SetFilterValue(static_cast<CCustomHeader*>(view->header())->GetHeaderObjectOfCombo()->GetComboCurrentText());
}
