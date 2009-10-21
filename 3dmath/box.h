#ifndef BOX_H
#define BOX_H

class Box
{
    Box(Vector4& first, Vector4& second);
    ~Box();
    
    float intersect(Ray ray);
    Vector4 intersect(Ray ray);
}

#endif //BOX_H
