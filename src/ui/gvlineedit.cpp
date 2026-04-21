#include <gvlineedit.h>
#include <ui.h>

namespace ui {

gvLineEdit::gvLineEdit()
    : gvItem(120, 20) {
}

gvLineEdit::~gvLineEdit() = default;

QRectF gvLineEdit::boundingRect() const {
  return QRectF(0, 0, 120, 20);
}

void gvLineEdit::mousePressEvent(QGraphicsSceneMouseEvent* event) {
}

void gvLineEdit::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
}

void gvLineEdit::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget) {
}

} // namespace ui