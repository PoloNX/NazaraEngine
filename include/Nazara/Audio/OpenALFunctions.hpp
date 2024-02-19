// Copyright (C) 2024 Jérôme "SirLynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - Audio module"
// For conditions of distribution and use, see copyright notice in Export.hpp

// no header guards

#if (!defined(NAZARA_AUDIO_AL_FUNCTION) || !defined(NAZARA_AUDIO_ALC_FUNCTION)) && !defined(NAZARA_AUDIO_AL_ALC_FUNCTION)
#error You must define NAZARA_AUDIO_AL_FUNCTION and NAZARA_AUDIO_ALC_FUNCTION, or NAZARA_AUDIO_AL_ALC_FUNCTION before including this file
#endif

#ifndef NAZARA_AUDIO_AL_FUNCTION
#define NAZARA_AUDIO_AL_FUNCTION(func) NAZARA_AUDIO_AL_ALC_FUNCTION(func)
#endif

#ifndef NAZARA_AUDIO_ALC_FUNCTION
#define NAZARA_AUDIO_ALC_FUNCTION(func) NAZARA_AUDIO_AL_ALC_FUNCTION(func)
#endif

#ifndef NAZARA_AUDIO_AL_EXT_FUNCTION
#define NAZARA_AUDIO_AL_EXT_FUNCTION(func) NAZARA_AUDIO_AL_FUNCTION(func)
#endif

#ifndef NAZARA_AUDIO_AL_EXT_BEGIN
#define NAZARA_AUDIO_AL_EXT_BEGIN(ext)
#endif

#ifndef NAZARA_AUDIO_AL_EXT_END
#define NAZARA_AUDIO_AL_EXT_END()
#endif

#ifndef NAZARA_AUDIO_ALC_EXT_FUNCTION
#define NAZARA_AUDIO_ALC_EXT_FUNCTION(func) NAZARA_AUDIO_AL_EXT_FUNCTION(func)
#endif

#ifndef NAZARA_AUDIO_ALC_EXT_BEGIN
#define NAZARA_AUDIO_ALC_EXT_BEGIN(ext) NAZARA_AUDIO_AL_EXT_BEGIN(ext)
#endif

#ifndef NAZARA_AUDIO_ALC_EXT_END
#define NAZARA_AUDIO_ALC_EXT_END() NAZARA_AUDIO_AL_EXT_END()
#endif

NAZARA_AUDIO_AL_FUNCTION(alBuffer3f)
NAZARA_AUDIO_AL_FUNCTION(alBuffer3i)
NAZARA_AUDIO_AL_FUNCTION(alBufferData)
NAZARA_AUDIO_AL_FUNCTION(alBufferf)
NAZARA_AUDIO_AL_FUNCTION(alBufferfv)
NAZARA_AUDIO_AL_FUNCTION(alBufferi)
NAZARA_AUDIO_AL_FUNCTION(alBufferiv)
NAZARA_AUDIO_AL_FUNCTION(alDeleteBuffers)
NAZARA_AUDIO_AL_FUNCTION(alDeleteSources)
NAZARA_AUDIO_AL_FUNCTION(alDisable)
NAZARA_AUDIO_AL_FUNCTION(alDistanceModel)
NAZARA_AUDIO_AL_FUNCTION(alDopplerFactor)
NAZARA_AUDIO_AL_FUNCTION(alDopplerVelocity)
NAZARA_AUDIO_AL_FUNCTION(alEnable)
NAZARA_AUDIO_AL_FUNCTION(alGenBuffers)
NAZARA_AUDIO_AL_FUNCTION(alGenSources)
NAZARA_AUDIO_AL_FUNCTION(alGetBoolean)
NAZARA_AUDIO_AL_FUNCTION(alGetBooleanv)
NAZARA_AUDIO_AL_FUNCTION(alGetBuffer3f)
NAZARA_AUDIO_AL_FUNCTION(alGetBuffer3i)
NAZARA_AUDIO_AL_FUNCTION(alGetBufferf)
NAZARA_AUDIO_AL_FUNCTION(alGetBufferfv)
NAZARA_AUDIO_AL_FUNCTION(alGetBufferi)
NAZARA_AUDIO_AL_FUNCTION(alGetBufferiv)
NAZARA_AUDIO_AL_FUNCTION(alGetDouble)
NAZARA_AUDIO_AL_FUNCTION(alGetDoublev)
NAZARA_AUDIO_AL_FUNCTION(alGetEnumValue)
NAZARA_AUDIO_AL_FUNCTION(alGetError)
NAZARA_AUDIO_AL_FUNCTION(alGetFloat)
NAZARA_AUDIO_AL_FUNCTION(alGetFloatv)
NAZARA_AUDIO_AL_FUNCTION(alGetInteger)
NAZARA_AUDIO_AL_FUNCTION(alGetIntegerv)
NAZARA_AUDIO_AL_FUNCTION(alGetListener3f)
NAZARA_AUDIO_AL_FUNCTION(alGetListener3i)
NAZARA_AUDIO_AL_FUNCTION(alGetListenerf)
NAZARA_AUDIO_AL_FUNCTION(alGetListenerfv)
NAZARA_AUDIO_AL_FUNCTION(alGetListeneri)
NAZARA_AUDIO_AL_FUNCTION(alGetListeneriv)
NAZARA_AUDIO_AL_FUNCTION(alGetProcAddress)
NAZARA_AUDIO_AL_FUNCTION(alGetSource3f)
NAZARA_AUDIO_AL_FUNCTION(alGetSource3i)
NAZARA_AUDIO_AL_FUNCTION(alGetSourcef)
NAZARA_AUDIO_AL_FUNCTION(alGetSourcefv)
NAZARA_AUDIO_AL_FUNCTION(alGetSourcei)
NAZARA_AUDIO_AL_FUNCTION(alGetSourceiv)
NAZARA_AUDIO_AL_FUNCTION(alGetString)
NAZARA_AUDIO_AL_FUNCTION(alIsBuffer)
NAZARA_AUDIO_AL_FUNCTION(alIsEnabled)
NAZARA_AUDIO_AL_FUNCTION(alIsExtensionPresent)
NAZARA_AUDIO_AL_FUNCTION(alIsSource)
NAZARA_AUDIO_AL_FUNCTION(alListener3f)
NAZARA_AUDIO_AL_FUNCTION(alListener3i)
NAZARA_AUDIO_AL_FUNCTION(alListenerf)
NAZARA_AUDIO_AL_FUNCTION(alListenerfv)
NAZARA_AUDIO_AL_FUNCTION(alListeneri)
NAZARA_AUDIO_AL_FUNCTION(alListeneriv)
NAZARA_AUDIO_AL_FUNCTION(alSource3f)
NAZARA_AUDIO_AL_FUNCTION(alSource3i)
NAZARA_AUDIO_AL_FUNCTION(alSourcef)
NAZARA_AUDIO_AL_FUNCTION(alSourcefv)
NAZARA_AUDIO_AL_FUNCTION(alSourcei)
NAZARA_AUDIO_AL_FUNCTION(alSourceiv)
NAZARA_AUDIO_AL_FUNCTION(alSourcePause)
NAZARA_AUDIO_AL_FUNCTION(alSourcePausev)
NAZARA_AUDIO_AL_FUNCTION(alSourcePlay)
NAZARA_AUDIO_AL_FUNCTION(alSourcePlayv)
NAZARA_AUDIO_AL_FUNCTION(alSourceQueueBuffers)
NAZARA_AUDIO_AL_FUNCTION(alSourceRewind)
NAZARA_AUDIO_AL_FUNCTION(alSourceRewindv)
NAZARA_AUDIO_AL_FUNCTION(alSourceStop)
NAZARA_AUDIO_AL_FUNCTION(alSourceStopv)
NAZARA_AUDIO_AL_FUNCTION(alSourceUnqueueBuffers)
NAZARA_AUDIO_AL_FUNCTION(alSpeedOfSound)

