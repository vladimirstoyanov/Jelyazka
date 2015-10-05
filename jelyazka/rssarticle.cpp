#include "rssarticle.h"

RSSArticle::RSSArticle()
{

}

//get
QString RSSArticle::getTitle()
{
    return title;
}

QString RSSArticle::getLink()
{
    return link;
}

QString RSSArticle::getText()
{
    return text;
}

//set
void RSSArticle::setTitle(QString title_tmp)
{
    title = title_tmp;
}

void RSSArticle::setLink(QString link_tmp)
{
    link = link_tmp;
}

void RSSArticle::setText(QString text_tmp)
{
    text = text_tmp;
}
