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


ViewWindow::ViewWindow(QWidget *parent, SiteStruct *tmp_site_struct):
    QWidget(parent),
    ui(new Ui::ViewWindow)
{
    ui->setupUi(this);

    //make window without frames
    this->setWindowFlags( Qt::FramelessWindowHint);

    //set minimum width and height
    this->setMinimumHeight(200);
    this->setMinimumWidth(350);

    resizing = false;

    initFilters();

    help_gui = new Help();

    site_struct = tmp_site_struct;
    wsi = new WebSearchInterface (0, site_struct, this);

    ow = new OptionsWindow(0,site_struct, this);
    connect(site_struct,SIGNAL(Finish(QString, bool)),ow,SLOT(onFinish(QString, bool)));

    isXchanged = 0;
    isMinimizechanged=0;
    isMaximizechanged=0;
    flagMaximized = 0;
    pressReleased = 0;

    qApp->installEventFilter(this);

    //when click link in textBrowser, open default browser and load url
    ui->textBrowser->setOpenLinks(1);
    ui->textBrowser->setOpenExternalLinks(1);

    //load "Add RSS" image
    imageAddRSSLabel = new QLabel(this);
    add_rss_button_img  = QImage("../resources/rss-icon-40x40.png");
    imageAddRSSLabel->setPixmap(QPixmap::fromImage(add_rss_button_img));
    imageAddRSSLabel->setGeometry(QRect(5,5,40,40));
    imageAddRSSLabel->setWhatsThis("Add RSS Feeds");
    imageAddRSSLabel->show();
    imageAddRSSLabel->setToolTip("Add RSS Feed(s)");
	#ifdef _WIN32
		imageAddRSSLabel->setToolTipDuration(5000);
	#endif
    


    //laod "Options" image
    imageOptionsLabel = new QLabel(this);
    options_button_img  = QImage("../resources/Black_Settings.png");
    imageOptionsLabel->setPixmap(QPixmap::fromImage(options_button_img));
    imageOptionsLabel->setGeometry(QRect(50,5,40,40));
    imageOptionsLabel->setWhatsThis("Options");
    imageOptionsLabel->show();
    imageOptionsLabel->setToolTip("Options");
	#ifdef _WIN32
		imageAddRSSLabel->setToolTipDuration(5000);
	#endif

    //laod "Refresh" image
    imageRefreshLabel = new QLabel(this);
    refresh_button_img = QImage("../resources/refresh.png");
    imageRefreshLabel->setPixmap(QPixmap::fromImage(refresh_button_img));
    imageRefreshLabel->setGeometry(QRect(95,5,40,40));
    imageRefreshLabel->setWhatsThis("Help");
    imageRefreshLabel->show();
    imageRefreshLabel->setToolTip("Refresh");
    #ifdef _WIN32
		imageAddRSSLabel->setToolTipDuration(5000);
	#endif

    //laod "Help" image
    imageHelpLabel = new QLabel(this);
    help_button_img  = QImage("../resources/icon40x40help.png");
    imageHelpLabel->setPixmap(QPixmap::fromImage(help_button_img));
    imageHelpLabel->setGeometry(QRect(140,5,40,40));
    imageHelpLabel->setWhatsThis("Help");
    imageHelpLabel->show();
    imageHelpLabel->setToolTip("Help");
	#ifdef _WIN32
		imageAddRSSLabel->setToolTipDuration(5000);
	#endif

    QSize window_size = QWidget::size();
    width = window_size.width();
    height = window_size.height();

    //laod "X" image
    imageXLabel = new QLabel(this);
    x_button_img  = QImage("../resources/x_button.png");
    imageXLabel->setPixmap(QPixmap::fromImage(x_button_img));
    imageXLabel->setGeometry(QRect(window_size.width()-35,5,30,30));
    imageXLabel->show();
    imageXLabel->setToolTip("Close");
	#ifdef _WIN32
		imageAddRSSLabel->setToolTipDuration(5000);
	#endif

    //laod "Minimize" image
    imageMinimizeLabel = new QLabel(this);
    minimize_button_img  = QImage("../resources/minimize_button.png");
    imageMinimizeLabel->setPixmap(QPixmap::fromImage(minimize_button_img));
    imageMinimizeLabel->setGeometry(QRect(window_size.width()-97,5,30,30));
    imageMinimizeLabel->show();
    imageMinimizeLabel->setToolTip("Minimize");
	#ifdef _WIN32
		imageAddRSSLabel->setToolTipDuration(5000);
	#endif

    //laod "Maximize" image
    imageMaximizeLabel = new QLabel(this);
    maximize_button_img  = QImage("../resources/maximize_button.png");
    imageMaximizeLabel->setPixmap(QPixmap::fromImage(maximize_button_img));
    imageMaximizeLabel->setGeometry(QRect(window_size.width()-66,5,30,30));
    imageMaximizeLabel->show();
    imageMaximizeLabel->setToolTip("Maximize");
	#ifdef _WIN32
		imageAddRSSLabel->setToolTipDuration(5000);
	#endif
    minimize = 0;
    close = 0;

}

