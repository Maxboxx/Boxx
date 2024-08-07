#ifndef _BOXX_PIXEL_HEADER
#define _BOXX_PIXEL_HEADER

#include "Types.h"
#include "Array.h"
#include "Color.h"
#include "String.h"
#include "File.h"
#include "Math.h"
#include "Set.h"
#include "Pair.h"
#include "Error.h"
#include "Map.h"
#include "Optional.h"
#include "Collection.h"
#include "Tuple.h"

///[Settings] block: indent

///[Namespace] Boxx
namespace Boxx {
	///[Heading] Pixel

	///[Title] Pixel
	/// Class for loading and writing pixel files.
	///[para] Documentation for the pixel format can be found here: https://maxboxx.com/pixel
	///[Block] Pixel
	class Pixel {
	public:
		///[Heading] Constructors

		Pixel();

		/// Creates an empty pixel image with the specified size.
		Pixel(const UShort width, const UShort height);

		/// Creates a pixel image with the specified size and the specified pixel colors.
		///[Arg] pixels: An array containing the color for all pixels in the image.
		///[Error] PixelSizeError: Thrown if the size of {pixels} is not {width * height}.
		Pixel(const UShort width, const UShort height, const Array<ColorRGBA>& pixels);

		Pixel(const Pixel& pixel);
		Pixel(Pixel&& pixel) noexcept;
		~Pixel();

		///[Heading] Methods

		/// Gets the width of the image.
		UInt Width() const;

		/// Gets the height of the image.
		UInt Height() const;

		/// Gets the color from a specific pixel.
		ColorRGBA GetColor(const UShort x, const UShort y) const;

		/// Sets the color of a specific pixel.
		void SetColor(const UShort x, const UShort y, const ColorRGBA& color);

		/// Gets an array of all pixel colors in the image.
		Array<ColorRGBA> GetPixels() const;

		/// Sets the array of all pixel colors in the image.
		///[Error] PixelSizeError: Thrown if the size of {pixels} is not {width * height}.
		void SetPixels(const Array<ColorRGBA>& pixels);

		///[Heading] Static functions

		/// Loads a pixel image from a file.
		///[Error] PixelLoadError: Thrown if loading fails.
		///[Error] FileNotFoundError: Thrown if the file was not found.
		static Pixel LoadFromFile(const String& filename);

		enum class Format : UByte;

		/// Writes a pixel image to a file.
		///[Error] PixelEncodeError: Thrown if the encoding of the image fails.
		///[Error] FileOpenError: Thrown if the file could not be opened.
		static void WriteToFile(const String& filename, const Pixel& pixel);

		/// Writes a pixel image to a file.
		///[Error] PixelEncodeError: Thrown if the encoding of the image fails.
		///[Error] FileOpenError: Thrown if the file could not be opened.
		static void WriteToFile(const String& filename, const Pixel& pixel, const Format format);

		void operator=(const Pixel& pixel);
		void operator=(Pixel&& pixel) noexcept;

		///[Heading] Enums

		///[Title] Format
		/// Bitflags for the pixel file format.
		///[Block] Format
		enum class Format : UByte {
			/// No format.
			None = 0,

			/// The repeat format.
			Repeat = 1,

			/// The double bytes format.
			DoubleBytes = 2,

			/// The double size format.
			DoubleSize = 4,

			/// The background format.
			Background = 8,

			/// The alpha format.
			Alpha = 16,

			/// The transpose format.
			Transpose = 32
		};

	private:
		UShort width, height;
		Array<ColorRGBA> pixels;

		static void WriteToFile(const String& filename, const Pixel& pixel, const Optional<Format>& format);

		static void DecodePixels(Pixel& pixel, Buffer& data, const Format format, const UShort colorCount);
		static void DecodeDefault(Pixel& pixel, Buffer& data, const Format format, const Array<ColorRGBA>& colors);
		static void DecodeRepeat(Pixel& pixel, Buffer& data, const Format format, const Array<ColorRGBA>& colors);
		static void DecodeBackground(Pixel& pixel, Buffer& data, const Format format, const Array<ColorRGBA>& colors);

