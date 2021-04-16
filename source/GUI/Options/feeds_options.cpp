#include "GUI/Options/feeds_options.h"

FeedsOptions::FeedsOptions(QWidget *parent,
                           const int tree_widget_width,
                           const int ok_button_height,
                           const int ok_button_y):
    feed_list_  (std::make_shared<QListWidget>(parent))
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
    for (int i=0; i< removed_feeds_.size(); ++i)
    {
        data_base_.removeDataFromFeedList(removed_feeds_.at(i));
        data_base_.removeDataFromRssData(removed_feeds_.at(i));
    }
}

void FeedsOptions::loadSettings ()
{

}

void FeedsOptions::setupGui ()
{
    feed_list_->setSelectionMode(QAbstractItemView::MultiSelection);

    connect(remove_button_.get(),
                SIGNAL(clicked()),
                this,
                SLOT(on_removeButton_clicked()));

    show();
}
void FeedsOptions::show ()
{
    positioningFeedsOptionWidgets();

    remove_button_->show();
    feed_list_->show();
}
void FeedsOptions::hide ()
{
    remove_button_->hide();
    feed_list_->hide();
}

void FeedsOptions::positioningFeedsOptionWidgets()
{
    int width = parent_->width();
    width -= (offset_between_widgets_*2 + tree_widget_width_);

    feed_list_->setGeometry(tree_widget_width_ + offset_between_widgets_,
                                offset_between_widgets_,
                                width,
                                parent_->height()-(offset_between_widgets_*3 + ok_button_height_));

    remove_button_->setGeometry(feed_list_->x(),
                                  ok_button_y_,
                                  remove_button_->width(),
                                  ok_button_height_);
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
    removed_feeds_.clear();
    fillFeedListView();
}

//'Remove' button click event
void FeedsOptions::on_removeButton_clicked()
{
    //get selected items
    QModelIndexList list =feed_list_->selectionModel()->selectedIndexes();

    foreach(const QModelIndex &index, list){
        removed_feeds_.append( index.data(Qt::DisplayRole ).toString());
        feed_list_->takeItem(index.row());
    }
}
