CC = cc

time: time.tab.c
	$(CC) time.tab.c -o time

time.tab.c: time.y
	bison time.y
