#include "chpch.h"
#include "RenderingResource.h"
#include "Chernobyl/Core/UUID.h"

namespace CH {

	Vector<Ref<RenderingResource>> RendererVault::s_Resources;

	void RendererVault::Submit(const std::shared_ptr<RenderingResource>& resource)
	{
		resource->m_UUID = UUID().Get();
		s_Resources.push_back(resource);
	}

	Ref<RenderingResource>& RendererVault::GetResource(String uuid)
	{
		for (Ref<RenderingResource>& resource : s_Resources)
		{
			if (resource->GetUUID() == uuid)
				return resource;
		}

		CH_CORE_WARN("Unknown UUID");
		return (Ref<RenderingResource>)nullptr;
	}

	template<RenderingResource::Type T>
	static Ref<RenderingResource>& RendererVault::GetResource(const String& name)
	{
		for (Ref<RenderingResource>& resource : s_Resources)
		{
			if (resource->GetType() == T && resource->GetName() == name)
				return resource;
		}

		CH_CORE_WARN("Unknown UUID");
		return (Ref<RenderingResource>)nullptr;
	}

}