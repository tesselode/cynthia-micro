#include "Oscillator.h"

double Oscillator::Blep(double t, double dt)
{
	if (t < dt)
	{
		t /= dt;
		return t + t - t * t - 1.0;
	}
	else if (t > 1.0 - dt)
	{
		t = (t - 1.0) / dt;
		return t * t + t + t + 1.0;
	}
	return 0.0;
}

void Oscillator::ResetPhase()
{
	phase = 0.0;
}

double Oscillator::Next(double dt, double frequency, OscillatorWaveform waveform)
{
	double phaseIncrement = frequency * dt;
	phase += phaseIncrement;
	while (phase >= 1.0) phase -= 1.0;
	if (waveform == OscillatorWaveformSine)
		return sin(phase * twoPi);
	if (waveform == OscillatorWaveformSaw)
		return 1 - 2 * phase + Blep(phase, phaseIncrement);
}