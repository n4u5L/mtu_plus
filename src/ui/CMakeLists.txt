add_library(ui STATIC)
add_library(MyProject::ui ALIAS ui)

target_sources(ui PRIVATE
    gvlayout.h gvlayout.cpp
    gvitem.h gvitem.cpp
    gvlineedit.h gvlineedit.cpp
    ui.h ui.cpp
)

target_include_directories(ui PUBLIC .)
target_link_libraries(ui PUBLIC Qt6::Widgets MyProject::core)