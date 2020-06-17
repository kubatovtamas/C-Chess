add_library(libsakk libsakk.c board.c filehandler.c filehandler.h piece.c)
target_include_directories(libsakk PUBLIC .)