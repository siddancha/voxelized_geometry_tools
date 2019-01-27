#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace voxelized_geometry_tools
{
namespace pointcloud_voxelization
{
namespace cuda_helpers
{
/*
bool IsAvailable();

float* PreparePointCloud(const int32_t num_points, const float* points);

int32_t* PrepareTrackingGrid(const int64_t num_cells);

void RaycastPoints(
    const float* device_points_ptr, const int32_t num_points,
    const float* const pointcloud_origin_transform,
    const float* const inverse_grid_origin_transform,
    const float inverse_step_size, const float inverse_cell_size,
    const int32_t num_x_cells, const int32_t num_y_cells,
    const int32_t num_z_cells, int32_t* const device_tracking_grid_ptr);

float* PrepareFilterGrid(
    const int64_t num_cells, const void* host_data_ptr);

void FilterTrackingGrids(
    const int64_t num_cells, const int32_t num_device_tracking_grids,
    int32_t* const* device_tracking_grid_ptrs,
    float* const device_filter_grid_ptr, const float percent_seen_free,
    const int32_t outlier_points_threshold,
    const int32_t num_cameras_seen_free);

void RetrieveTrackingGrid(
    const int64_t num_cells, const int32_t* const device_tracking_grid_ptr,
    void* host_data_ptr);

void RetrieveFilteredGrid(
    const int64_t num_cells, const float* const device_filter_grid_ptr,
    void* host_data_ptr);

void CleanupDeviceMemory(
    const int32_t num_device_pointclouds, float* const* device_pointcloud_ptrs,
    const int32_t num_device_tracking_grids,
    int32_t* const* device_tracking_grid_ptrs, float* device_filter_grid_ptr);

void SetCudaDevice(const int32_t device);
*/

class CudaVoxelizationHelperInterface
{
public:
  virtual ~CudaVoxelizationHelperInterface() {}

  virtual bool IsAvailable() const = 0;

  virtual std::vector<int64_t> PrepareTrackingGrids(
      const int64_t num_cells, const int32_t num_grids) = 0;

  virtual void RaycastPoints(
      const std::vector<float>& raw_points,
      const float* const pointcloud_origin_transform,
      const float* const inverse_grid_origin_transform,
      const float inverse_step_size, const float inverse_cell_size,
      const int32_t num_x_cells, const int32_t num_y_cells,
      const int32_t num_z_cells,
      const int64_t tracking_grid_starting_offset) = 0;

  virtual void PrepareFilterGrid(
       const int64_t num_cells, const void* host_data_ptr) = 0;

  virtual void FilterTrackingGrids(
       const int64_t num_cells, const int32_t num_grids,
       const float percent_seen_free, const int32_t outlier_points_threshold,
       const int32_t num_cameras_seen_free) = 0;

  virtual void RetrieveTrackingGrid(
      const int64_t num_cells, const int64_t tracking_grid_starting_index,
      void* host_data_ptr) = 0;

  virtual void RetrieveFilteredGrid(
      const int64_t num_cells, void* host_data_ptr) = 0;

  virtual void CleanupAllocatedMemory() = 0;
};

CudaVoxelizationHelperInterface* MakeHelperInterface(
    const std::map<std::string, int32_t>& options);
}  // namespace cuda_helpers
}  // namespace pointcloud_voxelization
}  // namespace voxelized_geometry_tools
