CXX = g++

FILE = main.cpp \
		dwarf.cpp \
		character_2.cpp \
		state.cpp \
		game.cpp \
		game_mode_1_state.cpp \
		game_mode_2_state.cpp \
		main_menu_state.cpp \
		gui.cpp \
		chose_character_1_state.cpp \
		chose_character_2_state.cpp \
		chose_character_3_state.cpp \
		chose_character_4_state.cpp \
		entity.cpp \
		movement_component.cpp \
		animation_component.cpp \
		editor_state.cpp \
		hitbox_component.cpp \
		tile.cpp\
		pause_menu.cpp \
		settings_state.cpp\
		tile_map.cpp\
		graphics_settings.cpp

		
SRC = $(addprefix src/,$(FILE))

OBJ = $(SRC:.cpp=.o)

SFML = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

ERROR = -Werror -W -Wall -Wextra

EXEC = Tiphereth

all: $(EXEC)

$(EXEC) : $(OBJ)
	$(CXX) -o $(EXEC) $(OBJ) $(SFML) $(ERROR) -g3

%.o : src/%.cpp
	$(CXX) -o $(OBJ) -c $(SRC)

clean : 
	rm -f $(addprefix src/, *.o)

re : all clean 