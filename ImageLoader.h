/*
 * ImageLoader.h
 *
 *  Created on: 2011-05-01
 *      Author: jarrett
 */

#ifndef IMAGELOADER_H_
#define IMAGELOADER_H_

#include <sstream>

#include "FreeImage.h"

#include "../../common/logger/Logger.h"

namespace utilities {

enum Format
{
	FORMAT_UNKNOWN = -1,
	FORMAT_RGB,
	FORMAT_RGBA
};

struct Image
{
	std::vector<char> data;
	int width;
	int height;
	Format format;
};

class ImageLoader {
public:
	ImageLoader()
	{
	}
	virtual ~ImageLoader()
	{
	}

	std::unique_ptr<Image> loadImageData(const std::string filename, bool hasAlpha = true)
	{
		return loadImageData(filename.c_str());
	}

	std::unique_ptr<Image> loadImageData(const char* filename, bool hasAlpha = true)
	{
		LOG_DEBUG( "Loading image." );
		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
		FIBITMAP* imageBitmap = FreeImage_Load(format, filename);

		LOG_DEBUG( "image loaded." );

		FIBITMAP* temp = imageBitmap;
		if ( hasAlpha )
			imageBitmap = FreeImage_ConvertTo32Bits(imageBitmap);
		else
			imageBitmap = FreeImage_ConvertTo24Bits(imageBitmap);
		FreeImage_Unload(temp);

		int w = FreeImage_GetWidth(imageBitmap);
		int h = FreeImage_GetHeight(imageBitmap);
		std::stringstream msg;
		msg << "The size of the image '" << filename << "' is: " << w << "*" << h;
		LOG_DEBUG( msg.str() );

		GLubyte* imageBytes;
		int imageBytesLength = 0;
		if ( hasAlpha )
			imageBytesLength = 4 * w * h;
		else
			imageBytesLength = 3 * w * h;
		
		imageBytes = new GLubyte[imageBytesLength];

		char* pixels = (char*) FreeImage_GetBits(imageBitmap);

		std::unique_ptr<Image> retImage = std::unique_ptr<Image>();
		
		// FreeImage loads in BGR format, so you need to swap some bytes (Or use GL_BGR)
		if ( pixels != nullptr )
		{
			int pixelSize = 3;
			if ( hasAlpha )
				pixelSize = 4;

			for ( int j = 0; j < w * h; j++ )
			{
				imageBytes[j * pixelSize + 0] = pixels[j * pixelSize + 2];
				imageBytes[j * pixelSize + 1] = pixels[j * pixelSize + 1];
				imageBytes[j * pixelSize + 2] = pixels[j * pixelSize + 0];
				if ( hasAlpha )
					imageBytes[j * pixelSize + 3] = pixels[j * pixelSize + 3];
				//cout<<j<<": "<<imageBytes[j*4+0]<<"**"<<imageBytes[j*4+1]<<"**"<<imageBytes[j*4+2]<<"**"<<imageBytes[j*4+3]<<endl;
			}

			retImage = std::unique_ptr<Image>(new Image());
			
			// Transfer raw data into a vector
			retImage->data = std::vector<char>(pixels, pixels+imageBytesLength);
			
			retImage->width = w;
			retImage->height = h;
			if (hasAlpha)
				retImage->format = FORMAT_RGBA;
			else
				retImage->format = FORMAT_RGB;
		}
		
		FreeImage_Unload(imageBitmap);

		return retImage;
	}
};

}

#endif /* IMAGELOADER_H_ */












