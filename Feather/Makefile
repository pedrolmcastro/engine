TGT := libFeather.a

SRCDIR := src
OBJDIR := obj

PCHIN  := $(SRCDIR)/Precompiled.hpp
PCHOUT := $(PCHIN).gch

CXXFLAGS += -std=c++2a
CPPFLAGS += -I ../Vendor/GLFW/include -I ../Vendor/Glad/include


ifeq ($(RELEASE), 1)
	CPPFLAGS += -O3
else # DEBUG
	CPPFLAGS += -O0 -g -DLOGGING -DASSERTING
endif


SRCS := $(shell find $(SRCDIR) -name *.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCDIR   := $(shell find $(SRCDIR) -type d)
CPPFLAGS += $(addprefix -I, $(INCDIR))


$(TGT): $(OBJS)
	@$(AR) rcs $(TGT) $(OBJS)
	@cp $(TGT) ../Sandbox/lib

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(PCHOUT)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

$(PCHOUT): $(PCHIN)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(PCHIN) -o $(PCHOUT)


.PHONY: clean

clean:
	@$(RM) $(OBJS) $(DEPS) $(TGT)


-include $(DEPS)
