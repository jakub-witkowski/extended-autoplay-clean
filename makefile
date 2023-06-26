CC=gcc
CFLAGS=-lpthread
SOURCES1=gracz1/player.c gracz1/load_status.c gracz1/load_player_input.c gracz1/map.c gracz1/list.c gracz1/train.c gracz1/move.c gracz1/attack.c gracz1/save.c gracz1/mining.c
SOURCES2=gracz2/player.c gracz2/load_status.c gracz2/load_player_input.c gracz2/map.c gracz2/list.c gracz2/train.c gracz2/move.c gracz2/attack.c gracz2/save.c gracz2/mining.c
SOURCES3=/mediator/mediator.c mediator/load_status.c mediator/load_orders.c
all: player1 player2 arbiter

player1: $(SOURCES1)
	$(CC) -o player1 $(SOURCES1) $(CFLAGS)
player2: $(SOURCES2)
	$(CC) -o player2 $(SOURCES2) $(CFLAGS)	
arbiter: $(SOURCES3)
	$(CC) -o arbiter $(SOURCES3)

run: ./arbiter