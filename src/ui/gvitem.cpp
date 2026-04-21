#include <gvitem.h>
#include <gvlayout.h>
#include <ui.h>
#include <QPainter>

namespace ui {

gvItem::gvItem(int w, int h, QGraphicsItem* parent)
    : QGraphicsObject(parent) {
  width_ = w, height_ = h;
  w_ = w, h_ = h;
  minw_ = w, minh_ = h;

  inner_ = QBrush(UI_theme_default.inner);
  outline_ = QPen(UI_theme_default.outline);
  qreal radius = std::min(w_, h_) * UI_theme_default.roundness;
  shape_.addRoundedRect(0, 0, w, h, radius, radius);
}

gvItem::gvItem(int w, int h, int minw, int minh, QGraphicsItem* parent)
    : QGraphicsObject(parent) {
  width_ = w, height_ = h;
  w_ = w, h_ = h;
  minw_ = minw, minh_ = minh;
}

gvItem::~gvItem() = default;

void gvItem::setSize(int w, int h) {
  if (!parent_) {
    width_ = std::max(minw_, w);
    height_ = std::max(minh_, h);
  }
}

void gvItem::setPreferredSize(int w, int h) {
  w_ = std::max(w, minw_);
  h_ = std::max(h, minh_);
}

void gvItem::setMinimumSize(int w, int h) {
  minw_ = std::max(w, 0);
  minh_ = std::max(h, 0);
}

void gvItem::setLayout(std::unique_ptr<gvLayout> layout) {
  layout_ = std::move(layout);
  layout_->parent_ = this;
  layout_->setParentItem(this);
}

QRectF gvItem::boundingRect() const {
  return QRectF(0, 0, width_, height_);
}

void gvItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
                   QWidget* widget) {
  painter->setPen(outline_);
  painter->setBrush(inner_);
  painter->drawPath(shape_);
}

} // namespace ui