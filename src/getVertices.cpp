
#include "getVertices.h"

struct ImageInfo {
    unsigned long width, height;
    int depth;
    double widthHeightRatio, minVal, maxVal;
    void print() {
        printf("width: %lu\theight: %lu\tdepth: %d\tratio: %f\tminVal: %f\tmaxVal: %f\n", width, height, depth, widthHeightRatio, minVal, maxVal);
    }
};

Uint16* getVertices()
{
    char fileName[]{"/home/dstanto2/Documents/Data/NeurohackingCourse/BRAINIX/DICOM/FLAIR/IM-0001-0001.dcm"};

    DicomImage *image = new DicomImage(fileName);

    struct ImageInfo imgInfo = { image->getWidth(), image->getHeight(), image->getDepth(), image->getWidthHeightRatio(), 0.0, 0.0 };
    image->getMinMaxValues(imgInfo.minVal, imgInfo.maxVal);

//    imgInfo.print();

    // according to this:
    // https://stackoverflow.com/questions/38258460/dcmtk-c-how-to-get-data-pixels-from-dicom-files
    // returns data with full grayscale range
    const DiPixel* pixelData = image->getInterData();

    const Uint16* colBuffer = (Uint16*) pixelData->getData();

    Uint16* buffer = new Uint16[imgInfo.height * imgInfo.width * 3];

    std::cout << "height: " << imgInfo.height << "\n";
    std::cout << "width: " << imgInfo.width << "\n";
    std::cout << "minVal: " << imgInfo.minVal << "\n";
    std::cout << "maxVal: " << imgInfo.maxVal << "\n";


    for (int i = 0, col = 0, row = 0; i < imgInfo.height * imgInfo.width; ++i) {
//    for (int i = 0, col = 0, row = 0; i < imgInfo.height * imgInfo.width; ++i) {
//        buffer[i * 3] = col / (float) (imgInfo.height * imgInfo.width);
//        buffer[i * 3 + 1] = row / (float) (imgInfo.height * imgInfo.width);
//        buffer[i * 3 + 2] = (float) colBuffer[i] / (float) 65535;
//        buffer[i * 3] = col;
//        buffer[i * 3 + 1] = row;
        buffer[i] = colBuffer[(imgInfo.height * imgInfo.width) - i - 1];

//        if (col == imgInfo.width)
//            col = 0, ++row;
//        else
//            ++col;
    }
//    for (int i = 0; i < imgInfo.height * imgInfo.width * 3; ++i) {
//            std::cout << buffer[i] << "\n";
//    }

//
    unsigned long c = pixelData->getCount();
    unsigned long ic = pixelData->getInputCount();
    EP_Representation rep = pixelData->getRepresentation();
    int planes = pixelData->getPlanes();

    if (rep == EPR_Uint16)
        std::cout << "uint16\n";
    else if (rep == EPR_Sint16)
        std::cout << "sint16\n";
    else {
        std::cout << "different rep\n";
    }

    printf("count: %lu\n", c);
    printf("input count: %lu\n", ic);
    printf("planes: %d\n", planes);
    // get rows
    // get columns
    //

//    if (image->getStatus() == EIS_Normal) {
//        if (image->isMonochrome()) {
//            std::cout << "hooray\n";
//        }
//    }
    delete colBuffer;
    return buffer;
}
