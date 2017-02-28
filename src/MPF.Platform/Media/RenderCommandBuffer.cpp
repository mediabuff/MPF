//
// MPF Platform
// Render Command Buffer
// ���ߣ�SunnyCase
// ����ʱ�䣺2016-07-22
//
#include "stdafx.h"
#include "RenderCommandBuffer.h"
#include "ResourceManagerBase.h"
using namespace WRL;
using namespace NS_PLATFORM;

RenderCommandBuffer::RenderCommandBuffer(ResourceManagerBase* resourceManager)
	:_resourceManager(resourceManager)
{
}

HRESULT RenderCommandBuffer::DrawGeometry(IResource * geometry, IResource* pen, IResource* brush, float* values)
{
	try
	{
		GeometryRenderCommand command{ static_cast<ResourceRef*>(geometry), static_cast<ResourceRef*>(pen), static_cast<ResourceRef*>(brush) };
		DirectX::XMStoreFloat4x4(&command.Transform, DirectX::XMMatrixTranspose(DirectX::XMMATRIX(values)));
		_commands.emplace_back(std::move(command));
		return S_OK;
	}
	CATCH_ALL();
}

HRESULT RenderCommandBuffer::DrawGeometry3D(IResource * geometry, IResource* material, float* values)
{
	try
	{
		Geometry3DRenderCommand command{ static_cast<ResourceRef*>(geometry), static_cast<ResourceRef*>(material) };
		DirectX::XMStoreFloat4x4(&command.Transform, DirectX::XMMatrixTranspose(DirectX::XMMATRIX(values)));
		_command3Ds.emplace_back(std::move(command));
		return S_OK;
	}
	CATCH_ALL();
}