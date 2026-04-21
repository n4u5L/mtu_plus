#pragma once

#include <fixed.h>
#include <cstdint>
#include <QVarLengthArray>

namespace core {

namespace helper {

struct GlyphMetrics {
  Fixed x, y;
  Fixed width, height;
  Fixed xoff, yoff;
};

struct GlyphJust {
  enum JustType { JustNone, JustSpace, JustKashida };

  unsigned int type : 2;
  unsigned int kashidas : 6;
  unsigned int space : 24;
};

struct GlyphAttr {
  unsigned char cluster_start : 1;
  unsigned char dont_print : 1;
  unsigned char just : 4;
  unsigned char reserved : 2;
};

struct GlyphLayout {
  static constexpr int SpaceNeeded = sizeof(uint32_t) + sizeof(Fixed) +
                                     sizeof(FixedPoint) + sizeof(GlyphAttr) +
                                     sizeof(GlyphJust);

  FixedPoint* offsets;
  uint32_t* glyphs;
  Fixed* advances;
  GlyphJust* justs;
  GlyphAttr* attrs;

  int glyph_num;

  GlyphLayout(char* address, int n) {
    offsets = reinterpret_cast<FixedPoint*>(address);
    address += n * sizeof(FixedPoint);
    glyphs = reinterpret_cast<uint32_t*>(address);
    address += n * sizeof(uint32_t);
    advances = reinterpret_cast<Fixed*>(address);
    address += n * sizeof(Fixed);
    justs = reinterpret_cast<GlyphJust*>(address);
    address += n * sizeof(GlyphJust);
    attrs = reinterpret_cast<GlyphAttr*>(address);

    glyph_num = n;
  }
};

struct GlyphLayoutVLA : private QVarLengthArray<void*>, public GlyphLayout {
private:
  typedef QVarLengthArray<void*> Array;

public:
  explicit GlyphLayoutVLA(int n)
      : Array(n * SpaceNeeded / sizeof(void*) + 1),
        GlyphLayout(reinterpret_cast<char*>(Array::data()), n) {
    memset(Array::data(), 0, Array::size() * sizeof(void*));
  }

  void resize(int n) {
    Array::resize(n * SpaceNeeded / sizeof(void*) + 1);
    *((GlyphLayout*)this) =
        GlyphLayout(reinterpret_cast<char*>(Array::data()), n);
    memset(Array::data(), 0, Array::size() * sizeof(void*));
  }
};

} // namespace helper

} // namespace core