		static void EncodePixels(const Pixel& pixel, const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format);
		static void EncodeDefault(const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format);
		static void EncodeRepeat(const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format);
		static void EncodeBackgroundDefault(const Pixel& pixel, const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format, const UShort backID);
		static void EncodeBackgroundRepeat(const Pixel& pixel, const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format, const UShort backID);
		static void EncodeBackground(const Pixel& pixel, const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format);
		static void EncodeHeader(const List<ColorRGBA>& colors, const Pixel& pixel, Buffer& data, const Format format);

		static UByte GetBitCount(const UShort number);
		static UByte GetBitCount2(const UShort number);
		static Set<Format> GetAllFormats();

		Tuple<List<ColorRGBA>, Array<UShort>> GetColorIDs() const;
	};

	BOXX_ENUM_FLAGS(Pixel::Format);

	///[Title] PixelError
	/// Base class for all pixel errors.
	///[Block] PixelError: Error
	class PixelError : public Error {
	public:
		PixelError() : Error() {}
		PixelError(const char* const msg) : Error(msg) {}

		virtual String Name() const override {
			return "PixelError";
		}
	};

	///[Title] PixelLoadError
	/// Used if loading fails.
	///[Block] PixelLoadError: PixelError
	class PixelLoadError : public PixelError {
	public:
		PixelLoadError() : PixelError() {}
		PixelLoadError(const char* const msg) : PixelError(msg) {}

		virtual String Name() const override {
			return "PixelLoadError";
		}
	};

	///[Title] PixelEncodeError
	/// Used if encoding fails.
	///[Block] PixelEncodeError: PixelError
	class PixelEncodeError : public PixelError {
	public:
		PixelEncodeError() : PixelError() {}
		PixelEncodeError(const char* const msg) : PixelError(msg) {}

		virtual String Name() const override {
			return "PixelEncodeError";
		}
	};

	///[Title] PixelSizeError
	/// Used if a mismatch in size occurs.
	///[Block] PixelSizeError: PixelError
	class PixelSizeError : public PixelError {
	public:
		PixelSizeError() : PixelError() {}
		PixelSizeError(const char* const msg) : PixelError(msg) {}

		virtual String Name() const override {
			return "PixelSizeError";
		}
	};

	inline Pixel::Pixel() {
		width = 0;
		height = 0;
	}

	inline Pixel::Pixel(const UShort width, const UShort height) {
		this->width = width;
		this->height = height;
		pixels = Array<ColorRGBA>((UInt)width * (UInt)height);
	}

	inline Pixel::Pixel(const UShort width, const UShort height, const Array<ColorRGBA>& pixels) {
		if ((UInt)width * (UInt)height != pixels.Length()) throw PixelSizeError("The array size does not match the image size");

		this->width = width;
		this->height = height;
		this->pixels = pixels;
	}

	inline Pixel::Pixel(const Pixel& pixel) {
		width = pixel.width;
		height = pixel.height;
		pixels = pixel.pixels;
	}

	inline Pixel::Pixel(Pixel&& pixel) noexcept {
		width = pixel.width;
		height = pixel.height;
		pixels = std::move(pixel.pixels);
	}

	inline Pixel::~Pixel() {
		
	}

	inline UInt Pixel::Width() const {
		return width;
	}

	inline UInt Pixel::Height() const {
		return height;
	}

	inline ColorRGBA Pixel::GetColor(const UShort x, const UShort y) const {
		return pixels[(UInt)x + (UInt)y * (UInt)width];
	}

	inline void Pixel::SetColor(const UShort x, const UShort y, const ColorRGBA& color) {
		pixels[(UInt)x + (UInt)y * (UInt)width] = color;
	}

	inline Array<ColorRGBA> Pixel::GetPixels() const {
		return pixels;
	}

	inline void Pixel::SetPixels(const Array<ColorRGBA>& pixels) {
		if ((UInt)width * (UInt)height != pixels.Length()) throw PixelSizeError("The array size does not match the image size");
		this->pixels = pixels;
	}

