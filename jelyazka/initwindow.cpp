/*
    initwindow.cpp
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
#include "initwindow.h"
#include "ui_initwindow.h"
#include <QDesktopWidget>

InitWindow::InitWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InitWindow)
{
    ui->setupUi(this);
    tp = new QThreadPool(this);

    ui->label->setGeometry(5,260,250,40);
    ui->label->setStyleSheet("QLabel { color : white; }");
    ui->label->setText("");

    this->setWindowFlags( Qt::FramelessWindowHint);
    this->setGeometry(30,100,300,300);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center()); //move the window to the center of the screen
    this->setStyleSheet("background-color:black;");

    imageInitLabel = new QLabel(this);
    init_img  = new QImage("../resources/jelyazka_02_end.png");
    imageInitLabel->setPixmap(QPixmap::fromImage(*init_img));
    imageInitLabel->setGeometry(QRect(0,0,300,300));
    imageInitLabel->show();
    imageInitLabel->lower();
}

InitWindow::~InitWindow()
{
    delete ui;
    delete init_img;
    delete imageInitLabel;
    delete tp;
}

//load RSS feeds in thread pool
void InitWindow::setSignal(SiteStruct *s_struct, Data *data_tmp)
{
    data = data_tmp;
    site_struct = s_struct;
    connect(s_struct,SIGNAL(loadRSS(QString,QString)),this,SLOT(onLoadRss(QString,QString)));
    int i=0;

    while (i<data->size())
    {
        tp->start(site_struct);
        i++;
    }
    if (data->size()==0)
    {
        site_struct->first_load = true;
        this->hide();
        emit Done();
    }
    site_struct->setAutoDelete(true);
}
void InitWindow::onLoadRss(QString name, QString url)
{
    if (url == "" && name == "") //if loading RSS feeds finish
    {
        site_struct->first_load = true;
        this->hide();
        emit Done();
        return;
    }

    ui->label->setText("Loading: " + name);
}
