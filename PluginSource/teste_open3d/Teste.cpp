#include <string>
#include <iostream>
#include "open3d/Open3D.h"

#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

void pointCloud();

int main(int argc, char *argv[]) {    
    pointCloud();
    return 0;
}

// ------------------------------------------------------------------------
// Plugin itself


// Link following functions C-style (required for plugins)
extern "C"
{
    EXPORT_API int CreateSphere() {
        auto sphere = open3d::geometry::TriangleMesh::CreateSphere(1.0);
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
} // end of export C block

void pointCloud()
{
    auto pointSet = open3d::geometry::PointCloud();
    open3d::io::ReadPointCloudOption options = open3d::io::ReadPointCloudOption("ply", false, false, false);
    // open3d::io::ReadPointCloudOption options = open3d::io::ReadPointCloudOption("xyz", false, false, false);
    open3d::io::ReadPointCloudFromXYZ("sensor_data.xyz", pointSet, options);
    // open3d::io::ReadPointCloudFromPLY("room.ply", pointSet, options);
    auto downpcd = pointSet.VoxelDownSample(0.03);
    auto search = open3d::geometry::KDTreeSearchParamHybrid(0.1, 30);
    auto dist = downpcd->ComputeNearestNeighborDistance();
    auto avg_dist = (dist[0]+dist[1])/2;
    double radius = 3*avg_dist;
    double radius2 = radius*2;
    // std::vector<double> vec = {radius, radius2};
    downpcd->EstimateNormals(search);
    auto mesh = open3d::geometry::TriangleMesh::CreateFromPointCloudBallPivoting(*downpcd, {radius, radius2});
    auto filter = open3d::geometry::MeshBase::FilterScope::All;
    mesh->FilterSmoothLaplacian(10, 0.5, filter);
    // auto mesh = std::get<0>(tuple);
    // mesh->ComputeVertexNormals();
    mesh->PaintUniformColor({0.0, 0.0, 1.0});
    open3d::visualization::DrawGeometries({mesh});
    
    // auto box = open3d::geometry::TriangleMesh::CreateBox(1.0, 1.0, 1.0);
    // auto set = box->SamplePointsUniformly(20, false);
    // open3d::io::WritePointCloudOption options = open3d::io::WritePointCloudOption(true, false);
    // auto pointSet = *set.get();
    // open3d::io::WritePointCloudToXYZ("pointcloud.xyz", pointSet, options);
    // box->ComputeVertexNormals();
    // box->PaintUniformColor({0.0, 0.0, 1.0});
    // open3d::visualization::DrawGeometries({box});

}