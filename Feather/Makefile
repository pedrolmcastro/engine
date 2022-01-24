TGT := libFeather.a

SRCDIR := ./src
OBJDIR := ./obj
LIBDIR := ./lib

PCHIN  := $(SRCDIR)/Precompiled.hpp
PCHOUT := $(PCHIN).gch

CXXFLAGS += -std=c++2a
CPPFLAGS += -O3


SRCS := $(shell find $(SRCDIR) -name *.cpp)
LIBS := $(shell find $(LIBDIR) -name *.o)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCDIR   := $(shell find $(SRCDIR) -type d)
CPPFLAGS += $(addprefix -I, $(INCDIR))


# Create Static Library
$(TGT): $(OBJS) $(LIBS)
	@$(AR) rcs $(TGT) $(OBJS) $(LIBS)

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
