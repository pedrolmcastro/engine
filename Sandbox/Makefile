TGT := Sandbox.out

SRCDIR := src
OBJDIR := obj
LIBDIR := lib

# Include Libraries
LDFLAGS = -L$(LIBDIR)
LDLIBS  = -lFeather -lglad $(shell pkg-config --static --libs glfw3)

# Include Library Headers
# TODO: Export Headers
CPPFLAGS += -I ../Feather/src
CXXFLAGS += -std=c++2a


ifeq ($(RELEASE), 1)
	CPPFLAGS += -O3 -DRELEASE
else
	CPPFLAGS += -O0 -g -DDEBUG
endif


SRCS := $(shell find $(SRCDIR) -name *.cpp)
LIBS := $(shell find $(LIBDIR) -name *.a)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCDIR   := $(shell find $(SRCDIR) -type d)
CPPFLAGS += $(addprefix -I, $(INCDIR))


# Compile Binary
$(TGT): $(OBJS) $(LIBS)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Compile Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@


.PHONY: run clean

run:
	@./$(TGT)

clean:
	@$(RM) $(OBJS) $(DEPS) $(TGT)


-include $(DEPS)
