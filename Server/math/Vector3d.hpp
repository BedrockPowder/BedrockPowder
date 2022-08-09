//
// Created by pepef on 27.07.2022.
//

#ifndef BEDROCKPOWDER_VECTOR3D_HPP
#define BEDROCKPOWDER_VECTOR3D_HPP

#include <sstream>
#include "Server/utils/StdEnv.h"

float square(float t) {
    return t * t;
}

class Vector3d {
public:
    explicit Vector3d(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    explicit Vector3d(int x = 0, int y = 0, int z = 0) {
        this->x = (float)x;
        this->y = (float)y;
        this->z = (float)z;
    }

    Vector3d* add(int x_, int y_ = 0, int z_ = 0) {
        this->x += (float)x_;
        this->y += (float)y_;
        this->z += (float)z_;
        return this;
    }

    Vector3d* add(float x_, float y_ = 0.0f, float z_ = 0.0f) {
        this->x += x_;
        this->y += y_;
        this->z += z_;
        return this;
    }

    Vector3d* substract(int x_, int y_ = 0, int z_ = 0) {
        return this->add(-x_, y_, -z_);
    }

    Vector3d* substract(float x_, float y_ = 0, float z_ = 0) {
        return this->add(-x_, y_, -z_);
    }

    Vector3d* addVector(Vector3d* v3d) {
        return this->add(v3d->getX(), v3d->getY(), v3d->getZ());
    }

    Vector3d* substractVector(Vector3d* v3d) {
        return this->add(-v3d->getX(), -v3d->getY(), -v3d->getZ());
    }

    Vector3d* _ceil() {
        this->x = ceil(this->x);
        this->y = ceil(this->y);
        this->z = ceil(this->z);
        return this;
    }

    Vector3d* _floor() {
        this->x = (float)this->getFloorX();
        this->y = (float)this->getFloorY();
        this->z = (float)this->getFloorZ();
        return this;
    }

    // todо. round.

    Vector3d* multiply(float multi) {
        this->x *= multi;
        this->y *= multi;
        this->z *= multi;
        return this;
    }

    Vector3d* divide(float num) {
        this->x /= num;
        this->y /= num;
        this->z /= num;
        return this;
    }

    float distanceSquared(Vector3d* pos) const {
        return (square((this->x - pos->getX()))) + (square((this->y - pos->getY()))) + square((this->z - pos->getZ()));
    }

    float distance(Vector3d* pos) const {
        return sqrt(this->distanceSquared(pos));
    }

    [[nodiscard]]
    float lengthSquared() const {
        return square(this->x) + square(this->y) + square(this->z);
    }

    [[nodiscard]]
    float length() const {
        return sqrt(this->lengthSquared());
    }

    Vector3d* normalize() {
        float lngthsqrd = this->lengthSquared();
        if (lngthsqrd > 0) {
            return this->divide(sqrt(lngthsqrd));
        }
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
        return this;
    }

    [[nodiscard]]
    std::string toString() const {
        std::stringstream s_str("");
        s_str << "Vector3d<x=" << std::to_string(this->x) << ",y=" << std::to_string(this->y) << ",z=" << std::to_string(this->z) << ">";
        return s_str.str();
    }

    [[nodiscard]]
    float getX() const {
        return this->x;
    }

    [[nodiscard]]
    float getY() const {
        return this->y;
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
    int getFloorY() const {
        return (int)floor(this->y);
    }

    [[nodiscard]]
    int getFloorZ() const {
        return (int)floor(this->z);
    }
private:
    float x, y, z;
};

#endif //BEDROCKPOWDER_VECTOR3D_HPP
