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

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::Help)
{
    ui_->setupUi(this);

    //with bottom 2 lines, when clicks on a link in textBrowser widget,
    //it opens default web browser and loading the link
    ui_->textBrowser->setOpenLinks(1);
    ui_->textBrowser->setOpenExternalLinks(1);
}

Help::~Help()
{
    delete ui_;
}

void Help::showEvent(QShowEvent *)
{
    ui_->textBrowser->setGeometry(5,5,this->width()-10, this->height()-10);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    loadHelp();
}

void Help::resizeEvent(QResizeEvent *event)
{
    ui_->textBrowser->setGeometry(5,5,this->width()-10, this->height()-10);
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

    ui_->textBrowser->setHtml(html_source);
}
