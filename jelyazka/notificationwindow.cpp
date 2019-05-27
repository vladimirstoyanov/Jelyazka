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
#include "notificationwindow.h"

NotificationWindow::NotificationWindow(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::NotificationWindow),
    image_label_(nullptr),
    //rss_thread_(nullptr),
    show_window_animation_ (std::make_shared<QPropertyAnimation>(this, "geometry")),
    hide_window_animation_ (std::make_shared<QPropertyAnimation>(this, "geometry")),
    is_mouse_clicked_ (false),
    is_X_changed_(true)

{
    ui_->setupUi(this);

    //makes the window without frames
	#ifdef _WIN32
		setWindowFlags( Qt::FramelessWindowHint | windowFlags() | Qt::Tool);
	#else
		setWindowFlags( Qt::FramelessWindowHint | Qt::Tool);
	#endif
    
    //image of 'X' button load
    LoadImage_();
    
    //make transperent background of textEdit
    ui_->textBrowser->setGeometry(5,60, this->width()-10, this->height()-65);
    ui_->textBrowser->viewport()->setAutoFillBackground(false);

    //when click on a link, open default web browser and load this link
    ui_->textBrowser->setOpenLinks(1);
    ui_->textBrowser->setOpenExternalLinks(1);

    connect (show_window_animation_.get(), SIGNAL(finished()), this, SLOT(onShowAnimationFinished()));
    connect (hide_window_animation_.get(), SIGNAL(finished()), this, SLOT(onHideAnimationFinished()));

    qApp->installEventFilter(this);

}

NotificationWindow::~NotificationWindow()
{
}

void NotificationWindow::showEvent(QShowEvent *)
{
    showWindowAnimation();
}

//Get horizontal and vertical resolution of a desktop
void NotificationWindow::getDesktopResolution(int& horizontal, int& vertical)
{
   QDesktopWidget widget;
   QRect desktop = widget.availableGeometry(widget.primaryScreen());

   horizontal = desktop.width();
   vertical = desktop.height();
   qDebug()<<"Horizontal/vertical: "<<horizontal<<" "<<vertical;
}

//Show window animation
void NotificationWindow::showWindowAnimation()
{
    int width=0, height =0;
    getDesktopResolution(width, height);

    show_window_animation_->setDuration(2000); //time to show
    show_window_animation_->setStartValue(QRect(width-this->width(),height,this->width(),this->height()));
    show_window_animation_->setEndValue(QRect(width-this->width(),height - this->height(),this->width(),this->height()));
    show_window_animation_->start();
    is_mouse_clicked_ = false;
}

//Hide window animation
void NotificationWindow::hideWindowAnimation()
{
    int width=0, height =0;
    getDesktopResolution(width, height);

    hide_window_animation_->setDuration(2000); //time to hide
    hide_window_animation_->setStartValue(QRect(width-this->width(),height - this->height(),this->width(),this->height()));
    hide_window_animation_->setEndValue(QRect(width-this->width(),height,this->width(),this->height()));
    hide_window_animation_->start();
}

//Load 'X' button image
void NotificationWindow::LoadImage_()
{
   image_label_ = std::make_shared<QLabel>(this);
   close_button_image_  = QImage("../resources/x_button.png");
   image_label_->setPixmap(QPixmap::fromImage(close_button_image_));
   image_label_->setGeometry(QRect(this->width()-35,5,30,30));
   image_label_->show();
}

void NotificationWindow::mousePressEvent ( QMouseEvent * e )
{
    if (e->x()>this->width()-50 && e->y()<50) //'X' button has been clicked
        this->hide();
}

void NotificationWindow::onShowAnimateWindow(QString data_str)
{
    QString html_source="";
    if (data_str== "")
        return;

    QList<unsigned int> indexes = getIndexes(data_str);
    if (indexes.size() == 0)
        return;

    for (int i=0; i<indexes.size(); i++)
        if (data_->size()>indexes[i])
            if (data_->at(indexes[i])->getArticlesSize()>0)
                html_source+="<a href = \""
                        + data_->at(indexes[i])->articleAt(0).getLink()
                        + "\" style=\"color: #000000\">"
                        + data_->at(indexes[i])->getSiteName()
                        + ": "
                        + data_->at(indexes[i])->articleAt(0).getTitle()
                        + "</a><br><hr>";

    //Add links
    ui_->textBrowser->setHtml(html_source);
    this->show();
}

void NotificationWindow::onShowAnimationFinished()
{
    delay(5);
    if (!is_mouse_clicked_)
        hideWindowAnimation(); //window hiding animation
}

void NotificationWindow::onHideAnimationFinished()
{
    this->hide();
}

//Get indexes from data string
QList<unsigned int> NotificationWindow::getIndexes(QString data_str)
{
    QStringList split = data_str.split("<index=");
    QList<unsigned int> indexes;

    if (split.size() == 0)
        return indexes;

    for (unsigned int i=0; i<split.size(); i++)
    {
        QString tmp_str = split.at(i);
        if (tmp_str.length() > 0)
        {
            tmp_str.remove(tmp_str.length()-1, 1);
            int index = tmp_str.toInt();
            if (index>data_->size() || index < 0)
                continue;
            indexes.append(index);
        }
    }
    return indexes;
}

//make connection to RSSThread instance.
void NotificationWindow::setSignal(std::shared_ptr<RSSThread> rssThread, std::shared_ptr<Data> data)
{
    //rss_thread_ = rssThread;
    data_ = data;
    //connect(rss_thread_.get(), SIGNAL(showAnimateWindow(QString)), this, SLOT(onShowAnimateWindow(QString)));
}

//This method is similar of 'Sleep(mseconds)' function in 'windows.h'
void NotificationWindow::delay(int seconds)
{
    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


bool NotificationWindow::eventFilter(QObject *o, QEvent *event)
{
    QPoint p = this->mapFromGlobal(QCursor::pos());
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (o->objectName() == "CAnimateWindowWindow")
            is_mouse_clicked_ = true;
    }

    if (event->type() == QEvent::MouseMove && o->objectName() == "CAnimateWindowWindow")
    {
        if (is_X_changed_)
        {
            close_button_image_  = QImage("../resources/x_button.png");
            image_label_->setPixmap(QPixmap::fromImage(close_button_image_));
            image_label_->show();
            is_X_changed_=0;

        }

        if (p.x()>this->width()-36 && p.x()<this->width() -4 && p.y()>4 && p.y()<36)
        {
            close_button_image_  = QImage("../resources/x_button_gradient.png");
            image_label_->setPixmap(QPixmap::fromImage(close_button_image_));
            image_label_->show();
            is_X_changed_ = 1;
            QApplication::restoreOverrideCursor();
        }
    }

    return 0;
}

void NotificationWindow::paintEvent(QPaintEvent *)
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

void NotificationWindow::gradientRect(int x, int y, int width, int height)
{
    QRect myQRect (x,y,width, height);
    QPainter painter(this);
    QLinearGradient gradient(myQRect.bottomLeft(), myQRect.topLeft());
    gradient.setColorAt(0, Qt::gray);
    gradient.setColorAt(1, Qt::white);
    painter.fillRect(myQRect, gradient);

}
