#include "ladraglistview.h"

LaDragListView::LaDragListView() :QStandardItem()
{

}


LaDragListView::LaDragListView(const QIcon &icon, const QIcon &icon_hover, const QString &text)
    :QStandardItem()
{
    Img = icon;
    Img_hover = icon_hover;
    setIcon(Img);
    setText(text);
}
