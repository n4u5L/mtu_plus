#pragma once

#include <QGraphicsObject>
#include <memory>
#include <QPen>
#include <QBrush>
#include <QPainterPath>

namespace ui {

struct gvLayout;

struct gvItem : QGraphicsObject {
  gvItem(int w, int h, QGraphicsItem* parent = nullptr);
  gvItem(int w, int h, int minw, int minh, QGraphicsItem* parent = nullptr);
  ~gvItem();

  void setSize(int w, int h);
  void setMinimumSize(int w, int h);
  void setPreferredSize(int w, int h);
  void setLayout(std::unique_ptr<gvLayout> layout);

  gvLayout* ownLayout() const {
    return layout_.get();
  }

  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget = nullptr) override;

private:
  friend struct gvLayout;
  friend struct gvRowLayout;

  gvLayout* parent_ = nullptr;
  std::unique_ptr<gvLayout> layout_;

protected:
  int width_, height_;
  int w_, h_;
  int minw_, minh_;

  QPen outline_;
  QBrush inner_;
  QPainterPath shape_;
};

} // namespace ui