	inline Pixel Pixel::LoadFromFile(const String& filename) {
		FileReader file;
		
		try {
			file = FileReader(filename, FileMode::Binary);
		}
		catch (FileNotFoundError e) {
			throw e;
		}

		Buffer data = file.ReadToBuffer();
		file.Close();

		try {
			String signature = data.ReadString(3);

			if (signature != "pxl") {
				throw PixelLoadError("Invalid file signature");
			}

			Format format = data.Read<Format>(Endian::Big);
			bool doubleBytes = (format & Format::DoubleBytes) != Format::None;
			bool doubleSize = (format & Format::DoubleSize) != Format::None;

			if ((UByte)format > (UByte)Format::Transpose * 2)
				throw PixelLoadError("Format not supported");
		
			UShort width, height, colorCount;

			if (doubleSize) {
				width  = data.Read<UShort>(Endian::Big);
				height = data.Read<UShort>(Endian::Big);
			}
			else {
				width  = data.Read<UByte>(Endian::Big);
				height = data.Read<UByte>(Endian::Big);
			}

			if (doubleBytes) {
				colorCount = data.Read<UShort>(Endian::Big);
			}
			else {
				colorCount = data.Read<UByte>(Endian::Big);
			}

			Pixel pixel = (format & Format::Transpose) != Format::None ? Pixel(height, width) : Pixel(width, height);

			DecodePixels(pixel, data, format, colorCount + 1);

			if ((format & Format::Transpose) != Format::None) {
				Pixel transpose = Pixel(width, height);

				for (UInt x = 0; x < pixel.width; x++)
					for (UInt y = 0; y < pixel.height; y++)
						transpose.pixels[y + x * pixel.height] = pixel.pixels[x + y * pixel.width];

				return transpose;
			}

			return pixel;
		}
		catch (BufferReadError e) {
			throw PixelLoadError("Incomplete pixel file");
		}

		return Pixel();
	}

	inline void Pixel::DecodePixels(Pixel& pixel, Buffer& data, const Format format, const UShort colorCount) {
		Array<ColorRGBA> colors = Array<ColorRGBA>(colorCount);
		colors[0] = ColorRGBA(0, 0, 0, 0);
		bool alphaFormat = (format & Format::Alpha) != Format::None;

		for (UShort i = 1; i < colorCount; i++) {
			UByte r = data.Read<UByte>(Endian::Big);
			UByte g = data.Read<UByte>(Endian::Big);
			UByte b = data.Read<UByte>(Endian::Big);

			if (alphaFormat) {
				colors[i] = ColorRGBA(r, g, b, data.Read<UByte>(Endian::Big));
			}
			else {
				colors[i] = ColorRGBA(r, g, b);
			}
		}

		if ((format & Format::Background) != Format::None) {
			DecodeBackground(pixel, data, format, colors);
		}
		else if ((format & Format::Repeat) != Format::None) {
			DecodeRepeat(pixel, data, format, colors);
		}
		else {
			DecodeDefault(pixel, data, format, colors);
		}
	}

	inline void Pixel::DecodeDefault(Pixel& pixel, Buffer& data, const Format format, const Array<ColorRGBA>& colors) {
		bool doubleBytes = (format & Format::DoubleBytes) != Format::None;

		UByte colorBits = GetBitCount2(colors.Length());
		UByte segments = (doubleBytes ? 16 : 8) / colorBits;

		UShort colorMask = (doubleBytes ? Math::UShortMax() : Math::UByteMax()) >> ((doubleBytes ? 16 : 8) - colorBits);

		UInt pixels = (UInt)pixel.width * (UInt)pixel.height;
		UInt p = 0;

		while (p < pixels) {
			UShort color = doubleBytes ? data.Read<UShort>(Endian::Big) : data.Read<UByte>(Endian::Big);

			for (UShort i = 0; i < segments && p < pixels; i++) {
				UShort colorId = color & colorMask;
				color = color >> colorBits;
				pixel.pixels[p] = colors[colorId];
				p++;
			}
		}
	}

