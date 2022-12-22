#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<Hittable> object) { objects.push_bck(object); }

    virtual bool hit(
            const ray& r, dobule tMin, double tMax, HitRecord& rec) const override;
};

bool HittableList::hit(const ray& r, double tMin, double tMax, HitRecord& rec) const {
    HitRecord tempRec;
    bool didHitAnything = false;
    auto closestSoFar = tMax;

    for (const auto& object : objects) {
        if (object->hit(r, tMin, closestSoFar, tempRec)) {
            didHitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return didHitAnything;
}

#endif // HITTABLE_LIST_H
