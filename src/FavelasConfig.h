#ifndef FAVELAS_CONFIG_H
#define FAVELAS_CONFIG_H

#include <vector>

namespace FavelasConstants {
constexpr float nbOfRows = 4.0f;
constexpr float housesPerRowMin = 3.0f;
constexpr float housesPerRowMax = 6.0f;
constexpr float houseRotationMin = -10.0f;
constexpr float houseRotationMax = 10.0f;
constexpr float rowWidth = 10.0f;
} // namespace FavelasConstants

struct DoorConfig {
    float r, g, b;
    bool fullWindow;
};

struct House {
    float rotation;
    float width;
    float height;
    float depth;
    float depthOffset;
    float roofSlope;
    float r, g, b;
    struct DoorConfig door;
    House(float rot = 0, float w = 0, float h = 0, float d = 0, float dOffset = 0)
        : rotation(rot), width(w), height(h), depth(d), depthOffset(dOffset) {}
};

struct RowOfHouse {
    unsigned int houseWidth; // Should be near BlockConfig.width
    std::vector<House> houses;
};

struct BlockConfig {
    unsigned int housesPerRow;
    unsigned int width = 20;
    std::vector<RowOfHouse> rows;
};

class FavelasConfig {
  public:
    void generateConfiguration();
    BlockConfig getConfig();

  private:
    BlockConfig config;
};

#endif