	inline void Pixel::DecodeRepeat(Pixel& pixel, Buffer& data, const Format format, const Array<ColorRGBA>& colors) {
		bool doubleBytes = (format & Format::DoubleBytes) != Format::None;

		UByte colorBits = GetBitCount(colors.Length());
		UByte repeatBits = (doubleBytes ? 16 : 8) - colorBits;

		UShort colorMask = (doubleBytes ? Math::UShortMax() : Math::UByteMax()) >> repeatBits;

		UInt pixels = (UInt)pixel.width * (UInt)pixel.height;
		UInt p = 0;

		while (p < pixels) {
			UShort color = doubleBytes ? data.Read<UShort>(Endian::Big) : data.Read<UByte>(Endian::Big);
			UShort colorId = color & colorMask;
			UInt repeatCount = ((UInt)color >> colorBits) + 1;

			ColorRGBA rgba = colors[colorId];

			for (UInt i = 0; i < repeatCount && p < pixels; i++) {
				pixel.pixels[p] = rgba;
				p++;
			}
		}
	}

	inline void Pixel::DecodeBackground(Pixel& pixel, Buffer& data, const Format format, const Array<ColorRGBA>& colors) {
		bool doubleBytes = (format & Format::DoubleBytes) != Format::None;
		bool doubleSize = (format & Format::DoubleSize) != Format::None;
		bool repeat = (format & Format::Repeat) != Format::None;
		bool transpose = (format & Format::Transpose) != Format::None;

		UByte colorBits = 0, repeatBits = 0, segments = 0;
		UShort colorMask = 0;

		if (repeat) {
			colorBits = GetBitCount(colors.Length());
			repeatBits = (doubleBytes ? 16 : 8) - colorBits;
			colorMask = (doubleBytes ? Math::UShortMax() : Math::UByteMax()) >> repeatBits;
		}
		else {
			colorBits = GetBitCount2(colors.Length());
			segments = (doubleBytes ? 16 : 8) / colorBits;
		}

		UShort backID = doubleBytes ? data.Read<UShort>(Endian::Big) : data.Read<UByte>(Endian::Big);
		ColorRGBA backColor = colors[backID];

		for (UInt i = 0; i < pixel.pixels.Length(); i++) {
			pixel.pixels[i] = backColor;
		}

		while (true) {
			UInt count = doubleBytes ? data.Read<UShort>(Endian::Big) : data.Read<UByte>(Endian::Big);

			if (count == 0) break;

			UShort x = doubleSize ? data.Read<UShort>(Endian::Big) : data.Read<UByte>(Endian::Big);
			UShort y = doubleSize ? data.Read<UShort>(Endian::Big) : data.Read<UByte>(Endian::Big);

			if (transpose) {
				UShort temp = x;
				x = y;
				y = temp;
			}

			if (x >= pixel.width || y >= pixel.height)
				throw PixelLoadError("Pixel position is not inside the image");

			if (repeat) {
				UInt p = (UInt)x + (UInt)y * (UInt)pixel.width;

				for (UInt i = 0; i < count; i++) {
					UShort color = doubleBytes ? data.Read<UShort>(Endian::Big) : data.Read<UByte>(Endian::Big);
					UShort colorId = color & colorMask;
					UInt repeatCount = ((UInt)color >> colorBits) + 1;

					ColorRGBA rgba = colors[colorId];

					for (UInt u = 0; u < repeatCount; u++) {
						if (p >= pixel.pixels.Length())
							throw PixelLoadError("Pixel position is not inside the image");

						pixel.pixels[p] = rgba;
						p++;
					}
				}
			}
			else {
				UShort colorMask = (doubleBytes ? Math::UShortMax() : Math::UByteMax()) >> ((doubleBytes ? 16 : 8) - colorBits);

				UInt p = (UInt)x + (UInt)y * (UInt)pixel.width;

				UInt i = 0;

				while (i < count) {
					UShort color = doubleBytes ? data.Read<UShort>(Endian::Big) : data.Read<UByte>(Endian::Big);

					for (UShort u = 0; u < segments && i < count; u++) {
						if (p >= pixel.pixels.Length())
							throw PixelLoadError("Pixel position is not inside the image");

						UShort colorId = color & colorMask;
						color = color >> colorBits;
						pixel.pixels[p] = colors[colorId];
						p++;
						i++;
					}
				}
			}
		}
	}

