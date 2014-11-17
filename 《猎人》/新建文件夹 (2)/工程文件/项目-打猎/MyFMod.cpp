#include "MyFMod.h"

MyFMod::MyFMod()
{

}
MyFMod::~MyFMod()
{
	system->release();
}

bool MyFMod::InitFMod()
{
	FMOD_RESULT    result;
	unsigned int   version;
	int      numdrivers;
	FMOD_SPEAKERMODE speakermode;
	FMOD_CAPS    caps;
	char     name[256];

	/*
	Create a System object and initialize
	*/
	FMOD::System_Create(&system);

	system->getVersion(&version);

	if (version < FMOD_VERSION)
	{
	   return false;
	}

	system->getNumDrivers(&numdrivers);

	if (numdrivers == 0)
	{
	   system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
	}
	else
	{
	   system->getDriverCaps(0, &caps, 0, &speakermode);
	   /*
	   Set the user selected speaker mode
	   */
	   system->setSpeakerMode(speakermode);
	   if (caps & FMOD_CAPS_HARDWARE_EMULATED)
	   {
		/*
		The user has the 'Acceleration' slider set to off! This is really bad
		for latency! You might want to warn the user about this
		*/
		system->setDSPBufferSize(1024, 10);
	   }
	   system->getDriverInfo(0, name, 256, 0);
	  
	   if (strstr(name, "SigmaTel"))
	   {
		/*
		Sigmatel sound devices crackle for some reason if the format is PCM 16bit
		PCM floating point output seems to solve it
		*/
		system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0,FMOD_DSP_RESAMPLER_LINEAR);
	   }
}
	result = system->init(100, FMOD_INIT_NORMAL, 0);
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
	   /*
	   Ok, the speaker mode selected isn't supported by this soundcard. Switch it
	   back to stereo...
	   */
	   system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
	   /*
	   ... and re-init
	   */
	   system->init(100, FMOD_INIT_NORMAL, 0);
	}

	return true;
}

void MyFMod::update()
{
	system->update();
}

//////////////////////////////////////////////////////////////////////////
void MyFMod::LoadStream(const char * fileName)
{
	//FMOD_DEFAULT等效于FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE
	system->createStream(fileName, FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
}
void MyFMod::PlayStream(bool paused)
{
	system->playSound(FMOD_CHANNEL_REUSE, sound, paused, &channel);
}
void MyFMod::SetStreamVolume(float volume)
{
	channel->setVolume(volume);
}
void MyFMod::SetStreamPaused(bool state)
{
	channel->setPaused(state);
}
void MyFMod::SetStreamLooping(bool loop)
{
	if(loop)
	   sound->setMode(FMOD_LOOP_NORMAL);
	else
	   sound->setMode(FMOD_LOOP_OFF);
}
void MyFMod::StopStream()
{
	channel->stop();
}
void MyFMod::ReleaseStream()
{
	sound->release();
	sound=0;
}
//////////////////////////////////////////////////////////////////////////
void MyFMod::LoadSound(const char * fileName)
{
FMOD::Sound* sound;

//FMOD_DEFAULT等效于FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE
//也可以使用FMOD_SOFTWARE实现软件混合
system->createSound(fileName, FMOD_DEFAULT, 0, &sound);

soundArray.push_back(sound);
channelArray.push_back(0);
}
void MyFMod::PlaySound(unsigned char id,bool paused)
{
	FMOD::Channel* channel;

	system->playSound(FMOD_CHANNEL_FREE, soundArray[id], paused, &channel);

	channelArray[id]=channel;
}
void MyFMod::SetSoundVolume(unsigned char id,float volume)
{
	channelArray[id]->setVolume(volume);
}
void MyFMod::SetSoundPaused(unsigned char id,bool state)
{
	channelArray[id]->setPaused(state);
}
void MyFMod::SetSoundLooping(unsigned char id,bool loop)
{
	if(loop)
	   soundArray[id]->setMode(FMOD_LOOP_NORMAL);
	else
	   soundArray[id]->setMode(FMOD_LOOP_OFF);
}
void MyFMod::StopSound(unsigned char id)
{
	channelArray[id]->stop();
}
void MyFMod::ReleaseSound(unsigned char id)
{
	soundArray[id]->release();
	soundArray[id]=0;
	channelArray[id]=0;
}
void MyFMod::ReleaseAllSound()
{
	for(vector<FMOD::Sound*>::iterator iter=soundArray.begin();
	   iter!=soundArray.end();++iter)
	{
	   (*iter)->release();
	}
	soundArray.clear();
	channelArray.clear();
}