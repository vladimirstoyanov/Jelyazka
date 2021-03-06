#include "RSS/parse_rss.h"

ParseRSS::ParseRSS()
{

}


void ParseRSS::getStoryTag (const QString &web_content, QString &storyOpenTag, QString &storyEndTag)
{
     Search search;

    int item_index=0;
    search.searchAfter(web_content,"<item ", &item_index);

    int entry_index=0;
    search.searchAfter(web_content,"<entry ", &entry_index);

    if (item_index!=-1)
    {
        storyOpenTag = "<item";
        storyEndTag = "</item";
        return;
    }
    storyOpenTag = "<entry";
    storyEndTag = "</entry";
}

int ParseRSS::checkWebSourceForRSSContent(const QString &web_source, QString &title, int &version)
{
        Search cs;
        QString begin="<?xml";
        //Logger log;
        //log.write(web_source, "web_source");
        if (web_source.length()<4)
        {
            //log.write("CheckForRss funtion: source.length()<4!");
            return 1;
        }
        int i=0, j=0, r=0, f=0;
        cs.searchAfter(web_source, "<?xml", &i);
        cs.searchAfter(web_source, "<rss", &j);
        cs.searchAfter(web_source, "<rdf", &r);
        cs.searchAfter(web_source, "<feed", &f);

        if (i==0 || (j==-1 && r==-1 && f ==-1) || (j!=-1 && i>j) || (r!=-1 && i>r) || (f!=-1 && i>f))
        {
            return 1;
        }

        if (f!=-1 && j==-1 && r==-1)
        {
            version = 2005;
        }

        //get rss title
        i=0;
        cs.searchAfter(web_source, "<title>", &i);
        if (i==-1)
        {
            //log.write("CheckForRss funtion: can't find <title>");
            return 1;
        }

        title = "";
        int n = web_source.length();

        if (i>=n-2)
        {
            return 1;
        }

        if (web_source[i] == '<' && web_source[i+1] == '!') //ignoring '<![CDATA'
        {
            title+=web_source[i++];
        }

        while (web_source[i]!='<')
        {
            title+=web_source[i++];

            if (i>=n-2)
            {
                //log.write("CheckForRss funtion: fail to get </title>.");
                return 1;
            }
            if (web_source[i] == '<' && web_source[i+1] == '!') //ignoring '<![CDATA'
            {
                title+=web_source[i++];
            }
        }


        i++;
        begin = "/title";

        for(j=0;j<begin.length(); j++)
        {
            if (web_source[i++]!=begin[j])
            {
                return 1;
            }
        }

        return 0;
}


void ParseRSS::getRSSDataByWebSource (const QString &web_source, std::shared_ptr<RSSData> rss_data)
{
    qDebug()<<__PRETTY_FUNCTION__;

    QString title="";
    int version=0;

    if (checkWebSourceForRSSContent(web_source, title, version)) //found rss
    {
        qDebug()<<__PRETTY_FUNCTION__<<": something wrong with checkWebSourceForRSSContent!";
        return;
    }
    QString encoding  = getEncodingByWebSource(web_source);

    rss_data->setSiteName(title);

    if (!version)
    {
        rss_data->setVersion(0);
        rss_data->setEncoding(encoding);
        getArticlesFromRSSContent(web_source, rss_data);
    }
    else
    {
        rss_data->setVersion("2005");
        getArticlesFromRDFContent(web_source, rss_data);
    }
}