	inline void Pixel::EncodePixels(const Pixel& pixel, const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format) {
		if ((format & Format::Background) != Format::None) {
			EncodeBackground(pixel, colors, colorIDs, data, format);
		}
		else if ((format & Format::Repeat) != Format::None) {
			EncodeRepeat(colors, colorIDs, data, format);
		}
		else {
			EncodeDefault(colors, colorIDs, data, format);
		}
	}

	inline void Pixel::EncodeDefault(const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format) {
		bool doubleBytes = (format & Format::DoubleBytes) != Format::None;

		UByte colorBits = GetBitCount2(colors.Count());
		UByte segments = (doubleBytes ? 16 : 8) / colorBits;

		UShort segment = 0;
		UShort color = 0;

		for (const UShort c : colorIDs) {
			color |= c << segment * colorBits;
			segment++;

			if (segment >= segments) {
				segment = 0;

				if (doubleBytes) {
					data.Write<UShort>(color, Endian::Big);
				}
				else {
					data.Write<UByte>((UByte)color, Endian::Big);
				}

				color = 0;
			}
		}

		if (segment > 0) {
			if (doubleBytes) {
				data.Write<UShort>(color, Endian::Big);
			}
			else {
				data.Write<UByte>((UByte)color, Endian::Big);
			}
		}
	}

	inline void Pixel::EncodeRepeat(const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format) {
		bool doubleBytes = (format & Format::DoubleBytes) != Format::None;

		UByte colorBits = GetBitCount(colors.Count());
		UByte repeatBits = (doubleBytes ? 16 : 8) - colorBits;
		UShort repeatMax = (UShort)1 << repeatBits;

		UShort count = 0;
		UShort color = 0;

		for (const UShort c : colorIDs) {
			if ((c != color && count > 0) || count == repeatMax) {
				UShort repeatColor = color | ((count - 1) << colorBits);

				if (doubleBytes) {
					data.Write<UShort>(repeatColor, Endian::Big);
				}
				else {
					data.Write<UByte>((UByte)repeatColor, Endian::Big);
				}

				count = 0;
			}

			color = c;
			count++;
		}

		if (count > 0) {
			UShort repeatColor = color | ((count - 1) << colorBits);

			if (doubleBytes) {
				data.Write<UShort>(repeatColor, Endian::Big);
			}
			else {
				data.Write<UByte>((UByte)repeatColor, Endian::Big);
			}
		}
	}

	inline void Pixel::EncodeBackgroundDefault(const Pixel& pixel, const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format, const UShort backID) {
		bool doubleBytes = (format & Format::DoubleBytes) != Format::None;
		bool doubleSize = (format & Format::DoubleSize) != Format::None;
		bool transpose = (format & Format::Transpose) != Format::None;

		UByte colorBits = GetBitCount2(colors.Count());
		UByte segments = (doubleBytes ? 16 : 8) / colorBits;

		UInt maxColors = doubleBytes ? Math::UShortMax() : Math::UByteMax();
		UInt backMax = 3 * segments;

		for (UInt i = 0; i < colorIDs.Length(); i++) {
			if (colorIDs[i] != backID) {
				UInt pos = i;
				List<UShort> colorList;
				UInt backCount = 0;

				for (; i < colorIDs.Length(); i++) {
					if (colorIDs[i] == backID) {
						backCount++;

						if (backCount > backMax) {
							break;
						}
					}
					else {
						backCount = 0;
					}

					colorList.Add(colorIDs[i]);

					if (colorList.Count() >= maxColors) 
						break;
				}

				while (colorList.Last() == backID)
					colorList.RemoveLast();

				if (doubleBytes)
					data.Write<UShort>((UShort)colorList.Count(), Endian::Big);
				else
					data.Write<UByte>((UByte)colorList.Count(), Endian::Big);

				UShort x = transpose ? pos / pixel.width : pos % pixel.width;
				UShort y = transpose ? pos % pixel.width : pos / pixel.width;

				if (doubleSize) {
					data.Write<UShort>(x, Endian::Big);
					data.Write<UShort>(y, Endian::Big);
				}
				else {
					data.Write<UByte>((UByte)x, Endian::Big);
					data.Write<UByte>((UByte)y, Endian::Big);
				}

				EncodeDefault(colors, colorList.ToArray(), data, format);
			}
		}

		if (doubleBytes) {
			data.Write<UShort>(0, Endian::Big);
		}
		else {
			data.Write<UByte>(0, Endian::Big);
		}
	}

