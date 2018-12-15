/*
    about.cpp
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
#include "about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    ui->textBrowser->setGeometry(0,0,this->width(), this->height());
    //ui->pushButton->setGeometry(this->width() - (ui->pushButton->width()+5), this->height() - (ui->pushButton->height()+5), ui->pushButton->width(), ui->pushButton->height());

    ui->textBrowser->setHtml("Jelyazka RSS Reader written by Vladimir Stoyanov.<p>e-mail:<a href=\"mailto:vlado_stoyanov@yahoo.com\">vlado_stoyanov@yahoo.com</p>");

    ui->textBrowser->setOpenLinks(1);
    ui->textBrowser->setOpenExternalLinks(1);
}

About::~About()
{
    delete ui;
}

//'OK' button has been clicked
void About::OKButtonClicked()
{
    this->hide();
}

void About::closeEvent(QCloseEvent *)
{
    this->hide();
}

void About::showEvent(QShowEvent *)
{

}
