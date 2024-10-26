#include "Railing.h"

#include <glm/exponential.hpp>
#include <glm/trigonometric.hpp>
/*
 * Generate the geometry of the railing
 */
void Railing::makeRailing(GLfloat width, GLfloat height, GLfloat depth, GLfloat angle, GLboolean cross) {
    float t = 0.03f;  // tile size
    float r = 0.05f;  // rectangle size
    float l = 0.075f; // space between tile for cross railing

    float xPoints[2] = {0.0f, t};
    float yPoints[8] = {
        0, t, t + l, t + l + t, t + l + t + r, t + l + t + r + t, t + l + t + r + t + l, t + l + t + r + t + l + t};

    // Compute angle
    float angleRotation = glm::atan(glm::sin(angle) / width); // TOA = tan(angle) = Opposite / Adjacent
    float hypotenuse = glm::sqrt(glm::pow(width, 2) + glm::pow(angle, 2));

    // Space between fence and number of fence in width
    float spaceWidth = 0.0f;
    float widthT = hypotenuse - t;
    int nbRailingWidth = 0;
    int nbWidth = 1;

    //  Space between fence and number of fence in depth
    float spaceDepth = 0.0f;
    float depthT = hypotenuse - t;
    int nbRailingDepth = 0;
    int nbDepth = 1;

    // Compute space between fence in width
    while (spaceWidth < 0.30f) {
        spaceWidth = (nbWidth / (widthT * 4.0f));
        widthT -= t;
        nbWidth++;
    }
    nbRailingWidth = glm::round(widthT / spaceWidth);
    spaceWidth = (hypotenuse - 0.05f) / nbRailingWidth;

    // Compute space between fence in depth
    while (spaceDepth < 0.30f) {
        spaceDepth = (nbDepth / (depthT * 4.0f));
        depthT -= t;
        nbDepth++;
    }
    nbRailingDepth = glm::round(widthT / spaceWidth);
    spaceDepth = (hypotenuse - 0.05f) / nbRailingWidth;

    std::vector<GLuint> base_indices({2, 0, 1, 1,  3, 2, 4, 2,  3,  3,  5,  4,  6,  4,  5,  5,  7,  6,  8,  6,  7,
                                      7, 9, 8, 10, 8, 9, 9, 11, 10, 12, 10, 11, 11, 13, 12, 14, 12, 13, 13, 15, 14});

    std::vector<GLuint> indices;
    std::vector<glm::vec3> vertices;

    float addSpace = 0.0f;

    for (int i = 0; i < nbRailingWidth; i++) {
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 2; k++)
                vertices.push_back(glm::vec3(xPoints[k] + addSpace, yPoints[j], 0.0f));
        for (int l = 0; l < base_indices.size(); l++)
            indices.push_back(base_indices[l] + i * 16);
        if (i > 0) {
            // Link the fence to make the railing
            indices.insert(indices.end(),
                           {static_cast<GLuint>(15 + ((i - 1) * 16)), static_cast<GLuint>(13 + ((i - 1) * 16)),
                            static_cast<GLuint>(12 + (i * 16)), static_cast<GLuint>(12 + (i * 16)),
                            static_cast<GLuint>(14 + (i * 16)), static_cast<GLuint>(15 + ((i - 1) * 16))});
        }
        addSpace = spaceWidth + addSpace;
    }

    this->indices = indices;
    computeVertexNormals(vertices);
    setupMesh();
}