	inline void Pixel::EncodeBackgroundRepeat(const Pixel& pixel, const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format, const UShort backID) {
		bool doubleBytes = (format & Format::DoubleBytes) != Format::None;
		bool doubleSize = (format & Format::DoubleSize) != Format::None;
		bool transpose = (format & Format::Transpose) != Format::None;

		UByte colorBits = GetBitCount(colors.Count());

		UInt maxColors = doubleBytes ? Math::UShortMax() : Math::UByteMax();
		UInt maxRepeat = (1 << ((doubleBytes ? 16 : 8) - colorBits));
		UInt backMax = 3 * maxRepeat;

		struct RepeatColor {
			UInt count;
			UShort id;
		};

		for (UInt i = 0; i < colorIDs.Length(); i++) {
			if (colorIDs[i] != backID) {
				UInt pos = i;
				List<RepeatColor> repeatColors;
				UInt backCount = 0;
				RepeatColor currentColor = RepeatColor();
				currentColor.count = 1;
				currentColor.id = colorIDs[i];

				for (i++; i < colorIDs.Length(); i++) {
					if (currentColor.count > 0 && currentColor.count < maxRepeat && colorIDs[i] == currentColor.id) {
						currentColor.count++;

						if (currentColor.id == backID) {
							backCount++;

							if (backCount > backMax) break;
						}
						else {
							backCount = 0;
						}

						if (currentColor.count >= maxRepeat) {
							repeatColors.Add(currentColor);

							if (repeatColors.Count() >= maxColors) break;

							currentColor.count = 0;
						}
					}
					else {
						if (currentColor.count > 0)
							repeatColors.Add(currentColor);

						if (repeatColors.Count() >= maxColors) break;

						currentColor.count = 1;
						currentColor.id = colorIDs[i];

						backCount = currentColor.id == backID ? 1 : 0;
					}
				}

				if (currentColor.count > 0) {
					if (repeatColors.Count() == maxColors) {
						i--;
					}
					else {
						repeatColors.Add(currentColor);
					}
				}

				while (repeatColors.Last().id == backID)
					repeatColors.RemoveLast();

				if (doubleBytes)
					data.Write<UShort>(repeatColors.Count(), Endian::Big);
				else
					data.Write<UByte>(repeatColors.Count(), Endian::Big);

				UShort x = transpose ? pos / pixel.height : pos % pixel.width;
				UShort y = transpose ? pos % pixel.height : pos / pixel.width;

				if (doubleSize) {
					data.Write<UShort>(x, Endian::Big);
					data.Write<UShort>(y, Endian::Big);
				}
				else {
					data.Write<UByte>((UByte)x, Endian::Big);
					data.Write<UByte>((UByte)y, Endian::Big);
				}

				for (const RepeatColor& color : repeatColors) {
					UShort repeatColor = color.id | ((UShort)(color.count - 1) << colorBits);

					if (doubleBytes) {
						data.Write<UShort>(repeatColor, Endian::Big);
					}
					else {
						data.Write<UByte>((UByte)repeatColor, Endian::Big);
					}
				}
			}
		}

		if (doubleBytes) {
			data.Write<UShort>(0, Endian::Big);
		}
		else {
			data.Write<UByte>(0, Endian::Big);
		}
	}

