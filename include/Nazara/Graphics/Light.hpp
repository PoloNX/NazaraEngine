// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_LIGHT_HPP
#define NAZARA_LIGHT_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/Color.hpp>
#include <Nazara/Core/ObjectLibrary.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Graphics/Enums.hpp>
#include <Nazara/Graphics/Renderable.hpp>

class NzLight;
class NzShader;
struct NzLightUniforms;

using NzLightConstRef = NzObjectRef<const NzLight>;
using NzLightLibrary = NzObjectLibrary<NzLight>;
using NzLightRef = NzObjectRef<NzLight>;

class NAZARA_GRAPHICS_API NzLight : public NzRenderable
{
	public:
		NzLight(nzLightType type = nzLightType_Point);
		NzLight(const NzLight& light) = default;
		~NzLight() = default;

		void AddToRenderQueue(NzAbstractRenderQueue* renderQueue, const InstanceData& instanceData) const override;

		NzLight* Clone() const;
		NzLight* Create() const;

		bool Cull(const NzFrustumf& frustum, const InstanceData& instanceData) const override;

		float GetAmbientFactor() const;
		float GetAttenuation() const;
		NzColor GetColor() const;
		float GetDiffuseFactor() const;
		float GetInnerAngle() const;
		float GetInnerAngleCosine() const;
		float GetInvRadius() const;
		nzLightType GetLightType() const;
		float GetOuterAngle() const;
		float GetOuterAngleCosine() const;
		float GetOuterAngleTangent() const;
		float GetRadius() const;

		void SetAmbientFactor(float factor);
		void SetAttenuation(float attenuation);
		void SetColor(const NzColor& color);
		void SetDiffuseFactor(float factor);
		void SetInnerAngle(float innerAngle);
		void SetLightType(nzLightType type);
		void SetOuterAngle(float outerAngle);
		void SetRadius(float radius);

		void UpdateBoundingVolume(InstanceData* instanceData) const;

		NzLight& operator=(const NzLight& light) = default;

		template<typename... Args> static NzLightRef New(Args&&... args);

	private:
		void MakeBoundingVolume() const override;

		nzLightType m_type;
		NzColor m_color;
		float m_ambientFactor;
		float m_attenuation;
		float m_diffuseFactor;
		float m_innerAngle;
		float m_innerAngleCosine;
		float m_invRadius;
		float m_outerAngle;
		float m_outerAngleCosine;
		float m_outerAngleTangent;
		float m_radius;

		static NzLightLibrary::LibraryMap s_library;
};

struct NzLightUniforms
{
	struct UniformLocations
	{
		int type;
		int color;
		int factors;
		int parameters1;
		int parameters2;
		int parameters3;
	};

	bool ubo;

	union
	{
		UniformLocations locations;
		int blockLocation;
	};
};

#include <Nazara/Graphics/Light.inl>

#endif // NAZARA_LIGHT_HPP
