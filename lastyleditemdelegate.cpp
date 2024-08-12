#include "lastyleditemdelegate.h"
#include "ladraglistview.h"
#include "ladraglist.h"
#include <QPainter>

// LaStyledItemDelegate 的构造函数
// 调用父类 QStyledItemDelegate 的构造函数，初始化父对象
LaStyledItemDelegate::LaStyledItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

// 重写的 paint 方法，用于自定义项的绘制
void LaStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 获取当前绘制项的视图，检查它是否正在拖拽
    LaDragList *dragView = qobject_cast<LaDragList *>(option.styleObject);
    bool isDraging = dragView->isDraging();

    // 获取项的矩形区域
    QRect rect = option.rect;

    // 开启抗锯齿效果，提高绘制质量
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);  // 不使用边框线

    // 检查当前项是否被鼠标悬停或选中
    if(option.state & (QStyle::State_MouseOver | QStyle::State_Selected)){

        // 获取当前项对应的模型，并获取该项的自定义视图项
        QStandardItemModel *listModel = qobject_cast<QStandardItemModel *>(dragView->model());
        LaDragListView *item = static_cast<LaDragListView *>(listModel->item(index.row()));

        // 根据项的状态设置图标
        item->setIcon(option.state & QStyle::State_MouseOver ? item->Img_hover : item->Img);

        if(option.state & QStyle::State_Selected){
            // 如果项被选中，绘制选中效果
            painter->setBrush(QColor(180, 0, 0));
            painter->drawRect(rect.topLeft().x(), rect.topLeft().y(), 4, rect.height());  // 绘制左边的红色边框

            painter->setBrush(QColor(230, 231, 234));
            painter->drawRect(rect.topLeft().x() + 4, rect.topLeft().y(), rect.width() - 4, rect.height());  // 绘制灰色背景
        }
    } else {
        // 如果未选中或鼠标未悬停，则恢复默认图标
        QStandardItemModel *listModel = qobject_cast<QStandardItemModel *>(dragView->model());
        LaDragListView *item = static_cast<LaDragListView *>(listModel->item(index.row()));
        item->setIcon(item->Img);
    }

    // 如果当前视图正在拖拽项
    if(isDraging){
        // 获取拖拽行、选中行、突出显示的行以及总行数
        int theDragRow = dragView->dragRow();
        int theSelectedRow = dragView->selectedRow();
        int UpRow = dragView->highlightedRow();
        int DownRow = UpRow + 1;
        int rowCount = dragView->model()->rowCount() - 1;

        // 只绘制空隙，不绘制DropIndicator
        // 当拖拽行非选中行时，需要在选中行上面或下面绘制空隙以显示DropIndicator
        if(index.row() == theSelectedRow && theDragRow != theSelectedRow){
            if(index.row() == UpRow && index.row() != theDragRow - 1){
                // 绘制下方空隙及三角形
                int offset = 3;
                QPolygon trianglePolygon_bottomLeft;
                trianglePolygon_bottomLeft << QPoint(rect.bottomLeft().x(), rect.bottomLeft().y() - (offset + WIDTH) + 1);
                trianglePolygon_bottomLeft << QPoint(rect.bottomLeft().x(), rect.bottomLeft().y() - (offset + WIDTH + POLYGON) + 1);
                trianglePolygon_bottomLeft << QPoint(rect.bottomLeft().x() + POLYGON, rect.bottomLeft().y() - (offset + WIDTH) + 1);

                QPolygon trianglePolygon_bottomRight;
                trianglePolygon_bottomRight << QPoint(rect.bottomRight().x() + 1, rect.bottomRight().y() - (offset + WIDTH) + 1);
                trianglePolygon_bottomRight << QPoint(rect.bottomRight().x() + 1, rect.bottomRight().y() - (offset + WIDTH + POLYGON) + 1);
                trianglePolygon_bottomRight << QPoint(rect.bottomRight().x() - POLYGON + 1, rect.bottomRight().y() - (offset + WIDTH) + 1);

                painter->setBrush(QColor(245, 245, 247));
                painter->drawPolygon(trianglePolygon_bottomLeft);
                painter->drawPolygon(trianglePolygon_bottomRight);
                painter->drawRect(rect.bottomLeft().x(), rect.bottomLeft().y() - (offset + WIDTH) + 1, rect.width(), offset + WIDTH);
            } else if(index.row() == DownRow && index.row() != theDragRow + 1){
                // 绘制上方空隙及三角形
                int offset = 3;

                QPolygon trianglePolygon_topLeft;
                trianglePolygon_topLeft << QPoint(rect.topLeft().x(), rect.topLeft().y() + offset + WIDTH);
                trianglePolygon_topLeft << QPoint(rect.topLeft().x(), rect.topLeft().y() + offset + WIDTH + POLYGON);
                trianglePolygon_topLeft << QPoint(rect.topLeft().x() + POLYGON, rect.topLeft().y() + offset + WIDTH);

                QPolygon trianglePolygon_topRight;
                trianglePolygon_topRight << QPoint(rect.topRight().x() + 1, rect.topRight().y() + offset + WIDTH);
                trianglePolygon_topRight << QPoint(rect.topRight().x() + 1, rect.topRight().y() + offset + WIDTH + POLYGON);
                trianglePolygon_topRight << QPoint(rect.topRight().x() - POLYGON + 1, rect.topRight().y() + offset + WIDTH);

                painter->setBrush(QColor(245, 245, 247));
                painter->drawPolygon(trianglePolygon_topLeft);
                painter->drawPolygon(trianglePolygon_topRight);
                painter->drawRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), offset + WIDTH);
            }
        }

        // 绘制DropIndicator
        if(index.row() == UpRow && index.row() != theDragRow - 1 && index.row() != theDragRow){
            painter->setBrush(QColor(66, 133, 244));

            if(UpRow == rowCount){
                // 到达列表底部，绘制向上移动的三角形
                QPolygon trianglePolygon_bottomLeft;
                trianglePolygon_bottomLeft << QPoint(rect.bottomLeft().x(), rect.bottomLeft().y() - (POLYGON + WIDTH) + 1 - WIDTH);
                trianglePolygon_bottomLeft << QPoint(rect.bottomLeft().x(), rect.bottomLeft().y() - WIDTH + 1 - WIDTH);
                trianglePolygon_bottomLeft << QPoint(rect.bottomLeft().x() + POLYGON, rect.bottomLeft().y() - WIDTH + 1 - WIDTH);

                QPolygon trianglePolygon_bottomRight;
                trianglePolygon_bottomRight << QPoint(rect.bottomRight().x() + 1, rect.bottomRight().y() - (POLYGON + WIDTH) + 1 - WIDTH);
                trianglePolygon_bottomRight << QPoint(rect.bottomRight().x() + 1, rect.bottomRight().y() - WIDTH + 1 - WIDTH);
                trianglePolygon_bottomRight << QPoint(rect.bottomRight().x() - POLYGON + 1, rect.bottomRight().y() - WIDTH + 1 - WIDTH);

                painter->drawRect(rect.bottomLeft().x(), rect.bottomLeft().y() - 2 * WIDTH + 1, rect.width(), 2 * WIDTH);  // 绘制矩形
                painter->drawPolygon(trianglePolygon_bottomLeft);
                painter->drawPolygon(trianglePolygon_bottomRight);
            } else {
                // 正常情况，绘制上半部分
                QPolygon trianglePolygon_bottomLeft;
                trianglePolygon_bottomLeft << QPoint(rect.bottomLeft().x(), rect.bottomLeft().y() - (POLYGON + WIDTH) + 1);
                trianglePolygon_bottomLeft << QPoint(rect.bottomLeft().x(), rect.bottomLeft().y() - WIDTH + 1);
                trianglePolygon_bottomLeft << QPoint(rect.bottomLeft().x() + POLYGON, rect.bottomLeft().y() - WIDTH + 1);

                QPolygon trianglePolygon_bottomRight;
                trianglePolygon_bottomRight << QPoint(rect.bottomRight().x() + 1, rect.bottomRight().y() - (POLYGON + WIDTH) + 1);
                trianglePolygon_bottomRight << QPoint(rect.bottomRight().x() + 1, rect.bottomRight().y() - WIDTH + 1);
                trianglePolygon_bottomRight << QPoint(rect.bottomRight().x() - POLYGON + 1, rect.bottomRight().y() - WIDTH + 1);

                painter->drawRect(rect.bottomLeft().x(), rect.bottomLeft().y() - WIDTH + 1, rect.width(), WIDTH);  // 绘制矩形
                painter->drawPolygon(trianglePolygon_bottomLeft);
                painter->drawPolygon(trianglePolygon_bottomRight);
            }
        } else if(index.row() == DownRow && index.row() != theDragRow + 1 && index.row() != theDragRow){
            painter->setBrush(QColor(66, 133, 244));

            if(DownRow == 0){
                // 到达列表头部，绘制向下移动的三角形
                QPolygon trianglePolygon_topLeft;
                trianglePolygon_topLeft << QPoint(rect.topLeft().x(), rect.topLeft().y() + (POLYGON + WIDTH) + WIDTH);
                trianglePolygon_topLeft << QPoint(rect.topLeft().x(), rect.topLeft().y() + WIDTH + WIDTH);
                trianglePolygon_topLeft << QPoint(rect.topLeft().x() + POLYGON, rect.topLeft().y() + WIDTH + WIDTH);

                QPolygon trianglePolygon_topRight;
                trianglePolygon_topRight << QPoint(rect.topRight().x() + 1, rect.topRight().y() + (POLYGON + WIDTH) + WIDTH);
                trianglePolygon_topRight << QPoint(rect.topRight().x() + 1, rect.topRight().y() + WIDTH + WIDTH);
                trianglePolygon_topRight << QPoint(rect.topRight().x() - POLYGON + 1, rect.topRight().y() + WIDTH + WIDTH);

                painter->drawRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), 2 * WIDTH);  // 绘制矩形
                painter->drawPolygon(trianglePolygon_topLeft);
                painter->drawPolygon(trianglePolygon_topRight);
            } else {
                // 正常情况，绘制下半部分
                QPolygon trianglePolygon_topLeft;
                trianglePolygon_topLeft << QPoint(rect.topLeft().x(), rect.topLeft().y() + (POLYGON + WIDTH));
                trianglePolygon_topLeft << QPoint(rect.topLeft().x(), rect.topLeft().y() + WIDTH);
                trianglePolygon_topLeft << QPoint(rect.topLeft().x() + POLYGON, rect.topLeft().y() + WIDTH);

                QPolygon trianglePolygon_topRight;
                trianglePolygon_topRight << QPoint(rect.topRight().x() + 1, rect.topRight().y() + (POLYGON + WIDTH));
                trianglePolygon_topRight << QPoint(rect.topRight().x() + 1, rect.topRight().y() + WIDTH);
                trianglePolygon_topRight << QPoint(rect.topRight().x() - POLYGON + 1, rect.topRight().y() + WIDTH);

                painter->drawRect(rect.topLeft().x(), rect.topLeft().y(), rect.width(), WIDTH);  // 绘制矩形
                painter->drawPolygon(trianglePolygon_topLeft);
                painter->drawPolygon(trianglePolygon_topRight);
            }
        }

        // 高亮拖拽行，使拖拽行的样式与选中相同
        if(index.row() == theDragRow && theDragRow != theSelectedRow){
            painter->setBrush(QColor(180, 0, 0));
            painter->drawRect(rect.topLeft().x(), rect.topLeft().y(), 4, rect.height());  // 绘制左边的红色边框

            painter->setBrush(QColor(230, 231, 234));
            painter->drawRect(rect.topLeft().x() + 4, rect.topLeft().y(), rect.width() - 4, rect.height());  // 绘制灰色背景

            // opt.state 用于高亮字体
            QStyleOptionViewItem opt(option);
            opt.state |= QStyle::State_Selected;
            QStyledItemDelegate::paint(painter, opt, index);
            return;
        }

        // 调用基类的 paint 方法绘制剩余部分
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    // 调用基类的 paint 方法绘制未拖拽状态下的项
    QStyledItemDelegate::paint(painter, option, index);
}
