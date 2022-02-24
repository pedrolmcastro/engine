TGT := libstb.a

SRCDIR := src
OBJDIR := obj

CPPFLAGS += -O3 -I include


SRCS := $(SRCDIR)/stb_image.cpp
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))


$(TGT): $(OBJS)
	@$(AR) rcs $(TGT) $(OBJS)
	@cp $(TGT) ../../Sandbox/lib

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


.PHONY: clean

clean:
	@$(RM) $(OBJS) $(TGT)
