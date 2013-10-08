

#include "guicontroller.hxx"

#include <iostream>

#include "../jack.hxx"
#include "../event.hxx"
#include "../gridlogic.hxx"

extern Jack* jack;

LupppGUI::LupppGUI() :
  Controller()
{
}

void LupppGUI::masterVolume(float f)
{
  EventTrackVol e( -1, f );
  writeToGuiRingbuffer( &e );
}

void LupppGUI::metronomeEnable(bool r)
{
  EventMetronomeActive e( r );
  writeToGuiRingbuffer( &e );
}

void LupppGUI::recordArm(int t, bool r)
{
  EventTrackRecordArm e( t, r );
  writeToGuiRingbuffer( &e );
}

void LupppGUI::trackSend(int t, int send, float r)
{
  EventTrackSend e( t, static_cast<Event::SEND_TYPE>(send), r );
  writeToGuiRingbuffer( &e );
}

void LupppGUI::trackSendActive(int t, int send, bool a)
{
  EventTrackSendActive e( t, static_cast<Event::SEND_TYPE>(send), a );
  writeToGuiRingbuffer( &e );
}

void LupppGUI::setSceneState(int t, int clip, GridLogic::State s)
{
  EventGridState e( t, clip, s );
  writeToGuiRingbuffer( &e );
}

void LupppGUI::launchScene( int scene )
{
  EventGridLaunchScene e( scene );
  writeToGuiRingbuffer( &e );
}

void LupppGUI::mute(int t, bool b)
{
  
}

void LupppGUI::tapTempo( bool b )
{
  EventTimeTempoTap e(b);
  writeToGuiRingbuffer( &e );
}

void LupppGUI::bpm(int bpm)
{
  EventTimeBPM e(bpm);
  writeToGuiRingbuffer( &e );
}

void LupppGUI::volume(int t, float f)
{
  EventTrackVol e( t, f );
  writeToGuiRingbuffer( &e );
}

void LupppGUI::progress(int t, int s, float f)
{
  EventLooperProgress e( t, f );
  writeToGuiRingbuffer( &e );
}