void ParseRSS::findFeedDataRSS(int &index, const QString &content, RSSArticle &ar)
{
    int item_b_index=index, item_e_index=index;
    Search cs;
    int n = content.length();

    while (1)
    {
         cs.searchAfter(content,"<item", &item_b_index);
         if (item_b_index == -1) // if not found <item
         {
             index = -1;
             return;
         }

         item_e_index = item_b_index;
         cs.searchBefore(content,"</item", &item_e_index);

         if (item_e_index == -1)
         {
             index = -1;
             return;
         }

         if (item_b_index<n)
         {
             if (content[item_b_index] == 's') //if found <items tag
                 continue;
         }
         index = item_e_index;
         break;
    }

    index = item_e_index;
    QString title, link, text, date;

    if(getTextBetweenIndexes(item_b_index, item_e_index, "<title>", "</title>", title, content))
    {
         return;
    }
    convertString(title, false);
    if (getTextBetweenIndexes(item_b_index, item_e_index, "<link>", "</link>", link,content))
    {
         return;
    }
    convertString(link, true);
    getDescription(item_b_index, item_e_index, text, content);

    //get date if exist
    getTextBetweenIndexes(item_b_index, item_e_index, "<pubDate", "</pubDate>", date, content);

    ar.setLink(link);
    ar.setText(text);
    ar.setTitle(title);
    ar.setDate(date);
}

void ParseRSS::findFeedDataRDF(int &index, const QString &content, RSSArticle &ar)
{
    int item_b_index=index, item_e_index=index;
    Search cs;

     while (1)
     {
         cs.searchAfter(content,"<entry", &item_b_index);
         if (item_b_index == -1) // if not found <item
         {
             index = -1;
             return;
         }

         item_e_index = item_b_index;
         cs.searchBefore(content,"</entry", &item_e_index);

         if (item_e_index == -1)
         {
             index = -1;
             return;
         }

         index = item_e_index;
         break;
     }

     index = item_e_index;
     QString title, link, text, date;

     if(getTextBetweenIndexes(item_b_index, item_e_index, "<title", "</title>", title, content))
     {
         return;
     }
     convertString(title, false);
     int index_link = item_b_index;
     cs.searchBefore(content, "<link", &index_link);
     if (index_link == -1 || index_link>item_e_index)
     {
         return;
     }
     link = returnURL(content, index_link);
     convertString(link, true);

     getContent(item_b_index, item_e_index, text, content);

     //get date if exist
     getTextBetweenIndexes(item_b_index, item_e_index, "<pubDate", "</pubDate>", date, content);

     ar.setLink(link);
     ar.setText(text);
     ar.setTitle(title);
     ar.setDate(date);
}



int ParseRSS::getTextBetweenIndexes(const int item_b_index, const int item_e_index, const QString &begin_text, const QString &end_text, QString &text, const QString &content)
{
    Search cs;
    int tag_b_index, tag_e_index;

    tag_b_index =item_b_index;
    cs.searchAfter(content,begin_text, &tag_b_index);

    if (tag_b_index == -1)
    {
        return 1;
    }
    if (tag_b_index<item_b_index || tag_b_index > item_e_index)
    {
        return 1;
    }

    tag_e_index = tag_b_index;
    cs.searchBefore(content, end_text, &tag_e_index);

    if (tag_e_index == -1)
    {
        return 1;
    }
    if (tag_e_index<item_b_index || tag_e_index > item_e_index)
    {
        return 1;
    }


    if (begin_text[begin_text.length()-1] != '>')//version == 2005
    {
        while(content[tag_b_index]!='>' && tag_b_index<tag_e_index)
        {
            tag_b_index++;
        }
        tag_b_index++;
    }

    text = "";
    for (int i=tag_b_index; i <tag_e_index; i++)
    {
        text+=content[i];
    }

    return 0;

}

