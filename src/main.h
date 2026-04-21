#pragma once

#include <QCoreApplication>
#include <QAbstractEventDispatcher>
#include <QDebug>
#include <chrono>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <qgraphicsscene.h>
#include <qnamespace.h>
#include <qpen.h>
#include <qtmetamacros.h>

struct GraphicsScene : QGraphicsScene {
  Q_OBJECT
public:
  explicit GraphicsScene(const QRectF& rect)
      : QGraphicsScene(rect) {
  }

protected:
  void drawBackground(QPainter* painter, const QRectF&) override {
    QPen pen(Qt::black);
    painter->setPen(pen);
    painter->setBrush(QBrush(QColor(Qt::black)));
    painter->drawRect(sceneRect());
  }
};

class GraphicsView : public QGraphicsView {
  Q_OBJECT
public:
  explicit GraphicsView(QWidget* parent = nullptr)
      : QGraphicsView(parent) {
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setDragMode(QGraphicsView::NoDrag);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
  }

protected:
  void wheelEvent(QWheelEvent* event) override {
    constexpr double scaleFactor = 1.15;

    if (event->angleDelta().y() > 0) {
      scale(scaleFactor, scaleFactor);
    } else {
      scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
  }

  void mousePressEvent(QMouseEvent* event) override {
    if (event->button() == Qt::MiddleButton) {
      m_lastPos = event->pos();
      setCursor(Qt::ClosedHandCursor);
      event->accept();
    }
  }

  void mouseMoveEvent(QMouseEvent* event) override {
    ;
  }

  void mouseReleaseEvent(QMouseEvent* event) override {
    if (event->button() == Qt::MiddleButton) {
      setCursor(Qt::ArrowCursor);
      event->accept();
      return;
    }
    QGraphicsView::mouseReleaseEvent(event);
  }

private:
  QPoint m_lastPos;
};