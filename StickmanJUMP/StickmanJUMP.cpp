#include <iostream>

#include "Engine.h"

int main()
{
    Engine* engine = new Engine();

    std::cout << "\nCreated by Michal Balcerak \n\n";
    std::cout << " Sound effects taken from: \n\n  https://pixabay.com\n  https://tuna.voicemod.net\n  https://Mixkit.co\n\n";
    std::cout << " Music in-game: \n\n  Adventure by Alexander Nakarada | https://creatorchords.com \n  Music promoted by https://www.chosic.com/free-music/all/ \n  Attribution 4.0 International(CC BY 4.0) \n  https://creativecommons.org/licenses/by/4.0/";

    while (engine->isRunning()) {
        // Update
        engine->update();

        // Render
        engine->render();
    }

    return 0;
}