	inline void Pixel::EncodeBackground(const Pixel& pixel, const List<ColorRGBA>& colors, const Array<UShort>& colorIDs, Buffer& data, const Format format) {
		bool doubleBytes = (format & Format::DoubleBytes) != Format::None;

		Array<UInt> colorCount = Array<UInt>(colors.Count());

		for (UShort i = 0; i < colorCount.Length(); i++) {
			colorCount[i] = 0;
		}

		for (const UShort id : colorIDs) {
			colorCount[id]++;
		}

		UInt best = 0;
		UShort backID = 0;

		for (UInt i = 0; i < colorCount.Length(); i++) {
			if (colorCount[i] > best) {
				best = colorCount[i];
				backID = i;
			}
		}

		if (doubleBytes) {
			data.Write<UShort>(backID, Endian::Big);
		}
		else {
			data.Write<UByte>((UByte)backID, Endian::Big);
		}

		if ((format & Format::Repeat) != Format::None) {
			EncodeBackgroundRepeat(pixel, colors, colorIDs, data, format, backID);
		}
		else {
			EncodeBackgroundDefault(pixel, colors, colorIDs, data, format, backID);
		}
	}

	inline void Pixel::EncodeHeader(const List<ColorRGBA>& colors, const Pixel& pixel, Buffer& data, const Format format) {
		data.Write<String>("pxl");

		data.Write<Format>(format, Endian::Big);

		if ((format & Format::DoubleSize) != Format::None) {
			data.Write<UShort>(pixel.width, Endian::Big);
			data.Write<UShort>(pixel.height, Endian::Big);
		}
		else {
			data.Write<UByte>((UByte)pixel.width, Endian::Big);
			data.Write<UByte>((UByte)pixel.height, Endian::Big);
		}

		if ((format & Format::DoubleBytes) != Format::None) {
			data.Write<UShort>(colors.Count() - 1, Endian::Big);
		}
		else {
			data.Write<UByte>((UByte)(colors.Count() - 1), Endian::Big);
		}

		bool alphaFormat = (format & Format::Alpha) != Format::None;

		for (const ColorRGBA& color : colors) {
			if (color.a != 0) {
				data.Write<UByte>(color.r, Endian::Big);
				data.Write<UByte>(color.g, Endian::Big);
				data.Write<UByte>(color.b, Endian::Big);

				if (alphaFormat) {
					data.Write<UByte>(color.a, Endian::Big);
				}
			}
		}
	}

	inline void Pixel::WriteToFile(const String& filename, const Pixel& pixel) {
		WriteToFile(filename, pixel, Optional<Format>(nullptr));
	}

	inline void Pixel::WriteToFile(const String& filename, const Pixel& pixel, const Format format) {
		if ((UByte)format > (UByte)Format::Transpose * 2)
			throw PixelEncodeError("Format not supported");

		WriteToFile(filename, pixel, Optional<Format>(format));
	}

