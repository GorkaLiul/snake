snake: obj/snake.o obj/func.o
	gcc -o snake obj/snake.o obj/func.o
obj/snake.o: src/snake.c src/snake.h
	gcc -c src/snake.c -o obj/snake.o
obj/func.o: src/func.c src/snake.h
	gcc -c src/func.c -o obj/func.o
clean:
	rm -rf obj/*.o snake
