CC = g++
OUT = Funkin

SDIR = src
INC = include/ -I include/external
LIB = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer_ext -lSDL2_ttf
OPTIONS = -m64 -Wall -std=c++20

default:
	cp -r assets bin

#   move .o to current directory to not recompile shit we don't need to do
	mv obj/*.o ./ || echo
#   external folder for shit not made by me lol (we have to use .o files now and link because of this however)
	${CC} -c ${SDIR}/external/*.c* ${LIB} ${OPTIONS} -I ${INC}
	${CC} -c ${SDIR}/*.c* ${LIB} ${OPTIONS} -I ${INC}
#   put .o back into obj folder (yes it's a very hacky solution, but what can i do? figure it out? nah this is dumbass 13 y/o programmer bs)
	mv *.o obj/

	${CC} obj/*.o ${LIB} ${OPTIONS} -I ${INC} -o bin/${OUT}
