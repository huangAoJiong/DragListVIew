#ifndef LADRAGLIST_H
#define LADRAGLIST_H

#include <QListView>

class LaDragList : public QListView
{
    Q_OBJECT

public:
    explicit LaDragList(QWidget *parent = nullptr);

    bool isDraging() const {return IsDraging;}
    int offset() const {return 19;}
    int highlightedRow() const {return theHighlightedRow;}
    int dragRow() const {return theDragRow;}
    int selectedRow() const {return theSelectedRow;}
    static QString myMimeType() { return QStringLiteral("TestListView/text-icon-icon_hover"); }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    QPoint startPos;
    bool IsDraging = false;
    int theHighlightedRow = -2;
    int oldHighlightedRow = -2;
    int theDragRow = -1;
    int theSelectedRow = -1;
    int theInsertRow = -1;
};


#endif // LADRAGLIST_H
