#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>

#include <Windows.h>

enum class FgColor
{
	Black = 30,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White
};

enum class BgColor
{
	Black = 40,
	Red,
	Green,
	Yellow,
	Blue,
	Magenta,
	Cyan,
	White
};


void setColor(FgColor fg = FgColor::White, BgColor bg = BgColor::Black)
{
	std::cout << "\033[" << (int)fg << ";" << (int)bg << "m";
}

std::string getNextFretNote(std::string note)
{
	static const std::unordered_map<std::string, std::string> nextFret
	{
		{ "A", "A#" },
		{ "A#", "B" }, { "Bb", "B" },
		{ "B", "C" },
		{ "C", "C#" },
		{ "C#", "D" }, { "Db", "D" },
		{ "D", "D#" },
		{ "D#", "E" }, { "Eb", "E" },
		{ "E", "F" },
		{ "F", "F#" },
		{ "F#", "G" }, { "Gb", "G" },
		{ "G", "G#" },
		{ "G#", "A" }, { "Ab", "A" }
	};

	return nextFret.at(note);
}

BgColor getOctaveColor(int octave)
{
	switch (octave)
	{
	case 1:
		return BgColor::Green;
	case 2:
		return BgColor::Yellow;
	case 3:
		return BgColor::Red;
	case 4:
		return BgColor::Magenta;
	case 5:
		return BgColor::Red;
	case 6:
		return BgColor::Yellow;
	default:
		return BgColor::Black;
	}
}

std::string getNote(std::string tuning, int fret)
{
	if (fret == 0)
		return tuning;

	return getNextFretNote(getNote(tuning, fret - 1));
}

int main()
{
	const std::vector<std::pair<std::string, int>> tunings
	{
		{ "E", 1 },
		{ "A", 1 },
		{ "D", 2 },
		{ "G", 2 }
	};

	const int frets = 24;

	for (int fret = 0; fret <= frets; ++fret)
	{
		std::cout << std::setw(2) << fret << "|";
	}

	std::cout << std::endl;

	for (int i = 0; i < tunings.size(); ++i)
	{
		const auto tuningNote = tunings.at(i).first;
		const auto tuningOctave = tunings.at(i).second;

		std::cout << std::string(3 * (frets + 1), '-') << std::endl;

		int octave = tuningOctave;

		for (int fret = 0; fret <= frets; ++fret)
		{
			auto note = getNote(tuningNote, fret);

			if (note == "C")
				++octave;

			// Just to hide semitones.
			if (note.length() > 1 && fret > 0)
				note = "";

			setColor(FgColor::White, getOctaveColor(octave));
			std::cout << std::setw(2) << note;
			setColor();

			std::cout << "|";
		}

		std::cout << std::endl;
	}
}
