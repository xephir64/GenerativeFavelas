#ifndef FAVELAS_CONFIG_H
#define FAVELAS_CONFIG_H

#include <vector>

namespace FavelasConstants {
constexpr float nbOfRows = 4.0f;
constexpr float housesPerRowMin = 3.0f;
constexpr float housesPerRowMax = 6.0f;
constexpr float houseRotationMin = -5.0f;
constexpr float houseRotationMax = 5.0f;
constexpr float rowWidth = 13.0f;
constexpr float roofMinSlope = -0.3f;
constexpr float roofMaxSlope = 0.3f;
} // namespace FavelasConstants

namespace HouseConstants {
constexpr float houseHeightMin = 1.2f;
constexpr float houseHeightMax = 2.8f;
constexpr float houseDepthMin = 1.0f;
constexpr float houseDepthMax = 2.5f;
} // namespace HouseConstants

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
    House(float rot = 0.0f, float w = 0.0f, float h = 0.0f, float d = 0.0f, float dOffset = 0.0f, float slope = 0.0f)
        : rotation(rot), width(w), height(h), depth(d), depthOffset(dOffset), roofSlope(slope) {}
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