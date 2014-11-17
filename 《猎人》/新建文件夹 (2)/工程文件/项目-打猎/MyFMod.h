#ifndef _MYFMOD_H_
#define _MYFMOD_H_

//---------ʹ��fomd��Ҫ��ͷ�ļ������ļ�--------
#include <fmod.hpp>
#pragma comment(lib, "fmodexL_vc.lib")

//---------ʹ��STL��Ҫ��ͷ�ļ��������ռ�--------
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
	bool InitFMod();	//��ʼ������ϵͳ

	//��ÿһ֡�е���update�����Ǻ���Ҫ�ģ�������Ҫ��ε��ã�����ֻ��Ӱ��Ч��
	void update();

	//-------FStream�ʺ���������mp3��Ƶ������Ϸ��������---------
	//ʹ��Streamʱ������;���²���ʱ����ֹͣ��ǰ�Ĳ��Ŷ����²���
	void LoadStream(const char * fileName);
	//����Ϊtrueʱ�������ڿ�ʼ����ʱ��ͣ�������Ϳ��Ը������������Զ����ᱻ�û�����
	//Ȼ��ȡ����ͣ���ɲ���
	void PlayStream(bool paused);
	//����ȡֵ��Χ��0-1��Ĭ����1���������
	void SetStreamVolume(float volume);
	void SetStreamPaused(bool state); //true��ʾ��ͣ��false��ʾ�ؿ�ʼ
	void SetStreamLooping(bool loop); //true��ʾѭ����false��ʾ��ѭ��
	void StopStream();
	void ReleaseStream();


	//-------------------------FSound�ʺ���������ogg��Ч---------------------------
	//ʹ��Soundʱ������;���²���ʱ������ֹͣ��ǰ�Ĳ���
	//���������¿�һ��channel�������������Ч���ر���ǹе��������Ч
	void LoadSound(const char * fileName);
	//����1ָʾ��Ҫ����������ID�ţ�����2Ϊtrueʱ��
	//�����ڿ�ʼ����ʱ��ͣ�������Ϳ��Ը������������Զ����ᱻ�û�����
	void PlaySound(unsigned char id,bool paused);
	//����2ȡֵ��Χ��0-1��Ĭ����1���������
	void SetSoundVolume(unsigned char id,float volume);
	void SetSoundPaused(unsigned char id,bool state); //true��ʾ��ͣ��false��ʾ�ؿ�ʼ
	void SetSoundLooping(unsigned char id,bool loop); //true��ʾѭ����false��ʾ��ѭ��
	void StopSound(unsigned char id);
	void ReleaseSound(unsigned char id);
	void ReleaseAllSound();

};

#endif //_MYFMOD_H_