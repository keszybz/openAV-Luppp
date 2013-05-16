
#ifndef LUPPP_EVENT_H
#define LUPPP_EVENT_H

#include <stdint.h>

/*
    event.hxx
  
  This file provides declarations for each type of event that the engine uses.
  
*/

#include "looper.hxx"

namespace Event
{
  enum {
    LOAD_SAMPLE = 0,
    PLAY_SAMPLE,
    MASTER_VOL,
    RECORD,
    
    LOOPER_STATE,
    LOOPER_PROGRESS,
    LOOPER_LOOP_LENGTH,
    
    METRONOME_ACTIVE,
    
    GUI_PRINT,
  };
};

using namespace Event;

class AudioBuffer;

class EventBase
{
  public:
    virtual ~EventBase() {}
    
    virtual int type() = 0;
    virtual uint32_t size() = 0;
};

class EventMasterVol : public EventBase
{
  public:
    int type() { return int(MASTER_VOL); }
    uint32_t size() { return sizeof(EventMasterVol); }
    float vol;
    
    EventMasterVol(float v)
    {
      vol = v;
    }
};

class EventLooperState : public EventBase
{
  public:
    int type() { return int(LOOPER_STATE); }
    uint32_t size() { return sizeof(EventLooperState); }
    
    int track;
    Looper::State state;
    EventLooperState(){}
    EventLooperState(int t, Looper::State s) : track(t), state(s){}
};

class EventLooperProgress : public EventBase
{
  public:
    int type() { return int(LOOPER_PROGRESS); }
    uint32_t size() { return sizeof(EventLooperProgress); }
    
    int track;
    float progress;
    EventLooperProgress(){}
    EventLooperProgress(int t, float p) : track(t), progress(p) {}
};

class EventLooperLoopLength : public EventBase
{
  public:
    int type() { return int(LOOPER_LOOP_LENGTH); }
    uint32_t size() { return sizeof(EventLooperLoopLength); }
    
    int track;
    float scale; // multiply length by this
    EventLooperLoopLength(){}
    EventLooperLoopLength(int t, float s) : track(t), scale(s){}
};

class EventLoadSample : public EventBase
{
  public:
    int type() { return int(LOAD_SAMPLE); }
    uint32_t size() { return sizeof(EventLoadSample); }
    
    AudioBuffer* audioBufferPtr;
    
    EventLoadSample(AudioBuffer* a)
    {
      audioBufferPtr = a;
    }
};

class EventPlaySample : public EventBase
{
  public:
    int type() { return int(PLAY_SAMPLE); }
    uint32_t size() { return sizeof(EventPlaySample); }
    
    int track, bufferID;
    
    EventPlaySample(int t, int id)
    {
      track = t;
      bufferID = id;
    }
};

class EventMetronomeActive : public EventBase
{
  public:
    int type() { return int(METRONOME_ACTIVE); }
    uint32_t size() { return sizeof(EventMetronomeActive); }
    
    bool active;
    
    EventMetronomeActive() : active(false) {}
    EventMetronomeActive(bool a) : active(a) {}
};


// prints the string S in the GUI console
class EventGuiPrint : public EventBase
{
  public:
    int type() { return int(GUI_PRINT); }
    uint32_t size() { return sizeof(EventGuiPrint); }
    
    char stringArray[50];
    
    EventGuiPrint(){}
    EventGuiPrint(const char* s)
    {
      if ( strlen( s ) > 50 )
      {
        // this will be called from an RT context, and should be removed from
        // production code. It is here for the programmer to notice when they
        // are using code which causes too long a message.
        cout << "EventGuiPrint() error! Size of string too long!" << endl;
      }
      else
      {
        // move the sting into this event
        strcpy( &stringArray[0], s );
      }
    }
    char* getMessage()
    {
      return &stringArray[0];
    }
};

#endif // LUPPP_EVENT_H

