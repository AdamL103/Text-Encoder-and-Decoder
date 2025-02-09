FLAGS = -Wall -Werror -std=c99

all: encode decode

encode: encode.c
	gcc $(FLAGS) encode.c utils.c -o encode

decode: decode.c
	gcc $(FLAGS) decode.c utils.c -o decode

clean:
	rm -f encode decode