ViewWindow::~ViewWindow()
{
    delete ui;
    delete imageAddRSSLabel;
    delete imageHelpLabel;
    delete imageOptionsLabel;
    delete imageRefreshLabel;
    delete imageXLabel;
    delete imageMinimizeLabel;
    delete imageMaximizeLabel;
    delete wsi;
    delete help_gui;
    //delete size_grip;
}

//initialize text browser widget
void ViewWindow::initTextBrowser()
{
    //get current value form combobox
    QString cur_text= ui->comboBox->currentText();


    //find index of ui->comboBox->currentText() in 's_struct' structure
    int index=-1;
    for (uint i=0; i<site_struct->s_struct.size(); i++)
    {
        if (site_struct->s_struct[i].getSiteName()==cur_text)
        {
            index = i;
            break;
        }
    }

    if (index==-1)
    {
        ui->textBrowser->setHtml("");
        return;
    }

    showArticle(index,0); //show article in text browser with index=0 from 's_struct' structure
    current_article_index = 0;
    current_site_index=index;
}

void ViewWindow::onUpdate(QList<bool> l_items_for_remove)
{
    //remove unnecessary data from s_struct
    for (int i=l_items_for_remove.size()-1; i>=0; i--)
    {
        if (l_items_for_remove[i]==0)
            site_struct->s_struct.erase(site_struct->s_struct.begin() + i);
    }

    initDataInComboBoxFromStructure();
    initTextBrowser();
}

//initialize combobox from structure
void ViewWindow::initDataInComboBoxFromStructure()
{
    ui->comboBox->clear();

    for (uint i=0; i<site_struct->s_struct.size(); i++)
        addToCombobox(site_struct->s_struct[i].getSiteName());
}

void ViewWindow::addToCombobox(QString str)
{
    if (str=="")
        return;

    ui->comboBox->insertItem(0, str);
    ui->comboBox->setCurrentIndex (0);
}

int ViewWindow::showArticle(uint struct_index, uint article_index)
{
    if (struct_index>=site_struct->s_struct.size()||struct_index<0)
    {
         //qDebug()<<"show article first if.";
        return 0;
    }
    if (site_struct->s_struct[struct_index].getArticlesSize() == 0)
    {
        //qDebug()<<"show article second if.";
        ui->textBrowser->setHtml("");
        return 0;
    }
    if (article_index>=site_struct->s_struct[struct_index].getArticlesSize()||article_index<0)
    {
        if (!show_flag)
            ui->textBrowser->setHtml("");
         //qDebug()<<"show article third if.";
        return 0;
    }

    QString title_tmp = site_struct->s_struct[struct_index].articleAt(article_index).getTitle(),text_tmp = site_struct->s_struct[struct_index].articleAt(article_index).getText();
    if (!checkForFilters(title_tmp, text_tmp))
    {
        show_flag = false;
        showArticle(struct_index,article_index+1);

        return 0;
    }
    show_flag = true;

    ui->textBrowser->setHtml(QString("<h2>%1</h2>\nLink: <a href=\"%2\">%2</a><br><br>%3").arg(title_tmp,site_struct->s_struct[struct_index].articleAt(article_index).getLink(),text_tmp));

    return 1;
}

void ViewWindow::on_pushButton_clicked() // button '<'
{
    uint current_article_index_tmp = current_article_index;
    if (current_article_index_tmp!=0)
        current_article_index_tmp--;
    if (showArticle(current_site_index,current_article_index_tmp))
        current_article_index = current_article_index_tmp;
}

void ViewWindow::on_pushButton_2_clicked() // button '>'
{
    if (showArticle(current_site_index,current_article_index+1))
        current_article_index++;
}