int ParseRSS::getDescription(const int item_b_index, const int item_e_index, QString &description, const QString &content)
{
    Search cs;
    int tag_b_index, tag_e_index;

    tag_b_index =item_b_index;
    cs.searchAfter(content,"<description>", &tag_b_index);

    if (tag_b_index == -1)
    {
        return 1;
    }
    if (tag_b_index<item_b_index || tag_b_index > item_e_index)
    {
        return 1;
    }

    tag_e_index = tag_b_index;
    cs.searchBefore(content, "</description>", &tag_e_index);

    if (tag_e_index == -1)
    {
        return 1;
    }
    if (tag_e_index<item_b_index || tag_e_index > item_e_index)
    {
        return 1;
    }

    description = "";
    bool cdata = false;
    for (int i=tag_b_index; i <tag_e_index; i++)
    {
        if (content[i]=='&' && i+3 < tag_e_index)
        {
            if (content[i+1] == 'a' && content[i+2] == 'm' && content[i+3] == 'p')
            {
                description+='&';
                i+=5;
            }
            if(content[i+1] == 'l' && content[i+2]=='t' && content[i+3] == ';')
            {
                int index_tmp = i;
                cs.searchAfter(content,"&gt;",&index_tmp);
                if (index_tmp == -1)
                {
                    return 1;
                }
                if (index_tmp <= tag_e_index)
                {
                    i = index_tmp-1;
                }
                continue;
            }
        }
        if (cdata && content[i]=='[')
        {
            continue;
        }
        if (cdata && content[i] == ']')
        {
            if (i+2>=item_e_index)
            {
                break;
            }
            if (content[i+1] == ']' && content[i+2] == '>')
            {
                cdata = false;
                i+=2;
            }
            continue;
        }
        if (content[i] == '<')
        {
            if (item_e_index<=i+9)
            {
                description+=content[i];
                continue;
            }
            //<![CDATA["
            if (content[i+1] == '!'
                    && content[i+2] == '['
                    && content[i+3] == 'C'
                    && content[i+4] == 'D'
                    && content[i+5] == 'A'
                    && content[i+6] == 'T'
                    && content[i+7] == 'A'
                    && content[i+8] == '[')
            {
                i+=8;
                cdata = true;
                continue;
            }
        }
        description+=content[i];
    }
    return 0;
}

//Get articles from rss source
int ParseRSS::getArticlesFromRSSContent(const QString &content, std::shared_ptr<RSSData> rssData)
{
    int item_b_index=0, item_e_index=0;
    Search cs;
    int n = content.length();

    while(1)
    {
        cs.searchAfter(content,"<item", &item_b_index);
        if (item_b_index == -1)
        {
            break;
        }

        item_e_index = item_b_index;
        cs.searchBefore(content,"</item", &item_e_index);

        if (item_e_index == -1)
        {
            break;
        }

        if (item_b_index<n)
        {
            if (content[item_b_index] == 's') //if found <items tag
            {
                continue;
            }
        }

        QString title, link, text, date;
        if(getTextBetweenIndexes(item_b_index, item_e_index, "<title>", "</title>", title, content))
        {
            break;
        }
        convertString(title, false);
        if (getTextBetweenIndexes(item_b_index, item_e_index, "<link>", "</link>", link,content))
        {
            break;
        }

        convertString(link, true);
        getDescription(item_b_index, item_e_index, text, content);

        //get date if exist
        getTextBetweenIndexes(item_b_index, item_e_index, "<pubDate", "</pubDate>", date, content);

        RSSArticle art;
        art.setLink(link);
        art.setText(text);
        art.setTitle(title);
        art.setDate(date);

        rssData->articlesPushBack(art);
    }
    return 0;
}

//Get articles from rdf xml
int ParseRSS::getArticlesFromRDFContent(const QString &content, std::shared_ptr<RSSData> rssData)
{
    int item_b_index=0, item_e_index=0;
    Search cs;

    cs.searchAfter(content, "</channel", &item_e_index);
    if (item_e_index == -1)
    {
        return 1;
    }
    item_b_index = item_e_index;

    QString storyOpenTag, storyEndTag;
    getStoryTag(content, storyOpenTag, storyEndTag);

    while(1)
    {
        cs.searchAfter(content,storyOpenTag, &item_b_index);
        if (item_b_index == -1)
        {
            return 0;
        }

        item_e_index = item_b_index;
        cs.searchBefore(content, storyEndTag, &item_e_index);

        if (item_e_index == -1)
        {
            break;
        }

        QString title, link, text, date;

        if(getTextBetweenIndexes(item_b_index, item_e_index, "<title", "</title>", title, content))
        {
            break;
        }
        convertString(title, false); //what is the second argument

        if(getTextBetweenIndexes(item_b_index, item_e_index, "<link", "</link>", link, content))
        {
            break;
        }
        convertString(link, true);

        getDescription(item_b_index, item_e_index, text, content);

        //get date if exist
        getTextBetweenIndexes(item_b_index, item_e_index, "<pubDate", "</pubDate>", date, content);

        RSSArticle art;

        art.setLink(link);
        art.setText(text);
        art.setTitle(title);
        art.setDate(date);

        rssData->articlesPushBack(art);
    }
    return 0;
}

