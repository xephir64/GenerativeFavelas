#include "Railing.h"
#include "glm/common.hpp"

#include <glm/exponential.hpp>
#include <glm/trigonometric.hpp>
/*
 * Generate the geometry of the railing
 */
void Railing::makeRailing(GLfloat width, GLfloat height, GLfloat depth, GLfloat angle, GLboolean cross) {
    float t = 0.03f; // tile size
    float r = 0.03f; // space between tile for cross railing
    float l = 0.05f; // rectangle size

    float xPoints[2] = {0.0f, t};
    float yPoints[8] = {
        0, t, t + l, t + l + t, t + l + t + r, t + l + t + r + t, t + l + t + r + t + l, t + l + t + r + t + l + t};

    // Compute angle
    float angleRotation = glm::atan(glm::sin(angle) / width); // TOA = tan(angle) = Opposite / Adjacent
    float hypotenuse = glm::sqrt(glm::pow(width, 2) + glm::pow(angle, 2));

    // Space between fence and number of fence in width
    float spaceWidth = 0.0f;
    int nbRailingWidth = 0;

    // Space between fence and number of fence in depth
    float spaceDepth = 0.0f;
    int nbRailingDepth = 0;

    // Compute space between fence in width
    nbRailingWidth = glm::ceil((hypotenuse - t) / 0.15f);
    spaceWidth = (hypotenuse - t) / nbRailingWidth;
    nbRailingWidth = glm::ceil(hypotenuse / spaceWidth);

    // Compute space between fence in depth
    nbRailingDepth = glm::ceil((depth) / 0.15f);
    spaceDepth = ((depth - t) / nbRailingDepth);
    nbRailingDepth = glm::ceil(depth / spaceDepth);

    std::vector<GLuint> base_indices({2, 0, 1, 1,  3, 2, 4, 2,  3,  3,  5,  4,  6,  4,  5,  5,  7,  6,  8,  6,  7,
                                      7, 9, 8, 10, 8, 9, 9, 11, 10, 12, 10, 11, 11, 13, 12, 14, 12, 13, 13, 15, 14});

    std::vector<GLuint> indices;
    std::vector<glm::vec3> vertices;

    float addSpace = 0.0f;

    for (int i = 0; i < nbRailingDepth; i++) {
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 2; k++)
                vertices.push_back(glm::vec3(0.0f, yPoints[j], xPoints[k] + addSpace));

        for (int l = 0; l < base_indices.size(); l++)
            indices.push_back(base_indices[l] + i * 16);

        if (i > 0) {
            if (cross) {
                if (i & 1)
                    indices.insert(indices.end(),
                                   {static_cast<GLuint>(11 + ((i - 1) * 16)), static_cast<GLuint>(9 + ((i - 1) * 16)),
                                    static_cast<GLuint>(8 + (i * 16)), static_cast<GLuint>(8 + (i * 16)),
                                    static_cast<GLuint>(10 + (i * 16)), static_cast<GLuint>(11 + ((i - 1) * 16))});
                else
                    indices.insert(indices.end(),
                                   {static_cast<GLuint>(7 + ((i - 1) * 16)), static_cast<GLuint>(5 + ((i - 1) * 16)),
                                    static_cast<GLuint>(4 + (i * 16)), static_cast<GLuint>(4 + (i * 16)),
                                    static_cast<GLuint>(6 + (i * 16)), static_cast<GLuint>(7 + ((i - 1) * 16))});
            }
            indices.insert(indices.end(),
                           {static_cast<GLuint>(15 + ((i - 1) * 16)), static_cast<GLuint>(13 + ((i - 1) * 16)),
                            static_cast<GLuint>(12 + (i * 16)), static_cast<GLuint>(12 + (i * 16)),
                            static_cast<GLuint>(14 + (i * 16)), static_cast<GLuint>(15 + ((i - 1) * 16))});
        }

        addSpace += spaceDepth;
    }

    addSpace = 0.0f;

    for (int i = nbRailingDepth; i < nbRailingWidth + nbRailingDepth; i++) {
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 2; k++)
                vertices.push_back(glm::vec3(xPoints[k] + addSpace, yPoints[j], depth));

        for (int l = 0; l < base_indices.size(); l++)
            indices.push_back(base_indices[l] + i * 16);

        if (i > nbRailingDepth) {
            if (cross) {
                if ((i + 1) & 1)
                    indices.insert(indices.end(),
                                   {static_cast<GLuint>(11 + ((i - 1) * 16)), static_cast<GLuint>(9 + ((i - 1) * 16)),
                                    static_cast<GLuint>(8 + (i * 16)), static_cast<GLuint>(8 + (i * 16)),
                                    static_cast<GLuint>(10 + (i * 16)), static_cast<GLuint>(11 + ((i - 1) * 16))});
                else
                    indices.insert(indices.end(),
                                   {static_cast<GLuint>(7 + ((i - 1) * 16)), static_cast<GLuint>(5 + ((i - 1) * 16)),
                                    static_cast<GLuint>(4 + (i * 16)), static_cast<GLuint>(4 + (i * 16)),
                                    static_cast<GLuint>(6 + (i * 16)), static_cast<GLuint>(7 + ((i - 1) * 16))});
            }
            indices.insert(indices.end(),
                           {static_cast<GLuint>(15 + ((i - 1) * 16)), static_cast<GLuint>(13 + ((i - 1) * 16)),
                            static_cast<GLuint>(12 + (i * 16)), static_cast<GLuint>(12 + (i * 16)),
                            static_cast<GLuint>(14 + (i * 16)), static_cast<GLuint>(15 + ((i - 1) * 16))});
        }

        addSpace = spaceWidth + addSpace;
    }

    addSpace = 0.0f;

    for (int i = nbRailingWidth + nbRailingDepth; i < (nbRailingWidth + nbRailingDepth * 2); i++) {
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 2; k++)
                vertices.push_back(glm::vec3(hypotenuse, yPoints[j], xPoints[k] + addSpace));

        for (int l = 0; l < base_indices.size(); l++)
            indices.push_back(base_indices[l] + i * 16);

        if (i > nbRailingWidth + nbRailingDepth) {
            if (cross) {
                if (i & 1)
                    indices.insert(indices.end(),
                                   {static_cast<GLuint>(11 + ((i - 1) * 16)), static_cast<GLuint>(9 + ((i - 1) * 16)),
                                    static_cast<GLuint>(8 + (i * 16)), static_cast<GLuint>(8 + (i * 16)),
                                    static_cast<GLuint>(10 + (i * 16)), static_cast<GLuint>(11 + ((i - 1) * 16))});
                else
                    indices.insert(indices.end(),
                                   {static_cast<GLuint>(7 + ((i - 1) * 16)), static_cast<GLuint>(5 + ((i - 1) * 16)),
                                    static_cast<GLuint>(4 + (i * 16)), static_cast<GLuint>(4 + (i * 16)),
                                    static_cast<GLuint>(6 + (i * 16)), static_cast<GLuint>(7 + ((i - 1) * 16))});
            }
            indices.insert(indices.end(),
                           {static_cast<GLuint>(15 + ((i - 1) * 16)), static_cast<GLuint>(13 + ((i - 1) * 16)),
                            static_cast<GLuint>(12 + (i * 16)), static_cast<GLuint>(12 + (i * 16)),
                            static_cast<GLuint>(14 + (i * 16)), static_cast<GLuint>(15 + ((i - 1) * 16))});
        }

        addSpace = spaceDepth + addSpace;
    }

    this->angle = angleRotation;
    this->indices = indices;
    computeVertexNormals(vertices);
    setupMesh();
}