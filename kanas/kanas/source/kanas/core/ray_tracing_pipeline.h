#ifndef _RAY_TRACING_PIPELINE_H_
#define _RAY_TRACING_PIPELINE_H_

#include "pipeline.h"

_KANAS_CORE_BEGIN

class deferred_operation;

class ray_tracing_pipeline final : public pipeline
{

	friend class device;

	bool allocate(std::shared_ptr<deferred_operation> DeferredOperation);

public:

	ray_tracing_pipeline(device& owner);

	virtual ~ray_tracing_pipeline();

	void CmdTraceRays();

	void CmdTraceRaysIndirect();

};

_KANAS_CORE_END

#endif