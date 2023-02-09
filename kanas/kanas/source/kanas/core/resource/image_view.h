#ifndef _IMAGE_VIEW_H_
#define _IMAGE_VIEW_H_

#include "kanas/core/device_object.h"

_KANAS_CORE_BEGIN

class image;
class image_1d;
class image_1d_array;
class image_2d;
class image_2d_array;
class image_cube;
class image_cube_array;
class image_3d;

class image_view : public device_object<VkImageView>
{
	friend class device;

protected:

	bool allocate(
            std::shared_ptr<image> InImage,
            VkImageViewType InViewType, VkFormat InFormat,
            const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange);

public:
	
	image_view(device& owner);

	image_view(const image_view& other) = delete;
	image_view(image_view&& Other);

	image_view& operator=(const image_view& Other) = delete;

	virtual ~image_view() override;

private:

	std::shared_ptr<image> Image{};

	VkImageViewType ImageViewType{};

	VkFormat Format{};

public:

	std::shared_ptr<image> GetImage() const 
	{ 
		return Image; 
	}

	VkImageViewType GetViewType() const 
	{ 
		return ImageViewType; 
	}

	VkFormat GetViewFormat() const 
	{ 
		return Format; 
	}

};

/*
class image_view_1d final : protected image_view
{

    bool allocate_view_1d(
            std::shared_ptr<image_1d> img,
            const range& layers_range, const range& mips_range,
            VkFormat format, image_aspect_flags aspects
            );

public:

    image_view_1d();

    ~image_view_1d() override;

};

class image_view_1d_array final : protected image_view
{
public:

    image_view_1d_array();

    virtual ~image_view_1d_array() override;

};

class image_view_2d final : protected image_view
{
public:

    image_view_2d();

    virtual ~image_view_2d() override;

};

class image_view_2d_array final : protected image_view
{
public:

    image_view_2d_array();

    virtual ~image_view_2d_array() override;
};

class image_view_cube final : protected image_view
{
public:

    image_view_cube();

    virtual ~image_view_cube() override;
};

class image_view_cube_array final : protected image_view
{
public:

    image_view_cube_array();

    virtual ~image_view_cube_array() override;
};

class image_view_3d final : protected image_view
{
public:

    image_view_3d();

    virtual ~image_view_3d() override;

};
*/

_KANAS_CORE_END


#endif