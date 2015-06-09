make: main.c
	gcc -g main.c -o lights

clean: lights
	rm lights
