/*
    help.cpp
    Jelyazka RSS/RDF reader
    Copyright (C) 2014 Vladimir Stoyanov
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "help.h"
#include "ui_help.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);

    //with bottom 2 lines, clicked link in textBrowser widget, open default web browser and load the link 
    ui->textBrowser->setOpenLinks(1);
    ui->textBrowser->setOpenExternalLinks(1);
}

Help::~Help()
{
    delete ui;
}

void Help::showEvent(QShowEvent *)
{
    ui->textBrowser->setGeometry(5,5,this->width()-10, this->height()-10);
    loadHelp();
}

void Help::resizeEvent(QResizeEvent *event)
{
    ui->textBrowser->setGeometry(5,5,this->width()-10, this->height()-10);
}

void Help::loadHelp()
{
    QString html_source;
    QFile file("../resources/jelyazka_help/help.htm");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error!", "Can't read help file: " + file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        html_source+=line;
    }

    file.close();

    ui->textBrowser->setHtml(html_source);
}
