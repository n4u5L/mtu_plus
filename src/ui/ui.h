#pragma once

#include <QColor>

namespace ui {

struct gvTheme {
  QColor inner = QColor(84, 84, 84);
  QColor inner_sel = QColor(71, 114, 179);
  QColor outline = QColor(61, 61, 61);
  QColor outline_sel = QColor(61, 61, 61);
  float roundness = 0.2f;
};

inline constexpr gvTheme UI_theme_default;

} // namespace ui