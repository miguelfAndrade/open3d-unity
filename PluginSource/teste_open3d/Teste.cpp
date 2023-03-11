#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <utility>
#include "open3d/Open3D.h"


#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

// void vizSphere();
void pCloud(std::string pathData, std::string pathOBJ);

int main(int argc, char *argv[]) {
    pCloud("sensor_data.xyz", "sensor_data_obj.obj");
    return 0;
}

// ------------------------------------------------------------------------
// Plugin itself

// Link following functions C-style (required for plugins)
extern "C"
{
    EXPORT_API int CreateSphere() {
        auto sphere = open3d::geometry::TriangleMesh::CreateSphere(1.0);
        // vizSphere();
        sphere->ComputeVertexNormals();
        sphere->PaintUniformColor({0.0, 1.0, 0.0});

        open3d::visualization::DrawGeometries({sphere});
        return 0;
    }

    EXPORT_API void CreateFile() {
        auto sphere = open3d::geometry::TriangleMesh::CreateSphere(1.0);
        std::string path = "Assets/Resources/model.obj";
        bool res = open3d::io::WriteTriangleMesh(path, sphere->ComputeVertexNormals());
    }

    EXPORT_API int getPC() {
        pCloud("data/sensor_data.xyz", "Assets/Resources/sensor_data.obj");
        return 0;
    }
} // end of export C block

void pCloud(std::string filename, std::string pathOBJ) {

    auto pointSet = std::make_shared<open3d::geometry::PointCloud>(); // Creates an empty Point Cloud

    // Opens the file with the pointcloud data and stores it in the pointSet variable
    std::ifstream f(filename);
    if(f.is_open()) {
        pointSet->Clear();
        double x, y, z;
        while (f >> x >> y >> z) {
            pointSet->points_.push_back(Eigen::Vector3d(x, y, z));
            //std::cout << std::to_string(x) << "  " << std::to_string(y) << "  " << std::to_string(z) << std::endl;
        }
    }
    f.close();

    auto downSampledPCD = pointSet->VoxelDownSample(0.03);
    std::cout << "Point Cloud size: " << std::to_string(downSampledPCD->points_.size()) << std::endl;
    // std::cout << "HOME DIRECTORY: " << open3d::utility::filesystem::GetHomeDirectory() << std::endl;
    //std::cout << "Passed EstimateNormals function" << std::endl;

    /*
    for(int i=0; i < downSampledPCD->points_.size(); i++)
    {
        double x = downSampledPCD->points_[i].x();
        double y = downSampledPCD->points_[i].y();
        double z = downSampledPCD->points_[i].z();
        std::cout << std::to_string(x) << "  " << std::to_string(y) << "  " << std::to_string(z) << std::endl;
    }
    */

    open3d::geometry::KDTreeSearchParam search = open3d::geometry::KDTreeSearchParamKNN(5);
    (*downSampledPCD).EstimateNormals(search);

    (*downSampledPCD).OrientNormalsConsistentTangentPlane(50);
    auto tupleMesh = open3d::geometry::TriangleMesh::CreateFromPointCloudPoisson(*downSampledPCD, 9, 0.0f, 1.1f, false, -1);
    auto mesh = std::get<0>(tupleMesh);
    //open3d::io::WriteTriangleMesh(pathOBJ, mesh->ComputeVertexNormals());

    mesh->ComputeVertexNormals();
    open3d::visualization::DrawGeometries({mesh});
}
