#ifndef _MYFMOD_H_
#define _MYFMOD_H_

//---------使用fomd需要的头文件及库文件--------
#include <fmod.hpp>
#pragma comment(lib, "fmodexL_vc.lib")

//---------使用STL需要的头文件及命名空间--------
#include <vector>
using namespace std;

class MyFMod
{
private:
	FMOD::System    *system;
	//Sound
	vector<FMOD::Sound*> soundArray;
	vector<FMOD::Channel*> channelArray;

	//Stream
	FMOD::Sound     *sound;
	FMOD::Channel    *channel;

public:
	MyFMod();
	virtual ~MyFMod();
	bool InitFMod();	//初始化声音系统

	//在每一帧中调用update函数是很重要的，但不需要多次调用，那样只会影响效率
	void update();

	//-------FStream适合用来播放mp3音频，做游戏背景音乐---------
	//使用Stream时，当中途重新播放时，会停止先前的播放而重新播放
	void LoadStream(const char * fileName);
	//参数为true时，可以在开始播放时暂停，这样就可以更改声音的属性而不会被用户听见
	//然后取消暂停即可播放
	void PlayStream(bool paused);
	//参数取值范围是0-1，默认是1，最大音量
	void SetStreamVolume(float volume);
	void SetStreamPaused(bool state); //true表示暂停，false表示重开始
	void SetStreamLooping(bool loop); //true表示循环，false表示不循环
	void StopStream();
	void ReleaseStream();


	//-------------------------FSound适合用来播放ogg音效---------------------------
	//使用Sound时，当中途重新播放时，不会停止先前的播放
	//它会又重新开一个channel，这很适用于音效，特别是枪械连发的音效
	void LoadSound(const char * fileName);
	//参数1指示了要播放声音的ID号；参数2为true时，
	//可以在开始播放时暂停，这样就可以更改声音的属性而不会被用户听见
	void PlaySound(unsigned char id,bool paused);
	//参数2取值范围是0-1，默认是1，最大音量
	void SetSoundVolume(unsigned char id,float volume);
	void SetSoundPaused(unsigned char id,bool state); //true表示暂停，false表示重开始
	void SetSoundLooping(unsigned char id,bool loop); //true表示循环，false表示不循环
	void StopSound(unsigned char id);
	void ReleaseSound(unsigned char id);
	void ReleaseAllSound();

};

#endif //_MYFMOD_H_