#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public Hittable {

public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {};

    virtual bool hit(
        const ray& r, double tMin, double tMax, HitRecord& rec) const override;

public:
    point3 center;
    double radius;

};

bool sphere::hit(const ray& r, double tMin, double tMax, HitRecord& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().lengthSquared();
    auto halfB = dot(oc, r.direction());
    auto c = oc.lengthSquared() - radius*radius;
    auto discriminant = halfB*halfB - a*c;
    if (discriminant < 0) {
        return false;
    }

    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    auto root = (-halfB - sqrtd) / a;
    if (root < tMin || tMax < root) {
        root = (-halfB + sqrtd) / a;
        if (root < tMin || tMax < root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rect.t);
    rec.normal = (rec.p - center) / radius;
    vec3 outwardNormal = (rec.p - center) / radius;
    rect.setFaceNormal(r, outwardNormal);
    return true;
}

#endif // SPHERE_H