#ifdef AL_SOFT_source_latency
NAZARA_AUDIO_AL_EXT_BEGIN(AL_SOFT_source_latency)
NAZARA_AUDIO_AL_EXT_FUNCTION(alGetSource3dSOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alGetSource3i64SOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alGetSourcedSOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alGetSourcedvSOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alGetSourcei64SOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alGetSourcei64vSOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alSource3dSOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alSource3i64SOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alSourcedSOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alSourcedvSOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alSourcei64SOFT)
NAZARA_AUDIO_AL_EXT_FUNCTION(alSourcei64vSOFT)
NAZARA_AUDIO_AL_EXT_END()
#endif

NAZARA_AUDIO_ALC_FUNCTION(alcCaptureCloseDevice)
NAZARA_AUDIO_ALC_FUNCTION(alcCaptureOpenDevice)
NAZARA_AUDIO_ALC_FUNCTION(alcCaptureSamples)
NAZARA_AUDIO_ALC_FUNCTION(alcCaptureStart)
NAZARA_AUDIO_ALC_FUNCTION(alcCaptureStop)
NAZARA_AUDIO_ALC_FUNCTION(alcCloseDevice)
NAZARA_AUDIO_ALC_FUNCTION(alcCreateContext)
NAZARA_AUDIO_ALC_FUNCTION(alcDestroyContext)
NAZARA_AUDIO_ALC_FUNCTION(alcGetContextsDevice)
NAZARA_AUDIO_ALC_FUNCTION(alcGetCurrentContext)
NAZARA_AUDIO_ALC_FUNCTION(alcGetEnumValue)
NAZARA_AUDIO_ALC_FUNCTION(alcGetError)
NAZARA_AUDIO_ALC_FUNCTION(alcGetIntegerv)
NAZARA_AUDIO_ALC_FUNCTION(alcGetProcAddress)
NAZARA_AUDIO_ALC_FUNCTION(alcGetString)
NAZARA_AUDIO_ALC_FUNCTION(alcIsExtensionPresent)
NAZARA_AUDIO_ALC_FUNCTION(alcMakeContextCurrent)
NAZARA_AUDIO_ALC_FUNCTION(alcOpenDevice)
NAZARA_AUDIO_ALC_FUNCTION(alcProcessContext)
NAZARA_AUDIO_ALC_FUNCTION(alcSuspendContext)

#ifdef ALC_EXT_thread_local_context
NAZARA_AUDIO_ALC_EXT_BEGIN(ALC_EXT_thread_local_context)
NAZARA_AUDIO_ALC_EXT_FUNCTION(alcGetThreadContext)
NAZARA_AUDIO_ALC_EXT_FUNCTION(alcSetThreadContext)
NAZARA_AUDIO_ALC_EXT_END()
#endif

#undef NAZARA_AUDIO_AL_FUNCTION
#undef NAZARA_AUDIO_AL_ALC_FUNCTION
#undef NAZARA_AUDIO_AL_EXT_FUNCTION
#undef NAZARA_AUDIO_AL_EXT_BEGIN
#undef NAZARA_AUDIO_AL_EXT_END
#undef NAZARA_AUDIO_ALC_EXT_FUNCTION
#undef NAZARA_AUDIO_ALC_EXT_BEGIN
#undef NAZARA_AUDIO_ALC_EXT_END
#undef NAZARA_AUDIO_ALC_FUNCTION
