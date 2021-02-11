#include "GUI/Options/feeds_options.h"

FeedsOptions::FeedsOptions(QWidget *parent, const int tree_widget_width, const int ok_button_height):
     cf_find_feed_ (std::make_shared<QLineEdit> (parent))
    , cf_label_search_ (std::make_shared<QLabel>(parent))
    , feed_list_  (std::make_shared<QListWidget>(parent))
    , ok_button_height_ (ok_button_height)
    , tree_widget_width_ (tree_widget_width)
    , parent (parent)
{


}

FeedsOptions::~FeedsOptions()
{
    l_old_feed_list_.clear();
}

void FeedsOptions::resize()
{
    positioningFeedsOptionWidgets();
}

void FeedsOptions::saveSettings ()
{

}

void FeedsOptions::loadSettings ()
{

}

void FeedsOptions::setupGui ()
{
    feed_list_->setSelectionMode(QAbstractItemView::MultiSelection);

    connect(cf_find_feed_.get(),SIGNAL(textChanged(QString)), this, SLOT(on_textChanged(QString)));

    cf_label_search_->setText("Search");
    positioningFeedsOptionWidgets();

    feed_list_->show();
    cf_find_feed_->show();
    cf_label_search_->show();
}
void FeedsOptions::show ()
{
    positioningFeedsOptionWidgets();

    //ui_->removeButton->show(); //ToDo: add this object
    feed_list_->show();
    cf_find_feed_->show();
    cf_label_search_->show();
}
void FeedsOptions::hide ()
{
    //ui_->removeButton->hide(); //ToDo: add this object
    feed_list_->hide();
    cf_find_feed_->hide();
    cf_label_search_->hide();
}

void FeedsOptions::positioningFeedsOptionWidgets()
{
    int width = (parent->width() - (25 + tree_widget_width_));

    cf_label_search_->setGeometry(tree_widget_width_  + 5,
                                 5,
                                 50,
                                 cf_label_search_->height());

    cf_find_feed_->setGeometry(cf_label_search_->x() + cf_label_search_width()+5,
                              5,
                              width - (cf_label_search_width() + 5) ,
                              cf_find_feed_->height());

    feed_list_->setGeometry(cf_label_search_->x(),
                            cf_find_feed_->y() + cf_find_feed_->height()+10,
                            width,
                            parent->height()-(20 +cf_find_feed_->height() + ok_button_height_));

    /*
    ui_->removeButton->setGeometry(feed_list_->x(),
                                  ui_->okButton->y(),
                                  ui_->removeButton->width(),
                                  ui_->removeButton->height());
                                  */
}


int FeedsOptions::cf_label_search_width()
{
    QFontMetrics fm(cf_label_search_->font());
    QRect rect = fm.boundingRect(cf_label_search_->text());

    return rect.width();
}

void FeedsOptions::fillFeedListView()
{
    std::vector<QString> tmp;
    data_base_.getFeeds(&tmp);

    l_old_feed_list_.clear();

    for (unsigned int i=0; i<tmp.size(); i++)
    {
        feed_list_->insertItem(feed_list_->count(), tmp[i]);
        l_old_feed_list_.push_back(tmp[i]);
    }
}

//add string to feed_list (QListWidget var)
int FeedsOptions::addToFeedList(const QString &feed_name)
{
    int count = feed_list_->count(); //get count of listWidget
    if (feed_name=="")
    {
        return 1;
    }

    //check for identical strings
    for(int row = 0; row < feed_list_->count(); row++)
    {
        QListWidgetItem *item = feed_list_->item(row);
        if (feed_name == item->text())
        {
            return 1;
        }
    }

    feed_list_->insertItem(count, feed_name); //insert new element in the end of list widget

    return 0;
}

void FeedsOptions::initilize ()
{
    feed_list_->clear();
    fillFeedListView();
}

//'Remove' button click event
void FeedsOptions::on_removeButton_clicked()
{
    //get selected items
    QModelIndexList list =feed_list_->selectionModel()->selectedIndexes();
    QStringList slist;
    foreach(const QModelIndex &index, list){
        slist.append( index.data(Qt::DisplayRole ).toString());
        feed_list_->takeItem(index.row());
    }

    //remove selected items from db
    for (int i=0; i< slist.size(); ++i)
    {
        data_base_.removeDataFromFeedList(slist.at(i));
    }
}
