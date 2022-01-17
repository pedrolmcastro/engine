TGT := libEngine.a

SRCDIR := ./src
OBJDIR := ./obj

PCHIN  := $(SRCDIR)/Precompiled.hpp
PCHOUT := $(PCHIN).gch

CXXFLAGS += -std=c++2a

SRCS := $(shell find $(SRCDIR) -name *.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCDIR   := $(shell find $(SRCDIR) -type d)
CPPFLAGS += $(addprefix -I, $(INCDIR)) -MMD -MP


# Create Static Library
$(TGT): $(OBJS)
	@$(AR) rcs $(TGT) $(OBJS)

# Compile Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(PCHOUT)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Compile Precompiled Header
$(PCHOUT): $(PCHIN)
	@$(CXX) $(CXXFLAGS) $(PCHIN) -o $(PCHOUT)


.PHONY: clean

clean:
	@$(RM) $(OBJS) $(DEPS) $(PCHOUT) $(TGT)

-include $(DEPS)