void ParseRSS::convertString (QString &str, const bool link)
{
    QString entitie;
    QString str_tmp = "";
    bool cdata=false;
    for (int i=0; i<str.length(); i++)
    {
        if (str[i] == '&' && !link)
        {
            int c = i;
            entitie = "";
            while(str[i]!=';'&& i<str.length() && (i-c)<7)
            {
                entitie += str[i];
                i++;
            }
            QString conv = convert_entitie(entitie);
            if (conv == "")
            {
                i=c;
            }
            else
            {
                str_tmp += conv;
            }
            continue;
        }
        if (cdata && str[i] == ']')
        {
            cdata = false;
            if (i+2>=str.length())
            {
                break;
            }
            i+=2;
            continue;
        }
        if (str[i] == '<')
        {
            if (str.length()<=i+9)
            {
                str_tmp +=str[i];
                continue;
            }
            //<![CDATA["
            if (str[i+1] == '!' && str[i+2] == '[' && str[i+3] == 'C' && str[i+4] == 'D' && str[i+5] == 'A' && str[i+6] == 'T' && str[i+7] == 'A' && str[i+8] == '[')
            {
                i+=8;
                cdata = true;
                continue;
            }
        }
        str_tmp+=str[i];
    }
    str = str_tmp;
}

QString ParseRSS::returnURL(const QString &source, int index)
{
    if (index <0 || index>source.length())
    {
        return "";
    }

    QString label = "href=";
    int n = source.length();
    int n1 = label.length();


    int j = 0;
    while (source[index]!='>' && index<n)
    {
        if (j==n1) //found 'href' before '>'
        {
            break;
        }

        if (source[index]!=label[j])
        {
            j=0;
            index++;
            continue;
        }
        j++;
        index++;
    }
    if (index >= n) //if not found href= in source
    {
        return "";
    }

    while (source[index]!='\"' && index<n)
    {
        index++;
    }
    index++;
    QString url = "";
    while (source[index]!='\"' && index<n)
    {
        url+=source[index++];
    }

    return url;
}

int ParseRSS::getContent(const int item_b_index, const int item_e_index, QString &description, const QString &content)
{
    Search cs;
    int tag_b_index, tag_e_index;

    tag_b_index =item_b_index;
    cs.searchAfter(content,"<content", &tag_b_index);

    if (tag_b_index == -1)
    {
        return 1;
    }
    if (tag_b_index<item_b_index || tag_b_index > item_e_index)
    {
        return 1;
    }

    tag_e_index = tag_b_index;
    cs.searchBefore(content, "</content>", &tag_e_index);

    if (tag_e_index == -1)
    {
        return 1;
    }
    if (tag_e_index<item_b_index || tag_e_index > item_e_index)
    {
        return 1;
    }

    while(content[tag_b_index]!='>' && tag_b_index<tag_e_index)
    {
        tag_b_index++;
    }
    tag_b_index++;

    description = "";
    bool cdata = false;
    for (int i=tag_b_index; i <tag_e_index; i++)
    {
        if (content[i]=='&' && i+3 < tag_e_index)
        {
            if (content[i+1] == 'a' && content[i+2] == 'm' && content[i+3] == 'p')
            {
                description+='&';
                i+=5;
            }
            if(content[i+1] == 'l' && content[i+2]=='t' && content[i+3] == ';')
            {
                int index_tmp = i;
                cs.searchAfter(content,"&gt;",&index_tmp);
                if (index_tmp == -1)
                {
                    return 1;
                }
                if (index_tmp <= tag_e_index)
                {
                    i = index_tmp-1;
                }
                continue;
            }
        }
        if (cdata && content[i]=='[')
        {
            continue;
        }
        if (cdata && content[i] == ']')
        {
            if (i+2>=item_e_index)
            {
                break;
            }
            if (content[i+1] == ']' && content[i+2] == '>')
            {
                cdata = false;
                i+=2;
            }
            continue;
        }
        if (content[i] == '<')
        {
            if (item_e_index<=i+9)
            {
                description+=content[i];
                continue;
            }
            //<![CDATA["
            if (content[i+1] == '!'
                    && content[i+2] == '['
                    && content[i+3] == 'C'
                    && content[i+4] == 'D'
                    && content[i+5] == 'A'
                    && content[i+6] == 'T'
                    && content[i+7] == 'A'
                    && content[i+8] == '[')
            {
                i+=8;
                cdata = true;
                continue;
            }
        }
        description+=content[i];
    }
    return 0;
}

