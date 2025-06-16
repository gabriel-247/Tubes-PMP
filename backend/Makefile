CC = gcc
CFLAGS = -Ilib/mongoose
LIBS = -lws2_32 -lbcrypt
TARGET = build/server.exe

SRC = main.c \
      routes/api_tes_get.c \
      routes/api_tes_post.c \
      routes/api_dokter.c \
      lib/random_id/random_id.c \
      lib/mongoose/mongoose.c \
      lib/dokter/dokter.c

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	del /Q build\*.exe
