#include "FavelasConfig.h"
#include <stdlib.h>

unsigned int getRandomNumber(unsigned int min, unsigned int max) { return rand() % max - min; }

void FavelasConfig::generateConfiguration() {
    this->config.housesPerRow = getRandomNumber(housesPerRowMin, housesPerRowMax);
    // Generate Houses for each rows
    for (int i = 0; i < nbOfRows; i++) {
        for (int j = 0; j < this->config.housesPerRow; j++) {
        }
    }
}

BlockConfig FavelasConfig::getConfig() { return BlockConfig(); }