QString ParseRSS::convert_entitie(const QString &entitie)
{

    if (entitie == "&quot")
    {
        return "\"";
    }
    else if (entitie == "&nbsp" || entitie =="&#160")
    {
        return " ";
    }
    else if (entitie == "&amp" || entitie == "&#38")
    {
        return "&";
    }
    else if (entitie == "&lt" || entitie == "&#60")
    {
        return "<";
    }
    else if (entitie == "&qt" || entitie == "&#62")
    {
        return ">";
    }
    else if (entitie == "&OElig")
    {
        return "Œ";
    }
    else if (entitie == "&oelig")
    {
        return "œ";
    }
    else if (entitie == "&Scaron")
    {
        return "Š";
    }
    else if (entitie == "&scaron")
    {
        return "š";
    }
    else if (entitie == "&Yuml")
    {
        return "Ÿ";
    }
    else if (entitie == "&circ")
    {
        return "ˆ";
    }
    else if (entitie == "&tilde")
    {
        return "~";
    }
    else if (entitie == "&ndash")
    {
        return "–";
    }
    else if (entitie == "&ndash")
    {
        return "–";
    }
    else if (entitie == "&mdash")
    {
        return "—";
    }
    else if (entitie == "&lsquo")
    {
        return "‘";
    }
    else if (entitie == "&rsquo")
    {
        return "’";
    }
    else if (entitie == "&sbquo")
    {
        return "‚";
    }
    else if (entitie == "&ldquo")
    {
        return "“";
    }
    else if (entitie == "&rdquo")
    {
        return "”";
    }
    else if (entitie == "&bdquo")
    {
        return "„";
    }
    else if (entitie == "&dagger")
    {
        return "†";
    }
    else if (entitie == "&Dagger")
    {
        return "‡";
    }
    else if (entitie == "&permil")
    {
        return "‰";
    }
    else if (entitie == "&lsaquo")
    {
        return "‹";
    }
    else if (entitie == "&rsaquo")
    {
        return "›";
    }
    else if (entitie == "&euro" || entitie == "&#8364")
    {
        return "€";
    }
    else if (entitie == "&cent" || entitie == "&#162" )
    {
        return "¢";
    }
    else if (entitie == "&pound" || entitie == "&#163")
    {
        return "£";
    }
    else if (entitie == "&yen" || entitie == "&#165")
    {
        return "¥";
    }
    else if (entitie == "&copy" || entitie == "&#169")
    {
        return "©";
    }
    else if (entitie == "&reg" || entitie == "&#174")
    {
        return "®";
    }
    else
    {
        return "";
    }
}

QString ParseRSS::getEncodingByWebSource(const QString &web_content)
{
    Search cs;
    QString encoding="";
    int index1=0, index2=0;

    cs.searchAfter(web_content,"<?xml", &index1);

    if (index1 == -1)
    {
        return "";
    }

    cs.searchBefore(web_content, "?>", &index2);

    if (index2 == -1)
    {
        return "";
    }

    cs.searchAfter(web_content, "encoding=", &index1);

    if (index1 == -1 || index1>index2)
    {
        return "";
    }

    while (web_content[index1]!='\'' && web_content [index1]!='\"' && index1<index2)
    {
        index1++;
    }

    index1++;
    while (web_content[index1]!='\'' && web_content [index1]!='\"' && index1<index2)
    {
        encoding += web_content[index1++];
    }

    return encoding;
}
