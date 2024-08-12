#ifndef LADRAGLISTVIEW_H
#define LADRAGLISTVIEW_H

#include<QStandardItem>
class LaDragListView : public QStandardItem
{
public:
    explicit LaDragListView();
    explicit LaDragListView(const QIcon &icon, const QIcon &icon_hover, const QString &text);

    QIcon Img;
    QIcon Img_hover;
};

#endif // LADRAGLISTVIEW_H
