#include "vec3.h"
Vec3::Vec3(){
    x = 0;
    y = 0;
    z = 0;
}
Vec3::Vec3(float _x, float _y, float _z){
    x = _x;
    y = _y;
    z = _z;
}
Vec3 Vec3::operator+(Vec3 const & other){
    Vec3 temp(other.x + this->x, other.y + this->y, other.z + this->z);
    return temp;
}

Vec3 Vec3::operator-(Vec3 const & other){
    Vec3 temp(this.x - other->x, this.y - other->y, this.z - other->z);
    return temp;
}
Vec3 Vec3::operator*(Vec3 const & other){

}