TARGET = gitignorant
SRC = src/main.c src/menu.c src/init.c src/feature_branch.c src/feature_push.c
FLAGS = -Wall -Wextra -Werror -pedantic -std=c11 \
        -Wformat=2 -Wconversion -Wimplicit-fallthrough \
        -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS \
        -fstack-protector-strong -fstack-clash-protection -D_GNU_SOURCE

all: $(TARGET)

$(TARGET): $(SRC)
	@gcc $(FLAGS) -o $(TARGET) $(SRC) -lreadline

install: $(TARGET)
	@sudo mv $(TARGET) /usr/local/bin/

clean:
	@rm -f $(TARGET)

run: $(SRC)
	@gcc $(FLAGS) -o $(TARGET) $(SRC)
	@chmod +x $(TARGET)
	@./$(TARGET)