#include "FavelasConfig.h"
#include <random>
#include <stdlib.h>

std::knuth_b rand_engine;

unsigned int getRandomNumberuv(unsigned int min, unsigned int max) { return min + rand() % (max - min + 1); }

float getRandomNumberfv(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

bool getRandomBoolean(float probability) {
    std::bernoulli_distribution bd(probability);
    return bd(rand_engine);
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

            float height = getRandomNumberfv(HouseConstants::houseHeightMin, HouseConstants::houseHeightMax);
            float depth = getRandomNumberfv(HouseConstants::houseDepthMin, HouseConstants::houseDepthMax);
            float depthOffset = getRandomNumberfv(1, 3);

            float slope = getRandomNumberfv(FavelasConstants::roofMinSlope, FavelasConstants::roofMaxSlope);

            House house(rotation, width, height, depth, depthOffset, slope);
            house.r = getRandomNumberfv(0.0f, 1.0f);
            house.g = getRandomNumberfv(0.0f, 1.0f);
            house.b = getRandomNumberfv(0.0f, 1.0f);

            DoorConfig doorConfig;
            doorConfig.r = getRandomNumberfv(0.0f, 1.0f);
            doorConfig.g = getRandomNumberfv(0.0f, 1.0f);
            doorConfig.b = getRandomNumberfv(0.0f, 1.0f);
            doorConfig.fullWindow = getRandomNumberuv(0, 1);

            RailingConfig railingConf;
            railingConf.hasRailing = getRandomBoolean(RailingConstants::railingProbability);
            if (railingConf.hasRailing)
                railingConf.crossed = getRandomBoolean(RailingConstants::crossingProbability);

            house.door = doorConfig;
            house.railing = railingConf;

            row.houses.push_back(house);
            totalWidth += width;
        }
        row.houseWidth = totalWidth;
        this->config.rows.push_back(row);
    }
}

BlockConfig FavelasConfig::getConfig() { return this->config; }
