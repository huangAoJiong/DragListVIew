#ifndef LASTYLEDITEMDELEGATE_H
#define LASTYLEDITEMDELEGATE_H

#include <QStyledItemDelegate>

// 定义了两个宏，用于绘制项时的一些固定参数。
// POLYGON 用于定义等腰三角形的直角边长。
// WIDTH 用于定义分隔符的粗细（这里是分隔符宽度的一半）。
#define POLYGON 4   // 等腰三角形直角边长
#define WIDTH 1     // 分隔符粗细的一半

// LaStyledItemDelegate 类继承自 QStyledItemDelegate，
// 用于在视图中自定义项的绘制方式。
// QStyledItemDelegate 提供了模型视图中项的默认绘制方法，
// 继承它可以重写其绘制逻辑，适应特定需求。
class LaStyledItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT  // 使用 Q_OBJECT 宏是为了支持 Qt 的信号和槽机制。

public:
    // 构造函数，带有一个可选的父对象指针。
    // 当父对象被销毁时，委托对象也会被销毁。
    explicit LaStyledItemDelegate(QObject *parent = nullptr);

protected:
    // 重写 QStyledItemDelegate 的 paint 方法，以实现自定义的绘制逻辑。
    // painter 参数是用于绘制的 QPainter 对象。
    // option 参数包含项的样式选项（例如几何形状、状态等）。
    // index 参数是要绘制的模型项的索引。
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // LASTYLEDITEMDELEGATE_H
