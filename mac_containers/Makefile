# Define compiler and flags
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
FTFLAGS = $(CFLAGS) -D USING_FT -I./
STDFLAGS = $(CFLAGS) -D USING_STD

STDINCLUDEVEC = -I ./containers_test/srcs/vector/
STDINCLUDEMAP = -I ./containers_test/srcs/map/
STDINCLUDESTK = -I ./containers_test/srcs/stack/
STDINCLUDESET = -I ./containers_test/srcs/set/

# Define directories
VECDIR = ./ft_vector
MAPDIR = ./ft_map
SETDIR = ./ft_set
STACKDIR = ./ft_stack

VECSTDDIR = ./std_vector
MAPSTDDIR = ./std_map
SETSTDDIR = ./std_set
STKSTDDIR = ./std_stack

SRCS		= ./containers_test/srcs

VECFILE		=	${SRCS}/vector/assign.cpp             \
				${SRCS}/vector/at_const.cpp           \
				${SRCS}/vector/at.cpp                 \
				${SRCS}/vector/bidirect_it.cpp        \
				${SRCS}/vector/copy_construct.cpp     \
				${SRCS}/vector/erase.cpp              \
				${SRCS}/vector/insert.cpp             \
				${SRCS}/vector/insert2.cpp            \
				${SRCS}/vector/ite_arrow.cpp          \
				${SRCS}/vector/ite.cpp                \
				${SRCS}/vector/ite_eq_ope.cpp         \
				${SRCS}/vector/push_pop.cpp           \
				${SRCS}/vector/relational_ope.cpp     \
				${SRCS}/vector/rev_ite_construct.cpp  \
				${SRCS}/vector/rite2.cpp              \
				${SRCS}/vector/rite_arrow.cpp         \
				${SRCS}/vector/rite.cpp               \
				${SRCS}/vector/rite_eq_ope.cpp        \
				${SRCS}/vector/size.cpp               \
				${SRCS}/vector/swap.cpp

MAPFILE		=	${SRCS}/map/bounds.cpp                \
				${SRCS}/map/comp.cpp                  \
				${SRCS}/map/copy_construct.cpp        \
				${SRCS}/map/empty.cpp                 \
				${SRCS}/map/erase2.cpp                \
				${SRCS}/map/erase.cpp                 \
				${SRCS}/map/find_count.cpp            \
				${SRCS}/map/insert2.cpp               \
				${SRCS}/map/insert.cpp                \
				${SRCS}/map/ite_arrow.cpp             \
				${SRCS}/map/more.cpp                  \
				${SRCS}/map/op_sqbr.cpp               \
				${SRCS}/map/relational_ope.cpp        \
				${SRCS}/map/rev_ite_construct.cpp     \
				${SRCS}/map/rite_arrow.cpp            \
				${SRCS}/map/rite.cpp                  \
				${SRCS}/map/swap.cpp                  \
				${SRCS}/map/tricky_construct.cpp      \
				${SRCS}/map/tricky_erase.cpp

SETFILE		=	${SRCS}/set/bounds.cpp                \
				${SRCS}/set/comp.cpp                  \
				${SRCS}/set/copy_construct.cpp        \
				${SRCS}/set/empty.cpp                 \
				${SRCS}/set/erase2.cpp                \
				${SRCS}/set/erase.cpp                 \
				${SRCS}/set/find_count.cpp            \
				${SRCS}/set/insert2.cpp               \
				${SRCS}/set/insert.cpp                \
				${SRCS}/set/ite_arrow.cpp             \
				${SRCS}/set/ite_n1.cpp                \
				${SRCS}/set/more.cpp                  \
				${SRCS}/set/relational_ope.cpp        \
				${SRCS}/set/rev_ite_construct.cpp     \
				${SRCS}/set/rite_arrow.cpp            \
				${SRCS}/set/rite.cpp                  \
				${SRCS}/set/swap.cpp                  \
				${SRCS}/set/tricky_construct.cpp      \
				${SRCS}/set/tricky_erase.cpp

STKFILE		=	${SRCS}/stack/default_copy.cpp        \
				${SRCS}/stack/default.cpp             \
				${SRCS}/stack/list_copy.cpp           \
				${SRCS}/stack/relational_ope.cpp      \
				${SRCS}/stack/relational_ope_list.cpp

# Define source files and corresponding programs for vector directory
VECSRC = $(VECFILE)
VECPROG = $(patsubst ./containers_test/srcs/vector/%.cpp,$(VECDIR)/vector_%.exe,$(VECSRC))
VECSTDPROG = $(patsubst ./containers_test/srcs/vector/%.cpp,$(VECSTDDIR)/vector_%.exe,$(VECSRC))

# Define source files and corresponding programs for map directory
MAPSRC = $(MAPFILE)
MAPPROG = $(patsubst ./containers_test/srcs/map/%.cpp,$(MAPDIR)/map_%.exe,$(MAPSRC))
MAPSTDPROG = $(patsubst ./containers_test/srcs/map/%.cpp,$(MAPSTDDIR)/map_%.exe,$(MAPSRC))

