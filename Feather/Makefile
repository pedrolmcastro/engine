TGT := libFeather.a

SRCDIR := ./src
OBJDIR := ./obj

PCHIN  := $(SRCDIR)/Precompiled.hpp
PCHOUT := $(PCHIN).gch

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


# Create Static Library
$(TGT): $(OBJS)
	@$(AR) rcs $(TGT) $(OBJS)

# Compile Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(PCHOUT)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

# Compile Precompiled Header
$(PCHOUT): $(PCHIN)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(PCHIN) -o $(PCHOUT)


.PHONY: clean

clean:
	@$(RM) $(OBJS) $(DEPS) $(TGT)

-include $(DEPS)
