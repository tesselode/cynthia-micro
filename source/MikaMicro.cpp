#include "MikaMicro.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

void MikaMicro::InitParameters()
{
	GetParam((int)Parameters::Osc1Wave)->InitEnum("Oscillator 1 waveform", (int)Waveforms::Saw, (int)Waveforms::NumWaveforms);
	GetParam((int)Parameters::Osc1Coarse)->InitInt("Oscillator 1 coarse", 0, -24, 24, "semitones");
	GetParam((int)Parameters::Osc1Fine)->InitDouble("Oscillator 1 fine", 0.0, -1.0, 1.0, .01, "semitones");
	GetParam((int)Parameters::Osc1Split)->InitDouble("Oscillator 1 split", 0.0, -1.0, 1.0, .01, "semitones");
	GetParam((int)Parameters::Osc2Wave)->InitEnum("Oscillator 1 waveform", (int)Waveforms::Saw, (int)Waveforms::NumWaveforms);
	GetParam((int)Parameters::Osc2Coarse)->InitInt("Oscillator 2 coarse", 0, -24, 24, "semitones");
	GetParam((int)Parameters::Osc2Fine)->InitDouble("Oscillator 2 fine", 0.0, -1.0, 1.0, .01, "semitones");
	GetParam((int)Parameters::Osc2Split)->InitDouble("Oscillator 2 split", 0.0, -1.0, 1.0, .01, "semitones");
	GetParam((int)Parameters::OscMix)->InitDouble("Oscillator mix", 1.0, 0.0, 1.0, .01);

	GetParam((int)Parameters::FmMode)->InitEnum("FM mode", (int)FmModes::Off, (int)FmModes::NumFmModes);
	GetParam((int)Parameters::FmCoarse)->InitInt("FM coarse", 0, 0, 48);
	GetParam((int)Parameters::FmFine)->InitDouble("FM fine", 0.0, -1.0, 1.0, .01);

	GetParam((int)Parameters::FilterMode)->InitEnum("Filter mode", (int)FilterModes::Off, (int)FilterModes::NumFilterModes);
	GetParam((int)Parameters::FilterMode)->SetDisplayText((int)FilterModes::Off, "Off");
	GetParam((int)Parameters::FilterMode)->SetDisplayText((int)FilterModes::TwoPole, "Two pole");
	GetParam((int)Parameters::FilterMode)->SetDisplayText((int)FilterModes::Svf, "State variable");
	GetParam((int)Parameters::FilterMode)->SetDisplayText((int)FilterModes::FourPole, "Four pole");
	GetParam((int)Parameters::FilterCutoff)->InitDouble("Filter cutoff", 8000.0, 20.0, 8000.0, .01, "hz");
	GetParam((int)Parameters::FilterResonance)->InitDouble("Filter resonance", 0.0, 0.0, 1.0, .01);
	//GetParam((int)Parameters::FilterKeyTrack)->InitDouble("Filter key tracking", 0.0, -1.0, 1.0,

	GetParam((int)Parameters::VolEnvA)->InitDouble("Volume envelope attack time", 0.5, 0.0, 1.0, .01);
	GetParam((int)Parameters::VolEnvD)->InitDouble("Volume envelope decay time", 0.5, 0.0, 1.0, .01);
	GetParam((int)Parameters::VolEnvS)->InitDouble("Volume envelope sustain", 0.5, 0.0, 1.0, .01);
	GetParam((int)Parameters::VolEnvR)->InitDouble("Volume envelope release time", 0.5, 0.0, 1.0, .01);
	GetParam((int)Parameters::ModEnvA)->InitDouble("Mod envelope attack time", 0.5, 0.0, 1.0, .01);
	GetParam((int)Parameters::ModEnvD)->InitDouble("Mod envelope decay time", 0.5, 0.0, 1.0, .01);
	GetParam((int)Parameters::ModEnvS)->InitDouble("Mod envelope sustain", 0.5, 0.0, 1.0, .01);
	GetParam((int)Parameters::ModEnvR)->InitDouble("Mod envelope release time", 0.5, 0.0, 1.0, .01);
	GetParam((int)Parameters::LfoAmount)->InitDouble("Vibrato amount", 0.0, -0.1, 0.1, .01);
	GetParam((int)Parameters::LfoFrequency)->InitDouble("Vibrato frequency", 4.0, 0.1, 10.0, .01, "", "", 2.0);
	GetParam((int)Parameters::LfoDelay)->InitDouble("Vibrato delay", 0.1, 0.1, 1000.0, .01, "", "", .001);

	GetParam((int)Parameters::VolEnvFm)->InitDouble("Volume envelope to FM amount", 0.0, -24.0, 24.0, .01, "semitones");
	GetParam((int)Parameters::ModEnvFm)->InitDouble("Modulation envelope to FM amount", 0.0, -24.0, 24.0, .01, "semitones");
	GetParam((int)Parameters::LfoFm)->InitDouble("Vibrato to FM amount", 0.0, -24.0, 24.0, .01, "semitones");
	GetParam((int)Parameters::VolEnvCutoff)->InitDouble("Volume envelope to filter cutoff", 0.0, -8000.0, 8000.0, .01, "hz");
	GetParam((int)Parameters::ModEnvCutoff)->InitDouble("Modulation envelope to filter cutoff", 0.0, -8000.0, 8000.0, .01, "hz");
	GetParam((int)Parameters::LfoCutoff)->InitDouble("Vibrato to filter cutoff", 0.0, -8000.0, 8000.0, .01);
}

