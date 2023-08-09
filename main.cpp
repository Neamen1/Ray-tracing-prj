#include <fstream>
#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "triangle.h"
#include <random>
#include "OBJ_Loader.h"


color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.0001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        if(scattered.dir[0]==0 && scattered.dir[1]==0 &&scattered.dir[2]==0){
            return attenuation;
        }
        return color{0,0,0};
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);       //(linear interpolation) one color increases with t, other decreases
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 4;   //(100)  antialiasing
    const int max_depth = 1;   //(50) max amount of child rays when doing diffusion

    //world
    hittable_list world;

    //choosing material & color
    //auto material_mesh_tri = make_shared<solid>(color(0.39,0.39,1.0));

//obj loader
    objl::Loader Loader;

    // Load .obj File
    bool loadout = Loader.LoadFile("models/gourd.obj");

    // Check to see if it loaded
    // If so continue
    if (loadout)
    {
        // Create/Open e1Out.txt
        //std::ofstream file("e1Out.txt");

        // Go through each loaded mesh and out its contents
        for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
        {
            // Copy one of the loaded meshes to be our current mesh
            objl::Mesh curMesh = Loader.LoadedMeshes[i];

            for (int j = 0; j < curMesh.Indices.size(); j += 3)
            {
                vec3 temp[3];
                temp[0] = {curMesh.Vertices[curMesh.Indices[j]].Position.X,
                           curMesh.Vertices[curMesh.Indices[j]].Position.Y,
                           curMesh.Vertices[curMesh.Indices[j]].Position.Z};
                temp[1] = {curMesh.Vertices[curMesh.Indices[j+1]].Position.X,
                           curMesh.Vertices[curMesh.Indices[j+1]].Position.Y,
                           curMesh.Vertices[curMesh.Indices[j+1]].Position.Z};
                temp[2] = {curMesh.Vertices[curMesh.Indices[j+2]].Position.X,
                           curMesh.Vertices[curMesh.Indices[j+2]].Position.Y,
                           curMesh.Vertices[curMesh.Indices[j+2]].Position.Z};
                world.add(make_shared<triangle>(temp[0], temp[1], temp[2],
                                                make_shared<solid>(color(0,0.545,0.545))));
            }
        }

        // Close File
        //file.close();
    }
        // If not output an error
    else
    {
        std::cerr << "Could't open file\n" << std::flush;
        return 1;
//        // Create/Open e1Out.txt
//        std::ofstream file("e1Out.txt");
//
//        // Output Error
//        file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";
//
//        // Close File
//        file.close();
    }



    // Camera
    camera cam(point3(2,1,-2), point3(0,0,0), vec3(0,0,1), 60, aspect_ratio);       //vec3 ->view up vector; {0,1,0} means y axis is vertical


    // Render
    std::ofstream out;
    out.open("img.ppm");

    //camera for different angles in loop depending on "rotating" modifier
    //double rotationCircleRadius = 100;
    //camera cam(point3(rotationCircleRadius* cos(2*pi/(rotating)),rotationCircleRadius* sin(2*pi/(rotating)),1.5), point3(0.5,0.5,0.5), vec3(0,0,1), 120, aspect_ratio);


    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to img.ppm

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        // thread here if you want to make thread for each column
        // TODO:
        for (int i = 0; i < image_width; ++i) {
            // thread here if you want to make thread for each pixel
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);

        }
    }
    std::cout.rdbuf(coutbuf);   //return buffer to original state
    std::cerr << "\nDone.\n";

}