void ViewWindow::on_comboBox_currentIndexChanged(const QString &arg1) //event when content is changed
{
    initTextBrowser();
}
void ViewWindow::closeEvent(QCloseEvent *event)
{
        this->hide();
        event->ignore(); // Don't let the event propagate to the base class
}
void ViewWindow::showEvent(QShowEvent *)
{
    if (minimize || close)
    {
        minimize=0;
        close = 0;
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
    width = window_size.width();
    height = window_size.height();

    ui->comboBox->resize(window_size.width()-170, ui->comboBox->height());

    ui->textBrowser->resize(window_size.width()-10, window_size.height() - 105);

    imageXLabel->setGeometry(QRect(window_size.width()-35,5,30,30)); //'X' button

    imageMinimizeLabel->setGeometry(QRect(window_size.width()-97,5,30,30)); //'Minimize' button

    imageMaximizeLabel->setGeometry(QRect(window_size.width()-66,5,30,30)); //'Maximize' button
}

void ViewWindow::mouseButtonPressed(QPoint p , QObject *o)
{
    if (ui->comboBox->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
    }
    else if (ui->pushButton->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
    }
    else if (ui->pushButton_2->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
    }
    else if (imageAddRSSLabel->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
        wsi->show();
    }
    else if (imageRefreshLabel->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
        refreshFeed();
    }
    else if (imageHelpLabel->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
        help_gui->show();
    }
    else if (imageOptionsLabel->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
        ow->show();
    }
    else if (ui->textBrowser->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
    }
    else if (imageXLabel->geometry().contains(p))
    {

        resizing = 0;
        pressReleased = 0;
        close = 1;
        this->hide();

        //e->ignore();
    }
    else if (imageMaximizeLabel->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
        if (!flagMaximized)
        {
            //old_size = this->geometry();
            this->showMaximized();
            flagMaximized = 1;
        }
        else
        {
            this->showNormal();
            flagMaximized = 0;
        }
    }
    else if (imageMinimizeLabel->geometry().contains(p))
    {
        resizing = 0;
        pressReleased = 0;
        minimize = 1;
        this->showMinimized();
    }
    else if (mouseInGrip(p) && o->objectName() == "ViewWindow")
    {
        pressReleased = 0;
        resizing = 1;
        resizePoint = p;
    }
    else
    {
        if (o->objectName() == "ViewWindow")
            pressReleased = 1;
        resizing = 0;
    }
}
void ViewWindow::refreshFeed()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString content="";

    Net net;
    if (site_struct->s_struct.size()<=current_site_index || current_site_index<0 || site_struct->s_struct.size() == 0)
    {
        QApplication::restoreOverrideCursor();
        return;
    }
    if (!net.getQuery(site_struct->s_struct[current_site_index].getURL(),content))
    {
        site_struct->synchronizeData(current_site_index, content);
        if (site_struct->s_struct[current_site_index].getArticlesSize()<=current_article_index)
            current_article_index = 0;
        showArticle(current_site_index,current_article_index);

    }
    QApplication::restoreOverrideCursor();
}
void ViewWindow::mouseDblClicked(QMouseEvent * mouseEvent)
{
    if (mouseEvent -> button() == Qt::LeftButton) {
        if (!flagMaximized)
        {
            this->showMaximized();
            flagMaximized = 1;
        }
        else
        {
            this->showNormal();
            flagMaximized = 0;
        }
        pressReleased = 0;
    }

}
void ViewWindow::mouseMove(QPoint p, QMouseEvent *e, QObject *o)
{
    this->repaint();
    movePointPos = p;

    if (isXchanged)
    {
        x_button_img  = QImage("../resources/x_button.png");
        imageXLabel->setPixmap(QPixmap::fromImage(x_button_img));
        imageXLabel->show();
        isXchanged=0;

    }

    if (isMaximizechanged)
    {
        maximize_button_img  = QImage("../resources/maximize_button.png");
        imageMaximizeLabel->setPixmap(QPixmap::fromImage(maximize_button_img));
        imageMaximizeLabel->show();
        isMaximizechanged=0;
    }
    if (isMinimizechanged)
    {
        minimize_button_img  = QImage("../resources/minimize_button.png");
        imageMinimizeLabel->setPixmap(QPixmap::fromImage(minimize_button_img));
        imageMinimizeLabel->show();
        isMinimizechanged=0;

    }

    if (p.x()>width-36 && p.x()<width -4 && p.y()>4 && p.y()<36)
    {
        x_button_img  = QImage("../resources/x_button_gradient.png");
        imageXLabel->setPixmap(QPixmap::fromImage(x_button_img));
        imageXLabel->show();
        isXchanged = 1;
        QApplication::restoreOverrideCursor();

    }
    else if (mouseInGrip(p) && o->objectName() == "ViewWindow")
    {
        QApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (resizing)
    {
        QPoint delta = p - resizePoint;
        resizePoint = p;
        this->setGeometry(this->x(), this->y(), this->width+delta.x(), this->height+delta.y());
    }
    else if (p.x()>width-66 && p.x()<width -35 && p.y()>4 && p.y()<36)
    {
        maximize_button_img  = QImage("../resources/maximize_button_gradient.png");
        imageMaximizeLabel->setPixmap(QPixmap::fromImage(maximize_button_img));
        imageMaximizeLabel->show();
        isMaximizechanged = 1;
        QApplication::restoreOverrideCursor();
    }
    else if (p.x()>width-96 && p.x()<width -65 && p.y()>4 && p.y()<36)
    {
        minimize_button_img  = QImage("../resources/minimize_button_gradient.png");
        imageMinimizeLabel->setPixmap(QPixmap::fromImage(minimize_button_img));
        imageMinimizeLabel->show();
        isMinimizechanged = 1;
        QApplication::restoreOverrideCursor();
    }
    else if (ui->textBrowser->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }
    else if (imageAddRSSLabel->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }
    else if (imageRefreshLabel->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }
    else if (imageHelpLabel->geometry().contains(p))
    {
        QApplication::restoreOverrideCursor();
    }
    else if (imageOptionsLabel->geometry().contains(p))
        QApplication::restoreOverrideCursor();
    else if (ui->comboBox->geometry().contains(p))
        QApplication::restoreOverrideCursor();
    else if (ui->pushButton->geometry().contains(p))
        QApplication::restoreOverrideCursor();
    else if (ui->pushButton_2->geometry().contains(p))
        QApplication::restoreOverrideCursor();
    else if (pressReleased && o->objectName() == "ViewWindow" && !flagMaximized)
    {
        QApplication::restoreOverrideCursor();
        move(e->globalX()-curPoint.x(),e->globalY()-curPoint.y());
    }
    else
        QApplication::restoreOverrideCursor();
}

//mouse move, mouse press, mouse release events
bool ViewWindow::eventFilter(QObject *o, QEvent *event)
{
    QPoint p = this->mapFromGlobal(QCursor::pos());

    if (event->type() == QEvent::MouseButtonDblClick && o->objectName() == "ViewWindow" && pressReleased)
    {
        QMouseEvent * mouseEvent = static_cast <QMouseEvent *> (event);
        mouseDblClicked(mouseEvent);
    }

    if (event->type() == QEvent::MouseButtonPress)
    {
        curPoint = p;
        mouseButtonPressed(p, o);

    }

    if (event->type() == QEvent::MouseButtonRelease)
    {
        pressReleased = 0;
        resizing = 0;
        resizePoint = p;
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
   gradientRect(0,0,this->width, this->height);
   QPainter painter(this);
   QPen linepen(Qt::black);
   linepen.setCapStyle(Qt::RoundCap);
   linepen.setWidth(2);
   painter.setRenderHint(QPainter::Antialiasing,true);
   painter.setPen(linepen);
   painter.drawRect(0,0,this->width, this->height);

   linepen.setColor(Qt::gray);
   linepen.setWidth(6);
   painter.setPen(linepen);
   painter.drawRect(this->width-10, this->height-10, 10,10);

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


   if (imageAddRSSLabel->geometry().contains(movePointPos))
       gradientRect(4,4,42,42);
   else if (imageOptionsLabel->geometry().contains(movePointPos))
       gradientRect(48,4,43,42);
   else if (imageRefreshLabel->geometry().contains(movePointPos))
       gradientRect(93,4,43,42);
   else if (imageHelpLabel->geometry().contains(movePointPos))
       gradientRect(138,4,43,42);


}

int ViewWindow::checkForFilters(QString &title, QString &article)
{
    if (l_filters.size() == 0)
        return 1;

    bool isHave = false;
    for (int i=0; i<l_filters.size(); i++)
    {
        QStringList sl = title.split(l_filters[i]);
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
                    title+=sl.value(j) + "<FONT style=\"BACKGROUND-COLOR: yellow\">" + l_filters[i] + "</FONT>";
                else
                    title+=sl.value(j) + l_filters[i];
            }
        }
        sl = article.split(l_filters[i]);
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
                    article+=sl.value(j) + "<FONT style=\"BACKGROUND-COLOR: yellow\">" + l_filters[i] + "</FONT>";
                else
                    article+=sl.value(j) + l_filters[i];
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
    QSqlQuery query;

    query.prepare( "SELECT * FROM filters" );

    if( !query.exec() )
    {
        qDebug()<<"Some error, when trying to read from \'filters' table...";
        return;
    }

    while( query.next() )
    {
        l_filters.append(query.value( 1 ).toByteArray().data());
    }

}

void ViewWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key == 16777236) //->
    {
        if (showArticle(current_site_index,current_article_index+1))
            current_article_index++;
    }
    else if(key==16777234)//<-
    {
        uint current_article_index_tmp = current_article_index;
        if (current_article_index_tmp!=0)
            current_article_index_tmp--;
        if (showArticle(current_site_index,current_article_index_tmp))
            current_article_index = current_article_index_tmp;
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
    return ((mousePos.x() > (this->width  - 10))&&  (mousePos.y() > (this->height - 10)));
}
