#ifndef __EVENT__
#define __EVENT__

#define NUM_PINS 13

/**
 * Base class representing an event source
 */
class EventSource {
  public:
    /* called by the interrupt dispatcher to notify a new event */
    virtual void notifyInterrupt(int pin) = 0;

  protected:
    void bindInterrupt(int pin);
}; 

/**
 * Class binding interrupts to event sources
 */
class InterruptDispatcher {
  public:
    InterruptDispatcher();        

    /* to bind an event source to a specific pin */
    void bind(int pin, EventSource* src);

    /* called by interrupt handlers */
    void notifyInterrupt(int pin);
  private:
    EventSource* sourceRegisteredOnPin[NUM_PINS];
    void (*notifyFunctions[NUM_PINS])() = {};
};

#endif
