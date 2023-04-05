#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <stdexcept>
#include <optional>
#include <span>
#include <tuple>

namespace libvtf {

  namespace ImageFormats {
    enum ImageFormat : int32_t {
      DEFAULT = -2,
      UNKNOWN = -1,

      SOURCE_FORMAT_FIRST = 0,

      RGBA8888 = SOURCE_FORMAT_FIRST,
      ABGR8888,
      RGB888,
      BGR888,
      RGB565,
      I8,
      IA88,
      P8,
      A8,
      RGB888_BLUESCREEN,
      BGR888_BLUESCREEN,
      ARGB8888,
      BGRA8888,
      DXT1,
      DXT3,
      DXT5,
      BGRX8888,
      BGR565,
      BGRX5551,
      BGRA4444,
      DXT1_ONEBITALPHA,
      BGRA5551,
      UV88,
      UVWQ8888,
      RGBA16161616F,
      RGBA16161616,
      UVLX8888,
      R32F,
      RGB323232F,
      RGBA32323232F,
      RG1616F,
      RG3232F,
      RGBX8888,

      NV_NULL,

      ATI2N,
      ATI1N,

      RGBA1010102,
      BGRA1010102,
      R16F,

      D16,
      D15S1,
      D32,
      D24S8,
      LINEAR_D24S8,
      D24X8,
      D24X4S4,
      D24FS8,
      D16_SHADOW,
      D24X8_SHADOW,

      LINEAR_BGRX8888,
      LINEAR_RGBA8888,
      LINEAR_ABGR8888,
      LINEAR_ARGB8888,
      LINEAR_BGRA8888,
      LINEAR_RGB888,
      LINEAR_BGR888,
      LINEAR_BGRX5551,
      LINEAR_I8,
      LINEAR_RGBA16161616,
      LINEAR_A8,
      LINEAR_DXT1,
      LINEAR_DXT3,
      LINEAR_DXT5,

      LE_BGRX8888,
      LE_BGRA8888,

      DXT1_RUNTIME,
      DXT5_RUNTIME,

      DXT3_RUNTIME,

      INTZ,

      SOURCE_FORMAT_LAST = INTZ,

      // Extended image formats used by VitaminSource.
      VITAMIN_FORMAT_BEGIN = SOURCE_FORMAT_LAST + 1,
      VITAMIN_BC4 = VITAMIN_FORMAT_BEGIN,
      VITAMIN_BC5,
      VITAMIN_BC6H,
      VITAMIN_BC7,
      VITAMIN_FORMAT_LAST = VITAMIN_BC7,
    };

    struct ImageFormatInfo {
      std::string_view name;

      uint8_t numBytes;
      uint8_t numRedBits;
      uint8_t numGreenBits;
      uint8_t numBlueBits;
      uint8_t numAlphaBits;
      uint8_t numDepthBits;
      uint8_t numStencilBits;
      bool    isCompressed  : 1;
      bool    isFloat       : 1;
      bool    isDepthFormat : 1;
    };

