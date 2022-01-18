TGT := Sandbox.out

LIB := ./lib/libFeather.a

SRCDIR := ./src
OBJDIR := ./obj

# Include Static Library
LDFLAGS = -L./lib
LDLIBS  = -lFeather

# Include Library Headers
CPPFLAGS += -I../Feather/src
CXXFLAGS += -std=c++2a

# TODO: Detect change and rebuild
ifeq ($(DEBUG), 1)
	CXXFLAGS += -O0 -g -DDEBUG
else
	CXXFLAGS += -O3 -DRELEASE
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
