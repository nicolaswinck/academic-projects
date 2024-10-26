#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include "SongCollection.h"

using namespace std;

SongCollection::SongCollection(const std::string fileName)
{
	// Opening file and defining a temporary holder for each line (record).
	ifstream songsFile(fileName);
	string line;

	// Adapted lambda function to trim remaining spaces from tokens (got from previous workshops I've done).
	auto trim = [](string token)
		{
			// Defining the character to be trimmed.
			char space = ' ';
			string result = "";
			// Getting the first and the last non-whitespace characters on string.
			size_t start = token.find_first_not_of(space);
			size_t end = token.find_last_not_of(space);
			// Preventing out of bounds.
			if (end < token.length())
			{
				result = token.substr(start, (end - start) + 1);
			}

			return result;
		};

	if (songsFile.is_open())
	{
		// Going through each record of the file and getting the line.
		while (getline(songsFile, line))
		{
			// Temporary object.
			Song song;
			// Tokenizing aaccording to instructions (fields of 25 then of 5 characters).
			song.m_title = trim(line.substr(0, 25));
			song.m_artist = trim(line.substr(24, 25));
			song.m_album = trim(line.substr(49, 25));
			song.m_releaseYear = trim(line.substr(74, 5));
			song.m_songLength = stoi(trim(line.substr(79, 5)));
			song.m_price = stod(trim(line.substr(84, 5)));
			// Adding to the m_songs vector.
			m_songs.push_back(song);
		}
	}
	else
	{
		throw runtime_error("ERROR: could not open file " + fileName);
	}
}

void SongCollection::display(std::ostream& out) const
{
	// Holder for the total playing time.
	int totalTime = 0;

	// Printing and accumulating playing time.
	for (const auto& song : m_songs)
	{
		totalTime += song.m_songLength;

		out << song << endl;
	}

	// Converting seconds into hours, minutes and seconds.
	int totalTimeHours = totalTime / 3600;
	totalTime %= 3600;
	int totalTimeMins = totalTime / 60;
	int totalTimeSecs = totalTime % 60;

	// Formatting according to the example output (adapted from the main() tester headers).
	out << setw(89) << setfill('-') << '\n' << setfill(' ');
	out << "| " << setw(77) << "Total Listening Time: ";
	// Displaying H:MM:SS.
	out << totalTimeHours << ':' << totalTimeMins << ':' << totalTimeSecs << " |\n";
}

void SongCollection::sort(std::string field)
{
	// Sorting with argument lambda to compare two Song objects.
	if (field == "title")
	{
		std::sort(m_songs.begin(), m_songs.end(), [](Song& song1, Song& song2)
			{
				return song1.m_title < song2.m_title;
			});
	}
	else if (field == "length")
	{
		std::sort(m_songs.begin(), m_songs.end(), [](Song& song1, Song& song2)
			{
				return song1.m_songLength < song2.m_songLength;
			});
	}
}

void SongCollection::cleanAlbum()
{
	// Using lambda as argument, use a Song object to check for None album.
	for_each(m_songs.begin(), m_songs.end(), [](Song& song)
		{
			if (song.m_album == "[None]")
			{
				// "Erase" the string.
				song.m_album = "";
			}
		});
}

bool SongCollection::inCollection(std::string artistName) const
{
	// Count all the matches for the artist name and return if there's any.
	int n = count_if(m_songs.begin(), m_songs.end(), [&](const Song& song)
		{
			return song.m_artist == artistName;
		});

	return n > 0;
}

std::list<Song> SongCollection::getSongsForArtist(std::string artistName) const
{
	// List to hold the results.
	list<Song> result;
	// Add matches to the back of the list (if any).
	std::copy_if(m_songs.begin(), m_songs.end(), back_inserter(result), [&](const Song& song)
		{
			return song.m_artist == artistName;
		});

	return result;
}

std::ostream& operator<<(std::ostream& out, const Song& theSong)
{
	// Calculating seconds into minutes and seconds.
	int lengthSrc = theSong.m_songLength;
	int lengthSec = lengthSrc % 60;
	int lengthMin = lengthSrc / 60;
	string lenStr = "";

	// Adding padded zero to minutes (as per example output).
	if (lengthSec < 10)
	{
		lenStr = to_string(lengthMin) + ':' + '0' + to_string(lengthSec);
	}
	else
	{
		lenStr = to_string(lengthMin) + ':' + to_string(lengthSec);
	}

	out << "| " << left << setw(20) << theSong.m_title;
	out << " | " << setw(15) << theSong.m_artist;
	out << " | " << setw(20) << theSong.m_album;
	out << " | " << right << setw(6) << theSong.m_releaseYear;
	out << " | " << lenStr;
	out << " | " << theSong.m_price << " |";

	return out;
}