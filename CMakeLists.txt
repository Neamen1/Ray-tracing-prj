cmake_minimum_required(VERSION 3.20)
project(raytracing_in_1_weekend)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracing_in_1_weekend main.cpp vec3.h color.h ray.h hittable.h sphere.h hittable_list.h rtweekend.h camera.h material.h triangle.h)
