/*
    mainwindow2.cpp
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
#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "addnewurldislog.h"
#include "web_search_interface.h"


MainWindow2::MainWindow2(QWidget *parent, SiteStruct *s_struct) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);

    //read a file and load sites
    site_stuct = s_struct;
    InitValueToComboBox();
    LoadWatchList();
}

MainWindow2::~MainWindow2()
{
    delete ui;
}
void MainWindow2::LoadWatchList() //load watchlist from file watchlist.cfg
{
    ifstream myfile;
    myfile.open("watchlist.cfg",ios::in);

    //check if file open
    if (myfile.fail())
        return;

    QString watch_list_data="";
    while (!myfile.eof())
    {
        char a;
        myfile.get(a);

        if (a == '\n') //add to watchlist
        {
            AddStringToWatchList(watch_list_data);
            watch_list_data="";
            continue;
        }

        watch_list_data+=a;
    }
    myfile.close();
}
void MainWindow2::InitValueToComboBox()
{
    //clear values
    ui->comboBox->clear();
    //add new values
    for (int i=0;i<site_stuct->s_struct.size(); i++)
        AddToCombobox(site_stuct->s_struct[i].site_name);
}

void MainWindow2::on_pushButton_3_clicked() //add new site button
{
    WebSearchInterface wsi(0,site_stuct);// = new WebSearchInterface (0,site_stuct);
    wsi.show();
    //AddNewURLDislog *anud = new AddNewURLDislog(this,0,site_stuct);
    //anud->show();

}

void MainWindow2::AddToCombobox(QString web_site)
{
    ui->comboBox->insertItem(0, web_site);// add Item
    ui->comboBox->setCurrentIndex (0);
    //ui->listView->
}

void MainWindow2::setSiteStruct(SiteStruct *s_struct)
{
    site_stuct = s_struct;
    InitValueToComboBox();
}

void MainWindow2::on_pushButton_2_clicked()//cancel button clicked
{
    this->hide();
}

void MainWindow2::on_pushButton_clicked() //ok button clicked
{
    //remember watch list
    ofstream  myfile;
    myfile.open("watchlist.cfg",ios::out);


    //write all from watchlist
    for(int row = 0; row < ui->listWidget->count(); row++)
    {
        QListWidgetItem *item = ui->listWidget->item(row);
        // process item
        QByteArray ba = item->text().toLocal8Bit();
        myfile<<ba.data()<<endl;//trqbva da se preobrazuva qstring do char*
    }
    myfile.close();
    this->hide();
}
void MainWindow2::AddStringToWatchList(QString str)
{
    int count = ui->listWidget->count(); //get count of listWidget
    if (str=="")
        return;
    ui->listWidget->insertItem(count, str); //insert new element of end of list widget
}

void MainWindow2::on_pushButton_4_clicked() //add to list widget button
{
    QString cur_text= ui->comboBox->currentText(); //get current text
    int count = ui->listWidget->count(); //get count of listWidget
    if (cur_text=="")
        return;

    //check for identical
    for(int row = 0; row < ui->listWidget->count(); row++)
    {
        QListWidgetItem *item = ui->listWidget->item(row);
        // process item
        if (cur_text == item->text())
            return;
    }
    ui->listWidget->insertItem(count, cur_text); //insert new element of end of list widget

}

void MainWindow2::on_pushButton_5_clicked() //remove button
{
    qDeleteAll(ui->listWidget->selectedItems()); //removed
}

void MainWindow2::closeEvent(QCloseEvent *event) //close event
{
        this->hide();
        event->ignore(); // Don't let the event propagate to the base class
}
