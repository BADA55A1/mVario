TOP_DIR    = ../../

include $(TOP_DIR)/make_variables.mk

DEPS       = menu.h value_edit.h
SRCS       = menu.cpp value_edit.cpp
OBJECTS    = $(SRCS:.cpp=.o)
OBJECTS    := $(addprefix $(OBJ_DIR)/,$(OBJECTS))


all: $(OBJECTS)
	+$(MAKE) -C menu_tree

$(OBJ_DIR)/%.o: %.cpp $(DEPS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)