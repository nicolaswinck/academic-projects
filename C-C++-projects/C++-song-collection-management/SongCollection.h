#ifndef SONGCOLLECTION_H
#define SONGCOLLECTION_H

#include <iostream>
#include <vector>
#include <list>
#include "SongCollection.h"

struct Song
{
	std::string m_artist;
	std::string m_title;
	std::string m_album;
	double m_price{ 0.0 };
	std::string m_releaseYear;
	int m_songLength{ 0 };
};

class SongCollection
{
	std::vector<Song> m_songs;

public:
	SongCollection(const std::string fileName);
	void display(std::ostream& out) const;
	void sort(std::string field);
	void cleanAlbum();
	bool inCollection(std::string artistName) const;
	std::list<Song> getSongsForArtist(std::string artistName) const;
};

// Free helper function.
std::ostream& operator<<(std::ostream& out, const Song& theSong);

#endif