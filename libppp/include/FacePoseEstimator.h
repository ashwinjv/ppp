#pragma once
#include "IFacePoseEstimator.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <vector>

namespace ppp {
class FacePoseEstimator final : public IFacePoseEstimator
{
public:
    FacePoseEstimator();

    cv::Vec3d estimatePose(const LandMarksSPtr & landMarks, double focalLength, cv::Point2d focalCenter) override;
    void projectPoint(const std::vector<cv::Point3d> & point3ds, std::vector<cv::Point2d> & point2ds) const;

private:
    std::vector<cv::Point3d> m_modelPoints;

    cv::Mat m_rotationVector; // Rotation in axis-angle form
    cv::Mat m_translationVector;
    cv::Mat m_cameraMatrix;
};
} // namespace ppp
