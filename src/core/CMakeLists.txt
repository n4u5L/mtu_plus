add_library(core STATIC)
add_library(MyProject::core ALIAS core)

target_sources(core PRIVATE .
)

target_include_directories(core PUBLIC .)

target_link_libraries(core PUBLIC Qt6::Gui)