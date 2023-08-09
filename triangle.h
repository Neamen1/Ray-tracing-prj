#ifndef RAYTRACING_IN_1_WEEKEND_TRIANGLE_H
#define RAYTRACING_IN_1_WEEKEND_TRIANGLE_H



#include "hittable.h"
#include "vec3.h"

class triangle : public hittable {
public:
    triangle() {}
    triangle(point3 vertex0, point3 vertex1, point3 vertex2, shared_ptr<material> m)
            : vertex0(vertex0), vertex1(vertex1), vertex2(vertex2), mat_ptr(m) {};

    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    point3 vertex0, vertex1, vertex2;
    shared_ptr<material> mat_ptr;
};

bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {

    vec3 edge1, edge2, h, s, q;
    double a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = cross(r.dir,edge2);
    a = dot(edge1, h);

    if (a > -t_min && a < t_min)   // This ray is parallel to this triangle.
        return false;

    f = 1.0/a;
    s = r.orig - vertex0;

    u = f * dot(s,h);

    if (u < 0.0 || u > 1.0)
        return false;

    q = cross(s,edge1);
    v = f * dot(r.dir,q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    // At this stage we can compute t to find out where the intersection point is on the line.
    double t = f * dot(edge2, q);

    if (t > t_min) // ray intersection
    {


        rec.t = t;
        rec.p = r.at(rec.t);
        rec.normal = cross(edge1,edge2);
        vec3 outward_normal = cross(edge1,edge2);
        rec.set_face_normal(r, outward_normal);

        //finding distances from current ray intersection point to the edges of triangle and making them black
        vec3 vecVert0ToPoint = rec.p - vertex0;
        vec3 vecVert2ToPoint = rec.p - vertex2;
        vec3 vecVert1ToPoint = rec.p - vertex1;

        vec3 edge3 = vertex2-vertex1;
        //cross(edge1, vecVert0ToPoint).length();    - area
        float distanceFromPointToEdge1 = (cross(edge1, vecVert0ToPoint).length()) / edge1.length();
        float distanceFromPointToEdge2 = (cross(edge2, vecVert2ToPoint).length()) / edge2.length();
        float distanceFromPointToEdge3 = (cross(edge3, vecVert1ToPoint).length()) / edge3.length();

        float coef = 0.005;//(edge1.length()+edge2.length()+edge3.length())/(3*40);

        if (distanceFromPointToEdge1 < coef || distanceFromPointToEdge2 < coef || distanceFromPointToEdge3 < coef) {
            rec.mat_ptr = make_shared<solid>(color(0, 0, 0));
        }
        else{
            rec.mat_ptr = mat_ptr;
        }

        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;
}


#endif //RAYTRACING_IN_1_WEEKEND_TRIANGLE_H
