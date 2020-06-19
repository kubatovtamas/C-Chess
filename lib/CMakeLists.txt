add_library(libsakk libsakk.c libsakk.h board.c board.h filehandler.c filehandler.h piece.c piece.h game.c game.h position.c position.h)
target_include_directories(libsakk PUBLIC .)