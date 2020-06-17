add_library(libsakk libsakk.c board.c filehandler.c filehandler.h)
target_include_directories(libsakk PUBLIC .)