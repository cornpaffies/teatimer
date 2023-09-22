teatimer: teatimer.c
	gcc -o tea teatimer.c `pkg-config --cflags --libs libnotify`

install:
	install tea $(HOME)/.local/bin/tea

clean:
	rm tea $(HOME)/.local/bin/tea
