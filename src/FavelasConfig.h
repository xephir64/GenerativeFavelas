#ifndef FAVELAS_CONFIG_H
#define FAVELAS_CONFIG_H

const int nbOfRows = 4;
const int housesPerRowMin = 3;
const int housesPerRowMax = 6;
const int houseRotationMin = -10;
const int houseRotationMax = 10;

typedef struct {
    int rotation;
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    unsigned int depthOffset;
} House;

typedef struct {
    unsigned int houseWidth; // Should be near BlockConfig.width
    House houses[];
} RowOfHouse;

typedef struct {
    unsigned int housesPerRow;
    unsigned int width = 20;
    RowOfHouse rows[4];
} BlockConfig;

class FavelasConfig {
  public:
    void generateConfiguration();
    BlockConfig getConfig();

  private:
    BlockConfig config;
};

#endif