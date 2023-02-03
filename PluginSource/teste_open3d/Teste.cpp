#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "open3d/Open3D.h"

using namespace std;

#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

// void vizSphere();
void p();

int main(int argc, char *argv[]) {    
    p();
    return 0;
}

// ------------------------------------------------------------------------
// Plugin itself

// void vizSphere()
// {
//     auto sphere = open3d::geometry::TriangleMesh::CreateSphere(1.0);
//     sphere->ComputeVertexNormals();
//     sphere->PaintUniformColor({0.0, 1.0, 0.0});
//     open3d::visualization::DrawGeometries({sphere});
//     // return sphere;
// }


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
        auto pointSet = open3d::geometry::PointCloud();
        open3d::io::ReadPointCloudOption options = open3d::io::ReadPointCloudOption("xyz", false, false, false);
        open3d::io::ReadPointCloudFromXYZ("data/sensor_data.xyz", pointSet, options);                
        auto vx = pointSet.VoxelDownSample(0.03);
        auto downpcd = (*vx);
        // open3d::geometry::KDTreeSearchParam::SearchType searchType = open3d::geometry::KDTreeSearchParam::SearchType::Knn;
        open3d::geometry::KDTreeSearchParam search = open3d::geometry::KDTreeSearchParamHybrid(0.1, 30);
        std::cout << "Passou Aqui!" << std::endl;
        // open3d::geometry::PointCloud::EstimateNormals();
        downpcd.EstimateNormals(search, false);
        std::cout << "Passou a funcção EstimateNormals()!" << std::endl;
        downpcd.OrientNormalsConsistentTangentPlane(50);
        auto tupleMesh = open3d::geometry::TriangleMesh::CreateFromPointCloudPoisson(downpcd, 9, 0.0f, 1.1f, false, -1);
        auto mesh = std::get<0>(tupleMesh);
        bool res = open3d::io::WriteTriangleMesh("Assets/Resources/sensor_data.obj", mesh->ComputeVertexNormals());
        return 0;
    }
} // end of export C block

void p() {
    auto pointSet = open3d::geometry::PointCloud();
    open3d::io::ReadPointCloudOption options = open3d::io::ReadPointCloudOption("xyz", false, false, false);
    open3d::io::ReadPointCloudFromXYZ("sensor_data.xyz", pointSet, options);                
    auto downpcd = pointSet.VoxelDownSample(0.03);
    auto search = open3d::geometry::KDTreeSearchParamHybrid(0.1, 30);
    downpcd->EstimateNormals(search, false);
    downpcd->OrientNormalsConsistentTangentPlane(50);
    auto tupleMesh = open3d::geometry::TriangleMesh::CreateFromPointCloudPoisson(*downpcd, 9, 0.0f, 1.1f, false, -1);
    auto mesh = std::get<0>(tupleMesh);
    bool res = open3d::io::WriteTriangleMesh("Assets/Resources/sensor_data.obj", mesh->ComputeVertexNormals());
    // return 0;
}

// void p() {
//     auto pointSet = open3d::geometry::PointCloud();
//     open3d::io::ReadPointCloudOption options = open3d::io::ReadPointCloudOption("xyz", false, false, false);
//     // open3d::io::ReadPointCloudFromXYZ("Assets/Resources/sensor_data.xyz", pointSet, options);        
//     open3d::io::ReadPointCloudFromXYZ("sensor_data.xyz", pointSet, options);        
//     auto downpcd = pointSet.VoxelDownSample(0.03);
//     // auto search = open3d::geometry::KDTreeSearchParamHybrid(0.1, 30);
//     auto search = open3d::geometry::KDTreeSearchParamKNN(30);
//     // auto dist = downpcd->ComputeNearestNeighborDistance();
//     // auto avg_dist = (dist[0]+dist[1])/2;
//     // double radius = 3*avg_dist;
//     // double radius2 = radius*2;
//     // std::vector<double> vec = {radius, radius2};
//     downpcd->EstimateNormals(search);
//     downpcd->OrientNormalsConsistentTangentPlane(50);
//     // auto mesh = open3d::geometry::TriangleMesh::CreateFromPointCloudBallPivoting(*downpcd, {radius, radius2});
//     // auto tupleMesh = open3d::geometry::TriangleMesh::CreateFromPointCloudPoisson(*downpcd, 9, 0.0f, 1.1f, false, -1);
//     // auto filter = open3d::geometry::MeshBase::FilterScope::All;
//     // mesh->FilterSmoothLaplacian(10, 0.5, filter);
//     // mesh->FilterSmoothLaplacian(10, 0.5, open3d::geometry::MeshBase::FilterScope::All);
//     // auto mesh = std::get<0>(tupleMesh);
//     auto mesh = std::get<0>(open3d::geometry::TriangleMesh::CreateFromPointCloudPoisson(*downpcd, 9, 0.0f, 1.1f, false, -1));
//     mesh->ComputeVertexNormals();
//     mesh->PaintUniformColor({0.0, 0.0, 1.0});
//     open3d::visualization::DrawGeometries({mesh});

//     // std::string path = "Assets/Resources/sensor_data.obj";
//     // bool res = open3d::io::WriteTriangleMesh("Assets/Resources/sensor_data.obj", mesh->ComputeVertexNormals());
//     bool res = open3d::io::WriteTriangleMesh("mesh.obj", mesh->ComputeVertexNormals());
    
//     // auto box = open3d::geometry::TriangleMesh::CreateBox(1.0, 1.0, 1.0);
//     // auto set = box->SamplePointsUniformly(20, false);
//     // open3d::io::WritePointCloudOption options = open3d::io::WritePointCloudOption(true, false);
//     // auto pointSet = *set.get();
//     // open3d::io::WritePointCloudToXYZ("pointcloud.xyz", pointSet, options);
//     // box->ComputeVertexNormals();
//     // box->PaintUniformColor({0.0, 0.0, 1.0});
//     // open3d::visualization::DrawGeometries({box});
//     // vizPointCloud();
//     // return 0;
// }
