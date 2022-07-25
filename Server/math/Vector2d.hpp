//
// Created by pepef on 26.07.2022.
//

#ifndef BEDROCKPOWDER_VECTOR2D_HPP
#define BEDROCKPOWDER_VECTOR2D_HPP

#include <sstream>
#include "Server/utils/StdEnv.h"

float square(float t) {
    return t * t;
}

class Vector2d {
public:
    explicit Vector2d(float x = 0.0f, float z = 0.0f) {
        this->x = x;
        this->z = z;
    }

    explicit Vector2d(int x = 0, int z = 0) {
        this->x = (float)x;
        this->z = (float)z;
    }

    Vector2d* add(int x_, int z_ = 0) {
        this->x += (float)x_;
        this->z += (float)z_;
        return this;
    }

    Vector2d* add(float x_, float z_ = 0.0f) {
        this->x += x_;
        this->z += z_;
        return this;
    }

    Vector2d* substract(int x_, int z_ = 0) {
        return this->add(-x_, -z_);
    }

    Vector2d* substract(float x_, float z_ = 0) {
        return this->add(-x_, -z_);
    }

    Vector2d* addVector(Vector2d* v2d) {
        return this->add(v2d->getX(), v2d->getZ());
    }

    Vector2d* substractVector(Vector2d* v2d) {
        return this->add(-v2d->getX(), -v2d->getZ());
    }

    Vector2d* _ceil() {
        this->x = ceil(this->x);
        this->z = ceil(this->z);
        return this;
    }

    Vector2d* _floor() {
        this->x = (float)this->getFloorX();
        this->z = (float)this->getFloorZ();
        return this;
    }

    // todо. round.

    Vector2d* multiply(float multi) {
        this->x *= multi;
        this->z *= multi;
        return this;
    }

    Vector2d* divide(float num) {
        this->x /= num;
        this->z /= num;
        return this;
    }

    float distanceSquared(Vector2d* pos) const {
        square((this->x - pos->getX()));
        return (square((this->x - pos->getX()))) + square((this->z - pos->getZ()));
    }

    float distance(Vector2d* pos) const {
        return sqrt(this->distanceSquared(pos));
    }

    [[nodiscard]]
    float lengthSquared() const {
        return square(this->x) + square(this->z);
    }

    [[nodiscard]]
    float length() const {
        return sqrt(this->lengthSquared());
    }

    Vector2d* normalize() {
        float lngthsqrd = this->lengthSquared();
        if (lngthsqrd > 0) {
            return this->divide(sqrt(lngthsqrd));
        }
        this->x = 0.0f;
        this->z = 0.0f;
        return this;
    }

    [[nodiscard]]
    std::string toString() const {
        std::stringstream s_str("");
        s_str << "Vector2d<x=" << std::to_string(this->x) << ",z=" << std::to_string(this->z) << ">";
        return s_str.str();
    }

    [[nodiscard]]
    float getX() const {
        return this->x;
    }

    [[nodiscard]]
    float getZ() const {
        return this->z;
    }

    [[nodiscard]]
    int getFloorX() const {
        return (int)floor(this->x);
    }

    [[nodiscard]]
    int getFloorZ() const {
        return (int)floor(this->z);
    }
private:
    float x, z;
};

#endif //BEDROCKPOWDER_VECTOR2D_HPP
