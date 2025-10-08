CXX := g++-9
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

TARGET := myapp

SRCDIR := src
BUILDDIR := build
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

all: $(BUILDDIR)/$(TARGET)

cmake-build:
	@mkdir -p $(BUILDDIR)
	@cd $(BUILDDIR) && cmake .. -DCMAKE_CXX_COMPILER=$(CXX) && make

$(BUILDDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(BUILDDIR)/$(TARGET)

clean:
	rm -rf $(BUILDDIR)

rebuild: clean all

debug: CXXFLAGS += -g -DDEBUG
debug: all

.PHONY: all clean rebuild run debug cmake-build