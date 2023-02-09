#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class queue_pool;
class fence;
class command_buffer;
class semaphore;
class swapchain;

struct submission_batch
{
	std::vector<std::pair<semaphore*, VkPipelineStageFlags>> semaphore_to_wait_before_execution;
	
	std::vector<command_buffer*> cmd_buffers;
	
	std::vector<semaphore*> semaphore_to_signal_after_execution;

};

struct BindSpareInfo
{

};

class queue final : public device_object<VkQueue>
{
	friend class device;

	bool allocate(std::uint32_t InQueueFamilyIndex, std::uint32_t InQueueIndex);

public:

	queue(device& owner);

	virtual ~queue() override;

	void bind_spare(const std::vector<BindSpareInfo>& InBindSparseInfos, fence* InFence = nullptr);

	void wait_idle();

	void submit(const std::vector<submission_batch>& batches, std::shared_ptr<fence> fen = nullptr);

	void present(const std::vector<std::shared_ptr<semaphore>>& _Semaphores,
		const std::vector<std::shared_ptr<swapchain>>& _Swapchains);

	queue_pool* owner() const;

	std::uint32_t get_family_index() const { return _queue_family_index; }

private:

	queue_pool* _owner{ nullptr };

	std::uint32_t _queue_family_index;

};


struct TransientQueueGroup
{

	std::vector<queue*> Queues;

	void BindSpare();

	void Submit();

};

_KANAS_CORE_END

#endif