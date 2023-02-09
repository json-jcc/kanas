#ifndef _DESCRIPTOR_SET_H_
#define _DESCRIPTOR_SET_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class descriptor_pool;
class descriptor_set_layout;
class descriptor_update_template;
class pipeline;
class buffer;
class sampler;
class image_view;


struct FDescriptorImageInfo
{
	std::shared_ptr<image_view> ImageView;
	std::shared_ptr<sampler> Sampler;
};

struct FDescriptorBufferInfo
{
	std::shared_ptr<buffer> Buffer;
};

class descriptor_set final : public device_object<VkDescriptorSet>
{
	bool allocate(std::shared_ptr<descriptor_set_layout> InLayout);

public:

	descriptor_set(device& owner, descriptor_pool& InPool);

	descriptor_set(const descriptor_set&) = delete;
	descriptor_set(descriptor_set&& Other);

	virtual ~descriptor_set() override;

	void Write(std::uint32_t BindingIndex, std::uint32_t ArrayIndex, const std::vector<FDescriptorImageInfo>& DescriptorImageInfos);

	void Copy(std::uint32_t SrcBindingIndex, std::uint32_t SrcArrayIndex, std::shared_ptr<descriptor_set> DstDescriptorSet, std::uint32_t DstBindingIndex, std::uint32_t DstArrayIndex, std::uint32_t CopyNum);

	void Update(std::shared_ptr<descriptor_update_template> InTemplate);
	
	void CmdPushDescriptorSet(command_buffer& InRecorder);

	void CmdPushDescriptorSetWithTemplate(command_buffer& InRecorder);
	
	std::shared_ptr<descriptor_set_layout> GetLayout() const;

private:

	descriptor_pool& Pool;

	std::shared_ptr<descriptor_set_layout> Layout;

};

_KANAS_CORE_END


#endif