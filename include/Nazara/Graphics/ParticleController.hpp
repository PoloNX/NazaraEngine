// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_PARTICLECONTROLLER_HPP
#define NAZARA_PARTICLECONTROLLER_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/ObjectLibrary.hpp>
#include <Nazara/Core/ObjectRef.hpp>
#include <Nazara/Core/RefCounted.hpp>
#include <Nazara/Core/Signal.hpp>
#include <Nazara/Graphics/Config.hpp>

class NzParticleController;
class NzParticleMapper;
class NzParticleSystem;

using NzParticleControllerConstRef = NzObjectRef<const NzParticleController>;
using NzParticleControllerLibrary = NzObjectLibrary<NzParticleController>;
using NzParticleControllerRef = NzObjectRef<NzParticleController>;

class NAZARA_GRAPHICS_API NzParticleController : public NzRefCounted
{
	friend NzParticleControllerLibrary;
	friend class NzGraphics;

	public:
		NzParticleController() = default;
		NzParticleController(const NzParticleController& controller);
		virtual ~NzParticleController();

		virtual void Apply(NzParticleSystem& system, NzParticleMapper& mapper, unsigned int startId, unsigned int endId, float elapsedTime) = 0;

		// Signals:
		NazaraSignal(OnParticleControllerRelease, const NzParticleController*); //< Args: me

	private:
		static bool Initialize();
		static void Uninitialize();

		static NzParticleControllerLibrary::LibraryMap s_library;
};

#endif // NAZARA_PARTICLECONTROLLER_HPP