    static constexpr ImageFormatInfo ImageFormatInfos[] = {
      { "UNKNOWN",                    0, 0, 0, 0, 0, 0, 0, false, false, false },
      { "RGBA8888",                   4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "ABGR8888",                   4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "RGB888",                     3, 8, 8, 8, 0, 0, 0, false, false, false },
      { "BGR888",                     3, 8, 8, 8, 0, 0, 0, false, false, false },
      { "RGB565",                     2, 5, 6, 5, 0, 0, 0, false, false, false },
      { "I8",                         1, 0, 0, 0, 0, 0, 0, false, false, false },
      { "IA88",                       2, 0, 0, 0, 8, 0, 0, false, false, false },
      { "P8",                         1, 0, 0, 0, 0, 0, 0, false, false, false },
      { "A8",                         1, 0, 0, 0, 8, 0, 0, false, false, false },
      { "RGB888_BLUESCREEN",          3, 8, 8, 8, 0, 0, 0, false, false, false },
      { "BGR888_BLUESCREEN",          3, 8, 8, 8, 0, 0, 0, false, false, false },
      { "ARGB8888",                   4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "BGRA8888",                   4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "DXT1",                       0, 0, 0, 0, 0, 0, 0, true, false, false },
      { "DXT3",                       0, 0, 0, 0, 8, 0, 0, true, false, false },
      { "DXT5",                       0, 0, 0, 0, 8, 0, 0, true, false, false },
      { "BGRX8888",                   4, 8, 8, 8, 0, 0, 0, false, false, false },
      { "BGR565",                     2, 5, 6, 5, 0, 0, 0, false, false, false },
      { "BGRX5551",                   2, 5, 5, 5, 0, 0, 0, false, false, false },
      { "BGRA4444",                   2, 4, 4, 4, 4, 0, 0, false, false, false },
      { "DXT1_ONEBITALPHA",           0, 0, 0, 0, 0, 0, 0, true, false, false },
      { "BGRA5551",                   2, 5, 5, 5, 1, 0, 0, false, false, false },
      { "UV88",                       2, 8, 8, 0, 0, 0, 0, false, false, false },
      { "UVWQ8888",                   4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "RGBA16161616F",              8, 16, 16, 16, 16, 0, 0, false, true, false },
      { "RGBA16161616",               8, 16, 16, 16, 16, 0, 0, false, false, false },
      { "UVLX8888",                   4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "R32F",                       4, 32, 0, 0, 0, 0, 0, false, true, false },
      { "RGB323232F",                 12, 32, 32, 32, 0, 0, 0, false, true, false },
      { "RGBA32323232F",              16, 32, 32, 32, 32, 0, 0, false, true, false },
      { "RG1616F",                    4, 16, 16, 0, 0, 0, 0, false, true, false },
      { "RG3232F",                    8, 32, 32, 0, 0, 0, 0, false, true, false },
      { "RGBX8888",                   4, 8, 8, 8, 0, 0, 0, false, false, false },

      { "NV_NULL",                    4,  8, 8, 8, 8, 0, 0, false, false, false },

      // Vendor-dependent compressed formats typically used for normal map compression
      { "ATI1N",                      0, 0, 0, 0, 0, 0, 0, true, false, false },
      { "ATI2N",                      0, 0, 0, 0, 0, 0, 0, true, false, false },

      { "RGBA1010102",                4, 10, 10, 10, 2, 0, 0, false, false, false },
      { "BGRA1010102",                4, 10, 10, 10, 2, 0, 0, false, false, false },
      { "R16F",                       2, 16, 0, 0, 0, 0, 0, false, false, false },

      // Vendor-dependent depth formats used for shadow depth mapping
      { "D16",                        2, 0, 0, 0, 0, 16, 0, false, false, true },
      { "D15S1",                      2, 0, 0, 0, 0, 15, 1, false, false, true },
      { "D32",                        4, 0, 0, 0, 0, 32, 0, false, false, true },
      { "D24S8",                      4, 0, 0, 0, 0, 24, 8, false, false, true },
      { "LINEAR_D24S8",               4, 0, 0, 0, 0, 24, 8, false, false, true },
      { "D24X8",                      4, 0, 0, 0, 0, 24, 0, false, false, true },
      { "D24X4S4",                    4, 0, 0, 0, 0, 24, 4, false, false, true },
      { "D24FS8",                     4, 0, 0, 0, 0, 24, 8, false, false, true },
      { "D16_SHADOW",                 2, 0, 0, 0, 0, 16, 0, false, false, true },
      { "D24X8_SHADOW",               4, 0, 0, 0, 0, 24, 0, false, false, true },

      { "LINEAR_BGRX8888",            4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "LINEAR_RGBA8888",            4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "LINEAR_ABGR8888",            4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "LINEAR_ARGB8888",            4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "LINEAR_BGRA8888",            4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "LINEAR_RGB888",              3, 8, 8, 8, 0, 0, 0, false, false, false },
      { "LINEAR_BGR888",              3, 8, 8, 8, 0, 0, 0, false, false, false },
      { "LINEAR_BGRX5551",            2, 5, 5, 5, 0, 0, 0, false, false, false },
      { "LINEAR_I8",                  1, 0, 0, 0, 0, 0, 0, false, false, false },
      { "LINEAR_RGBA16161616",        8, 16, 16, 16, 16, 0, 0, false, false, false },
      { "LINEAR_A8",                  1, 0, 0, 0, 8, 0, 0, false, false, false },
      { "LINEAR_DXT1",                0, 0, 0, 0, 0, 0, 0, true, false, false },
      { "LINEAR_DXT3",                0, 0, 0, 0, 8, 0, 0, true, false, false },
      { "LINEAR_DXT5",                0, 0, 0, 0, 8, 0, 0, true, false, false },

      { "LE_BGRX8888",                4, 8, 8, 8, 8, 0, 0, false, false, false },
      { "LE_BGRA8888",                4, 8, 8, 8, 8, 0, 0, false, false, false },

      { "DXT1_RUNTIME",               0, 0, 0, 0, 0, 0, 0, true, false, false },
      { "DXT5_RUNTIME",               0, 0, 0, 0, 8, 0, 0, true, false, false },
      { "DXT3_RUNTIME",               0, 0, 0, 0, 8, 0, 0, true, false, false },

      // Vendor-dependent depth formats used for resolving
      { "INTZ",                       4, 0, 0, 0, 0, 24, 8, false, false, true},

      // New formats from VitaminSource, unsupported on D3D9
      { "VITAMIN_BC4",                8, 0, 0, 0, 0,  0, 0, true, false, false},
      { "VITAMIN_BC5",                8, 8, 0, 0, 0,  0, 0, true, false, false},
      { "VITAMIN_BC6H",               8, 0, 0, 0, 0,  0, 0, true, true, false},
      { "VITAMIN_BC7",                8, 8, 8, 8, 0,  0, 0, true, false, false},
    };
  }
  using ImageFormat = ImageFormats::ImageFormat;

