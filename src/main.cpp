#include <opencv2/opencv.hpp>

#include "ObjParser.hpp"
#include "RayTracer.hpp"

Scene daltons() {
    ObjParser parser;
    PolygonMesh mesh = parser.readObj("../data/cube.obj");

    Scene scene(glm::vec3(235, 206, 135));

    auto plane = std::make_shared<Plane>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1),
                                         0, 0, 0.2, 0.25);

    auto sphere1 =
        std::make_shared<Sphere>(glm::vec3(6.16, 0.66, 1), glm::vec3(1, 1, 1), 1, 0, 0, 0.8, 0.22);
    auto sphere2 =
        std::make_shared<Sphere>(glm::vec3(5, 0, 0.66), glm::vec3(0, 1, 1), 0.66, 0, 0, 0.2, 0.1);
    auto sphere3 = std::make_shared<Sphere>(glm::vec3(4.16, 0.44, 0.20), glm::vec3(0, 0, 1), 0.20,
                                            0, 0, 0.1, 0.20);
    auto sphere4 = std::make_shared<Sphere>(glm::vec3(5.25, 3, 0.66), glm::vec3(1, 1, 1), 0.25,
                                            0.95, 1.5, 0, 0.05);

    // auto triangle1 = std::make_shared<Triangle>(
    //    glm::vec3(1.5, -0.5, -0.5), glm::vec3(1.5, 0.5, 0.5), glm::vec3(1.5, 0.5, -0.5));

    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 0.5), glm::vec3(1, 0, 0), 0.1, 0.1, 1000,
                                           1000, 0.05);
    auto lightSource = std::make_shared<DirectLight>(glm::vec3(0, 0, 10), glm::vec3(1, 1, 1), 2000);

    scene.addObject(plane);
    scene.addObject(sphere1);
    scene.addObject(sphere2);
    scene.addObject(sphere3);
    scene.addObject(sphere4);
    // TriangleMesh tMesh(mesh);
    // scene.addObject(std::make_shared<Triangle>(tMesh.getTriangles()[10]));
    // scene.addObject(std::make_shared<TriangleMesh>(tMesh));
    // scene.addObject(triangle1);
    scene.setCamera(camera);
    scene.addSource(lightSource);

    return scene;
}

void test() {
    Scene scene = daltons();
    StdRayTracer stdrt;

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }

    stdrt.render(scene);

    cv::waitKey(0);
}

int main(int argc, const char **argv) {
    test();
    return 0;
}