void MikaMicro::InitGraphics()
{
	IGraphics* pGraphics = MakeGraphics(this, GUI_WIDTH, GUI_HEIGHT, 120);
	pGraphics->AttachBackground(BG_ID, BG_FN);

	auto knobLeft = pGraphics->LoadIBitmap(KNOBLEFT_ID, KNOBLEFT_FN, 100);
	auto knobMiddle = pGraphics->LoadIBitmap(KNOBMIDDLE_ID, KNOBMIDDLE_FN, 100);
	auto knobRight = pGraphics->LoadIBitmap(KNOBRIGHT_ID, KNOBRIGHT_FN, 100);
	auto slider = pGraphics->LoadIBitmap(SLIDER_ID, SLIDER_FN, 1);
	auto sliderBg = pGraphics->LoadIBitmap(SLIDERBG_ID, SLIDERBG_FN, 1);
	auto waveformSwitch = pGraphics->LoadIBitmap(WAVEFORMSWITCH_ID, WAVEFORMSWITCH_FN, (int)Waveforms::NumWaveforms);
	auto toggleSwitch = pGraphics->LoadIBitmap(TOGGLESWITCH_ID, TOGGLESWITCH_FN, 2);
	auto fmModeSwitch = pGraphics->LoadIBitmap(FMMODESWITCH_ID, FMMODESWITCH_FN, 3);

	// oscillators
	pGraphics->AttachControl(new ISwitchControl(this, 22 * 4, 10 * 4, (int)Parameters::Osc1Wave, &waveformSwitch));
	pGraphics->AttachControl(new IKnobMultiControl(this, 38 * 4, 10 * 4, (int)Parameters::Osc1Coarse, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 54 * 4, 10 * 4, (int)Parameters::Osc1Fine, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 70 * 4, 10 * 4, (int)Parameters::Osc1Split, &knobMiddle));
	pGraphics->AttachControl(new ISwitchControl(this, 22 * 4, 26 * 4, (int)Parameters::Osc2Wave, &waveformSwitch));
	pGraphics->AttachControl(new IKnobMultiControl(this, 38 * 4, 26 * 4, (int)Parameters::Osc2Coarse, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 54 * 4, 26 * 4, (int)Parameters::Osc2Fine, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 70 * 4, 26 * 4, (int)Parameters::Osc2Split, &knobMiddle));
	pGraphics->AttachControl(new IBitmapControl(this, 91.5 * 4, 15 * 4, &sliderBg));
	pGraphics->AttachControl(new IFaderControl(this, 90.5 * 4, 16 * 4, 20 * 4, (int)Parameters::OscMix, &slider));

	// fm
	pGraphics->AttachControl(new ISwitchControl(this, 22 * 4, 42 * 4, (int)Parameters::FmMode, &fmModeSwitch));
	pGraphics->AttachControl(new IKnobMultiControl(this, 38 * 4, 42 * 4, (int)Parameters::FmCoarse, &knobLeft));
	pGraphics->AttachControl(new IKnobMultiControl(this, 54 * 4, 42 * 4, (int)Parameters::FmFine, &knobMiddle));

	// filter
	pGraphics->AttachControl(new ISwitchControl(this, 22 * 4, 62 * 4, (int)Parameters::FilterMode, &fmModeSwitch));
	pGraphics->AttachControl(new IKnobMultiControl(this, 38 * 4, 62 * 4, (int)Parameters::FilterCutoff, &knobRight));
	pGraphics->AttachControl(new IKnobMultiControl(this, 54 * 4, 62 * 4, (int)Parameters::FilterResonance, &knobLeft));
	//pGraphics->AttachControl(new IKnobMultiControl(this, 70 * 4, 62 * 4, (int)Parameters::FilterKeyTrack, &knobMiddle));

	// modulation sources
	pGraphics->AttachControl(new IBitmapControl(this, 121.5 * 4, 22 * 4, &sliderBg));
	pGraphics->AttachControl(new IFaderControl(this, 120.5 * 4, 23 * 4, 20 * 4, (int)Parameters::VolEnvA, &slider));
	pGraphics->AttachControl(new IBitmapControl(this, 129.5 * 4, 22 * 4, &sliderBg));
	pGraphics->AttachControl(new IFaderControl(this, 128.5 * 4, 23 * 4, 20 * 4, (int)Parameters::VolEnvD, &slider));
	pGraphics->AttachControl(new IBitmapControl(this, 137.5 * 4, 22 * 4, &sliderBg));
	pGraphics->AttachControl(new IFaderControl(this, 136.5 * 4, 23 * 4, 20 * 4, (int)Parameters::VolEnvS, &slider));
	pGraphics->AttachControl(new IBitmapControl(this, 145.5 * 4, 22 * 4, &sliderBg));
	pGraphics->AttachControl(new IFaderControl(this, 144.5 * 4, 23 * 4, 20 * 4, (int)Parameters::VolEnvR, &slider));
	//pGraphics->AttachControl(new IBitmapControl(this, 153.5 * 4, 22 * 4, &sliderBg));
	//pGraphics->AttachControl(new IFaderControl(this, 152.5 * 4, 23 * 4, 20 * 4, (int)Parameters::VolEnvV, &slider));
	pGraphics->AttachControl(new IBitmapControl(this, 121.5 * 4, 56.5 * 4, &sliderBg));
	pGraphics->AttachControl(new IFaderControl(this, 120.5 * 4, 57.5 * 4, 20 * 4, (int)Parameters::ModEnvA, &slider));
	pGraphics->AttachControl(new IBitmapControl(this, 129.5 * 4, 56.5 * 4, &sliderBg));
	pGraphics->AttachControl(new IFaderControl(this, 128.5 * 4, 57.5 * 4, 20 * 4, (int)Parameters::ModEnvD, &slider));
	pGraphics->AttachControl(new IBitmapControl(this, 137.5 * 4, 56.5 * 4, &sliderBg));
	pGraphics->AttachControl(new IFaderControl(this, 136.5 * 4, 57.5 * 4, 20 * 4, (int)Parameters::ModEnvS, &slider));
	pGraphics->AttachControl(new IBitmapControl(this, 145.5 * 4, 56.5 * 4, &sliderBg));
	pGraphics->AttachControl(new IFaderControl(this, 144.5 * 4, 57.5 * 4, 20 * 4, (int)Parameters::ModEnvR, &slider));
	//pGraphics->AttachControl(new IBitmapControl(this, 153.5 * 4, 56.5 * 4, &sliderBg));
	//pGraphics->AttachControl(new IFaderControl(this, 152.5 * 4, 57.5 * 4, 20 * 4, (int)Parameters::ModEnvV, &slider));
	pGraphics->AttachControl(new IKnobMultiControl(this, 171 * 4, 13.5 * 4, (int)Parameters::LfoAmount, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 187 * 4, 13.5 * 4, (int)Parameters::LfoFrequency, &knobLeft));
	pGraphics->AttachControl(new IKnobMultiControl(this, 203 * 4, 13.5 * 4, (int)Parameters::LfoDelay, &knobLeft));

	// targets
	pGraphics->AttachControl(new IKnobMultiControl(this, 171 * 4, 50.5 * 4, (int)Parameters::VolEnvFm, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 187 * 4, 50.5 * 4, (int)Parameters::ModEnvFm, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 203 * 4, 50.5 * 4, (int)Parameters::LfoFm, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 171 * 4, 66.5 * 4, (int)Parameters::VolEnvCutoff, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 187 * 4, 66.5 * 4, (int)Parameters::ModEnvCutoff, &knobMiddle));
	pGraphics->AttachControl(new IKnobMultiControl(this, 203 * 4, 66.5 * 4, (int)Parameters::LfoCutoff, &knobMiddle));

	// master
	//pGraphics->AttachControl(new ISwitchControl(this, 6 * 4, 90 * 4, (int)Parameters::VoiceMode, &fmModeSwitch));
	//pGraphics->AttachControl(new IKnobMultiControl(this, 22 * 4, 90 * 4, (int)Parameters::GlideLength, &knobLeft));
	//pGraphics->AttachControl(new IKnobMultiControl(this, 38 * 4, 90 * 4, (int)Parameters::MasterVolume, &knobLeft));

	//pGraphics->AttachControl(new PresetMenu(this, IRECT(0, 0, 100, 25)));

	AttachGraphics(pGraphics);
}

