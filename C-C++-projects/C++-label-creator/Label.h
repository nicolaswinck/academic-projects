#ifndef LABEL_H
#define LABEL_H

// Setting detault frame characters.
const char defaultFrame[9] = "+-+|+-+|";

class Label
{
	// Setting the frame string
	// (it doesn't have to be dynamically allocated,
	// since it has always the same size for dimensions).
	char m_frame[9];
	char* m_content;

public:

	Label();
	Label(const char* frameArg);
	Label(const char* frameArg, const char* content);
	~Label();
	std::istream& readLabel();
	std::ostream& printLabel()const;
	Label& text(const char* content);
};

#endif // !LABEL_H