TGT := libglad.a

SRCDIR := src
OBJDIR := obj

CPPFLAGS += -O3 -I include


SRCS := $(SRCDIR)/glad.c
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))


$(TGT): $(OBJS)
	@$(AR) rcs $(TGT) $(OBJS)
	@cp $(TGT) ../../Sandbox/lib

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


.PHONY: clean

clean:
	@$(RM) $(OBJS) $(TGT)