void MikaMicro::InitPresets()
{
	MakeDefaultPreset((char *) "-", 1);
}

MikaMicro::MikaMicro(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR((int)Parameters::NumParameters, 1, instanceInfo)
{
	TRACE;

	InitParameters();
	InitGraphics();
	InitPresets();
}

MikaMicro::~MikaMicro() {}

void MikaMicro::FlushMidi(int s)
{
	while (!midiQueue.Empty())
	{
		auto message = midiQueue.Peek();
		if (message->mOffset > s) break;

		auto status = message->StatusMsg();
		if (status == IMidiMsg::kNoteOn && message->Velocity() == 0) status = IMidiMsg::kNoteOff;

		switch (status)
		{
		case IMidiMsg::kNoteOff:
			for (auto &v : voices)
			{
				if (!v.volEnv.IsReleased() && v.note == message->NoteNumber())
					v.Release();
			}
			break;
		case IMidiMsg::kNoteOn:
			for (auto &v : voices)
			{
				if (v.volEnv.IsReleased())
				{
					v.Start(message->NoteNumber(), osc1SplitFactorA > 1.0);
					break;
				}
			}
			break;
		}

		midiQueue.Remove();
	}
}

void MikaMicro::UpdateParameters()
{
	osc1Wave.Update(dt);
	osc1SplitMix += (targetOsc1SplitMix - osc1SplitMix) * 100.0 * dt;
	osc2Wave.Update(dt);
	osc2SplitMix += (targetOsc2SplitMix - osc2SplitMix) * 100.0 * dt;
	oscMix += (targetOscMix - oscMix) * 100.0 * dt;
	filterMode.Update(dt);
}

double MikaMicro::GetVoice(Voice &voice)
{
	voice.volEnv.Update(dt);
	if (voice.volEnv.stage == EnvelopeStages::Idle) return 0.0;
	voice.modEnv.Update(dt);
	voice.lfoEnv.Update(dt);
	auto delayedLfoValue = lfoValue * voice.lfoEnv.value;

	auto osc1Frequency = osc1Tune * voice.frequency;
	auto osc2Frequency = osc2Tune * voice.frequency;

	auto fmMode = (FmModes)(int)GetParam((int)Parameters::FmMode)->Value();
	switch (fmMode)
	{
	case FmModes::Osc1:
	case FmModes::Osc2:
	{
		auto fmAmount = baseFmAmount;
		fmAmount += GetParam((int)Parameters::VolEnvFm)->Value() * voice.volEnv.value;
		fmAmount += GetParam((int)Parameters::ModEnvFm)->Value() * voice.modEnv.value;
		fmAmount += GetParam((int)Parameters::LfoFm)->Value() * delayedLfoValue;

		auto fmMultiplier = pitchFactor(voice.oscFm.Get(dt, osc1Frequency) * fmAmount);
		switch (fmMode)
		{
		case FmModes::Osc1:
			osc1Frequency *= fmMultiplier;
			break;
		case FmModes::Osc2:
			osc2Frequency *= fmMultiplier;
			break;
		}
		break;
	}
	}

	auto out = 0.0;
	if (oscMix < .999)
	{
		auto osc1Out = 0.0;
		osc1Out += voice.osc1a.Get(dt, osc1Wave, osc1Frequency * osc1SplitFactorA);
		if (osc1SplitMix > .001)
			osc1Out += osc1SplitMix * voice.osc1b.Get(dt, osc1Wave, osc1Frequency * osc1SplitFactorB);
		out += osc1Out * sqrt(1.0 - oscMix);
	}
	if (oscMix > .001)
	{
		auto osc2Out = 0.0;
		osc2Out += voice.osc2a.Get(dt, osc2Wave, osc2Frequency * osc2SplitFactorA);
		if (osc2SplitMix > .001)
			osc2Out += osc2SplitMix * voice.osc2b.Get(dt, osc2Wave, osc2Frequency * osc2SplitFactorB);
		out += osc2Out * sqrt(oscMix);
	}

	auto cutoff = GetParam((int)Parameters::FilterCutoff)->Value();
	cutoff += GetParam((int)Parameters::VolEnvCutoff)->Value() * voice.volEnv.value;
	cutoff += GetParam((int)Parameters::ModEnvCutoff)->Value() * voice.modEnv.value;
	cutoff += GetParam((int)Parameters::LfoCutoff)->Value() * delayedLfoValue;
	auto resonance = GetParam((int)Parameters::FilterResonance)->Value();
	out = voice.filter.Process(dt, out, filterMode, cutoff, resonance);

	out *= voice.volEnv.value;

	return out;
}

void MikaMicro::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
	for (int s = 0; s < nFrames; s++)
	{
		FlushMidi(s);
		UpdateParameters();
		lfoValue = lfo.Get(dt, GetParam((int)Parameters::LfoFrequency)->Value());
		auto out = 0.0;
		for (auto &v : voices) out += GetVoice(v);
		out *= .5;
		outputs[0][s] = out;
		outputs[1][s] = out;
	}
}

