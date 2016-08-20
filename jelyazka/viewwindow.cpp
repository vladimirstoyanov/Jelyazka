/*
    viewwindow.cpp
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
#include "viewwindow.h"
#include "ui_viewwindow.h"
#include <QDebug>
#include <QStyle>


ViewWindow::ViewWindow(QWidget *parent, RSSThread *rss_thread, Data *data):
    QWidget(parent),
    ui_(new Ui::ViewWindow)
{
    ui_->setupUi(this);

    data_ = data;
    //make window without frames
    this->setWindowFlags( Qt::FramelessWindowHint);

    //set minimum width and height
    this->setMinimumHeight(200);
    this->setMinimumWidth(350);

    is_resizing_ = false;

    initFilters();

    help_gui_ = new Help();

    rss_thread_ = rss_thread;
    wsi_ = new RSSSearchGUI (0, rss_thread_, this, data_);

    ow_ = new OptionsWindow(0,rss_thread_, this, data_);
    connect(rss_thread_,SIGNAL(Finish(QString, bool)),ow_,SLOT(onFinish(QString, bool)));

    is_X_changed_ = 0;
    is_minimize_changed_=0;
    is_maximize_changed_=0;
    is_flag_maximized_ = 0;
    is_press_released_ = 0;

    qApp->installEventFilter(this);

    //when click link in textBrowser, open default browser and load url
    ui_->textBrowser->setOpenLinks(1);
    ui_->textBrowser->setOpenExternalLinks(1);

    //load "Add RSS" image
    image_add_rss_label_ = new QLabel(this);
    add_rss_button_image_  = QImage("../resources/rss-icon-40x40.png");
    image_add_rss_label_->setPixmap(QPixmap::fromImage(add_rss_button_image_));
    image_add_rss_label_->setGeometry(QRect(5,5,40,40));
    image_add_rss_label_->setWhatsThis("Add RSS Feeds");
    image_add_rss_label_->show();
    image_add_rss_label_->setToolTip("Add RSS Feed(s)");
	#ifdef _WIN32
        image_add_rss_label_->setToolTipDuration(5000);
	#endif
    


    //laod "Options" image
    image_options_label_ = new QLabel(this);
    options_button_image_  = QImage("../resources/Black_Settings.png");
    image_options_label_->setPixmap(QPixmap::fromImage(options_button_image_));
    image_options_label_->setGeometry(QRect(50,5,40,40));
    image_options_label_->setWhatsThis("Options");
    image_options_label_->show();
    image_options_label_->setToolTip("Options");
	#ifdef _WIN32
        image_add_rss_label_->setToolTipDuration(5000);
	#endif

    //laod "Refresh" image
    image_refresh_label_ = new QLabel(this);
    refresh_button_image_ = QImage("../resources/refresh.png");
    image_refresh_label_->setPixmap(QPixmap::fromImage(refresh_button_image_));
    image_refresh_label_->setGeometry(QRect(95,5,40,40));
    image_refresh_label_->setWhatsThis("Help");
    image_refresh_label_->show();
    image_refresh_label_->setToolTip("Refresh");
    #ifdef _WIN32
        image_add_rss_label_->setToolTipDuration(5000);
	#endif

    //laod "Help" image
    image_help_label_ = new QLabel(this);
    help_button_image_  = QImage("../resources/icon40x40help.png");
    image_help_label_->setPixmap(QPixmap::fromImage(help_button_image_));
    image_help_label_->setGeometry(QRect(140,5,40,40));
    image_help_label_->setWhatsThis("Help");
    image_help_label_->show();
    image_help_label_->setToolTip("Help");
	#ifdef _WIN32
        image_add_rss_label_->setToolTipDuration(5000);
	#endif

    QSize window_size = QWidget::size();
    width_ = window_size.width();
    height_ = window_size.height();

    //laod "X" image
    image_X_label_ = new QLabel(this);
    x_button_image_  = QImage("../resources/x_button.png");
    image_X_label_->setPixmap(QPixmap::fromImage(x_button_image_));
    image_X_label_->setGeometry(QRect(window_size.width()-35,5,30,30));
    image_X_label_->show();
    image_X_label_->setToolTip("Close");
	#ifdef _WIN32
        image_add_rss_label_->setToolTipDuration(5000);
	#endif

    //laod "Minimize" image
    image_minimize_label_ = new QLabel(this);
    minimize_button_image_  = QImage("../resources/minimize_button.png");
    image_minimize_label_->setPixmap(QPixmap::fromImage(minimize_button_image_));
    image_minimize_label_->setGeometry(QRect(window_size.width()-97,5,30,30));
    image_minimize_label_->show();
    image_minimize_label_->setToolTip("Minimize");
	#ifdef _WIN32
        image_add_rss_label_->setToolTipDuration(5000);
	#endif

    //laod "Maximize" image
    image_maximize_label_ = new QLabel(this);
    maximize_button_image_  = QImage("../resources/maximize_button.png");
    image_maximize_label_->setPixmap(QPixmap::fromImage(maximize_button_image_));
    image_maximize_label_->setGeometry(QRect(window_size.width()-66,5,30,30));
    image_maximize_label_->show();
    image_maximize_label_->setToolTip("Maximize");
	#ifdef _WIN32
        image_add_rss_label_->setToolTipDuration(5000);
	#endif
    is_minimize_ = 0;
    is_close_ = 0;

}

ViewWindow::~ViewWindow()
{
    delete ui_;
    delete image_add_rss_label_;
    delete image_help_label_;
    delete image_options_label_;
    delete image_refresh_label_;
    delete image_X_label_;
    delete image_minimize_label_;
    delete image_maximize_label_;
    delete wsi_;
    delete help_gui_;
    //delete size_grip;
}

//initialize text browser widget
void ViewWindow::initTextBrowser()
{
    //get current value form combobox
    QString cur_text= ui_->comboBox->currentText();


    //find index of ui->comboBox->currentText() in 's_struct' structure
    int index=-1;
    for (uint i=0; i<data_->size(); i++)
    {
        if (data_->at(i)->getSiteName()==cur_text)
        {
            index = i;
            break;
        }
    }

    if (index==-1)
    {
        ui_->textBrowser->setHtml("");
        return;
    }

    showArticle(index,0); //show article in text browser with index=0 from 's_struct' structure
    current_article_index_ = 0;
    current_site_index_=index;
}

void ViewWindow::onUpdate(QList<bool> l_items_for_remove)
{
    //remove unnecessary data from s_struct
    for (int i=l_items_for_remove.size()-1; i>=0; i--)
    {
        if (l_items_for_remove[i]==0)
            data_->erase(i);
    }

    initDataInComboBoxFromStructure();
    initTextBrowser();
}

//initialize combobox from structure
void ViewWindow::initDataInComboBoxFromStructure()
{
    ui_->comboBox->clear();

    for (int i=0; i<data_->size(); i++)
    {
        //QString site_name = data->at(i)->getSiteName();
        addToCombobox(data_->at(i)->getSiteName());
    }
}

void ViewWindow::addToCombobox(QString str)
{
    if (str=="")
        return;

    ui_->comboBox->insertItem(0, str);
    ui_->comboBox->setCurrentIndex (0);
}

int ViewWindow::showArticle(int struct_index, int article_index)
{
    if (struct_index>=data_->size()||struct_index<0)
    {
         //qDebug()<<"show article first if.";
        return 0;
    }
    if (data_->at(struct_index)->getArticlesSize() == 0)
    {
        //qDebug()<<"show article second if.";
        ui_->textBrowser->setHtml("");
        return 0;
    }
    if (article_index>=data_->at(struct_index)->getArticlesSize()||article_index<0)
    {
        if (!is_show_flag_)
            ui_->textBrowser->setHtml("");
         //qDebug()<<"show article third if.";
        return 0;
    }

    QString title_tmp = data_->at(struct_index)->articleAt(article_index).getTitle(),
            text_tmp = data_->at(struct_index)->articleAt(article_index).getText(),
            date_tmp = "";

    if (!checkForFilters(title_tmp, text_tmp))
    {
        is_show_flag_ = false;
        showArticle(struct_index,article_index+1);

        return 0;
    }
    is_show_flag_ = true;

    //date
    if (data_->at(struct_index)->articleAt(article_index).getDate()!="")
        date_tmp = "Date: " + data_->at(struct_index)->articleAt(article_index).getDate();


    ui_->textBrowser->setHtml(
                QString(
                    "<h2>%1</h2><i>%2</i><br>Link: <a href=\"%3\">%3</a><br><br>%4")
                .arg(title_tmp,
                     date_tmp,
                     data_->at(struct_index)->articleAt(article_index).getLink(),
                     text_tmp));

    return 1;
}

void ViewWindow::on_pushButton_clicked() // button '<'
{
    uint current_article_index_tmp = current_article_index_;
    if (current_article_index_tmp!=0)
        current_article_index_tmp--;
    if (showArticle(current_site_index_,current_article_index_tmp))
        current_article_index_ = current_article_index_tmp;
}

void ViewWindow::on_pushButton_2_clicked() // button '>'
{
    if (showArticle(current_site_index_,current_article_index_+1))
        current_article_index_++;
}

void ViewWindow::on_comboBox_currentIndexChanged(const QString &arg1) //event when content is changed
{
    qDebug()<<"[ViewWindow::on_comboBox_currentIndexChanged] current RSS:"<<arg1;
    initTextBrowser();
}
void ViewWindow::closeEvent(QCloseEvent *event)
{
        this->hide();
        event->ignore(); // Don't let the event propagate to the base class
}
void ViewWindow::showEvent(QShowEvent *)
{
    if (is_minimize_ || is_close_)
    {
        is_minimize_ =0;
        is_close_ = 0;
        return;
    }

    this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    initDataInComboBoxFromStructure();
}

void ViewWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QSize window_size = QWidget::size();
    width_ = window_size.width();
    height_ = window_size.height();

    ui_->comboBox->resize(window_size.width()-170, ui_->comboBox->height());

    ui_->textBrowser->resize(window_size.width()-10, window_size.height() - 105);

    image_X_label_->setGeometry(QRect(window_size.width()-35,5,30,30)); //'X' button

    image_minimize_label_->setGeometry(QRect(window_size.width()-97,5,30,30)); //'Minimize' button

    image_maximize_label_->setGeometry(QRect(window_size.width()-66,5,30,30)); //'Maximize' button
}

void ViewWindow::mouseButtonPressed(QPoint p , QObject *o)
{
    if (ui_->comboBox->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
    }
    else if (ui_->pushButton->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
    }
    else if (ui_->pushButton_2->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
    }
    else if (image_add_rss_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        wsi_->show();
    }
    else if (image_refresh_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        refreshFeed();
    }
    else if (image_help_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        help_gui_->show();
    }
    else if (image_options_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        ow_->show();
    }
    else if (ui_->textBrowser->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
    }
    else if (image_X_label_->geometry().contains(p))
    {

        is_resizing_ = 0;
        is_press_released_ = 0;
        is_close_ = 1;
        this->hide();

        //e->ignore();
    }
    else if (image_maximize_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        if (!is_flag_maximized_)
        {
            //old_size = this->geometry();
            this->showMaximized();
            is_flag_maximized_ = 1;
        }
        else
        {
            this->showNormal();
            is_flag_maximized_ = 0;
        }
    }
    else if (image_minimize_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        is_minimize_ = 1;
        this->showMinimized();
    }
    else if (mouseInGrip(p) && o->objectName() == "ViewWindow")
    {
        is_press_released_ = 0;
        is_resizing_ = 1;
        resize_point_ = p;
    }
    else
    {
        if (o->objectName() == "ViewWindow")
            is_press_released_ = 1;
        is_resizing_ = 0;
    }
}
void ViewWindow::refreshFeed()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString content="";

    HTTP http;
    if (data_->size()<=current_site_index_ || current_site_index_<0 || data_->size() == 0)
    {
        QApplication::restoreOverrideCursor();
        return;
    }
    if (!http.getQuery(data_->at(current_site_index_)->getURL(),content))
    {
        rss_thread_->synchronizeData(current_site_index_, content);
        if (data_->at(current_site_index_)->getArticlesSize()<=current_article_index_)
            current_article_index_ = 0;
        showArticle(current_site_index_,current_article_index_);

    }
    QApplication::restoreOverrideCursor();
}

void ViewWindow::mouseDblClicked(QMouseEvent * mouseEvent)
{
    if (mouseEvent -> button() == Qt::LeftButton) {
        if (!is_flag_maximized_)
        {
            this->showMaximized();
            is_flag_maximized_ = 1;
        }
        else
        {
            this->showNormal();
            is_flag_maximized_ = 0;
        }
        is_press_released_ = 0;
    }

}
void ViewWindow::mouseMove(QPoint p, QMouseEvent *e, QObject *o)
{
    this->repaint();
    move_point_pos_ = p;

    if (is_X_changed_)
    {
        x_button_image_  = QImage("../resources/x_button.png");
        image_X_label_->setPixmap(QPixmap::fromImage(x_button_image_));
        image_X_label_->show();
        is_X_changed_=0;

    }

    if (is_maximize_changed_)
    {
        maximize_button_image_  = QImage("../resources/maximize_button.png");
        image_maximize_label_->setPixmap(QPixmap::fromImage(maximize_button_image_));
        image_maximize_label_->show();
        is_maximize_changed_=0;
    }
    if (is_minimize_changed_)
    {
        minimize_button_image_  = QImage("../resources/minimize_button.png");
        image_minimize_label_->setPixmap(QPixmap::fromImage(minimize_button_image_));
        image_minimize_label_->show();
        is_minimize_changed_=0;

    }

    if (p.x()>width_-36 && p.x()<width_ -4 && p.y()>4 && p.y()<36)
    {
        x_button_image_  = QImage("../resources/x_button_gradient.png");
        image_X_label_->setPixmap(QPixmap::fromImage(x_button_image_));
        image_X_label_->show();
        is_X_changed_ = 1;
        QApplication::restoreOverrideCursor();

    }
    else if (mouseInGrip(p) && o->objectName() == "ViewWindow")
    {
        QApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (is_resizing_)
    {
        QPoint delta = p - resize_point_;
        resize_point_ = p;
        this->setGeometry(this->x(), this->y(), this->width_+delta.x(), this->height_+delta.y());
    }
    else if (p.x()>width_-66 && p.x()<width_ -35 && p.y()>4 && p.y()<36)
    {
        maximize_button_image_  = QImage("../resources/maximize_button_gradient.png");
        image_maximize_label_->setPixmap(QPixmap::fromImage(maximize_button_image_));
        image_maximize_label_->show();
        is_maximize_changed_ = 1;
        QApplication::restoreOverrideCursor();
    }
    else if (p.x()>width_-96 && p.x()<width_ -65 && p.y()>4 && p.y()<36)
    {
        minimize_button_image_  = QImage("../resources/minimize_button_gradient.png");
        image_minimize_label_->setPixmap(QPixmap::fromImage(minimize_button_image_));
        image_minimize_label_->show();
        is_minimize_changed_ = 1;
        QApplication::restoreOverrideCursor();
    }
    else if (ui_->textBrowser->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }
    else if (image_add_rss_label_->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }
    else if (image_refresh_label_->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }
    else if (image_help_label_->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }
    else if (image_options_label_->geometry().contains(p))
        QApplication::restoreOverrideCursor();
    else if (ui_->comboBox->geometry().contains(p))
        QApplication::restoreOverrideCursor();
    else if (ui_->pushButton->geometry().contains(p))
        QApplication::restoreOverrideCursor();
    else if (ui_->pushButton_2->geometry().contains(p))
        QApplication::restoreOverrideCursor();
    else if (is_press_released_ && o->objectName() == "ViewWindow" && !is_flag_maximized_)
    {
        QApplication::restoreOverrideCursor();
        move(e->globalX()-cur_point_.x(),e->globalY()-cur_point_.y());
    }
    else
        QApplication::restoreOverrideCursor();
}

//mouse move, mouse press, mouse release events
bool ViewWindow::eventFilter(QObject *o, QEvent *event)
{
    QPoint p = this->mapFromGlobal(QCursor::pos());

    if (event->type() == QEvent::MouseButtonDblClick && o->objectName() == "ViewWindow" && is_press_released_)
    {
        QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
        mouseDblClicked(mouseEvent);
    }

    if (event->type() == QEvent::MouseButtonPress)
    {
        cur_point_ = p;
        mouseButtonPressed(p, o);

    }

    if (event->type() == QEvent::MouseButtonRelease)
    {
        is_press_released_ = 0;
        is_resizing_ = 0;
        resize_point_ = p;
    }

    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        mouseMove(p, e, o);
    }
    return 0;
}

void ViewWindow::paintEvent(QPaintEvent *e) //paint backgraund image
{
   //setAttribute(Qt::WA_OpaquePaintEvent);
   gradientRect(0,0,this->width_, this->height_);
   QPainter painter(this);
   QPen linepen(Qt::black);
   linepen.setCapStyle(Qt::RoundCap);
   linepen.setWidth(2);
   painter.setRenderHint(QPainter::Antialiasing,true);
   painter.setPen(linepen);
   painter.drawRect(0,0,this->width_, this->height_);

   linepen.setColor(Qt::gray);
   linepen.setWidth(6);
   painter.setPen(linepen);
   painter.drawRect(this->width_-10, this->height_-10, 10,10);

   linepen.setColor(Qt::black);
   linepen.setWidth(2);
   painter.setPen(linepen);
   //add rss feed button
   painter.drawRect(3,3,44,44);

   //options
   painter.drawRect(47,3,45,44);
   //refresh
   painter.drawRect(92,3,45,44);
   //help
   painter.drawRect(137,3,45,44);


   if (image_add_rss_label_->geometry().contains(move_point_pos_))
       gradientRect(4,4,42,42);
   else if (image_options_label_->geometry().contains(move_point_pos_))
       gradientRect(48,4,43,42);
   else if (image_refresh_label_->geometry().contains(move_point_pos_))
       gradientRect(93,4,43,42);
   else if (image_help_label_->geometry().contains(move_point_pos_))
       gradientRect(138,4,43,42);


}

int ViewWindow::checkForFilters(QString &title, QString &article)
{
    if (filters_qlist.size() == 0)
        return 1;

    bool isHave = false;
    for (int i=0; i<filters_qlist.size(); i++)
    {
        QStringList sl = title.split(filters_qlist[i]);
        if(sl.size()>1)
        {
            title = "";
            for (int j=0; j<sl.size(); j++)
            {
                isHave = true;
                if (j == sl.size()-1)
                {
                    title+=sl.value(j);
                    break;
                }
                if (checkForFontTag(sl.value(j+1)))
                    title+=sl.value(j) + "<FONT style=\"BACKGROUND-COLOR: yellow\">" + filters_qlist[i] + "</FONT>";
                else
                    title+=sl.value(j) + filters_qlist[i];
            }
        }
        sl = article.split(filters_qlist[i]);
        if (sl.size()>1)
        {
            article = "";
            for (int j=0; j<sl.size(); j++)
            {
                isHave = true;
                if (j == sl.size()-1)
                {
                    article+=sl.value(j);
                    break;
                }
                if (checkForFontTag(sl.value(j+1)))
                    article+=sl.value(j) + "<FONT style=\"BACKGROUND-COLOR: yellow\">" + filters_qlist[i] + "</FONT>";
                else
                    article+=sl.value(j) + filters_qlist[i];
            }
        }
    }
    if (isHave)
        return 1;
    return 0;
}

int ViewWindow::checkForFontTag(QString str1)
{
    QString font = "</FONT>";
    for (int i=0; i<str1.length(); i++)
    {
        if (i==font.length())
            return 0;
        if (str1[i]!=font[i])
            return 1;
    }
    return 1;
}

void ViewWindow::initFilters()
{
    boost::ptr_vector<QString>::iterator it;
    boost::ptr_vector<QString> tmp;
    data_base.getFilterList(&tmp);

    for (it=tmp.begin(); it!=tmp.end(); ++it)
        filters_qlist.append(*it);
}

void ViewWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key == 16777236) //->
    {
        if (showArticle(current_site_index_,current_article_index_+1))
            current_article_index_++;
    }
    else if(key==16777234)//<-
    {
        uint current_article_index_tmp = current_article_index_;
        if (current_article_index_tmp!=0)
            current_article_index_tmp--;
        if (showArticle(current_site_index_,current_article_index_tmp))
            current_article_index_ = current_article_index_tmp;
    }
}

void ViewWindow::gradientRect(int x, int y, int width, int height)
{
    QRect myQRect (x,y,width, height);
    QPainter painter(this);
    //QLinearGradient gradient(myQRect.topLeft(), myQRect.bottomRight()); // diagonal gradient from top-left to bottom-right
    QLinearGradient gradient(myQRect.bottomLeft(), myQRect.topLeft());
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);
    painter.fillRect(myQRect, gradient);
}
bool ViewWindow::mouseInGrip(QPoint mousePos)
{
    return ((mousePos.x() > (this->width_  - 10))&&  (mousePos.y() > (this->height_ - 10)));
}
