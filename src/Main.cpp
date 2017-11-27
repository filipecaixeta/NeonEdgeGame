#include "Game.h"

int main (int argc, char** argv) {
    try {
        Game game = Game("Prototipo Sidescroller");
        game.Run();
    }
    catch(std::string &s) {
        std::cerr << s << std::endl;
    }
		
    return 0;
}