# Define source files and corresponding programs for set directory
SETSRC = $(SETFILE)
SETPROG = $(patsubst ./containers_test/srcs/set/%.cpp,$(SETDIR)/set_%.exe,$(SETSRC))
SETSTDPROG = $(patsubst ./containers_test/srcs/set/%.cpp,$(SETSTDDIR)/set_%.exe,$(SETSRC))

# Define source files and corresponding programs for stack directory
STACKSRC = $(STKFILE)
STACKPROG = $(patsubst ./containers_test/srcs/stack/%.cpp,$(STACKDIR)/stack_%.exe,$(STACKSRC))
STACKSTDPROG = $(patsubst ./containers_test/srcs/stack/%.cpp,$(STKSTDDIR)/stack_%.exe,$(STACKSRC))

# Default target
all: directories $(VECPROG) $(MAPPROG) $(SETPROG) $(STACKPROG) $(VECSTDPROG) $(MAPSTDPROG) $(SETSTDPROG) $(STACKSTDPROG)

directories:
	mkdir -p $(VECDIR)
	mkdir -p $(VECSTDDIR)
	mkdir -p $(MAPDIR)
	mkdir -p $(MAPSTDDIR)
	mkdir -p $(STACKDIR)
	mkdir -p $(STKSTDDIR)
	mkdir -p $(SETDIR)
	mkdir -p $(SETSTDDIR)

t:
	./test.sh
mil:
	cd ./containers_test/ && bash do.sh
jc:
	cd ./test_container/ && bash launch.sh

# Compile object files for vector directory
$(VECDIR)/%.o: ./containers_test/srcs/vector/%.cpp
	$(CC) $(FTFLAGS) -c -o $@ $<
$(VECSTDDIR)/%.o: ./containers_test/srcs/vector/%.cpp
	$(CC) $(STDFLAGS) $(STDINCLUDEVEC) -c -o $@ $<


# Compile object files for map directory
$(MAPDIR)/%.o: ./containers_test/srcs/map/%.cpp
	$(CC) $(FTFLAGS) -c -o $@ $<
$(MAPSTDDIR)/%.o: ./containers_test/srcs/map/%.cpp
	$(CC) $(STDFLAGS) $(STDINCLUDEMAP) -c -o $@ $<

# Compile object files for set directory
$(SETDIR)/%.o: ./containers_test/srcs/set/%.cpp
	$(CC) $(FTFLAGS) -c -o $@ $<
$(SETSTDDIR)/%.o: ./containers_test/srcs/set/%.cpp
	$(CC) $(STDFLAGS) $(STDINCLUDESET) -c -o $@ $<

# Compile object files for stack directory
$(STACKDIR)/%.o: ./containers_test/srcs/stack/%.cpp
	$(CC) $(FTFLAGS) -c -o $@ $<
$(STKSTDDIR)/%.o: ./containers_test/srcs/stack/%.cpp
	$(CC) $(STDFLAGS) $(STDINCLUDESTK) -c -o $@ $<

# Link object files into programs for vector directory
$(VECDIR)/vector_%.exe: $(VECDIR)/%.o
	$(CC) $(FTFLAGS) -o $@ $<
$(VECSTDDIR)/vector_%.exe: $(VECSTDDIR)/%.o
	$(CC) $(STDFLAGS) $(STDINCLUDEVEC) -o $@ $<

# Link object files into programs for map directory
$(MAPDIR)/map_%.exe: $(MAPDIR)/%.o
	$(CC) $(FTFLAGS) -o $@ $<
$(MAPSTDDIR)/map_%.exe: $(MAPSTDDIR)/%.o
	$(CC) $(STDFLAGS) $(STDINCLUDEMAP) -o $@ $<

# Link object files into programs for set directory
$(SETDIR)/set_%.exe: $(SETDIR)/%.o
	$(CC) $(FTFLAGS) -o $@ $<
$(SETSTDDIR)/set_%.exe: $(SETSTDDIR)/%.o
	$(CC) $(STDFLAGS) $(STDINCLUDESET) -o $@ $<

# Link object files into programs for stack directory
$(STACKDIR)/stack_%.exe: $(STACKDIR)/%.o
	$(CC) $(FTFLAGS) -o $@ $<
$(STKSTDDIR)/stack_%.exe: $(STKSTDDIR)/%.o
	$(CC) $(STDFLAGS) $(STDINCLUDESTK) -o $@ $<

# Clean all object files and programs
clean:
	rm -f $(VECDIR)/*.o $(VECPROG) $(MAPDIR)/*.o $(MAPPROG) $(SETDIR)/*.o $(SETPROG) $(STACKDIR)/*.o $(STACKPROG)
	rm -f $(VECSTDDIR)/*.o $(VECSTDPROG) $(MAPSTDDIR)/*.o $(MAPSTDPROG) $(SETSTDDIR)/*.o $(SETSTDPROG) $(STKSTDDIR)/*.o $(STACKSTDPROG)

fclean:
	rm -rf $(VECDIR) $(VECSTDDIR) $(MAPDIR) $(MAPSTDDIR) $(STACKDIR) $(STKSTDDIR) $(SETDIR) $(SETSTDDIR)

re: fclean all

