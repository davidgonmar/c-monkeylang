.PHONY: format


C_SOURCES = $(wildcard src/*.c src/*.h test/*.c)

format:
	clang-format -i $(C_SOURCES)
