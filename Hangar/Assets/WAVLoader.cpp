#include "Precompiled.h"
#include "WAVLoader.h"
#include <IO/File.h>
#include <Audio/AudioClip.h>
#include <Audio/AudioEngine.h>
#include <Memory/MemoryManager.h>
#include <Debug/Logger.h>

#define WAV_DESC_SIZE 4

#pragma pack(push, 1)
struct WAVInfo {
	char signature[WAV_DESC_SIZE];
	uint32_t filesize;
	char wavDesc[WAV_DESC_SIZE];
	char fmtDesc[WAV_DESC_SIZE];
	uint32_t wavSectionSize;
	uint16_t typeFormat;
	uint16_t channels;
	uint32_t frequency;
	uint32_t rate;
	uint16_t alignment;
	uint16_t bitsSample;
	char dataDesc[WAV_DESC_SIZE];
	uint32_t dataSize;
};
#pragma pack(pop)

AudioClip* WAVLoader::Load(File* file) {
	AudioClip* clip = new AudioClip();
	if (!file->ReOpen()) {
		Logger::Error("Failed to load WAV file: " + file->GetPath());
		delete file;
		return nullptr;
	}
	WAVInfo info = file->Read<WAVInfo>();
	void* buffer = file->ReadBuffer(info.dataSize);
	clip->SetData(buffer, AudioEngine::GetFormat(info.channels, info.bitsSample), info.dataSize, info.frequency);
	MemoryFree(buffer);
	file->Rewind();
	return clip;
}