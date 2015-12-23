/*
    animatewindow.cpp
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
#include "animatewindow.h"
#include "ui_animatewindow.h"
#include <QPainter>

CAnimateWindow::CAnimateWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAnimateWindow)
{
    ui->setupUi(this);
    animation = NULL;
    imageLabel = NULL;
    
	#ifdef _WIN32
		setWindowFlags( Qt::FramelessWindowHint | windowFlags() | Qt::Tool);
	#else
		setWindowFlags( Qt::FramelessWindowHint | Qt::Tool);
	#endif
    //make window without frames
    

    site_struct=NULL;
    
    //image of 'X' button load
    LoadImage_();
    
    //make transperent background of textEdit
    ui->textBrowser->setGeometry(5,60, this->width()-10, this->height()-65);
    ui->textBrowser->viewport()->setAutoFillBackground(false);

    //when click on a link, open default web browser and load this link
    ui->textBrowser->setOpenLinks(1);
    ui->textBrowser->setOpenExternalLinks(1);

    animation = new QPropertyAnimation(this, "geometry");
    animation2 = new QPropertyAnimation(this, "geometry");

    connect (animation, SIGNAL(finished()), this, SLOT(on_animation_finished()));
    connect (animation2, SIGNAL(finished()), this, SLOT(on_animation_finished2()));

    mouse_clicked = false;

    qApp->installEventFilter(this);

    isXchanged = 1;
}

CAnimateWindow::~CAnimateWindow()
{
    if (animation!=NULL)
        delete animation;
    if (animation!=NULL)
        delete animation2;
    if (imageLabel!=NULL)
        delete imageLabel;

    delete ui;
}
void CAnimateWindow::showEvent(QShowEvent *)
{
    animate();
}

//Get horizontal and vertical resolution of a desktop
void CAnimateWindow::getDesktopResolution(int& horizontal, int& vertical)
{
   QDesktopWidget widget;
   QRect desktop = widget.availableGeometry(widget.primaryScreen());

   horizontal = desktop.width();
   vertical = desktop.height();
   qDebug()<<"Horizontal/vertical: "<<horizontal<<" "<<vertical;
}
//Show window animation
void CAnimateWindow::animate()
{
    int width=0, height =0;
    getDesktopResolution(width, height);

    animation->setDuration(2000); //time to show
    animation->setStartValue(QRect(width-this->width(),height,this->width(),this->height()));
    animation->setEndValue(QRect(width-this->width(),height - this->height(),this->width(),this->height()));
    animation->start();
    mouse_clicked = false;
}

//Hide window animation
void CAnimateWindow::animate2()
{
    int width=0, height =0;
    getDesktopResolution(width, height);

    animation2->setDuration(2000); //time to hide
    animation2->setStartValue(QRect(width-this->width(),height - this->height(),this->width(),this->height()));
    animation2->setEndValue(QRect(width-this->width(),height,this->width(),this->height()));
    animation2->start();
}

//Load 'X' button image
void CAnimateWindow::LoadImage_()
{
   imageLabel = new QLabel(this);
   close_button_img  = QImage("../resources/x_button.png");
   imageLabel->setPixmap(QPixmap::fromImage(close_button_img));
   imageLabel->setGeometry(QRect(this->width()-35,5,30,30));
   imageLabel->show();
}

void CAnimateWindow::mousePressEvent ( QMouseEvent * e )
{
    if (e->x()>this->width()-50 && e->y()<50) //'X' button has been clicked
        this->hide();
}

void CAnimateWindow::onShowAnimateWindow(QString data_str)
{
    QString html_source="";
    if (data_str== "")
        return;

    QList<int> indexes = getIndexes(data_str);
    if (indexes.size() == 0)
        return;

    for (int i=0; i<indexes.size(); i++)
        if (data->size()>indexes[i])
            if (data->at(indexes[i])->getArticlesSize()>0)
                html_source+="<a href = \""+data->at(indexes[i])->articleAt(0).getLink() + "\" style=\"color: #000000\">"+data->at(indexes[i])->getSiteName() +": " + data->at(indexes[i])->articleAt(0).getTitle()+ "</a><br><hr>";

    //Add links
    ui->textBrowser->setHtml(html_source);
    this->show();
}

void CAnimateWindow::on_animation_finished()
{
    delay(5);
    if (!mouse_clicked)
        animate2(); //window hiding animation
}

void CAnimateWindow::on_animation_finished2()
{
    this->hide();
}

//Get indexes from data string
QList<int> CAnimateWindow::getIndexes(QString data_str)
{
    QStringList split = data_str.split("<index=");
    QList<int> indexes;

    if (split.size() == 0)
        return indexes;

    for (int i=0;i<split.size(); i++)
    {
        QString tmp_str = split.at(i);
        if (tmp_str.length() > 0)
        {
            tmp_str.remove(tmp_str.length()-1, 1);
            int index = tmp_str.toInt();
            if (index>data->size() || index < 0)
                continue;
            indexes.append(index);
        }
    }
    return indexes;
}

//make connection to RSSThread instance.
void CAnimateWindow::setSignal(RSSThread *s_struct, Data *data_tmp)
{
    site_struct = s_struct;
    data = data_tmp;
    connect(s_struct,SIGNAL(showAnimateWindow(QString)),this,SLOT(onShowAnimateWindow(QString)));
}

//This method is similar of 'Sleep(mseconds)' function in 'windows.h'
void CAnimateWindow::delay(int seconds)
{
    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


bool CAnimateWindow::eventFilter(QObject *o, QEvent *event)
{
    QPoint p = this->mapFromGlobal(QCursor::pos());
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (o->objectName() == "CAnimateWindowWindow")
            mouse_clicked = true;
    }

    if (event->type() == QEvent::MouseMove && o->objectName() == "CAnimateWindowWindow")
    {
        if (isXchanged)
        {
            close_button_img  = QImage("../resources/x_button.png");
            imageLabel->setPixmap(QPixmap::fromImage(close_button_img));
            imageLabel->show();
            isXchanged=0;

        }

        if (p.x()>this->width()-36 && p.x()<this->width() -4 && p.y()>4 && p.y()<36)
        {
            close_button_img  = QImage("../resources/x_button_gradient.png");
            imageLabel->setPixmap(QPixmap::fromImage(close_button_img));
            imageLabel->show();
            isXchanged = 1;
            QApplication::restoreOverrideCursor();
        }
    }

    return 0;
}

void CAnimateWindow::paintEvent(QPaintEvent *)
{
   gradientRect(0, 0, this->width(), this->height());

   QPainter painter(this);
   QPen linepen(Qt::black);
   linepen.setCapStyle(Qt::RoundCap);
   linepen.setWidth(2);
   painter.setRenderHint(QPainter::Antialiasing,true);
   painter.setPen(linepen);
   painter.drawRect(0,0,this->width(), this->height()); //paint backgraund gradient
}

void CAnimateWindow::gradientRect(int x, int y, int width, int height)
{
    QRect myQRect (x,y,width, height);
    QPainter painter(this);
    QLinearGradient gradient(myQRect.bottomLeft(), myQRect.topLeft());
    gradient.setColorAt(0, Qt::gray);
    gradient.setColorAt(1, Qt::white);
    painter.fillRect(myQRect, gradient);

}
