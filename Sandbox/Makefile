TGT := Sandbox.out

LIB := ./lib/libEngine.a

SRCDIR := ./src
OBJDIR := ./obj

# Include Static Library
LDFLAGS = -L./lib
LDLIBS  = -lEngine

# Include Library Headers
CPPFLAGS += -I../Engine/src
CXXFLAGS += -std=c++2a

SRCS := $(shell find $(SRCDIR) -name *.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCDIR  := $(shell find $(SRCDIR) -type d)
CPPFLAGS += $(addprefix -I, $(INCDIR)) -MMD -MP


$(TGT): $(OBJS) $(LIB)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Compile Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


.PHONY: clean run

run:
	@./$(TGT)

clean:
	@$(RM) $(OBJS) $(DEPS) $(TGT)

-include $(DEPS)
