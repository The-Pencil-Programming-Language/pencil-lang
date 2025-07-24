# === CONFIG ===
CC = gcc
CFLAGS = -Ifrontend/include -std=c99 -w
OBJDIR = build
SRCDIR = frontend/src
TESTDIR = tests

# === SOURCES ===
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

TEST_SRC = $(wildcard $(TESTDIR)/*.c)
TEST_OBJ = $(patsubst $(TESTDIR)/%.c, $(OBJDIR)/%.test.o, $(TEST_SRC))

BIN = test.exe

# === RULES ===
all: $(OBJDIR) $(BIN)

# Create build directory if not exist
$(OBJDIR):
	mkdir $(OBJDIR)

# Compile frontend .c files to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files to .test.o
$(OBJDIR)/%.test.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link all object files into final binary
$(BIN): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Optional: build only frontend (no tests)
frontend: $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) -o frontend.exe $(OBJ)

# Clean build artifacts
clean:
	-del /Q $(OBJDIR)\*.o 2>nul
	-del /Q *.exe 2>nul
	@echo Cleaned.

.PHONY: all clean frontend
