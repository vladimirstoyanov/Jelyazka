#include "rssarticle.h"

RSSArticle::RSSArticle():
    is_marked_for_remove_(false)
{

}

//get
QString RSSArticle::getTitle()
{
    return title_;
}

QString RSSArticle::getLink()
{
    return link_;
}

QString RSSArticle::getText()
{
    return text_;
}

QString RSSArticle::getDate()
{
    return date_;
}

bool RSSArticle::getIsMarkedForRemove()
{
    return is_marked_for_remove_;
}

//set
void RSSArticle::setTitle(QString title)
{
    title_ = title;
}

void RSSArticle::setLink(QString link)
{
    link_ = link;
}

void RSSArticle::setText(QString text)
{
    text_ = text;
}

void RSSArticle::setDate(QString date)
{
    date_ = date;
}

void RSSArticle::setIsMarkedForRemove (bool is_marked_for_remove)
{
    is_marked_for_remove_ = is_marked_for_remove;
}
