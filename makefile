hello: objdir linklist.o hashtable.o main

objdir:
	mkdir -p obj

linklist.o: linklist/linklist.c
	gcc -c -o "obj/$@" $<

hashtable.o: hashtable/hashtable.c
	gcc -c -o "obj/$@" $<

main: linklist.o hashtable.o
	cc -o main main.c obj/linklist.o obj/hashtable.o

clean:
	rm -rf obj
	rm main