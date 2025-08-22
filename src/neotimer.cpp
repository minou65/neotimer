// 
// 
// 

#include "neotimer.h"

//Default constructor
Neotimer::Neotimer() {
	this->_timer.time = 1000; //Default 1 second interval if not specified
	this->_timer.started = false;
}

Neotimer::Neotimer(unsigned long _t) {
	this->_timer.time = _t;
	this->_timer.started = false;
}

//Default destructor
Neotimer::~Neotimer() {

}

//Initializations
void Neotimer::init() {
	this->_waiting = false;
}

boolean Neotimer::repeatdone(int times) {
	bool ret_ = this->repeat(times);
	if (this->repetitions == 0) {
		this->done();
	}
	return ret_;
}

/*
 * Repeats a timer x times
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat(10)){
 * 	  do something 10 times, every second (default)
 * }
 */
boolean Neotimer::repeat() {
	if (this->done()) {
		this->reset();
		return true;
	}
	if (!this->_timer.started) {
		this->_timer.last = millis();
		this->_timer.started = true;
		this->_waiting = true;
	}
	return false;
}

/*
 * Repeats a timer x times with a defined period
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat(10,5000)){
 * 	  do something 10 times, every 5 seconds
 * }
 */
boolean Neotimer::repeat(int times, unsigned long _t) {
	this->_timer.time = _t;
	return this->repeat(times);
}

/*
 * Repeats a timer indefinetely
 * Useful to execute a task periodically.
 * Usage:
 * if(timer.repeat()){
 * 	  do something indefinetely, every second (default)
 * }
 */
boolean Neotimer::repeat() {
	if (this->done()) {
		this->reset();
		return true;
	}
	if (!this->_timer.started) {
		this->_timer.last = millis();
		this->_timer.started = true;
		this->_waiting = true;
	}
	return false;
}

void Neotimer::repeatReset() {
	this->repetitions = -1;
}

/*
 * Checks if timer has finished
 * Returns true if it finished
 */
boolean Neotimer::done() {
	if (!this->_timer.started) 
		return false;
	unsigned long _now = millis();
	if ((_now - this->_timer.last) >= this->_timer.time) {
		this->_timer.done = true;
		this->_waiting = false;
		return true;
	}
	return false;
}

/*
 * Sets a timer preset
 */
void Neotimer::set(unsigned long t) {
	this->_timer.time = t;
}


/*
 * Gets the timer preset
 */
unsigned long Neotimer::get() {
	return this->_timer.time;
}

/*
 * Debounces a digital signal (e.g. from a button or switch).
 * Call this function repeatedly with the current raw signal value.
 * When the signal changes, a timer is started. Only if the signal remains
 * stable for the configured debounce interval, the debounced state is updated.
 * The function returns true only when the debounced state changes.
 *
 * Parameters:
 *   signal - the current raw (unfiltered) digital input value
 *
 * Returns:
 *   true  - if the debounced state has changed (either to HIGH or LOW)
 *   false - if there is no stable change
 *
 * Note:
 *   Use getDebouncedState() to query the current debounced state at any time.
 */
boolean Neotimer::debounce(boolean signal) {
	if (signal != this->_lastSignal) {
		this->start();
		this->_lastSignal = signal;
	}

	if (this->done()) {
		if (signal != this->_debouncedState) {
			this->_debouncedState = signal;
			return true; // State has changed and is stable
		}
	}
	return false;
}

/*
 * Returns the current debounced state of the digital input.
 * This function should be used in conjunction with debounce().
 * It always provides the last stable (debounced) value, regardless of whether
 * a change has just occurred.
 *
 * Returns:
 *   true  - if the debounced state is HIGH
 *   false - if the debounced state is LOW
 *
 * Example usage:
 *   if (myTimer.debounce(rawSignal)) {
 *       // State changed, you can check the new state:
 *       if (myTimer.getDebouncedState()) {
 *           // Button is pressed
 *       } else {
 *           // Button is released
 *       }
 *   }
 */
boolean Neotimer::getDebouncedState() const {
	return this->_debouncedState;
}

/*
 * Resets a timer
 */
void Neotimer::reset() {
	this->stop();
	this->_timer.last = millis();
	this->_timer.done = false;
}

/*
 * Start a timer
 */
void Neotimer::start() {
	this->reset();
	this->_timer.started = true;
	this->_waiting = true;
}

// start a timer with a specific interval
void Neotimer::start(unsigned long t) {
	this->set(t);
	this->reset();
	this->_timer.started = true;
	this->_waiting = true;
}

/*
 * Stops a timer
 */
unsigned long Neotimer::stop() {
	this->_timer.started = false;
	this->_waiting = false;
	return this->getEllapsed();
}

/*
 * Gets ellapsed time
 */
unsigned long Neotimer::getEllapsed() {
	return millis() - this->_timer.last;
}

/*
 * Continues a stopped timer
 */
void Neotimer::restart() {
	if (!this->done()) {
		this->_timer.started = true;
		this->_waiting = true;
	}
}

/*
 * Indicates if the timer is active
 * but has not yet finished.
 */
boolean Neotimer::waiting() {
	return (this->_timer.started && !this->done()) ? true : false;
}

boolean Neotimer::started() {
	return this->_timer.started;
}
