#pragma once

#include <gvitem.h>
#include <QString>

namespace ui {

struct gvLineEdit : gvItem {
  gvLineEdit();
  ~gvLineEdit();

  QRectF boundingRect() const override;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

  QString text_;
  int cursor_ = 0;
  int sel_start_ = 0, sel_end_ = 0;
};

} // namespace ui