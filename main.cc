#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

double hitSphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}

color rayColor(const ray& r) {
    auto t = hitSphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unitVector(r.at(t) - vec3(0, 0, -1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unitDirection = unitVector(r.direction());
    t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // Camera
    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focalLength);

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for (int j = imageHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            auto u = double(i) / (imageWidth-1);
            auto v = double(j) / (imageHeight-1);
            ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
            color pixelColor = rayColor(r);
            writeColor(std::cout, pixelColor);
        }
    }
    std::cerr << "\nDone.\n";
    return 0;
}