  constexpr const ImageFormats::ImageFormatInfo* getImageFormatInfo(ImageFormat format) {
    uint32_t index = static_cast<uint32_t>(static_cast<int32_t>(format) + 1);
    if (index < 0 || index >= std::size(ImageFormats::ImageFormatInfos))
      return nullptr;

    return &ImageFormats::ImageFormatInfos[index];
  }

  constexpr std::tuple<uint16_t, uint16_t, uint16_t> adjustImageSizeByMip(uint16_t width, uint16_t height, uint16_t depth, uint8_t mipLevel) {
    return std::tuple<uint16_t, uint16_t, uint16_t> {
      std::max<uint16_t>(width  >> mipLevel, 1u),
      std::max<uint16_t>(height >> mipLevel, 1u),
      std::max<uint16_t>(depth  >> mipLevel, 1u),
    };
  }

  constexpr uint32_t getMemoryRequiredForMip(uint16_t width, uint16_t height, uint16_t depth, ImageFormat imageFormat) {
    const auto *fmt = getImageFormatInfo(imageFormat);
    if (!fmt || !width || !height || !depth)
      return 0;
    if (!fmt->isCompressed)
      return width * height * depth * fmt->numBytes;

    width  = std::max<uint16_t>(width  >> 2, 1u);
    height = std::max<uint16_t>(height >> 2, 1u);

    uint32_t numBlocks = width * height * depth;
    switch (imageFormat) {
      case ImageFormats::DXT1:
      case ImageFormats::DXT1_RUNTIME:
      case ImageFormats::LINEAR_DXT1:
      case ImageFormats::ATI1N:
        return numBlocks * 8;

      case ImageFormats::DXT3:
      case ImageFormats::DXT3_RUNTIME:
      case ImageFormats::DXT5:
      case ImageFormats::DXT5_RUNTIME:
      case ImageFormats::LINEAR_DXT3:
      case ImageFormats::LINEAR_DXT5:
      case ImageFormats::ATI2N:
        return numBlocks * 16;

      default:
        // Unknown type.
        break;
    }

    return 0;
  }

  namespace meta {