void MikaMicro::Reset()
{
	TRACE;
	IMutexLock lock(this);
	dt = 1.0 / GetSampleRate();
}

void MikaMicro::OnParamChange(int paramIdx)
{
	IMutexLock lock(this);

	auto parameter = (Parameters)paramIdx;
	auto value = GetParam(paramIdx)->Value();

	switch (parameter)
	{
	case Parameters::Osc1Wave:
		osc1Wave.Switch(value);
		break;
	case Parameters::Osc1Coarse:
	case Parameters::Osc1Fine:
	{
		auto coarse = GetParam((int)Parameters::Osc1Coarse)->Value();
		auto fine = GetParam((int)Parameters::Osc1Fine)->Value();
		osc1Tune = pitchFactor(coarse + fine);
		break;
	}
	case Parameters::Osc1Split:
		targetOsc1SplitMix = value != 0.0 ? 1.0 : 0.0;
		osc1SplitFactorA = pitchFactor(-value);
		osc1SplitFactorB = pitchFactor(value);
		break;
	case Parameters::Osc2Wave:
		osc2Wave.Switch(value);
		break;
	case Parameters::Osc2Coarse:
	case Parameters::Osc2Fine:
	{
		auto coarse = GetParam((int)Parameters::Osc2Coarse)->Value();
		auto fine = GetParam((int)Parameters::Osc2Fine)->Value();
		osc2Tune = pitchFactor(coarse + fine);
		break;
	}
	case Parameters::Osc2Split:
		targetOsc2SplitMix = value != 0.0 ? 1.0 : 0.0;
		osc2SplitFactorA = pitchFactor(-value);
		osc2SplitFactorB = pitchFactor(value);
		break;
	case Parameters::OscMix:
		targetOscMix = 1.0 - value;
		break;
	case Parameters::FmCoarse:
	case Parameters::FmFine:
	{
		auto fmCoarse = GetParam((int)Parameters::FmCoarse)->Value();
		auto fmFine = GetParam((int)Parameters::FmFine)->Value();
		baseFmAmount = fmCoarse + fmFine;
		break;
	}
	case Parameters::FilterMode:
		filterMode.Switch(value);
		break;
	case Parameters::VolEnvA:
	{
		auto volEnvA = 1000 - 999.9 * (.5 - .5 * cos(pow(value, .1) * pi));
		for (auto &v : voices) v.volEnv.a = volEnvA;
		break;
	}
	case Parameters::VolEnvD:
	{
		auto volEnvD = 1000 - 999.9 * (.5 - .5 * cos(pow(value, .1) * pi));
		for (auto &v : voices) v.volEnv.d = volEnvD;
		break;
	}
	case Parameters::VolEnvS:
		for (auto &v : voices) v.volEnv.s = value;
		break;
	case Parameters::VolEnvR:
	{
		auto volEnvR = 1000 - 999.9 * (.5 - .5 * cos(pow(value, .1) * pi));
		for (auto &v : voices) v.volEnv.r = volEnvR;
		break;
	}
	case Parameters::ModEnvA:
	{
		auto modEnvA = 1000 - 999.9 * (.5 - .5 * cos(pow(value, .1) * pi));
		for (auto &v : voices) v.modEnv.a = modEnvA;
		break;
	}
	case Parameters::ModEnvD:
	{
		auto modEnvD = 1000 - 999.9 * (.5 - .5 * cos(pow(value, .1) * pi));
		for (auto &v : voices) v.modEnv.d = modEnvD;
		break;
	}
	case Parameters::ModEnvS:
		for (auto &v : voices) v.modEnv.s = value;
		break;
	case Parameters::ModEnvR:
	{
		auto modEnvR = 1000 - 999.9 * (.5 - .5 * cos(pow(value, .1) * pi));
		for (auto &v : voices) v.modEnv.r = modEnvR;
		break;
	}
	case Parameters::LfoDelay:
	{
		auto p = GetParam(paramIdx);
		auto lfoDelay = p->GetMin() + p->GetMax() - p->Value();
		for (auto &v : voices) v.lfoEnv.a = lfoDelay;
		break;
	}
	case Parameters::LfoCutoff:
		lfoToCutoff = copysign((value * .000125) * (value * .000125) * 8000.0, value);
		break;
	}
}
