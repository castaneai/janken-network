client: kadaiclient.c game_janken.c
	gcc kadaiclient.c game_janken.c -o client

server: kadaiserv.c game_janken.c
	gcc kadaiserv.c game_janken.c -o serv

clean:
	rm -f client serv
