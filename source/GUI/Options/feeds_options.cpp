#include "GUI/Options/feeds_options.h"

FeedsOptions::FeedsOptions(QWidget *parent,
                           const int tree_widget_width,
                           const int ok_button_height,
                           const int ok_button_y):
     cf_find_feed_ (std::make_shared<QLineEdit> (parent))
    , cf_label_search_ (std::make_shared<QLabel>(parent))
    , feed_list_  (std::make_shared<QListWidget>(parent))
    , remove_button_ (std::make_shared<QPushButton> ("Remove", parent))
    , ok_button_height_ (ok_button_height)
    , ok_button_y_(ok_button_y)
    , offset_between_widgets_(5)
    , tree_widget_width_ (tree_widget_width)
    , parent_ (parent)
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

    show();
}
void FeedsOptions::show ()
{
    positioningFeedsOptionWidgets();

    remove_button_->show();
    feed_list_->show();
    cf_find_feed_->show();
    cf_label_search_->show();
}
void FeedsOptions::hide ()
{
    remove_button_->hide();
    feed_list_->hide();
    cf_find_feed_->hide();
    cf_label_search_->hide();
}

void FeedsOptions::positioningFeedsOptionWidgets()
{
    int width = parent_->width();
    width -= (offset_between_widgets_*2 + tree_widget_width_);

    cf_label_search_->setGeometry(tree_widget_width_ + offset_between_widgets_,
                                    offset_between_widgets_,
                                    50,
                                    cf_label_search_->height());

    cf_find_feed_->setGeometry(cf_label_search_->x() + cf_label_search_width()+offset_between_widgets_,
                                offset_between_widgets_,
                                width - (cf_label_search_width() + offset_between_widgets_) ,
                                cf_find_feed_->height());

    feed_list_->setGeometry(cf_label_search_->x(),
                                cf_find_feed_->y() + cf_find_feed_->height()+10,
                                width,
                                parent_->height()-(20 +cf_find_feed_->height() + ok_button_height_));

    remove_button_->setGeometry(feed_list_->x(),
                                  ok_button_y_,
                                  remove_button_->width(),
                                  ok_button_height_);
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

    for (const QString &item: tmp)
    {
        feed_list_->insertItem(feed_list_->count(), item);
        l_old_feed_list_.push_back(item);
    }
}

int FeedsOptions::addToFeedList(const QString &feed_name)
{
    int count = feed_list_->count();
    if (feed_name=="")
    {
        return 1;
    }

    //check for identical strings
    for(int row = 0; row < feed_list_->count(); ++row)
    {
        QListWidgetItem *item = feed_list_->item(row);
        if (feed_name == item->text())
        {
            return 1;
        }
    }

    feed_list_->insertItem(count, feed_name); //insert a new element in the end of 'feed_list_' widget

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
