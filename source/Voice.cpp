#include "Voice.h"

void Voice::Start()
{
	if (GetVolume() == 0.0)
	{
		osc1a.Reset();
		osc1b.Reset();
		osc2a.Reset();
		osc2b.Reset();
		oscFm.Reset();
	}
	volumeEnvelope.Start();
}
void Voice::Release()
{
	volumeEnvelope.Release();
}

double Voice::GetOscillators()
{
	double out = 0.0;

	double osc1BaseFrequency = baseFrequency * osc1TuneFactor;

	// fm
	double fmFactor = 1.0;
	if (fmCoarse != 0)
	{
		double fmAmount = fabs(fmCoarse) + fmFine;
		double fmValue = oscFm.Next(osc1BaseFrequency, OscillatorWaveformSine);
		fmFactor = pitchFactor(fmAmount * fmValue);
	}

	// osc 1
	if (oscMix < 1.0)
	{
		if (fmCoarse < 0) osc1BaseFrequency *= fmFactor;
		auto osc1Out = 0.0;
		if (osc1SplitFactorA != 1.0)
		{
			osc1Out += osc1a.Next(osc1BaseFrequency * osc1SplitFactorA, OscillatorWaveformSaw);
			osc1Out += osc1b.Next(osc1BaseFrequency * osc1SplitFactorB, OscillatorWaveformSaw);
		}
		else
			osc1Out = osc1a.Next(osc1BaseFrequency, OscillatorWaveformSaw);
		out += osc1Out * (1.0 - oscMix);
	}

	// osc 2
	if (oscMix > 0.0)
	{
		double osc2BaseFrequency = baseFrequency * osc2TuneFactor;
		if (fmCoarse > 0) osc2BaseFrequency *= fmFactor;
		auto osc2Out = 0.0;
		if (osc2SplitFactorA != 1.0)
		{
			osc2Out += osc2a.Next(osc2BaseFrequency * osc2SplitFactorA, OscillatorWaveformSaw);
			osc2Out += osc2b.Next(osc2BaseFrequency * osc2SplitFactorB, OscillatorWaveformSaw);
		}
		else
			osc2Out = osc2a.Next(osc2BaseFrequency, OscillatorWaveformSaw);
		out += osc2Out * oscMix;
	}
	
	return out;
}

double Voice::Next()
{
	UpdateEnvelopes();
	if (GetVolume() == 0.0) return 0.0;

	auto out = GetOscillators();
	if (filterF < 1.0)
	{
		for (int i = 0; i < 2; i++)
			out = filter.Process(out, filterF);
	}
	out *= GetVolume();
	return out;
}
