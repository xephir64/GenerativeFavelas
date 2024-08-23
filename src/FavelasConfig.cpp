#include "FavelasConfig.h"
#include <random>
#include <stdlib.h>

unsigned int getRandomNumberuv(unsigned int min, unsigned int max) { return min + rand() % (max - min + 1); }

float getRandomNumberfv(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

void FavelasConfig::generateConfiguration() {
    this->config.housesPerRow = getRandomNumberuv(FavelasConstants::housesPerRowMin, FavelasConstants::housesPerRowMax);

    for (int i = 0; i < FavelasConstants::nbOfRows; i++) {
        RowOfHouse row;
        float totalWidth = 0;
        for (int j = 0; j < this->config.housesPerRow; j++) {
            float remainingWidth = FavelasConstants::rowWidth - totalWidth;
            float averageWidth = remainingWidth / (this->config.housesPerRow - j);
            float width = getRandomNumberfv(averageWidth - 1, averageWidth + 1);
            if (j == this->config.housesPerRow - 1)
                width = remainingWidth;

            float rotation = getRandomNumberfv(FavelasConstants::houseRotationMin, FavelasConstants::houseRotationMax);

            float height = getRandomNumberfv(1, 3);
            float depth = getRandomNumberfv(1, 3);
            float depthOffset = getRandomNumberfv(1, 3);

            House house(rotation, width, height, depth, depthOffset);
            row.houses.push_back(house);
            totalWidth += width;
        }
        row.houseWidth = totalWidth;
        this->config.rows.push_back(row);
    }
}

BlockConfig FavelasConfig::getConfig() { return this->config; }
