#include "../libvtf++.hpp"

#include <iostream>
#include <fstream>
#include <cassert>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: vtf_dumper <path to vtf>" << std::endl;  
    return 1;
  }

  std::ifstream file(argv[1], std::ios::in | std::ios::binary);
  if (!file || file.bad()) {
    std::cerr << "Could not open file." << std::endl;
    return 1;
  }

  std::vector<uint8_t> buffer;
  // Resize buffer to file size
  file.seekg(0, std::ios::end);
  auto size = file.tellg();
  buffer.resize(size);
  file.seekg(0, std::ios::beg);

  // Read file into buffer
  file.read((char*)&buffer[0], size);

  libvtf::VTFData data(buffer);

  const auto& header = data.getHeader();

  std::cout << "version: " << header.version[0] << "." << header.version[1] << std::endl;
  std::cout << "width: " << header.width << std::endl;
  std::cout << "height: " << header.height << std::endl;
  std::cout << "flags: " << header.flags << std::endl;
  std::cout << "numFrames: " << header.numFrames << std::endl;
  std::cout << "reflectivity: " << header.reflectivity[0] << " " << header.reflectivity[1] << " " << header.reflectivity[2] << std::endl;
  std::cout << "bumpScale: " << header.bumpScale << std::endl;
  std::cout << "format: " << libvtf::getImageFormatInfo(header.format)->name << std::endl;
  std::cout << "numMipLevels: " << (uint32_t)header.numMipLevels << std::endl;
  std::cout << "lowResImageFormat: " << libvtf::getImageFormatInfo(header.lowResImageFormat)->name << std::endl;
  std::cout << "lowResImageWidth: " << (uint32_t)header.lowResImageWidth << std::endl;
  std::cout << "lowResImageHeight: " << (uint32_t)header.lowResImageHeight << std::endl;
  std::cout << "depth: " << (uint32_t)header.depth << std::endl;
  std::cout << "numResources: " << (uint32_t)header.numResources << std::endl;
  auto image_data = data.imageData(0, 0, 0);
  assert(image_data.size() > 0);

  return 0;
}