    namespace VTFFlags {
      static constexpr uint32_t POINTSAMPLE                = 0x00000001;
      static constexpr uint32_t TRILINEAR                  = 0x00000002;
      static constexpr uint32_t CLAMPS                     = 0x00000004;
      static constexpr uint32_t CLAMPT                     = 0x00000008;
      static constexpr uint32_t ANISOTROPIC                = 0x00000010;
      static constexpr uint32_t HINT_DXT5                  = 0x00000020;
      static constexpr uint32_t PWL_CORRECTED              = 0x00000040;
      static constexpr uint32_t NORMAL                     = 0x00000080;
      static constexpr uint32_t NOMIP                      = 0x00000100;
      static constexpr uint32_t NOLOD                      = 0x00000200;
      static constexpr uint32_t ALL_MIPS                   = 0x00000400;
      static constexpr uint32_t PROCEDURAL                 = 0x00000800;
      static constexpr uint32_t ONEBITALPHA                = 0x00001000;
      static constexpr uint32_t EIGHTBITALPHA              = 0x00002000;
      static constexpr uint32_t ENVMAP                     = 0x00004000;
      static constexpr uint32_t RENDERTARGET               = 0x00008000;
      static constexpr uint32_t DEPTHRENDERTARGET          = 0x00010000;
      static constexpr uint32_t NODEBUGOVERRIDE            = 0x00020000;
      static constexpr uint32_t SINGLECOPY                 = 0x00040000;
      static constexpr uint32_t SRGB                       = 0x00080000;
      static constexpr uint32_t DEFAULT_POOL               = 0x00100000;
      static constexpr uint32_t COMBINED                   = 0x00200000;
      static constexpr uint32_t ASYNC_DOWNLOAD             = 0x00400000;
      static constexpr uint32_t NODEPTHBUFFER              = 0x00800000;
      static constexpr uint32_t SKIP_INITIAL_DOWNLOAD      = 0x01000000;
      static constexpr uint32_t CLAMPU                     = 0x02000000;
      static constexpr uint32_t VERTEXTEXTURE              = 0x04000000;
      static constexpr uint32_t SSBUMP                     = 0x08000000;
      static constexpr uint32_t MOST_MIPS                  = 0x10000000;
      static constexpr uint32_t BORDER                     = 0x20000000;
      static constexpr uint32_t YCOCG                      = 0x40000000;
      static constexpr uint32_t ASYNC_SKIP_INITIAL_LOW_RES = 0x80000000;
    }

#pragma pack(push, 1)

    struct VTFBaseHeader {
      static constexpr std::array<char, 4> ValidSignature = { 'V', 'T', 'F', '\0' };

      std::array<char, 4> signature{};
      std::array<int32_t, 2> version{};
      int32_t headerSize{};
    };

    struct VTFHeader_7_0 : public VTFBaseHeader {
      static constexpr std::array<int32_t, 2> Version = { 7, 0 };

      VTFHeader_7_0() = default;
      VTFHeader_7_0(const VTFBaseHeader& header) : VTFBaseHeader(header) { }

      uint16_t width{};
      uint16_t height{};
      uint32_t flags{};
      uint16_t numFrames{};
      alignas(16) std::array<float, 3> reflectivity{{1.0f, 1.0f, 1.0f}};
      alignas(16) float bumpScale{};
      ImageFormat format{ImageFormat::UNKNOWN};
      uint8_t numMipLevels{};
      ImageFormat lowResImageFormat{ImageFormat::UNKNOWN};
      uint8_t lowResImageWidth{};
      uint8_t lowResImageHeight{};
    };

    // Ensure struct is packed correctly.
    static_assert(offsetof(VTFHeader_7_0, lowResImageFormat) == offsetof(VTFHeader_7_0, numMipLevels) + 1);

    struct VTFHeader_7_1 : public VTFHeader_7_0 {
      static constexpr std::array<int32_t, 2> Version = { 7, 1 };

      VTFHeader_7_1() = default;
      VTFHeader_7_1(const VTFHeader_7_0& header) : VTFHeader_7_0(header) { }
    };

    struct VTFHeader_7_2 : public VTFHeader_7_1 {
      static constexpr std::array<int32_t, 2> Version = { 7, 2 };

