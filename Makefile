program_name = Funkin

source_paths = src/*.c*
include_paths = include/
libraries = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf
compiler_options = -m64 -Wall

default:
	cp -r assets bin
	g++ ${source_paths} ${libraries} ${compiler_options} -I ${include_paths} -o bin/${program_name}

release:
	cp -r ../assets ./
	g++ ${source_paths} ${libraries} -O3 ${compiler_options} -I ${include_paths} -o bin/${program_name}