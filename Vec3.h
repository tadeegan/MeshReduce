#ifndef VEC3_H
#define VEC3_H

class Vec3{
    public:
        Vec3(float x, float y, float z);
        float x;
        float y;
        float z;
        Vec3();
        Vec3 operator+(Vec3 const & other);
        Vec3 operator-(Vec3 const & other);
        Vec3 operator*(Vec3 const & other);
    private:
};

#endif