      VTFHeader_7_2() = default;
      VTFHeader_7_2(const VTFHeader_7_1& header) : VTFHeader_7_1(header) { }

      uint16_t depth{1};
    };

    struct VTFHeader_7_3 : public VTFHeader_7_2 {
      static constexpr std::array<int32_t, 2> Version = { 7, 3 };

      VTFHeader_7_3() = default;
      VTFHeader_7_3(const VTFHeader_7_2& header) : VTFHeader_7_2(header) { }

      alignas(4) uint32_t numResources{};
    };

    struct VTFHeader_7_4 : public VTFHeader_7_3 {
      static constexpr std::array<int32_t, 2> Version = { 7, 4 };

      VTFHeader_7_4() = default;
      VTFHeader_7_4(const VTFHeader_7_3& header) : VTFHeader_7_3(header) { }
    };

    struct VTFHeader_7_5 : public VTFHeader_7_4 {
      static constexpr std::array<int32_t, 2> Version = { 7, 5 };

      VTFHeader_7_5() = default;
      VTFHeader_7_5(const VTFHeader_7_4& header) : VTFHeader_7_4(header) { }
    };

    struct VTFHeader_X360 : public VTFBaseHeader {
      static constexpr std::array<int32_t, 2> Version = { 0x0360, 8 };

      uint32_t flags{};
      uint16_t width{};
      uint16_t height{};
      uint16_t depth{};
      uint16_t numFrames{};
      uint16_t preloadDataSize{};
      uint8_t mipSkipCount{};
      uint8_t numResources{};
      std::array<float, 3> reflectivity{{1.0f, 1.0f, 1.0f}};
      float bumpScale{};
      ImageFormat imageFormat{ImageFormat::UNKNOWN};
      std::array<uint8_t, 4> lowResImageSample{};
      uint32_t compressedSize{};
    };

    struct VTFHeader_PS3 : public VTFBaseHeader {
      static constexpr std::array<int32_t, 2> Version = { 0x0333, 8 };

      uint32_t flags{};
      uint16_t width{};
      uint16_t height{};
      uint16_t depth{};
      uint16_t numFrames{};
      uint16_t preloadDataSize{};
      uint8_t mipSkipCount{};
      uint8_t numResources{};
      std::array<float, 3> reflectivity{{1.0f, 1.0f, 1.0f}};
      float bumpScale{};
      ImageFormat imageFormat{ImageFormat::UNKNOWN};
      std::array<uint8_t, 4> lowResImageSample{};
      uint32_t compressedSize{};
    };

    struct VTFHeader : public VTFHeader_7_5 {
      VTFHeader() = default;
      VTFHeader(const VTFHeader_7_5& header) : VTFHeader_7_5{ header } { }
      VTFHeader(const VTFHeader_7_4& header) : VTFHeader_7_5{ header } { }
      VTFHeader(const VTFHeader_7_3& header) : VTFHeader_7_5{ VTFHeader_7_4{ header } } { }
      VTFHeader(const VTFHeader_7_2& header) : VTFHeader_7_5{ VTFHeader_7_4{ VTFHeader_7_3{ header } } } { }
      VTFHeader(const VTFHeader_7_1& header) : VTFHeader_7_5{ VTFHeader_7_4{ VTFHeader_7_3{ VTFHeader_7_2{ header } } } } { }
      VTFHeader(const VTFHeader_7_0& header) : VTFHeader_7_5{ VTFHeader_7_4{ VTFHeader_7_3{ VTFHeader_7_2{ VTFHeader_7_1{ header } } } } } { }
    };

    constexpr uint32_t MakeVTFResourceID(uint8_t a, uint8_t b, uint8_t c) {
      return (uint32_t(a)) | (uint32_t(b) << 8u) | (uint32_t(c) << 16u);
    }

    namespace ResourceEntryTypeFlags {
      static constexpr uint32_t HasNoDataChunk = 0x02;
    }

    struct ResourceEntryInfo {
      uint32_t type : 24;
      uint32_t flags : 8;
      uint32_t offset; // Offset in bytes from beginning of file
    };

