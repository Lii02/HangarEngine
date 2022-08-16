#ifndef WAVLOADER_H
#define WAVLOADER_H

class File;
class AudioClip;

namespace WAVLoader {
	AudioClip* Load(File* file);
}

#endif