	inline void Pixel::WriteToFile(const String& filename, const Pixel& pixel, const Optional<Format>& format) {
		if (format.HasValue()) {
			if (pixel.width > Math::UByteMax() || pixel.height > Math::UByteMax()) {
				if ((*format & Format::DoubleSize) == Format::None) {
					throw PixelEncodeError("Format should have double size for images with a width or height larger than 255");
				}
			} 
		}

		Buffer data = Buffer(pixel.pixels.Length());
		Format bestFormat = Format::None;
		Set<Format> formats = GetAllFormats();

		Tuple<List<ColorRGBA>, Array<UShort>> colors = pixel.GetColorIDs();
		Pixel transposePixel = Pixel(pixel.height, pixel.width, pixel.pixels);
		Array<UShort> transposeIDs = Array<UShort>(colors.value2.Length());

		if (format.HasValue()) {
			if (colors.value1.Count() > Math::UByteMax()) {
				if ((*format & Format::DoubleBytes) == Format::None) {
					throw PixelEncodeError("Format should have double bytes for images with more than 256 colors");
				}
			} 
		}

		for (UInt x = 0; x < pixel.width; x++)
			for (UInt y = 0; y < pixel.height; y++)
				transposeIDs[y + x * pixel.height] = colors.value2[x + y * pixel.width];

		if (!format) {
			for (Format format : formats) {
				if ((format & Format::DoubleSize) == Format::None) {
					if (pixel.width > Math::UByteMax() || pixel.height > Math::UByteMax()) {
						format |= Format::DoubleSize;
					}
				}

				if ((format & Format::DoubleBytes) == Format::None) {
					if (colors.value1.Count() > Math::UByteMax()) {
						continue;
					}
				}

				Buffer formatData = Buffer(pixel.pixels.Length());

				EncodeHeader(colors.value1, pixel, formatData, format);

				if ((format & Format::Transpose) != Format::None) {
					EncodePixels(pixel, colors.value1, transposeIDs, formatData, format);
				}
				else {
					EncodePixels(pixel, colors.value1, colors.value2, formatData, format);
				}

				if (formatData.Size() < data.Size() || data.Size() == 0) {
					bestFormat = format;
					data = formatData;
				}
			}
		}
		else {
			Buffer formatData = Buffer(pixel.pixels.Length());

			EncodeHeader(colors.value1, pixel, formatData, *format);

			if ((*format & Format::Transpose) != Format::None) {
				EncodePixels(pixel, colors.value1, transposeIDs, formatData, *format);
			}
			else {
				EncodePixels(pixel, colors.value1, colors.value2, formatData, *format);
			}

			bestFormat = *format;
			data = formatData;
		}

		try {
			FileWriter file = FileWriter(filename, FileMode::Binary);
			file.Write(data);
			file.Close();
		}
		catch (FileOpenError e) {
			throw e;
		}
	}

	inline UByte Pixel::GetBitCount(const UShort number) {
		UByte bits = 1;

		while (((UInt)1 << bits) < (UInt)number) {
			bits++;
		}

		return bits;
	}

	inline UByte Pixel::GetBitCount2(const UShort number) {
		UByte bits = 1;

		while (((UInt)1 << bits) < (UInt)number) {
			bits *= 2;
		}

		return bits;
	}

	inline Set<Pixel::Format> Pixel::GetAllFormats() {
		Set<Format> formatTypes;
		formatTypes.Add(Format::Repeat);
		formatTypes.Add(Format::DoubleBytes);
		formatTypes.Add(Format::Background);
		formatTypes.Add(Format::Transpose);

		Set<Format> formats;

		Collection<Set<Format>> combinations = formatTypes.AllCombinations();
		
		for (const Set<Format>& comb : combinations) {
			Format format = Format::None;

			for (const Format formatType : comb) {
				format |= formatType;
			}

			formats.Add(format);
		}

		return formats;
	}

	inline Tuple<List<ColorRGBA>, Array<UShort>> Pixel::GetColorIDs() const {
		Set<ColorRGBA> colorSet;
		
		ColorRGBA transparent = ColorRGBA(0, 0, 0, 0);
		colorSet.Add(transparent);

		for (const ColorRGBA& color : pixels) {
			if (color.a != 0) colorSet.Add(color);
		}

		List<ColorRGBA> colors{colorSet.Count()};
		Map<ColorRGBA, UShort> colorMap{colorSet.Count()};

		colors.Add(transparent);
		colorMap.Add(transparent, 0);

		for (const ColorRGBA& color : colorSet) {
			if (color.a != 0) {
				colorMap.Add(color, colors.Count());
				colors.Add(color);
			}
		}

		Array<UShort> colorIDs = Array<UShort>(pixels.Length());

		for (UInt i = 0; i < pixels.Length(); i++) {
			if (pixels[i].a == 0) {
				colorIDs[i] = colorMap[transparent];
			}
			else {
				colorIDs[i] = colorMap[pixels[i]];
			}
		}

		return Tuple<List<ColorRGBA>, Array<UShort>>(colors, colorIDs);
	}

	inline void Pixel::operator=(const Pixel& pixel) {
		width = pixel.width;
		height = pixel.height;
		pixels = pixel.pixels;
	}

	inline void Pixel::operator=(Pixel&& pixel) noexcept {
		width = pixel.width;
		height = pixel.height;
		pixels = std::move(pixel.pixels);
	}
}

#endif
