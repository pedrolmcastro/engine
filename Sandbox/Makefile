TGT := Sandbox.out

SRCDIR := src
OBJDIR := obj
LIBDIR := lib

LDFLAGS = -L$(LIBDIR)
LDLIBS  = -lFeather -lstb -lglad $(shell pkg-config --static --libs glfw3)

CPPFLAGS += -I ../Feather/src
CXXFLAGS += -std=c++2a


ifeq ($(RELEASE), 1)
	CPPFLAGS += -O3
else # DEBUG
	CPPFLAGS += -O0 -g -DLOGGING -DASSERTING
endif


SRCS := $(shell find $(SRCDIR) -name *.cpp)
LIBS := $(shell find $(LIBDIR) -name *.a)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

INCDIR   := $(shell find $(SRCDIR) -type d)
CPPFLAGS += $(addprefix -I, $(INCDIR))


$(TGT): $(OBJS) $(LIBS)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@


.PHONY: run clean

run:
	@./$(TGT)

clean:
	@$(RM) $(OBJS) $(DEPS) $(TGT)


-include $(DEPS)
