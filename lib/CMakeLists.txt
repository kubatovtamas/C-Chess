add_library(libsakk libsakk.c board.c filehandler.c piece.c)
target_include_directories(libsakk PUBLIC .)