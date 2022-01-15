TGT := Sandbox.out

SRCDIR := ./src
OBJDIR := ./obj

# Include Static Library
LDFLAGS = -L./lib
LDLIBS  = -lEngine

# Include Library Headers
CPPFLAGS += -I../Engine/src

SRCS := $(shell find $(SRCDIR) -name *.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCDIR  := $(shell find $(SRCDIR) -type d)
CPPFLAGS += $(addprefix -I, $(INCDIR)) -MMD -MP


$(TGT): $(OBJS)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Compile Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) -c $< -o $@


.PHONY: clean run

run:
	@./$(TGT)

clean:
	@$(RM) $(OBJS) $(DEPS) $(TGT)

-include $(DEPS)
