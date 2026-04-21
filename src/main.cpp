#include "main.h"
#include <gvitem.h>
#include <QApplication>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  GraphicsScene scene(QRectF(0, 0, 800, 600));
  GraphicsView view;
  view.setScene(&scene);
  auto* item = new ui::gvItem(120, 20);
  scene.addItem(item);
  view.show();
  return app.exec();
}