    struct TextureLegacyImage {
      static constexpr uint32_t ResourceID = MakeVTFResourceID(0x30, 0, 0);
      // Data follows...
    };

    struct TextureLegacyLowResImage {
      static constexpr uint32_t ResourceID = MakeVTFResourceID(0x01, 0, 0);
      // Data follows...
    };

    struct TextureSheet {
      static constexpr uint32_t ResourceID = MakeVTFResourceID(0x10, 0, 0);
      // Data follows...
    };

    struct TextureLODControlSettings {
      static constexpr uint32_t ResourceID = MakeVTFResourceID('L', 'O', 'D');

      std::array<uint8_t, 2> resolutionClamp;
      std::array<uint8_t, 2> resolutionClamp360;
    };

    struct TextureSettingsEx {
      static constexpr uint32_t ResourceID = MakeVTFResourceID('T', 'S', '0');

      std::array<uint8_t, 4> flags;
    };

    struct TextureCRC32 {
      static constexpr uint32_t ResourceID = MakeVTFResourceID('C', 'R', 'C');

      uint32_t crc32;
    };

#pragma pack(pop)
  }

  class VTFData {
  public:
    VTFData(std::span<const uint8_t> buffer)
      : m_buffer{ buffer }
      , m_header{ readHeader(buffer) } {
    }

    const meta::VTFHeader& getHeader() const { return m_header; }

    const uint8_t* imageData() const {
      if (m_header.numResources) {
        const meta::TextureLegacyImage* image = getResourcePointer<meta::TextureLegacyImage>();
        return reinterpret_cast<const uint8_t*>(image);
      }

      // Legacy path (7.0 - 7.2)
      uint32_t lowResImageSize = 0;
      if (m_header.lowResImageWidth != 0 && m_header.lowResImageHeight != 0) {
        lowResImageSize = getMemoryRequiredForMip(
          m_header.lowResImageWidth, m_header.lowResImageHeight, 1u, m_header.lowResImageFormat);
        printf("a: %d %d %d -> %d + %d\n", int(m_header.lowResImageWidth), int(m_header.lowResImageHeight), int(m_header.lowResImageFormat), int(m_header.headerSize), int(lowResImageSize));
      }

      return &m_buffer[m_header.headerSize + lowResImageSize];
    }

    std::span<const uint8_t> imageData(uint16_t frame, uint16_t face, uint8_t mipLevel) const {
      const uint8_t* data = imageData();
      if (!data)
        return std::span<const uint8_t>{};

      const uint32_t offset = imageOffset(frame, face, mipLevel);
      const uint32_t size   = imageMipSize(mipLevel);
      return std::span<const uint8_t>{data + offset, size};
    }

    std::span<const uint8_t> lowResImageData() const {
      if (m_header.lowResImageWidth == 0 || m_header.lowResImageHeight == 0)
        return std::span<const uint8_t>();

      const uint32_t size = getMemoryRequiredForMip(
        m_header.lowResImageWidth, m_header.lowResImageHeight, 1u, m_header.lowResImageFormat);

      if (m_header.numResources) {
        const meta::TextureLegacyLowResImage* image = getResourcePointer<meta::TextureLegacyLowResImage>();
        return std::span<const uint8_t>{reinterpret_cast<const uint8_t*>(image), size};
      }

      return std::span{&m_buffer[m_header.headerSize], size};
    }

    std::optional<uint32_t> crc32() const {
      const meta::TextureCRC32* crc32Resource = getResourcePointer<meta::TextureCRC32>();
      if (!crc32Resource)
        return std::nullopt;

      return crc32Resource->crc32;
    }

    const meta::TextureLODControlSettings* lodControlSettings() const {
      return getResourcePointer<meta::TextureLODControlSettings>();
    }

    const meta::TextureSettingsEx* settingsEx() const {
      return getResourcePointer<meta::TextureSettingsEx>();
    }

    uint32_t faceCount() const {
      return (!!(m_header.flags & meta::VTFFlags::ENVMAP)) ? 6u : 1u;
    }

  private:

