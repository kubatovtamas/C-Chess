add_library(libsakk libsakk.c board.c filehandler.c piece.c game.c game.h position.c position.h)
target_include_directories(libsakk PUBLIC .)