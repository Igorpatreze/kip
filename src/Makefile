CFLAGS = -Wall -Werror -Wformat=0 -fno-stack-protector
LIBS = -lX11 -lm

compile:
	gcc $(CFLAGS) -c kip.c $(LIBS)
	ar rvs kip.a kip.o
	rm kip.o

uninstall:
	sudo rm /usr/local/lib/libkip.a
	sudo rm /usr/local/include/kip.h
	sudo rm /usr/local/bin/gccx

install:
	cp kip.a libkip.a
	chmod 0644 kip.h libkip.a
	chmod 0755 gccx
	sudo rm -f /usr/local/include/kip.h
	sudo mkdir -p /usr/local/include
	sudo chmod 0755 /usr/local/include
	sudo cp kip.h /usr/local/include
	sudo mkdir -p /usr/local/lib
	sudo chmod 0755 /usr/local/lib
	sudo cp libkip.a /usr/local/lib
	sudo mkdir -p /usr/local/bin
	sudo chmod 0755 /usr/local/bin
	sudo cp gccx /usr/local/bin
	rm libkip.a