    uint32_t imageMipSize(uint8_t mipLevel) const {
      auto [width, height, depth] = adjustImageSizeByMip(m_header.width, m_header.height, m_header.depth, mipLevel);

      return getMemoryRequiredForMip(width, height, depth, m_header.format);
    }

    uint32_t imageMipOffset(uint8_t mipLevel) const {
      uint32_t offset = 0;
      for (int8_t i = int8_t(m_header.numMipLevels) - 1; i > int8_t(mipLevel); i--)
        offset += imageMipSize(i) * m_header.numFrames * faceCount();
      return offset;
    }

    uint32_t totalImageFaceSize() const {
      uint32_t size = 0;
      for (uint8_t i = 0; i < m_header.numMipLevels; i++) {
        auto [width, height, depth] = adjustImageSizeByMip(m_header.width, m_header.height, m_header.depth, i);
        size += getMemoryRequiredForMip(width, height, depth, m_header.format);
      }
      return size;
    }

    uint32_t imageTotalSize() const {
      return m_header.numFrames * this->faceCount() * totalImageFaceSize();
    }

    uint32_t imageOffset(uint16_t frame, uint16_t face, uint8_t mipLevel) const {
      const uint32_t faceSize  = imageMipSize(mipLevel);
      const uint32_t frameSize = faceCount() * faceSize;

      const uint32_t frameOffset = frame * frameSize;
      const uint32_t faceOffset  = face * faceSize;
      const uint32_t mipOffset   = imageMipOffset(mipLevel);

      return faceOffset + frameOffset + mipOffset;
    }

    template <typename T>
    const T* getResourcePointer() const {
      const meta::ResourceEntryInfo* resources = this->resourceEntries();
      for (uint32_t i = 0; i < m_header.numResources; i++) {
        if (resources[i].type != T::ResourceID)
          continue;

        if (resources[i].flags & meta::ResourceEntryTypeFlags::HasNoDataChunk) {
          return reinterpret_cast<const T*>(&resources[i].offset);
        } else {
          return reinterpret_cast<const T*>(&m_buffer[resources[i].offset]);
        }
      }

      return nullptr;
    }

    const meta::ResourceEntryInfo* resourceEntries() const {
      if (!m_header.numResources)
        return nullptr;
      return reinterpret_cast<const meta::ResourceEntryInfo*>(&m_buffer[m_header.headerSize - m_header.numResources * sizeof(meta::ResourceEntryInfo)]);
    }

    template <typename T>
    static const T* spanGet(std::span<const uint8_t> data) {
      if (data.size() < sizeof(T))
        throw std::runtime_error("Cannot read type from data span (EOF)");

      return reinterpret_cast<const T*>(data.data());
    }

    static meta::VTFHeader readHeader(std::span<const uint8_t> data) {
      const meta::VTFBaseHeader* baseHeader =
        spanGet<meta::VTFBaseHeader>(data);

      if (baseHeader->version == meta::VTFHeader_7_5::Version)
        return meta::VTFHeader{ *spanGet<meta::VTFHeader_7_5>(data) };
      else if (baseHeader->version == meta::VTFHeader_7_4::Version)
        return meta::VTFHeader{ *spanGet<meta::VTFHeader_7_4>(data) };
      else if (baseHeader->version == meta::VTFHeader_7_3::Version)
        return meta::VTFHeader{ *spanGet<meta::VTFHeader_7_3>(data) };
      else if (baseHeader->version == meta::VTFHeader_7_2::Version)
        return meta::VTFHeader{ *spanGet<meta::VTFHeader_7_2>(data) };
      else if (baseHeader->version == meta::VTFHeader_7_1::Version)
        return meta::VTFHeader{ *spanGet<meta::VTFHeader_7_1>(data) };
      else if (baseHeader->version == meta::VTFHeader_7_0::Version)
        return meta::VTFHeader{ *spanGet<meta::VTFHeader_7_0>(data) };
      else
        throw std::runtime_error("Unhandled VTF header version.");
    }

    std::span<const uint8_t> m_buffer;
    meta::VTFHeader          m_header;
  };

}
