#include <gtest/gtest.h>
#include <opencv2/imgcodecs.hpp>

#include "PhotoPrintMaker.h"
#include "PhotoStandard.h"
#include "PrintDefinition.h"

#include "TestHelpers.h"
#include "Utilities.h"

using namespace std;

namespace ppp {
class PhotoPrintMakerTests : public testing::Test
{
protected:
    PhotoPrintMakerSPtr m_pPhotoPrintMaker = make_shared<PhotoPrintMaker>();
};

void verifyEqualImage(const std::string & expectedImageFilePath, const cv::Mat & actualImage)
{

    const auto expectedImage = cv::imread(expectedImageFilePath);
    const auto numDistinctPixels = countNonZero(sum(cv::abs(expectedImage - actualImage)));
    EXPECT_LE(numDistinctPixels, 3) << "Actual image differs to image in file " << expectedImageFilePath;
}

TEST_F(PhotoPrintMakerTests, TestCroppingWorks)
{
    const PhotoStandard passportStandard(35.0, 45.0, 34.0, 0.0, 0.0, 300, "mm");
    const PrintDefinition printDefinition(6, 4, 300, "inch");

    const auto & imageFileName = resolvePath("research/sample_test_images/000.jpg");
    const cv::Point2d crownPos(941, 999);
    const cv::Point2d chinPos(927, 1675);

    const auto image = cv::imread(imageFileName);

    // Crop the photo to the right dimensions
    const auto croppedImage = m_pPhotoPrintMaker->cropPicture(image, crownPos, chinPos, passportStandard);
    benchmarkValidate(croppedImage, "_croppedPhoto");

    // Draw tiles into the printing canvas
    const auto tiledPhoto = m_pPhotoPrintMaker->tileCroppedPhoto(printDefinition, passportStandard, croppedImage);
    benchmarkValidate(tiledPhoto, "_tiledPhoto");
}

TEST_F(PhotoPrintMakerTests, TestCroppingWorksWithPadding)
{
    const PhotoStandard passportStandard(2, 2, 1.1875, 0.0, 0.0, 300, "inch");
    const PrintDefinition printDefinition(6, 4, 300, "inch", 0, 1.5 / 25.4);

    const auto & imageFileName = resolvePath("research/my_database/20191021_155155.jpg");
    const cv::Point2d crownPos(1155, 310);
    const cv::Point2d chinPos(1173, 1188);

    const auto image = cv::imread(imageFileName);

    // Crop the photo to the right dimensions
    const auto croppedImage = m_pPhotoPrintMaker->cropPicture(image, crownPos, chinPos, passportStandard);
    const auto printPhoto = m_pPhotoPrintMaker->tileCroppedPhoto(printDefinition, passportStandard, croppedImage);
    benchmarkValidate(printPhoto);
}

TEST_F(PhotoPrintMakerTests, DigitalSize)
{
    const PhotoStandard passportStandard(2, 2, 1.1875, 0.0, 0.0, 300, "inch");
    const PrintDefinition printDefinition(0, 0, 0, "inch", 0, 0);

    const auto & imageFileName = resolvePath("research/my_database/20191021_155155.jpg");
    const cv::Point2d crownPos(1155, 310);
    const cv::Point2d chinPos(1173, 1188);

    const auto image = cv::imread(imageFileName);
    const auto croppedImage = m_pPhotoPrintMaker->cropPicture(image, crownPos, chinPos, passportStandard);
    const auto printPhoto = m_pPhotoPrintMaker->tileCroppedPhoto(printDefinition, passportStandard, croppedImage);
    benchmarkValidate(printPhoto);
}

} // namespace ppp
