TARGET = Gitignorant
SRC = src/main.c src/menu.c src/init.c
FLAGS = -Wall -Wextra -Werror -pedantic -std=c11 \
        -Wformat=2 -Wconversion -Wimplicit-fallthrough \
        -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS \
        -fstack-protector-strong -fstack-clash-protection

all: $(TARGET)

$(TARGET): $(SRC)
	@gcc $(FLAGS) -o $(TARGET) $(SRC)
	@chmod +x $(TARGET)
	@./$(TARGET)

clean:
	@rm -f $(TARGET)
