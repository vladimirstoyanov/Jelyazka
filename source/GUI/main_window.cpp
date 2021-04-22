/*
    mainwindow.cpp
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
#include "main_window.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent)
    , add_rss_button_image_ ()
    , is_resizing_          (false)
    , image_add_rss_label_  (std::make_shared<QLabel>(this))
    , image_options_label_  (std::make_shared<QLabel>(this))
    , image_refresh_label_  (std::make_shared<QLabel>(this))
    , image_help_label_     (std::make_shared<QLabel>(this))
    , image_X_label_        (std::make_shared<QLabel>(this))
    , image_minimize_label_ (std::make_shared<QLabel>(this))
    , image_maximize_label_ (std::make_shared<QLabel>(this))
    , ui_                   (std::make_shared<Ui::MainWindow> ())
{
    setupGui();
}

MainWindow::~MainWindow()
{
}

//initialize combobox from structure
void MainWindow::initDataInComboBoxFromStructure()
{
    std::map<QString, RSSData>::iterator it;
    ui_->titleComboBox->clear();

    for (it = rss_data_.begin(); it!=rss_data_.end(); ++it)
    {
        addToCombobox(it->first);
    }
}

void MainWindow::addToCombobox(const QString &str)
{
    if (str=="")
    {
        return;
    }

    ui_->titleComboBox->insertItem(0, str);
    ui_->titleComboBox->setCurrentIndex (0);
}

void MainWindow::setHtmlContent (const RSSArticle rss_article)
{
    ui_->textBrowser->setHtml(
                QString("<h2>%1</h2><i>%2</i><br>Link: <a href=\"%3\">%3</a><br><br>%4")
                .arg(rss_article.getTitle(),
                     rss_article.getDate(),
                     rss_article.getLink(),
                     rss_article.getText()));
}

void MainWindow::showArticle()
{
    QString web_site_name = ui_->titleComboBox->currentText();
    std::map<QString, RSSData>::iterator it;
    it = rss_data_.find(web_site_name);
    if (it==rss_data_.end())
    {
        ui_->textBrowser->setHtml("");
        return;
    }

    setHtmlContent (it->second.getCurrentArticle());
}

void MainWindow::showNextArticle()
{
    //get current value form combobox
    QString web_site_name = ui_->titleComboBox->currentText();
    std::map<QString, RSSData>::iterator it;
    it = rss_data_.find(web_site_name);
    if (it==rss_data_.end())
    {
        ui_->textBrowser->setHtml("");
        return;
    }
    it->second.getNextArticle();
    setHtmlContent (it->second.getCurrentArticle());
}

void MainWindow::showPreviousArticle()
{
    //get current value form combobox
    QString web_site_name = ui_->titleComboBox->currentText();
    std::map<QString, RSSData>::iterator it;
    it = rss_data_.find(web_site_name);
    if (it==rss_data_.end())
    {
        ui_->textBrowser->setHtml("");
        return;
    }
    it->second.getPreviousArticle();
    setHtmlContent (it->second.getCurrentArticle());
}

void MainWindow::on_previousButton_clicked() // button '<'
{
    showPreviousArticle();
}

void MainWindow::on_nextButton_clicked() // button '>'
{
    showNextArticle();
}

void MainWindow::on_titleComboBox_currentIndexChanged(const QString &) //event when content is changed
{
    showArticle();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    event->ignore(); // Don't let the event propagate to the base class
}

void MainWindow::showEvent(QShowEvent *)
{
    if (is_minimize_ || is_close_)
    {
        is_minimize_ =0;
        is_close_ = 0;
        return;
    }

    this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QSize window_size = QWidget::size();
    width_ = window_size.width();
    height_ = window_size.height();

    ui_->titleComboBox->resize(window_size.width()-170, ui_->titleComboBox->height());
    ui_->textBrowser->resize(window_size.width()-10, window_size.height() - 105);
    image_X_label_->setGeometry(QRect(window_size.width()-35,5,30,30)); //'X' button
    image_minimize_label_->setGeometry(QRect(window_size.width()-97,5,30,30)); //'Minimize' button
    image_maximize_label_->setGeometry(QRect(window_size.width()-66,5,30,30)); //'Maximize' button
}

void MainWindow::mouseButtonPressed(QPoint p , QObject *o)
{
    if (ui_->titleComboBox->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
    }
    else if (ui_->previousButton->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
    }
    else if (ui_->nextButton->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
    }
    else if (image_add_rss_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        //wsi_->show();
        emit (stateChanged("ShowRssSearchWindow"));
    }
    else if (image_refresh_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        //refreshFeed();
    }
    else if (image_help_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        //help_gui_->show();
        emit (stateChanged("ShowHelpWindow"));
    }
    else if (image_options_label_->geometry().contains(p))
    {
        is_resizing_ = 0;
        is_press_released_ = 0;
        //ow_->show();
        emit (stateChanged("ShowOptionWindow"));
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
        //this->hide();
        emit (stateChanged("HideMainWindow"));

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
    else if (mouseInGrip(p) && o->objectName() == "MainWindow")
    {
        is_press_released_ = 0;
        is_resizing_ = 1;
        resize_point_ = p;
    }
    else
    {
        if (o->objectName() == "MainWindow")
            is_press_released_ = 1;
        is_resizing_ = 0;
    }
}

void MainWindow::mouseDblClicked(QMouseEvent * mouseEvent)
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
void MainWindow::mouseMove(QPoint p, QMouseEvent *e, QObject *o)
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

    else if (mouseInGrip(p) && o->objectName() == "MainWindow")
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
    {
        QApplication::restoreOverrideCursor();
    }

    else if (ui_->titleComboBox->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }

    else if (ui_->previousButton->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }

    else if (ui_->nextButton->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }

    else if (is_press_released_ && o->objectName() == "MainWindow" && !is_flag_maximized_)
    {
        QApplication::restoreOverrideCursor();
        move(e->globalX()-current_point_.x(),e->globalY()-current_point_.y());
    }

    else
    {
        QApplication::restoreOverrideCursor();
    }
}

//mouse move, mouse press, mouse release events
bool MainWindow::eventFilter(QObject *o, QEvent *event)
{
    QPoint p = this->mapFromGlobal(QCursor::pos());

    if (event->type() == QEvent::MouseButtonDblClick && o->objectName() == "MainWindow" && is_press_released_)
    {
        QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
        mouseDblClicked(mouseEvent);
    }

    if (event->type() == QEvent::MouseButtonPress)
    {
        current_point_ = p;
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

void MainWindow::paintEvent(QPaintEvent *e) //paint backgraund image
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
   {
       gradientRect(4,4,42,42);
   }

   else if (image_options_label_->geometry().contains(move_point_pos_))
   {
       gradientRect(48,4,43,42);
   }

   else if (image_refresh_label_->geometry().contains(move_point_pos_))
   {
       gradientRect(93,4,43,42);
   }

   else if (image_help_label_->geometry().contains(move_point_pos_))
   {
       gradientRect(138,4,43,42);
   }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key == 16777236) //-> key pressed
    {
        showNextArticle();
    }
    else if(key==16777234)//<- key pressed
    {
        showPreviousArticle();
    }
}

void MainWindow::gradientRect(int x, int y, int width, int height)
{
    QRect myQRect (x,y,width, height);
    QPainter painter(this);
    QLinearGradient gradient(myQRect.bottomLeft(), myQRect.topLeft());
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);
    painter.fillRect(myQRect, gradient);
}

bool MainWindow::mouseInGrip(QPoint mousePos)
{
    return ((mousePos.x() > (this->width_  - 10))&&  (mousePos.y() > (this->height_ - 10)));
}

void MainWindow::onUpdateRSSData()
{
    qDebug()<<__PRETTY_FUNCTION__;
    rss_data_.clear(); //
    rss_data_ = data_base.getRssData();
    initDataInComboBoxFromStructure();
    showArticle ();

    this->show();
}

void MainWindow::onRssDataUpdated (const std::vector<RSSData> &updated_rss_data)
{
    std::map<QString, RSSData>::iterator it;

    for (const RSSData &item: updated_rss_data)
    {
         it = rss_data_.find(item.getSiteName());
         if (it!=rss_data_.end())
         {
             for (int j=item.getArticlesSize()-1; j>=0; --j)
             {
                 it->second.articlesPushFront(item.articleAt(j));
             }
         }
    }
}


void MainWindow::setupGui()
{
    ui_->setupUi(this);

    //make window without frames
    this->setWindowFlags( Qt::FramelessWindowHint);

    //set minimum width and height
    this->setMinimumHeight(200);
    this->setMinimumWidth(350);

    //initFilters();

    is_X_changed_ = 0;
    is_minimize_changed_= 0;
    is_maximize_changed_= 0;
    is_flag_maximized_ = 0;
    is_press_released_ = 0;

    qApp->installEventFilter(this);

    //when click link in textBrowser, open default browser and load url
    ui_->textBrowser->setOpenLinks(1);
    ui_->textBrowser->setOpenExternalLinks(1);

    //load "Add RSS" image
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
    x_button_image_  = QImage("../resources/x_button.png");
    image_X_label_->setPixmap(QPixmap::fromImage(x_button_image_));
    image_X_label_->setGeometry(QRect(window_size.width()-35,5,30,30));
    image_X_label_->show();
    image_X_label_->setToolTip("Close");
    #ifdef _WIN32
        image_add_rss_label_->setToolTipDuration(5000);
    #endif

    //laod "Minimize" image
    minimize_button_image_  = QImage("../resources/minimize_button.png");
    image_minimize_label_->setPixmap(QPixmap::fromImage(minimize_button_image_));
    image_minimize_label_->setGeometry(QRect(window_size.width()-97,5,30,30));
    image_minimize_label_->show();
    image_minimize_label_->setToolTip("Minimize");
    #ifdef _WIN32
        image_add_rss_label_->setToolTipDuration(5000);
    #endif

    //laod "Maximize" image
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
