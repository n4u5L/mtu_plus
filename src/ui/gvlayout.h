#pragma once

#include <vector>

namespace ui {

struct gvItem;

struct gvLayoutItem {
  enum ItemType : uint8_t { Widget, LayoutRow, LayoutColumn };
  enum ItemFlag : uint8_t {
    AutoFixed = 1 << 0,
    Fixed = 1 << 1,
    NotDirty = 1 << 2,
    SizeHintChanged = 1 << 3,
    Pending = 1 << 4
  };
  enum LayoutAlignment : uint8_t { Left, Center, Right };

  gvLayoutItem(ItemType type)
      : type_(type) {
  }
  // virtual ~gvItem() = default;

  uint8_t type_ = 0;
  uint8_t flag_ = 0;
};

struct gvLayoutWidget : gvLayoutItem {
  gvLayoutWidget(gvItem* parent)
      : gvLayoutItem(ItemType::Widget),
        parent_(parent) {
  }

  gvItem* parent_;
};

struct gvLayout : gvLayoutItem {
  gvLayout(ItemType type)
      : gvLayoutItem(type) {
  }

  virtual ~gvLayout();

  void addWidget(gvItem* widget);
  void addLayout(gvLayout* layout);
  void updateAll() {
    update(ItemFlag::SizeHintChanged);
  }
  void updateOnly() {
    update(0);
  }
  void setMargin(int margin) {
    margin_ = margin;
  }
  void setSpacing(int spacing) {
    spacing_ = spacing;
  }

protected:
  friend struct gvItem;
  friend struct gvRowLayout;

  gvLayout* updateTop();
  void update(uint8_t flag);
  void flush();
  void setParentItem(gvItem* parent);

  void getItemSize(gvLayoutItem* item, int& w, int& h);
  void getItemMinSize(gvLayoutItem* item, int& w, int& h);
  int fitItemSize(const int w, const int x, const int all, const int available,
                  const bool is_last, float& extra);

  void setupGeom(); // only for top
  void calcGeom();  // only for top
  virtual void setupGeom_impl() = 0;
  virtual void calcGeom_impl() = 0;

  using gvLayoutItem::flag_;
  using gvLayoutItem::type_;

  int x_ = 0, y_ = 0;
  int width_ = 0, height_ = 0;
  int w_ = 0, h_ = 0;
  int minw_ = 0, minh_ = 0;
  int margin_ = 0;
  int spacing_ = 0;
  uint8_t align_ = 0;

  gvLayout* root_ = nullptr;
  gvLayout* top_ = nullptr;
  gvItem* parent_ = nullptr;
  std::vector<gvLayoutItem*> items_;
};

struct gvRowLayout final : gvLayout {
  gvRowLayout()
      : gvLayout(ItemType::LayoutRow) {
  }

private:
  void setupGeom_impl() override;
  void calcGeom_impl() override;
};

} // namespace ui