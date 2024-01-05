CFLAGS += -I.
OBJDIR = obj

opengl: $(OBJDIR)/app.o $(OBJDIR)/log.o
	$(CC) $(CFLAGS) -o opengl $(OBJDIR)/app.o $(OBJDIR)/log.o -lstdc++ $(LDFLAGS)

$(OBJDIR)/app.o: app.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c app.cpp -o $(OBJDIR)/app.o

$(OBJDIR)/log.o: src/log.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c src/log.cpp -o $(OBJDIR)/log.o
