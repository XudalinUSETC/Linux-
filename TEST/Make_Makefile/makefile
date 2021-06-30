src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))

inc_path=./inc

myArgs= -Wall -g

ALL:hello

hello:$(obj)
	gcc $^ -o $@ $(myArgs)

$(obj):./obj/%.o:./src/%.c
	gcc -c $< -o $@ $(myArgs) -I $(inc_path)

clean:
	-rm -rf $(obj) hello
.PHONY:clean ALL
