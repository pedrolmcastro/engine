TGT := Sandbox.out

SRCDIR := ./src
OBJDIR := ./obj
LIBDIR := ./lib

LIB := $(LIBDIR)/libFeather.a

# Include Static Library
LDFLAGS = -L$(LIBDIR)
LDLIBS  = -lFeather

# Include Library Headers
CPPFLAGS += -I../Feather/src
CXXFLAGS += -std=c++2a


ifeq ($(RELEASE), 1)
	CPPFLAGS += -O3 -DRELEASE
endif

ifeq ($(DEBUG), 1)
	CPPFLAGS += -O0 -g -DDEBUG
endif


SRCS := $(shell find $(SRCDIR) -name *.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCDIR   := $(shell find $(SRCDIR) -type d)
CPPFLAGS += $(addprefix -I, $(INCDIR))


$(TGT): $(OBJS) $(LIB)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Compile Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@


.PHONY: clean run

run:
	@./$(TGT)

clean:
	@$(RM) $(OBJS) $(DEPS) $(TGT)


-include $(DEPS)
